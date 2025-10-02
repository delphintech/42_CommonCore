import {getGameGuestData} from "../controllers/game_guest.controller.js"
import {createGameGuest} from "../controllers/game_guest.controller.js"
import {updateSideGameGuest} from "../controllers/game_guest.controller.js"
import {updateGameGuestFinished} from "../controllers/game_guest.controller.js"
import {deleteGameGuest} from "../controllers/game_guest.controller.js"

export default function gameRoutes(app) {

	/* Actions for a game with a guest on local */
	app.get('/api/gameDataGuest/:id', getGameGuestData); // all the data from the game and the data from plays and users

	app.post('/api/game_guest', createGameGuest);

	app.put('/api/change_side_game/:id', updateSideGameGuest); // changer les sides des games entre guest

	app.put('/api/gameGuestFinished/:id', updateGameGuestFinished); 
	
	app.delete('/api/deleteGameGuest/:id', deleteGameGuest); 
}

