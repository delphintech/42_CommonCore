import authRoutes from './auth.routes.js'
import userRoutes from './user.routes.js';
import gameRoutes from './game.routes.js';
import gameGuestRoutes from './game_guest.routes.js';
import playRoutes from './play.routes.js';
import tournamentRoutes from './tournament.routes.js';
import friendsRoutes from './friends.routes.js';

export default (app) => {
	authRoutes(app);
	userRoutes(app);
	gameRoutes(app);
	gameGuestRoutes(app);
	playRoutes(app);
	tournamentRoutes(app);
	friendsRoutes(app);
}