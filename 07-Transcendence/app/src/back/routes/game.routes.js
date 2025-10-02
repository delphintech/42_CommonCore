import {getAllGames} from "../controllers/game.controller.js"
import {getUserAllGames} from "../controllers/game.controller.js"
import {getUserActiveGame} from "../controllers/game.controller.js"
import {getGame} from "../controllers/game.controller.js"
import {getGameData} from "../controllers/game.controller.js"
import {createGame} from "../controllers/game.controller.js"
import {createGameInTournament} from "../controllers/game.controller.js"
import {getGamesTournament} from "../controllers/game.controller.js"
import {getGameTournamentResult} from "../controllers/game.controller.js"
import {updateGameStart} from "../controllers/game.controller.js"
import {updateGamesHold} from "../controllers/game.controller.js"
import {updateGameFinished} from "../controllers/game.controller.js"
import {deleteGame} from "../controllers/game.controller.js"

export default function gameRoutes(app) {

	/* Basic Getters */
	app.get('/api/gamesAll', getAllGames);
	app.get('/api/gamesUser', getUserAllGames);
	app.get('/api/activeGameUser', getUserActiveGame); // get the game and tournament 'on' or 'hold'
	app.get('/api/game/:id', getGame);
	app.get('/api/gameData/:id', getGameData); // all the data from the game and the data from plays and users

	/* Actions on normal games */
	// create a game from 2 players
	app.post('/api/game', createGame);
	// set the game.status to 'on'
	app.put('/api/gameStart/:id', updateGameStart);
	// set the game.status to 'done' + set winner + set time of end
	app.put('/api/gameFinished/:id', updateGameFinished);
	// Delete the games and its plays 
	app.delete('/api/deleteGame/:id', deleteGame);

	/* Actions of tournament's games */
	// Create a new game from the players decided by the tournament matchmaking (id = tournament.id)
	app.post('/api/game_tournament/:id', createGameInTournament);
	// get every game from a tournament and how many are done
	app.get('/api/game_tournament/:id', getGamesTournament);
	// set the tournament to end with winner and all 
	app.get('/api/game_tournament_results/:id', getGameTournamentResult);
	// set the games from a tournament from 'waiting_tournament' to 'hold'
	app.put('/api/setGamesActive', updateGamesHold);

}

