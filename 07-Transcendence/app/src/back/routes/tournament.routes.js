

import { getShow } from "../controllers/tournament.controller.js";
import { getCurrentUserData} from "../controllers/tournament.controller.js"
import { getTournamentsAvailable } from "../controllers/tournament.controller.js";
import { registerPlayer } from "../controllers/tournament.controller.js";
import { createTournament } from "../controllers/tournament.controller.js";
import { quitTournament } from "../controllers/tournament.controller.js";
import { deleteTournament } from "../controllers/tournament.controller.js";
import { createPairs } from '../controllers/tournament.controller.js';
import { startTournament } from "../controllers/tournament.controller.js";
import { getNextGameTour } from "../controllers/tournament.controller.js";
import { updateFinishedTournament } from "../controllers/tournament.controller.js";

export default function tournamentRoutes(app) {

  	app.get('/api/userData', getCurrentUserData);
	app.get('/api/tournamentsAvailable', getTournamentsAvailable);
	app.get('/api/show/:id', getShow);
	app.post('/api/createTour', createTournament);
	app.post('/api/registerPlayer/:id', registerPlayer);
  	app.post('/api/startTournament/:id', startTournament);
	app.delete('/api/quitTournament/:id', quitTournament);
	app.delete('/api/deleteTournament/:id', deleteTournament);

	app.get('/api/next_game_tournament/:id', getNextGameTour);

  	app.put('/api/savePairs', createPairs);
  	app.put('/api/finish_tournament/:id', updateFinishedTournament);
}