import { DataTypes } from 'sequelize';

export default (db) => {
	const Registration = db.define('Registration', {
		id: {
			type: DataTypes.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		player_id: {
			type: DataTypes.INTEGER,
			allowNull: false,
			references: {
				model: 'users',
				key: 'id'
			}
		},
		tournament_id: {
			type: DataTypes.INTEGER,
			allowNull: false,
			references: {
				model: 'tournaments',
				key: 'id'
			}
		},
		admin: {
			type: DataTypes.BOOLEAN,
			allowNull: false,
			defaultValue: false,
		},
	}, {
		tableName: 'registrations',
		timestamps: true
	});

	return Registration;
};
