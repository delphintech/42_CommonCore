import AView from "./views/AView.js";
import Landing from "./views/Landing.js";
import Error from "./views/404.js";
import Login from "./views/Login.js";
import Register from "./views/Register.js";
import Tableau from "./views/Tableau.js";
import Game from "./views/Game.js";
import LocalGame from "./views/LocalGame.js";
import Dashboard from "./views/Dashboard.js";
import StartGame from "./views/StartGame.js";
import Friends from "./views/Friends.js";
import WaitingRoom from "./views/WaitingRoom.js";
import LocalGuest from "./views/LocalGuest.js";
import Tournament from "./views/Tournament.js";
import Show from "./views/Show.js";
import { partialsArray } from "./views/partials/ui.js"

// Function to navigate to store in browser history api and go to selected route
export const navigateTo = (url: string) => {
	history.pushState({}, "", url);
	router();
}

// Function to list and access each routes
const router = async () => {
	const routes: { path: string; view: typeof AView }[] = [
		{ path: "/", view: Landing },
		{ path: "/404", view: Error },
		{ path: "/login", view: Login },
		{ path: "/register", view: Register },
		{ path: "/tableau/:id", view: Tableau },
		{ path: "/game", view: Game },
		{ path: "/local_game", view: LocalGame },
		{ path: "/dashboard", view: Dashboard },
		{ path: "/start_game", view: StartGame },
		{ path: "/friends", view: Friends },
		{ path: "/waiting_room", view: WaitingRoom },
		{ path: "/local_guest", view: LocalGuest },
		{ path: "/tournament", view: Tournament },
		{ path: "/show/:id", view: Show}
	]

	// Test each route for match
	const potentialMatches = routes.map(route => {
    const routeRegex = new RegExp("^" + route.path.replace(/:\w+/g, "([^/]+)") + "$");
		return {
			route: route,
			result: location.pathname.match(routeRegex)
		};
	});

	// Current path
	let match = potentialMatches.find(potential => potential.result);

	// Setup 404
	if (!match || !match) {
		match = {
			route: routes[1]!,
			result: [location.pathname]
		};
	}

	// To get Id in Url :
	const params: { [key: string]: string } = {};
	const values = match.result?.slice(1);
	const keys = Array.from(match.route.path.matchAll(/:(\w+)/g)).map(result => result[1]);
	keys.forEach((key, i) => {
		if (key !== undefined && values?.[i] !== undefined) {
			params[key] = values[i];
		}
	});

	// load view
	const view = new match.route.view();

	document.querySelector("#app")!.innerHTML = await view.getHTML();
	if (typeof view.onMounted === "function") {
		await view.onMounted();
	}
};

// Load history when arrows clicked
window.addEventListener("popstate", router);

// Listen to the page, prevent refresh and load appropriate route
document.addEventListener("DOMContentLoaded", () => {
	router();
	document.body.addEventListener("click", event => {
		const target = event.target as HTMLAnchorElement;
		if (target.matches("[data-link]")) {
			event.preventDefault();
			navigateTo(target.href);
		}
	})
})

// Client connection to websocket
import { io } from "socket.io-client";
export const socket = io(`https://${window.location.hostname}:4443`);

