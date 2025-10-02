import { user, getUser } from "../controllers/user.controller.js"
import { getFullUserProfile, updateUserProfile } from '../controllers/user.controller.js';
import { uploadAvatar, toggleTFA } from '../controllers/user.controller.js';

export default function userRoutes(app) {

	app.get('/api/user', user);
	app.get('/api/user/:id', getUser);
	app.put('/api/user/tfa', toggleTFA);

	app.delete('/api/users/:id', (req, res) =>
		res.send({title: 'Delete user'})
	);

  	app.get('/api/getUser', getFullUserProfile);
	app.put('/api/updateUser', updateUserProfile);
	app.put('/api/user/avatar', uploadAvatar);
}
