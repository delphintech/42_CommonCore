import  { DataTypes } from 'sequelize';

export default (db) => {
	const Friend = db.define('Friend', {
		id: {
			type: DataTypes.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		user_id: {
			type: DataTypes.INTEGER,
			allowNull: false,
			references: {
				model: 'users',
				key: 'id'
			}
		},
		friend_id: {
			type: DataTypes.INTEGER,
			allowNull: false,
			references: {
				model: 'users',
				key: 'id'
			}
		},
		approved: {
			type: DataTypes.BOOLEAN,
			allowNull: false,
			defaultValue: false
		},
	}, {
		tableName: 'friends',
		timestamps: true,
		indexes : [
			{
				unique: true,
				fields: ['user_id', 'friend_id']
			}
		]
	});

	return Friend;
};
