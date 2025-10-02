import { DataTypes } from 'sequelize';

export default (db) => {
	const Game = db.define('Game', {
		id: {
			type: DataTypes.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		start_at: {
			type: DataTypes.DATE,
			defaultValue: Date.now(),
			allowNull: false
		},
		end_at: {
			type: DataTypes.DATE,
		},
		status: {
			type: DataTypes.STRING,
			allowNull: false,
			validate: {
				isIn: [['waiting_tournament', 'hold', 'on', 'done']]
			}
		},
		winner_id: {
			type: DataTypes.INTEGER,
			references: {
				model: 'users',
				key: 'id'
			}
		},
		tournament_id: {
			type: DataTypes.INTEGER,
			references: {
				model: 'tournaments',
				key: 'id'
			}
		},
		ia: {
			type: DataTypes.BOOLEAN,
			allowNull: false,
			defaultValue: false,
		},
		guest: {
			type: DataTypes.STRING,
			allowNull: true,
			defaultValue: null,
		}
	}, {
		tableName: 'games',
		timestamps: true
	});

	return Game;
};