import fastify from "fastify"
import fastifySocketIO from 'fastify-socket.io';
import fastifyStatic from "@fastify/static"
import fastifyCookie from "@fastify/cookie"
import { join } from "path"
import { Sequelize } from "sequelize"
import APIRoutes from "./back/routes/routes.js"
import { initModel, createDefault} from "./back/models/models.js"
import middlewares from "./back/middlewares/middlewares.js"
import 'dotenv/config'
import { instrument } from "@socket.io/admin-ui";
import { v2 as cloudinary } from 'cloudinary';
import fastifyMultipart from '@fastify/multipart'
import client from 'prom-client';

const app = fastify({ logger: true, trustProxy: true })

/********** Initialization of websockets (socket.io) **********/

app.register(fastifySocketIO, {
	cors: {
    	origin: [process.env.HOST, "https://admin.socket.io/"], //DEV admin vision of websocket
  	}
});

/********** Database initilization **********/
const db = new Sequelize({
    dialect: 'sqlite',
    storage: '/data/transc.sqlite',
    logging: false
});

// Make Sequelize available throughout every files app using a decorator
app.decorate('db', db);

// Serve the assets folder as static
app.register(fastifyStatic, {
	root: join(process.cwd(), "./assets"),
	prefix: "/assets/",
	wildcard: false
});

// Cloudinary registration for photos
cloudinary.config({
	cloud_name: process.env.CLOUDY_NAME,
	api_key: process.env.CLOUDY_API_KEY,
	api_secret: process.env.CLOUDY_API_SECRET
});

app.register(fastifyMultipart,  {
	attachFieldsToBody: true,
	limits: {
		fieldNameSize: 100, // Max field name size in bytes
		fieldSize: 100,     // Max field value size in bytes
		fields: 10,         // Max number of non-file fields
		fileSize: 1000000,  // For multipart forms, the max file size in bytes
		files: 1            // Max number of file fields
	}
});

// make cloudinary accessible for the whole   app
app.decorate('cloudinary', cloudinary);
app.decorate('imageUpload', middlewares.imageUpload)

// Initialize all models and associations
const models = initModel(db);
// synchronize with database
await db.sync();
// Create IA user
await createDefault(cloudinary, models);

// make models accessible for the app
app.decorate('models', models);

/********** Routes definition **********/
// Call all the api routes
APIRoutes(app);

// Serve the compiled ts files as static
app.register(fastifyStatic, {
	root: join(process.cwd(), "./dist"),
	prefix: "/front/",
	decorateReply: false,
	wildcard: false
});

/********** Middleware registration **********/
app.addHook('preHandler', middlewares.authenticateToken);

// Cookie pluggin
app.register(fastifyCookie, {
	hook: 'onRequest',
	parseOptions: {}
})

// Get all the non-api routes for frontend
app.get('/*', function (request, reply) {
	reply.sendFile('index.html');
})

/* --------- Devops config -------------- */

// adding a custom metric manually for grafana board
const httpRequestCounter = new client.Counter({
	name: 'http_requests_total',
	help: 'Total HTTP requests',
	labelNames: ['method', 'status_code']
});

app.addHook('onResponse', (request, reply, done) => {
	const method = request.raw.method;
	const statusCode = reply.statusCode.toString();
	httpRequestCounter.labels(method, statusCode).inc();
	done();
})
	
const register = client.register;
client.register.registerMetric(httpRequestCounter);

app.get('/metrics', async (request, reply) => {
  try {
    const metrics = await register.metrics();
    reply
      .code(200)
      .header('Content-Type', register.contentType)
      .send(metrics);
  } catch (err) {
    reply.code(500).send(err.message);
  }
});

/********** Run server **********/
app.listen({ port: 3000, host: '0.0.0.0' }, function (err, address) {
	if (err) {
		app.log.error(err)
		process.exit(1)
	}
})

/********** Utilisation of WEBSOCKETS (socket.io) **********/
const userSockets = {}; // a map to link userIds to socketsIds

const games = {}; // the rooms of games
const tours = {}; // the rooms of tours
const ballSize = 15;
const paddleHeight = 75;
const paddleWidth = 14;
const paddleSpeed = 7;

