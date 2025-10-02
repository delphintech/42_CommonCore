import { DataTypes } from 'sequelize';

export default (db) => {
	const Play = db.define('Play', {
		id: {
			type: DataTypes.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		game_id: {
			type: DataTypes.INTEGER,
			allowNull: false,
			references: {
				model: 'games',
				key: 'id'
			}
		},
		player_id: {
			type: DataTypes.INTEGER,
			allowNull: false,
			references: {
				model: 'users',
				key: 'id'
			}
		},
		accepted: {
			type: DataTypes.BOOLEAN,
			allowNull: false,
			defaultValue: false,
		},
		ready_play: {
			type: DataTypes.BOOLEAN,
			allowNull: false,
			defaultValue: false,
		},
		score: {
			type: DataTypes.INTEGER,
			allowNull: false,
			defaultValue: 0,
			validate: {
				min: 0,
				max: 10
			}
		},
		win: {
			type: DataTypes.BOOLEAN,
		},
		side: {
			type: DataTypes.STRING,
			allowNull: false,
			validate: {
				isIn: [['right','left']]
			}
		}
	}, {
		tableName: 'plays',
		timestamps: true,
		indexes: [
            {
                unique: true,
                fields: ['game_id', 'player_id'],
                name: 'plays_id'
            }
        ]
	});

	return Play;
};
