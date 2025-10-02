import { Op, fn, col, where } from 'sequelize';

export const getAllGames = async (req, res, next) => {
	try {
		const {count, rows } = await req.server.models.Game.findAndCountAll();

		return res.status(200).send({
			nb_games: count,
			games: rows,
		});
	} catch (err) {
		console.error("ERROR while getting all games.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const getUserAllGames = async (req, res, next) => {
	try {
		const user = req.user;
		if (!user) {
			return res.status(404).send({ valid: false, message: "Current user not found." });
		}

		const plays = await req.server.models.Play.findAll({
            where: { player_id: user.id },
            include: [{
                model: req.server.models.Game,
                as: 'Game'
            }]
        });

        const games = plays.map(play => play.Game);

        return res.status(200).send({
            nb_games: games.length,
            games: games,
        });

	} catch (err) {
		console.error("ERROR while getting all user's games.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const getUserActiveGame = async (req, res, next) => {
	try {
		const user = req.user;
		if (!user) {
			return res.status(401).send({ valid: false, message: "Current user not found." });
		}

		const activeGames = await user.getGames({ where: { status: ['hold', 'on'] }})
		const activeTournaments = await user.getTournaments({ where: { status: ['hold', 'on'] }})

		if (activeGames.length == 1 && activeTournaments.length == 1) {
			return res.status(200).send({
				game: activeGames[0].get({ plain: true }),
				tournament: activeTournaments[0].get({ plain: true }),
			});
		} else if (activeGames.length == 1) {
			return res.status(200).send({
				game: activeGames[0].get({ plain: true }),
				tournament: null,
			});
		} else if (activeTournaments.length == 1) {
			return res.status(200).send({
				game: null,
				tournament: activeTournaments[0].get({ plain: true }),
			});
		}
		if (!activeGames.length || !activeTournaments.length) {
			return res.status(204).send({ valid: true, message: "Player available" });
		} else if (activeGames.length > 1) {
			return res.status(401).send({ valid: false, message: "Too many active games" });
		} else if (activeTournaments.length > 1) {
			return res.status(401).send({ valid: false, message: "Too many active tournaments" });
		}
	} catch (err) {
		console.error("ERROR while getting the user's game.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const getGame = async (req, res, next) => {
	try {
		const game_id = req.params.id;

		const actualGame = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!actualGame)
			return res.status(404).send({ valid: false, message: "Game not found." });

		return res.status(200).send({
            game: actualGame,
        });
	} catch (err) {
		console.error("ERROR while getting the game.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const getGameData = async (req, res, next) => {
	try {
		const game_id = req.params.id;

		const actualGame = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!actualGame)
			return res.status(404).send({ valid: false, message: "Game not found." });

		const count = await req.server.models.Play.count({where: { game_id: actualGame.id }});
		if (count != 2)
			return res.status(400).send({ valid: false, message: "Count of plays not equal to 2." });

		const playRight = await req.server.models.Play.findOne({where: { 
			game_id: actualGame.id,
			side: 'right'
		}});

		const playLeft = await req.server.models.Play.findOne({
			where: { 
				game_id: actualGame.id,
				side: 'left'
			}
		});
		if (!playRight || !playLeft)
			return res.status(404).send({ valid: false, message: "Plays not found." });

		const userRight = await req.server.models.User.findOne({ where: { id: playRight.player_id } });
		const userLeft = await req.server.models.User.findOne({ where: { id: playLeft.player_id } });
		if (!userRight || !userLeft)
			return res.status(404).send({ valid: false, message: "Users not found." });

		return res.status(200).send({
			playRight: playRight,
			playLeft: playLeft,
			userRight: userRight,
			userLeft: userLeft,
        });
	} catch (err) {
		console.error("ERROR while getting the game's data.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const createGame = async (req, res, next) => {
	try {
		const { playerR, playerL } = req.body;
		const userR = await req.server.models.User.findOne({ where: { id: playerR } });
		const userL = await req.server.models.User.findOne({ where: { id: playerL } });

		if (!userR || !userL) {
            return res.status(404).send({ valid: false, message: "User(s) not found." });
        }

		userR.set({available: false});
		await userR.save();

		const game = {
			status: 'hold',
			start_at: Date.now(),
		}
		const newGame = await req.server.models.Game.create(game);
		if (!newGame) {
			console.error("Error when creating the game in the database.", err);
			return res.status(500).send({valid: false, message: 'Internal server error'});
		}

		const playRight = {
			game_id: newGame.id,
			player_id: userR.id,
			accepted: true,
			side: "right",
		}
		const newplayRight = await req.server.models.Play.create(playRight);
		if (!newplayRight) {
			console.error("Error when creating play (1) of the game in the registration.", err);
			return res.status(500).send({valid: false, message: 'Internal server error'});
		}
		const playLeft = {
			game_id: newGame.id,
			player_id: userL.id,
			accepted: false,
			side: "left", 
		}
		const newplayLeft = await req.server.models.Play.create(playLeft);
		if (!newplayLeft) {
			console.error("Error when creating play (2) of the game in the registration.", err);
			return res.status(500).send({valid: false, message: 'Internal server error'});
		}

		return res.status(201).send({
			ia: false,
			game_id: newGame.id,
		});

	} catch (err) {
		console.error("ERROR while creating the new game and plays.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const createGameInTournament = async (req, res, next) => {
	try {
		const tour_id = req.params.id;

		const { playerR, playerL } = req.body;
		const userR = await req.server.models.User.findOne({ where: { id: playerR } });
		const userL = await req.server.models.User.findOne({ where: { id: playerL } });
		if (!userR || !userL) {
            return res.status(404).send({ valid: false, message: "User(s) not found (Tournament's Game)." });
        }
		userR.set({available: false});
		userL.set({available: false});
		await userR.save();
		await userL.save();

		const game = {
			status: 'waiting_tournament',
			start_at: Date.now(),
			tournament_id: tour_id
		}
		const newGame = await req.server.models.Game.create(game);
		if (!newGame) {
			console.error("Error when creating the game in the database (Tournament's Game).", err);
			return res.status(500).send({valid: false, message: 'Internal server error'});
		}

		const playRight = {
			game_id: newGame.id,
			player_id: userR.id,
			side: "right",
		}
		const newplayRight = await req.server.models.Play.create(playRight);
		if (!newplayRight) {
			console.error("Error when creating play (1) of the game in the registration (Tournament's Game).", err);
			return res.status(500).send({valid: false, message: 'Internal server error'});
		}
		const playLeft = {
			game_id: newGame.id,
			player_id: userL.id,
			side: "left",
		}
		const newplayLeft = await req.server.models.Play.create(playLeft);
		if (!newplayLeft) {
			console.error("Error when creating play (2) of the game in the registration (Tournament's Game).", err);
			return res.status(500).send({valid: false, message: 'Internal server error'});
		}

		return res.status(201).send({
			game_id: newGame.id,
		});

	} catch (err) {
		console.error("ERROR while creating the new game and plays (Tournament's Game).", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const getGamesTournament = async (req, res, next) => {
	try {
		const tour_id = req.params.id;

		const tournament = await req.server.models.Tournament.findByPk(tour_id)
		if (!tournament)
			return res.status(404).send({ valid: false, message: "Tournament not found." });

		const {count, games} = await req.server.models.Game.findAndCountAll({ where: { tournament_id: tour_id } });
		if (count == 0)
			return res.status(404).send({ valid: false, message: "Games not found." });
		if (count != 6)
			return res.status(400).send({ valid: false, message: "Not good number of games." });

		// Count 'done' games using filter and length
		const doneGamesCount = await req.server.models.Game.count({ where: { 
			tournament_id: tour_id,
			status: 'done'
		} });

		return res.status(200).send({
			tournament: tournament,
            games: games,
            done_games_count: doneGamesCount,
        });
	} catch (err) {
		console.error("ERROR while getting the game.", err);
		return 	res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const getGameTournamentResult = async (req, res, next) => {
	try {
		const game_id = req.params.id;

		const game = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!game)
			return res.status(404).send({ valid: false, message: "Game not found." });

		let status = '';


		if (game.status == 'waiting_tournament') {
			status = "not yet";
		} else if (game.status == 'hold' || game.status == 'on') {
			status = "playing";
		} else if (game.status == 'done') {
			if (game.winner_id) {
				const user = await req.server.models.User.findByPk(game.winner_id)
				if (user) {
					status = 'winner: ' + user.username;
				} else {
					return res.status(404).send({ valid: false, message: "User not found." });
				}
			} else {
				return res.status(400).send({ valid: false, message: "Game cannot be done without a winner." });
			}
		}

		return res.status(200).send({
            status: status,
        });
	} catch (err) {
		console.error("ERROR while getting the game.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const updateGameStart = async (req, res, next) => {
	try {
		const game_id = req.params.id;

		const actualGame = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!actualGame)
			return res.status(404).send({ valid: false, message: "Game not found." });
		
		actualGame.set({start_at: Date.now()});
		actualGame.set({status: 'on'});
		
		await actualGame.save();
		
		return res.status(200).send({valid: true, message: "Game's starting update ok"});
	} catch (err) {
		console.error("ERROR while updating the game when starting", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const updateGamesHold = async (req, res, next) => {
	try {
		const game0_id = req.body.game0;
		const game1_id = req.body.game1;

		const game0 = await req.server.models.Game.findOne({ where: { id: game0_id } });
		if (!game0)
			return res.status(404).send({ valid: false, message: "Game 1 not found." });
		
		if (game0.status == 'waiting_tournament') {
			game0.set({status: 'hold'});
			await game0.save();
		}

		const game1 = await req.server.models.Game.findOne({ where: { id: game1_id } });
		if (!game1)
			return res.status(404).send({ valid: false, message: "Game 2 not found." });
		
		if (game1.status == 'waiting_tournament') {
			game1.set({status: 'hold'});
			await game1.save();
		}
		
		return res.status(200).send({valid: true, message: "Game's holding update ok"});
	} catch (err) {
		console.error("ERROR while updating the game when starting", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const updateGameFinished = async (req, res, next) => {
	try {
		const { scoreR, scoreL, end_at } = req.body;
		const game_id = req.params.id;

		const actualGame = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!actualGame)
			return res.status(404).send({ valid: false, message: "Game not found." });

		const count = await req.server.models.Play.count({where: { game_id: game_id }})
		if (count != 2)
			return res.status(400).send({ valid: false, message: "Count of plays not equal to 2." });

		const playR = await req.server.models.Play.findOne({where: { game_id: game_id, side: "right" }});
		const playL = await req.server.models.Play.findOne({where: { game_id: game_id, side: "left" }});
		if (!playR || !playL)
			return res.status(404).send({ valid: false, message: "Plays not found." });

		const userR = await req.server.models.User.findOne({ where: { id: playR.player_id } });
		const userL = await req.server.models.User.findOne({ where: { id: playL.player_id } });
		if (!userR || !userL)
			return res.status(404).send({ valid: false, message: "Users not found." });
		
		if (!actualGame.tournament_id) {
			userR.set({available: true});
			userL.set({available: true});
		}
		playR.set({score: scoreR});
		playL.set({score: scoreL});
		actualGame.set({end_at: end_at, status: 'done'});
		
		let message = "";
		if (scoreR > scoreL){
			playR.set({win: true});
			playL.set({win: false});
			actualGame.set({winner_id: userR.id});
			message = `The winner is 🎉 ${userR.username} 🎉`;
		}
		else{
			playR.set({win: false});
			playL.set({win: true});
			actualGame.set({winner_id: userL.id});
			message = `The winner is 🎉 ${userL.username} 🎉`;
		}
		
		await userR.save();
		await userL.save();
		await playR.save();
		await playL.save();
		await actualGame.save();
		
		return res.status(200).send({
			game: actualGame,
			message: message,
			room: `game${actualGame.id}`,
		});

	} catch (err) {
		console.error("ERROR while updating the game and plays", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const deleteGame = async (req, res, next) => {
	try {
		const { player_1_id, player_2_id } = req.body;
		const game_id = req.params.id;

		await req.server.models.Play.destroy({
            where: { game_id: game_id }
        });

		await req.server.models.Game.destroy({
            where: { id: game_id }
        });

		const user_1 = await req.server.models.User.findOne({
			where: {
				id: player_1_id
			}
		});
		const user_2 = await req.server.models.User.findOne({
			where: {
				id: player_2_id
			}
		});
		if (!user_1 || !user_2) {
			console.error("ERROR while deleting the game and plays", err);
			return res.status(404).send({valid: false, message: '1 or 2 users not found'});
		}

		user_1.set({available: true});
		user_2.set({available: true});
		await user_1.save();
		await user_2.save();

		return res.status(204).send({valid: true, message: 'Game and Plays deleted + You are now available again'});
	} catch (err) {
		console.error("ERROR while deleting the game and plays", err);
		return 	res.status(500).send({valid: false, message: 'Internal server error'});
	}
}