// Socket.IO connection handler
app.ready().then(() => {
	app.io.on('connection', (socket) => {
		console.log("New connection, client_id: ", socket.id);

		/* -------------------- UTILS -------------------- */
			// Join a room
		socket.on('join_room', room => {
			socket.join(room)
		});

			// Leave a room
		socket.on('leave_room', room => {
			socket.leave(room)
		});

		socket.on('delete_games', () => { //DEV
			for (const room in games) {
				if (games[room].interval) {
					clearInterval(games[room].interval);
				}
				delete games[room];
			}
		})

		/* -------------------- LOG -------------------- */
			// When a client refresh while connected, gives the new socket to UserSockets[]
		socket.on('connected_user', (user) => {
			userSockets[user.id] = socket.id; // when a user connects, store their socket
			console.log(`User ${user.id} re-connected to socket ${socket.id}`);
			app.io.to(socket.id).emit('re_connection_game', user.id);
			socket.to('online').emit('online', user);
		});

			// Handle tab closing
			// when a client disconnect: delete the ancient websocket + send the info to people in games or in tournaments
		socket.on('disconnect', async (reason) => {
			const userId = Object.keys(userSockets).find(id => userSockets[id] === socket.id);
			if (userId) {
				delete userSockets[userId];
				console.log(`User ${userId} disconnected and removed from userSockets`);
				const user = await models.User.findByPk(userId);
				await user.update({online: false})
				socket.broadcast.emit('websocket_disconnection', userId, reason);
				socket.to('online').emit('offline', user);
			} else {
				console.log(`User with socket id ${socket.id} disconnected: ${reason}`);
			}
		});

			// When a user log in or register in the app
		socket.on('logged_in', (room, user) => {
			if (!room) {
				socket.broadcast.emit('online', user);
			} else {
				socket.to(room).emit('online', user);
			}
			userSockets[user.id] = socket.id; // when a user connects, store their socket
			console.log(`User ${user.id} connected and added to userSockets`);
		});

			// When a user log out in the app
		socket.on('logged_out', (room, user) => {
			if (!room) {
				socket.broadcast.emit('offline', user);
			} else {
				socket.to(room).emit('offline', user);
				socket.broadcast.emit('handle_participation_logout', user);
			}
			delete userSockets[user.id]; // when a user disconnects, delete their socket
			console.log(`User ${user.id} disconnected and removed from userSockets`);
		});

		/* -------------------- FRIENDS -------------------- */
		// Send friend request
		socket.on('friend_request', (requestData) => {
			const targetSocketId = userSockets[requestData.replier.id];
			if (targetSocketId) {
				app.io.to(targetSocketId).emit('friend_confirm', requestData);
			}
		});

		// Send the response to the friend request
		socket.on('friend_response', (responseData) => {
			const targetSocketId = userSockets[responseData.asker_id];
			if (targetSocketId) {
				app.io.to(targetSocketId).emit('friend_result', responseData);
			}
		});

		// Send unfriend notif
		socket.on('unfriend', (data) => {
			const targetSocketId = userSockets[data.victim_id];
			if (targetSocketId) { 
				app.io.to(targetSocketId).emit('unfriended', data);
			}
		});

		/* -------------------- CHALLENGE -------------------- */
			// when challenging a friend
				// 1. From Friend.ts 'user_challenger' lance un challenge a 'friend_challenge'
				// 2. Le server recoit l'info que UC challenge FC
		socket.on('challenge_friend', ({ friend_challenged, user_challenger, game }) => {
			const targetSocketId = userSockets[friend_challenged.id];
			if (targetSocketId) { 	// 3. Le server envoie l'info a FC que UC le challenge
				app.io.to(targetSocketId).emit('receive_challenge', { friend_challenged, user_challenger, game });
			}
		});
				// 4. in index.ts, FC repond par oui ou non a la demande (popup)
				// 5. Le server recoit la reponse de FC
		socket.on('challenge_response', ({ friend_challenged, user_challenger, game, accepted }) => {
			const challengerSocketId = userSockets[user_challenger.id];
			if (challengerSocketId) { // 6. Le server envoie le resultat a UC
				app.io.to(challengerSocketId).emit('challenge_result', { friend_challenged, user_challenger, game, accepted });
			}
		});
				// 7. (Fin) In waiting room, UC recoit le resultat

			// when quitting a challenge before a game starts
				// 1. In Waiting_room 'user_quitter' ne veut plus etre challenger et veut quitter la waiting room
				// 2. Le server recoit l'info que UQ veut quitter le challenge en commun avec FL
		socket.on('quit_challenge', ({ user_quitter, friend_left, in_tour }) => {
			const leftSocketId = userSockets[friend_left.id];
			if (leftSocketId) { // 3. Le server envoie l'info que UC quitte le challenge contre FL
				app.io.to(leftSocketId).emit('quit_challenge_result', { user_quitter, friend_left, in_tour });
			}
		});
				//4. In Waiting_room, FL recoit la notif et est naviguer to /

			// When ready or not ready in waiting_room for a game
		socket.on('ready_info', ({ to, ready }) => {
			const toSocketId = userSockets[to.id];
			if (to) {
				app.io.to(toSocketId).emit('ready_info_result', { to, ready });
			}
		});

		/* -------------------- GAME -------------------- */

			// when all players are ready
		socket.on('ready_lauch_game', (game, from, to) => {
			const socketId_from = userSockets[from.id];
			const socketId_to = userSockets[to.id];
			if (socketId_from && socketId_to) {
				app.io.to(socketId_from).emit('ready_lauch_game_ok', game , from);
				app.io.to(socketId_to).emit('ready_lauch_game_ok', game, to);
			}
		})

			// after coundown 3 sec
		socket.on('lauch_game', (game, playerR, playerL) => {
			app.io.to(`game${game.id}`).emit('lauch_game_ok', game, playerR, playerL);
		})

		socket.on('disconnected_game', gameId => {
			if (games[gameId]) {
				clearInterval(games[gameId].interval);
				delete games[gameId];
			} else {
				return console.error("ERROR in disconnected_game:", gameId);
			}
		});

		socket.on('quit_game', ({ game, user_quitter, friend_left }) => {
			if (games[game.id]) {
				clearInterval(games[game.id].interval);
				delete games[game.id];
			}
			const leftSocketId = userSockets[friend_left.id];
			if (leftSocketId) { // 3. Le server envoie l'info que UC quitte le game contre FL
				app.io.to(leftSocketId).emit('quit_game_result', { user_quitter, friend_left });
			}
		});

		/* -------------------- LOCALGAME -------------------- */

		socket.on('lauch_guest_game', (game) => {
			app.io.to(`game${game.id}`).emit('lauch_guest_game_ok', game);
		})

		/* -------------------- TOURNAMENT -------------------- */

		// Send invite to tournament
		socket.on('tour_request', (requestData) => {
			const targetSocketId = userSockets[requestData.replier.id];
			if (targetSocketId) {
				app.io.to(targetSocketId).emit('tour_confirm', requestData);
			}
		});

		// Send reply to tournament
		socket.on('tour_reply', (requestData) => {
			const targetSocketId = userSockets[requestData.asker.id];
			if (targetSocketId) {
				app.io.to(targetSocketId).emit('tour_result', requestData);
			}
		});


		socket.on('create_tour', (id_tour, id_admin) => {
			if (!tours[id_tour]) {
				tours[id_tour] = {
					id: id_tour,
					admin_id: id_admin,
					players: new Set([id_admin])
				}
			}
		});

		socket.on('join_tour', (id_tour, id_user) => {
			if (tours[id_tour]) {
				if (tours[id_tour].players.has(id_user)) {
					return;
				}
				tours[id_tour].players.add(id_user);
				const sentId = new Set();
				tours[id_tour].players.forEach(id => {
					const socket_id = userSockets[id];
					if (socket_id && !sentId.has(id)) {
						app.io.to(socket_id).emit('joined_tour', tours[id_tour], id_user);
						sentId.add(id);
					}
				});
			}
		});

		socket.on('leave_tour', (id_tour, id_user) => {
			if (tours[id_tour]) {
				if (tours[id_tour].players.has(id_user)) {
					tours[id_tour].players.delete(id_user);
				} else {
					return;
				}
				const sentId = new Set();
				tours[id_tour].players.forEach(id => {
					const socket_id = userSockets[id];
					if (socket_id && !sentId.has(id)) {
						app.io.to(socket_id).emit('left_tour', tours[id_tour], id_user);
						sentId.add(id);
					}
				});
			}
		});
		
		socket.on('delete_tour', (id_tour) => {
			if (tours[id_tour]) {
				tours[id_tour].players.forEach(id => {
					const socket_id = userSockets[id];
					app.io.to(socket_id).emit('deleted_tour', tours[id_tour]);
				});
				delete tours[id_tour];
			}
		});

		socket.on('start_tour', (id_tour) => {
			if (tours[id_tour]) {
				const senderId = Object.keys(userSockets).find(id => userSockets[id] === socket.id);

				tours[id_tour].players.forEach(id => {
					if (id == senderId) return;
					const socket_id = userSockets[id];
					app.io.to(socket_id).emit('tour_started', tours[id_tour]);
				});
			}
		});

		socket.on('update_tour', (id_tour, game_id) => {
			if (tours[id_tour]) {
				const senderId = Object.keys(userSockets).find(id => userSockets[id] === socket.id);
				
				tours[id_tour].players.forEach(id => {
					if (id == senderId) return;
					const socket_id = userSockets[id];
					app.io.to(socket_id).emit('tour_info', id_tour, game_id);
				});
			}
		})

		socket.on('finish_tour', (id_tour, winner) => {
			if (tours[id_tour]) {
				tours[id_tour].players.forEach(id => {
					const socket_id = userSockets[id];
					app.io.to(socket_id).emit('winner_announcement', id_tour, winner);
				});
			}
		})
		
		/* -------------------- GAMEPLAY -------------------- */

		// lancement de la game
		socket.on('in_game', (room, canvas_width, canvas_height) => {
			if (games[room]?.interval) {
				return;
			}
			startGameLoop(room, canvas_width, canvas_height);
		});

		async function startGameLoop(room, canvas_width, canvas_height) {
			if (games[room]?.interval) {
				return;
			}

			initGameRoom(room, canvas_width, canvas_height);

			// set interval toutes les 10 secondes pour la gestion du jeu par le serveur (mouvement balle + paddle) + envoi des infos aux client pour qu'ils puissent l'afficher sur leur canvas
			games[room].interval = setInterval(() => {

				const g = handleGame(room, canvas_width, canvas_height);

				// game is finished
				if (g.gameState == 'gameover') {
					clearInterval(games[room].interval);
					delete games[room];
					app.io.to(`game${room}`).emit('game_result', {
						game: room,
						scoreR: g.scoreR,
						scoreL: g.scoreL,
					});
					return;
				}

				// send info to the room toutes les 10 sec pour que les clients puissent dessiner le canvas
				app.io.to(`game${room}`).emit('game_state', {
					game: room,
					ball: g.ball,
					paddleR: g.paddleR,
					paddleL: g.paddleL,
					scoreR: g.scoreR,
					scoreL: g.scoreL,
				});
			}, 10);
		}

		// Recept paddle move and update position and resend it back to both players
		socket.on('paddle_move', (room, my_side, direction, on) => {
			if (games[room]) {
				if (my_side === 'left') {
					if (direction === 'up') {
						games[room].keyUpLeft = on;
					} else if (direction === 'down') {
						games[room].keyDownLeft = on;
					}
				}
				if (my_side === 'right') {
					if (direction === 'up') {
						games[room].keyUpRight = on;
					} else if (direction === 'down') {
						games[room].keyDownRight = on;
					}
				}
			}
		});

	});
		// Admin UI
	instrument(app.io, { auth: false });
});


	// creation of the game data structure / room == game.id
