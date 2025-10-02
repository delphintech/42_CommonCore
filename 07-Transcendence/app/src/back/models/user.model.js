import { DataTypes, Op } from 'sequelize';
import friendModel from "./friend.model.js"

export default (db) => {
	const User = db.define('User', {
		id: {
			type: DataTypes.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		username: {
			type: DataTypes.STRING,
			allowNull: false,
			unique: true,
		},
		email: {
			type: DataTypes.STRING,
			allowNull: false,
			unique: true,
			validate: {
				isEmail: true
			}
		},
		password: {
			type: DataTypes.STRING,
			allowNull: true
		},
		auth: {
			type: DataTypes.STRING,
			allowNull: false,
			defaultValue: 'local'
		},
		tfa: {
			type: DataTypes.BOOLEAN,
			allowNull: false,
			defaultValue: false
		},
		totp: {
			type: DataTypes.STRING,
			allowNull: true
		}, 
		avatar: {
			type: DataTypes.STRING,
			allowNull: true,
			defaultValue: 'default_avatar'
		},
		online: {
			type: DataTypes.BOOLEAN,
			defaultValue: false,
			allowNull: false
		},
		available: { // si dans tournoi / game = false
			type: DataTypes.BOOLEAN,
			defaultValue: true,
			allowNull: false
		},
		token: {
			type: DataTypes.STRING,
			allowNull: true
		},
	}, {
		tableName: 'users',
		timestamps: true
	});

	const Friend = friendModel(db);

	User.prototype.getFriendship = async function(friendID) {
		const friendship = await Friend.findOne({  where: {
			[Op.or]: [
				{ user_id: this.id, friend_id: friendID },
				{ user_id: friendID, friend_id: this.id }
			]}
		})
		return friendship
	}

	User.prototype.getCurrentFriends = async function() {
		const friends = []
		const friendships = await Friend.findAll({  where: {[Op.and]: [{
			[Op.or]: [
			{ user_id: this.id }, { friend_id: this.id }
			]},
			{ approved: true }
		]}})
		for (const friendship of friendships) {
			let friend
			if (friendship.user_id == this.id) {
				friend = await User.findByPk(friendship.friend_id)
			} else {
				friend = await User.findByPk(friendship.user_id)
			}
			friends.push(friend)
		}
		return friends
	}

	// Only the users that asked
	User.prototype.getPendingFriends = async function() {
		const friends = []
		const friendships = await Friend.findAll({  where: { friend_id: this.id , approved: false }})
		for (const friendship of friendships) {
			let friend
			friend = await User.findByPk(friendship.user_id)
			friends.push(friend)
		}
		return friends
	}

	User.prototype.getFriend = async function(friendID) {
		const friendship = await this.getFriendship(friendID)
		if (!frienship) { return null}
		let friend
		if (friendship.user_id == this.id) {
			friend = await User.findByPk(friendship.friend_id)
		} else {
			friend = await User.findByPk(friendship.user_id)
		}
		return friend
	}
	
	return User;
};