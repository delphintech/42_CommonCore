import { getUserPlay } from '../controllers/play.controller.js';
import { getUserActualPlay } from '../controllers/play.controller.js';
import { getGamePlay } from '../controllers/play.controller.js';
import { acceptChallenge } from '../controllers/play.controller.js';
import { readyPlay } from '../controllers/play.controller.js';

import { getUserStats } from '../controllers/play.controller.js';
import { getUserOpponents } from '../controllers/play.controller.js';

export default function playRoutes(app) {
	// get a user play
	// id = play's id
	app.get('/api/plays/:id', getUserPlay)

	// get the actual play (if there is one)
	app.get('/api/plays/active', getUserActualPlay)

	// get the game's plays (must be 2)
	// id = game's id
	app.get('/api/gameplays/:id', getGamePlay)

	app.put('/api/play/accept/:id', acceptChallenge)
	app.put('/api/play/ready/:id', readyPlay)

	app.get('/api/userStats', getUserStats);
	app.get('/api/opponents', getUserOpponents);

}