function initGameRoom(room, canvas_width, canvas_height) {
	games[room] = {
		ball: {
			x: canvas_width / 2 - 7,
			y: canvas_width / 2 - 7,
			dir_x: Math.random() * 2 > 1 ? 1 : -1,
			dir_y: Math.random() * 2 > 1 ? 1 : -1,
			speed_x: 3,
			speed_y: Math.random() * 4
		},
		paddleR: (canvas_height - paddleHeight) / 2,
		paddleL: (canvas_height - paddleHeight) / 2,
		scoreR: 0,
		scoreL: 0,
		gameState: 'play',
		interval: null,
		keyUpLeft: false,
		keyDownLeft: false,
		keyUpRight: false,
		keyDownRight: false,
	};
}

	// after a point = ball centered + speed and direction randomized / keys reseted
function resetStartPos(room, canvas_width) {
	games[room].ball.x = canvas_width / 2 - 7;
	games[room].ball.y = canvas_width / 2 - 7;
	games[room].ball.dir_x = Math.random() * 2 > 1 ? 1 : -1;
	games[room].ball.dir_y = Math.random() * 2 > 1 ? 1 : -1;
	games[room].ball.speed_x = 2;
	games[room].ball.speed_y = Math.random() * 4;
	games[room].keyUpLeft = false;
	games[room].keyDownLeft = false;
	games[room].keyUpRight = false;
	games[room].keyDownRight = false;
}

	// si la balle tape les extremes de la paddle
