import { Op, fn, col, where } from 'sequelize';

export const getGameGuestData = async (req, res, next) => {
	try {
		const game_id = req.params.id;

		const user = req.user;
		if (!user) {
			return res.status(404).send({ valid: false, message: "Current user not found." });
		}

		const actualGame = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!actualGame)
			return res.status(404).send({ valid: false, message: "Game not found." });

		const play = await req.server.models.Play.findOne({where: { 
			game_id: actualGame.id,
			player_id: user.id
		}});
		if (!play)
			return res.status(404).send({ valid: false, message: "Plays not found." });

		let playerRight = '';
		let playerLeft = '';
		if (play.side == 'right') {
			playerRight = user.username;
			playerLeft = actualGame.guest;
		} else {
			playerRight = actualGame.guest;
			playerLeft = user.username;
		}

		return res.status(200).send({
			play: play,
			playerRight: playerRight,
			playerLeft: playerLeft,
        });
	} catch (err) {
		console.error("ERROR while getting the game's data.", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const createGameGuest = async (req, res, next) => {
	try {
		// check if input is correct
		const guest = req.body.guest;
		if (!guest || guest == '') {
			return res.status(400).send({ valid: false, message: "Alias is invalid. Try again." });
		}
		
		const count = await req.server.models.User.count({
			where: where(fn('lower', col('username')), guest.toLowerCase())
		})
		if (count > 0) {
			return res.status(400).send({ valid: false, message: "Alias already used by an existing user. Try again." });
		}

		// really create game
		const user = req.user;
		if (!user) {
			return res.status(404).send({ valid: false, message: "Current user not found." });
		}
		
		user.set({available: false});
		await user.save();

		const game = {
			status: 'hold',
			start_at: Date.now(),
			guest: guest
		}
		const newGame = await req.server.models.Game.create(game);
		if (!newGame) {
			console.error("Error when creating the game in the database.", err);
			return res.status(500).send({valid: false, message: 'Internal server error'});
		}

		const play = {
			game_id: newGame.id,
			player_id: user.id,
			accepted: true,
			ready_play: true,
			side: "right",
		}
		const newplay = await req.server.models.Play.create(play);
		if (!newplay) {
			console.error("Error when creating play (1) of the game in the registration.", err);
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

export const updateSideGameGuest = async (req, res, next) => {
	try {
		const game_id = req.params.id;

		const actualGame = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!actualGame) {
			return res.status(404).send({ valid: false, message: "Game not found." });
		}

		const user = req.user;
		if (!user) {
			return res.status(404).send({ valid: false, message: "Current user not found." });
		}

		const play = await req.server.models.Play.findOne({where: { 
			game_id: actualGame.id,
			player_id: user.id
		}});
		if (!play) {
			return res.status(404).send({ valid: false, message: "Play not found." });
		}

		let current_side = '';
		let guest_side = '';
		if (play.side == 'right') {
			current_side = "left";
			guest_side = "right";
		} else {
			current_side = "right";
			guest_side = "left";
		}
	
		play.set({side: current_side});
		await play.save();
		
		return res.status(200).send({
			current_side: current_side, 
			guest_side: guest_side
		});
	} catch (err) {
		console.error("ERROR while updating the game when starting", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const updateGameGuestFinished = async (req, res, next) => {
	try {
		const { scoreR, scoreL, end_at } = req.body;
		const game_id = req.params.id;

		const actualGame = await req.server.models.Game.findOne({ where: { id: game_id } });
		if (!actualGame)
			return res.status(404).send({ valid: false, message: "Game not found." });

		const user = req.user;
		if (!user) {
			return res.status(404).send({ valid: false, message: "Current user not found." });
		}
		const actualUser = await req.server.models.User.findOne({ where: { id: user.id } });
		if (!actualUser)
			return res.status(404).send({ valid: false, message: "User not found." });

		const play = await req.server.models.Play.findOne({where: { 
			game_id: actualGame.id,
			player_id: user.id
		}});
		if (!play) {
			return res.status(404).send({ valid: false, message: "Play not found." });
		}

		let score = 0;
		if (play.side == 'right') {
			score = scoreR;
		} else {
			score = scoreL;
		}
		
		let message = "";
		if (score == 10) {
			play.set({win: true});
			actualGame.set({winner_id: user.id});
			message = `The winner is 🎉 ${user.username} 🎉`;
		} else {
			play.set({win: false});
			actualGame.set({winner_id: 1});
			message = `The winner is 🎉 ${actualGame.guest} 🎉`;
		}
		
		play.set({score: score});
		actualUser.set({available: true});
		actualGame.set({end_at: end_at, status: 'done'});

		
		await actualUser.save();
		await play.save();
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

export const deleteGameGuest = async (req, res, next) => {
	try {
		const user = req.user;
		if (!user) {
			return res.status(401).send({ valid: false, message: "Current user not found." });
		}
		const game_id = req.params.id;

		await req.server.models.Play.destroy({
            where: { game_id: game_id }
        });

		await req.server.models.Game.destroy({
            where: { id: game_id }
        });

		user.set({available: true});
		await user.save();

		return res.status(204).send({valid: true, message: 'Game and Plays deleted + You are now available again'});
	} catch (err) {
		console.error("ERROR while deleting the game and plays", err);
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}
