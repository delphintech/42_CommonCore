// // import { getAllUsers, getOneUser } from '../controllers/user.controller.js'; // CLEAN
// import { getFriendships } from '../controllers/friends.controller.js'; //CLEAN
import { getUserFriends, getUserFriend, createNewFriendship, deleteFriend  } from "../controllers/friends.controller.js"
import { getFriendRequests, updateFriendship} from "../controllers/friends.controller.js"


export default function friendsRoutes(app) {
	// app.get('/api/friendships', getFriendships); // CLEAN
	app.get('/api/friends', getUserFriends);
	app.get('/api/friend_requests', getFriendRequests)
	app.get('/api/friend/:id', getUserFriend);

	app.post('/api/newfriend', createNewFriendship);
	app.put('/api/friendship', updateFriendship);
	app.delete('/api/friend/:id', deleteFriend); 
}

