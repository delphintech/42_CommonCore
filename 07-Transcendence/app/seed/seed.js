import { Sequelize, Op } from "sequelize";
import 'dotenv/config';
import { initModel, createDefault} from "../src/back/models/models.js";
import { faker } from '@faker-js/faker';
import _ from 'underscore';
import bcrypt from "bcrypt";
import { v2 as cloudinary } from 'cloudinary';

// Cloudinary registration for photos
cloudinary.config({ 
	cloud_name: process.env.CLOUDY_NAME, 
	api_key: process.env.CLOUDY_API_KEY,
	api_secret: process.env.CLOUDY_API_SECRET
});

const db = new Sequelize({
    dialect: "sqlite",
    storage: "/data/transc.sqlite",
    logging: false,
});

// Erase all pictures from cloudinary
await cloudinary.api.delete_resources_by_prefix('avatars');

const models = initModel(db);

// Erase all datas from database
await db.sync({ force: true });
console.log("Data erased from all tables ... ❌\n");

// Creating IA user
await createDefault(cloudinary, models);

// Create 20 users
console.log("Creating 20 users ...")

const pwd = '1234';
const admins = [
	{ username: "manon", password: pwd, email: "manon@42.fr", avatar: "https://images.unsplash.com/photo-1639628735078-ed2f038a193e?q=80&w=400&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D" },
	{ username: "marie", password: pwd, email: "marie@42.fr", avatar: "https://images.unsplash.com/photo-1697482627403-55cd2d974a64?q=80&w=400&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D"},
	{ username: "dede", password: pwd, email: "dede@42.fr", avatar: "https://images.unsplash.com/photo-1655650876145-22fa34d94218?q=80&w=400&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D"},
]

for (const admin of admins) {
	const salt = await bcrypt.genSalt()
	admin.password = await bcrypt.hash('1234', salt)
	const image = await cloudinary.uploader.upload(admin.avatar, { folder: 'avatars' });
	admin.avatar = image.public_id
	models.User.create(admin);
}

for (let i = 0; i < 17; i++) {
	const salt = await bcrypt.genSalt()
	const hashedPwd = await bcrypt.hash('1234', salt)
	const image = await cloudinary.uploader.upload(faker.image.avatarGitHub(), { folder: 'avatars' });
	await models.User.create({
		username: faker.internet.username(),
		email: faker.internet.email(),
		password: hashedPwd,
		avatar: image.public_id
	})
}
console.log(" %d users created ✅", await models.User.count({ where: { username: { [Op.not]: 'BOT' }}}));

// For each users, create between 1 and 3 friends
console.log("Creating between 1 and 3 friend request for each users ...");

const users = await models.User.findAll({ where: { username: { [Op.not]: 'BOT' }}});

for (const user of users) {
	const friends = await models.User.findAll({
		order: db.random(),
		where: {  [Op.and]: [
            { id: { [Op.not]: user.id } },
            { username: { [Op.not]: 'BOT' } }
        ] } ,
		limit: _.random(1, 3)
	});
	for (const friend of friends) {
		if (await user.getFriendship(friend.id)) { continue }
		await models.Friend.create({
			user_id: user.id,
			friend_id: friend.id,
			approved: true
		});
	}
}
console.log(" %d frienship created ✅", await models.Friend.count());

// Create between 1 and 10 games per user with random opponent
console.log("Creating between 1 and 5 games per user ...");
for (const user of users) {
	const times = _.random(1, 5);
	for (let i = 0; i < times; i++) {
		let opponent;
		if (_.random(100) % 3 === 0) {
			opponent = await models.User.findOne({ order: db.random(), where: {id: {[Op.not]: user.id }}});
		} else { opponent = await models.User.findOne({ where: { username: 'BOT'}})}
		let start = faker.date.between({ from: '2024-01-01', to: Date.now() });
		let end = new Date(start.getTime() + _.random(1, 60) * 1000);
		let win = _.sample([user.id, opponent.id]);
		let game = await models.Game.create({
			start_at: start,
			end_at: end,
			status: 'done',
			winner_id: win,
		});
		// creates players play
		await models.Play.create({
			game_id: game.id,
			player_id: user.id,
			score: win === user.id ? 10 : _.random(1, 9),
			win: win === user.id ? true : false,
			side: 'right'
		});
		// creates opponent play
		await models.Play.create({
			game_id: game.id,
			player_id: opponent.id,
			score: win === user.id ? _.random(1, 9) : 10,
			win: win === user.id ? false : true,
			side: 'left'
		});
	}
}
console.log("... %d games created ✅", await models.Game.count());

/* console.log("Creating between 1 and 5 tournaments ...");
for (let i = 0; i < 10; i++) {
	let admin = await models.User.findOne({ where: {id: i + 2}});;
	if (!admin)
		console.log("Error while creating tournament: cannot find admin ❌", await models.Game.count());
	const tour = await models.Tournament.create({
		admin_id: admin.id,
		name: faker.location.city(),
		status: 'hold',
		player_number: 1,
	});
	if (!tour)
		console.log("Error while creating tournament: cannot create tournament ❌", await models.Game.count());
	await models.Registration.create({
		player_id: admin.id,
		tournament_id: tour.id,
		admin: true,
	});
}
console.log(" %d tournaments created ✅", await models.Tournament.count()); */