function fastBall(room, side) {
	games[room].ball.dir_x = -games[room].ball.dir_x;
	games[room].ball.speed_x = games[room].ball.speed_x + 1 > 6 ? games[room].ball.speed_x : games[room].ball.speed_x + 1;
	games[room].ball.speed_y = games[room].ball.speed_y + 2 > 6 ? games[room].ball.speed_y : games[room].ball.speed_y + 2;
	if ((side == 'top' && games[room].ball.dir_y > 0) || (side == 'bottom' && games[room].ball.dir_y < 0)) {
		games[room].ball.dir_y = -games[room].ball.dir_y;
	}
}

	// si la balle tape le centre de la paddle
function slowBall(room) {
	games[room].ball.dir_x = -games[room].ball.dir_x;
	games[room].ball.speed_x = Math.random() * 4 + 3;
	games[room].ball.speed_y = Math.random() * 2;
}

function normalBall(room) {
	games[room].ball.dir_x = -games[room].ball.dir_x;
	games[room].ball.speed_x = games[room].ball.speed_x + 1 > 5 ? games[room].ball.speed_x : games[room].ball.speed_x + 1;
	games[room].ball.speed_y = games[room].ball.speed_y + 1 < 0 ? games[room].ball.speed_y : games[room].ball.speed_y + 1;
}

