import bcrypt from "bcrypt"
import userModel from "./user.model.js"
import friendModel from "./friend.model.js"
import gameModel from "./game.model.js"
import playModel from "./play.model.js"
import tournamentModel from "./tournament.model.js"
import registrationModel from "./registration.model.js"

export const initModel = (db) => {
	const User = userModel(db);
	const Friend = friendModel(db);
	const Game = gameModel(db);
	const Play = playModel(db);
	const Tournament = tournamentModel(db);
	const Registration = registrationModel(db);

	// User associations
	User.hasMany(Friend, { foreignKey: 'user_id' });
	User.hasMany(Friend, { foreignKey: 'friend_id', as: 'friendOf' });
	User.belongsToMany(User, { as: 'UserFriends', through: Friend, foreignKey: 'user_id', otherKey: 'friend_id' });
	User.hasMany(Play, { foreignKey: 'player_id' });
	User.hasMany(Game, { foreignKey: 'winner_id', as: 'wonGames' });
	User.hasMany(Tournament, { foreignKey: 'winner_id', as: 'wonTournament' });
	User.belongsToMany(Game, { through: Play, foreignKey: 'player_id',otherKey: 'game_id' });
	User.hasMany(Registration, { foreignKey: 'player_id' });
	User.hasMany(Tournament, { foreignKey: 'admin_id', as: 'tournamentAdmin' });
	User.belongsToMany(Tournament, { through: Registration, foreignKey: 'player_id', otherKey: 'tournament_id' });

	// Friend associations
	Friend.belongsTo(User, { foreignKey: 'user_id', as: 'user' });
	Friend.belongsTo(User, { foreignKey: 'friend_id', as: 'friend' });

	// Game associations
	Game.hasMany(Play, { foreignKey: 'game_id' } );
	Game.belongsToMany(User, { through: Play, foreignKey: 'game_id', otherKey: 'player_id', as: 'players'} );
	Game.belongsTo(User, { foreignKey: 'winner_id', as: 'winner' });
	Game.belongsTo(Tournament, { foreignKey: 'tournament_id' });

	// Play associations
	Play.belongsTo(Game, { foreignKey: 'game_id' });
	Play.belongsTo(User, { foreignKey: 'player_id', as: 'opp' });

	// Tournament associations
	Tournament.hasMany(Game, { foreignKey: 'tournament_id' });
	Tournament.belongsTo(User, { foreignKey: 'admin_id', as: 'admin' });
	Tournament.belongsToMany(User, {through: Registration, foreignKey: 'tournament_id', otherKey: 'player_id' });
	Tournament.belongsTo(User, { foreignKey: 'winner_id', as: 'winner' });

	// Registration associations
	Registration.belongsTo(User);
	Registration.belongsTo(Tournament, { foreignKey: 'tournament_id' });

	return {
		User,
		Friend,
		Game,
		Play,
		Tournament,
		Registration
	}
}

export const createDefault = async (cloudinary, models) => {
	// Uplaoding, bot and default avatar
	try { await cloudinary.api.resource('default_avatar') }
	catch {
		await cloudinary.uploader.upload('./assets/default_avatar.png', {
			public_id: 'default_avatar',
			folder: 'avatars' })
	}
	try { await cloudinary.api.resource('bot_avatar') }
	catch {
		await cloudinary.uploader.upload('./assets/bot_avatar.png', {
			public_id: 'bot_avatar',
			folder: 'avatars' })
	}

	// Create IA user
	const salt = await bcrypt.genSalt()
	const pwd = await bcrypt.hash('1234', salt)
	await models.User.findOrCreate({
		where: { username: 'BOT'},
		defaults: {
			email: 'bot@ia.com',
			password: pwd,
			online: true,
			avatar: 'bot_avatar'
		}
	})
}