socket.on("connect", async () => {

	console.log("Connected to server via Socket.IO with", socket.id);
	const res = await fetch("/api/user");
	if (res.status == 200) {
		const user = await res.json();
		socket.emit('connected_user', user.user);
		socket.emit("join_room", 'online');
		partialsArray.notificationToast('You are reconnected to the server.', false);
		partialsArray.notificationToast('You were probably kicked from the game or tournament you were in.', false);
	}

	// When a user log in
	socket.on('online', data => {
		partialsArray.connectionToast(data.username, 'online');
		if (location.pathname == '/friends') { navigateTo('/friends')}
	});

	// When a user log out
	socket.on('offline', async data => {
		partialsArray.connectionToast(data.username, 'offline');
		if (location.pathname == '/friends') { navigateTo('/friends')}
		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.tournament) {
				if (game.tournament.admin_id == data.id) {
					await fetch('/api/deleteTournament/' + game.tournament.id, { method: "DELETE" });
					partialsArray.alertModal(
						`The host of your tournament logged out. The tournament was deleted.`, 
						() => {
							navigateTo('/');
						}
					);
				}
			}
		}
	});

	// Receive a challenge demand
	socket.on('receive_challenge', async ({ friend_challenged, user_challenger, game }) => {
		const handleLogout = async (user: any) => {
			if (user.id === user_challenger.id) {
				partialsArray.alertModal(
					`${user_challenger.username} logged out before you could answer the challenge.`,
					() => {
						const confirm_modal = document.getElementById('confirm-modal');
						if (confirm_modal) {
							confirm_modal.parentNode?.removeChild(confirm_modal);
						}
					}
				);
				const res = await fetch('/api/plays/active');
				if (res.status === 200) {
					const gameData = await res.json();
					if (gameData.otherPlayer.id === user.id) {
						await fetch(`/api/deleteGame/${gameData.game.id}`, {
							method: 'DELETE',
							headers: { "Content-Type": "application/json" },
							body: JSON.stringify({
								player_1_id: gameData.currentPlayer.id,
								player_2_id: gameData.otherPlayer.id,
							}),
						});
					}
				}
			}
			socket.off('handle_participation_logout', handleLogout);
		};

		socket.on('handle_participation_logout', handleLogout);

		partialsArray.confirmModal(
			`User ${user_challenger.username} challenges you! Accept?`, 
			async () => {
				const res = await fetch(`/api/play/accept/${game}`, {
					method: 'PUT',
				});
				if (res.ok) {
					navigateTo("/waiting_room");
					socket.emit('challenge_response', {
						friend_challenged,
						user_challenger,
						game,
						accepted: true
					});
				} else {
					socket.emit('challenge_response', {
						friend_challenged,
						user_challenger,
						game,
						accepted: false
					});
				}
				socket.off('handle_participation_logout', handleLogout);
			},
			() => {
				socket.emit('challenge_response', {
					friend_challenged,
					user_challenger,
					game,
					accepted: false
				});
				socket.off('handle_participation_logout', handleLogout);
			},
			() => {
				socket.emit('challenge_response', {
					friend_challenged,
					user_challenger,
					game,
					accepted: false
				});
				socket.off('handle_participation_logout', handleLogout);
			}
    	);
	});

	socket.on('re_connection_game', async (userId) => {
			const res = await fetch('/api/user');
			if (res.ok) {
				const user = await res.json();
				if (user.user.id == userId) {
					const res_game = await fetch('/api/activeGameUser');
					if (res_game.status === 200) {
						const game = await res_game.json();
						if (game.game) {
							if (!game.game.guest || game.game.guest == '') {
								return
							} else {
								const res_delete = await fetch(`/api/deleteGameGuest/${game.game.id}`, {
									method: 'DELETE'
								});
								if (res_delete.ok) {
									partialsArray.alertModal(
										`You were disconnected from the server.\n`, 
										() => {
											navigateTo('/');
											socket.off('re_connection_game');
										}
									);
								}
							}
						}
					}
				}
			}
		});

	// Tournament invitation
	socket.on('tour_confirm', (requestData) => {
		partialsArray.confirmModal(`${requestData.asker.username} asks you to join a tournament 🏆`,
			async () => {
				const res = await fetch(`/api/registerPlayer/${requestData.tournament.id}`, {
					method: 'POST',
					headers: {
						"Content-Type": "application/json"
					},
					body: JSON.stringify({ userId: requestData.replier.id })
				})
				requestData.joined = true
				if (res.ok) {
					socket.emit('tour_reply', requestData)
					socket.emit('join_tour', requestData.tournament.id, requestData.replier.id);
					navigateTo(`/show/${requestData.tournament.id}`)
				}
			}, 
			() => {
				requestData.joined = false
				socket.emit('tour_reply', requestData)
			}, 
			() => {
				requestData.joined = false
				socket.emit('tour_reply', requestData)
			});
	});

	// Tournament invitation
	socket.on('tour_result', async (requestData) => {
		if (requestData.joined) {
			partialsArray.notificationToast(`${requestData.replier.username} has joined the tournament`, true);
			navigateTo(`/show/${requestData.tournament.id}`)
		} else {
			partialsArray.notificationToast(`${requestData.replier.username} refused to join the tournament`, false);
		}
	});

	// Friend request
	socket.on('friend_confirm', async (requestData) => {
		partialsArray.notificationToast("You have a new friend request", true);
		if (location.pathname == '/friends') { navigateTo('/friends')}
	});
	
	socket.on('friend_result', async (requestData) => {
		if (requestData.approved) {
			partialsArray.notificationToast(`${requestData.replier.username} accepted your friend request !`, true);
			if (location.pathname == '/friends') { navigateTo('/friends')}
		} else {
			partialsArray.notificationToast(`${requestData.replier.username} does not want to be your friend`, false);
		}
	});

	socket.on('unfriended', async (data) => {
		partialsArray.notificationToast(`${data.deleter.username} is no longer your friend!`, true);
		if (location.pathname == '/friends') { navigateTo('/friends')}
	});
});