function handleGame(room, canvas_width, canvas_height) {
	const g = games[room];

	// ball movement even when its clear a player lost
	g.ball.x += g.ball.speed_x * g.ball.dir_x;
	g.ball.y += g.ball.speed_y * g.ball.dir_y;

	if (g.gameState === 'play') {
		// WALL COLLISION
		if (g.ball.y > canvas_height - ballSize || g.ball.y < 0) {
			g.ball.dir_y = -g.ball.dir_y;
		}

		// RIGHT PADDLE COLLISION
		if (g.ball.x + ballSize > canvas_width - ballSize) {
			g.scoreL += 1;
			if (g.scoreL >= 10)
				g.gameState ='gameover'
			resetStartPos(room, canvas_width);
		} else if (g.ball.x + ballSize > canvas_width - 65) {
			// do nothing
		} else if (g.ball.x + ballSize > canvas_width - 90) {
			if (g.ball.y + paddleWidth > g.paddleR && g.ball.y < g.paddleR + paddleHeight) {
				if (g.ball.y + paddleWidth > g.paddleR && g.ball.y < g.paddleR + 15) {
					fastBall(room, 'top');
				} else if (g.ball.y + paddleWidth > g.paddleR + 60 && g.ball.y < g.paddleR + paddleHeight) {
					fastBall(room, 'bottom');
				} else if (g.ball.y + paddleWidth > g.paddleR + 30 && g.ball.y < g.paddleR + 30) {
					slowBall(room);
				} else {
					normalBall(room);
				}
			}
		}

		// LEFT PADDLE COLLISION
		if (g.ball.x < ballSize) {
			g.scoreR += 1;
			if (g.scoreR >= 10)
				g.gameState ='gameover'
			resetStartPos(room, canvas_width);
		} else if (g.ball.x < 65) {
			// do nothing
		} else if (g.ball.x < 90) {
			if (g.ball.y + paddleWidth > g.paddleL && g.ball.y < g.paddleL + paddleHeight) {
				if (g.ball.y + paddleWidth > g.paddleL && g.ball.y < g.paddleL + 15) {
					fastBall(room, 'top');
				} else if (g.ball.y + paddleWidth > g.paddleL + 60 && g.ball.y < g.paddleL + paddleHeight) {
					fastBall(room, 'bottom');
				} else if (g.ball.y + paddleWidth > g.paddleL + 30 && g.ball.y < g.paddleL + 30) {
					slowBall(room);
				} else {
					normalBall(room);
				}
			}
		}

		// PADDLE MOVEMENT
		if (g.keyUpLeft) {
			g.paddleL = Math.max(g.paddleL - paddleSpeed, 0);
		}
		if (g.keyDownLeft) {
			g.paddleL = Math.min(g.paddleL + paddleSpeed, canvas_height - 75);
		}

		if (g.keyUpRight) {
			g.paddleR = Math.max(g.paddleR - paddleSpeed, 0);
		}
		if (g.keyDownRight) {
			g.paddleR = Math.min(g.paddleR + paddleSpeed, canvas_height - 75);
		}
	}

	return g;
}
