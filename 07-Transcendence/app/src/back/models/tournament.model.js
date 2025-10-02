import { DataTypes } from 'sequelize';

export default (db) => {
	const Tournament = db.define('Tournament', {
		id: {
			type: DataTypes.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		admin_id: {
			type: DataTypes.INTEGER,
			allowNull: false,
			references: {
				model: 'users',
				key: 'id'
			}
		},
		name: {
			type: DataTypes.STRING,
			allowNull: false,
			unique: true
		},
		status: {
			type: DataTypes.STRING,
			allowNull: false,
			validate: {
				isIn: [['hold', 'on', 'done']]
			}
		},
		player_number: {
			type: DataTypes.NUMBER,
			validates: {
				min: 1,
				max: 8
			}
		},
		winner_id: {
			type: DataTypes.INTEGER,
			references: {
				model: 'users',
				key: 'id'
			}
		},
		combinations: {
			type: DataTypes.STRING,
			allowNull: true
		}
	}, {
		tableName: 'tournaments',
		timestamps: true
	});

	return Tournament;
}; 
