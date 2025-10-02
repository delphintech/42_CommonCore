import AView from "./AView.js";
import { navigateTo } from "../index.js"
import { socket } from "../index.js";
import { partialsArray } from "./partials/ui.js";

export default class extends AView {
	constructor() { 
		super();
		this.setTitle("Waiting Room");
	}

	async getHTML() {

		return `
		 <!-- Conteneur général -->
        <div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

            <!-- Image avec le titre -->
            <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
                    <h1>Waiting Room</h1>
                </div>
            </div>
    
            <!-- Bloc des deux images -->
            <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
                <div class="flex flex-col items-center">

                    <!-- Image 1 -->
                    <div class="relative h-full w-full md:w-1/2 flex items-center justify-center">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />
						<div class="absolute top-[16%] z-10 h-1/5 w-full">
							<div class="">
								<p class="inset-x-1/2 text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl">You are waiting for the start of a game</p>
							</div>
                        </div>
						<div class="absolute top-[36%] h-3/5 w-5/6 right-0 overflow-y-scroll">
							<ul id="list_players" class="list-inside space-y-3">
								<li id="player_1" class="flex flex-row justify-between items-center w-11/12 h-2/12 font-on_paper sm:text-xl md:text-xl lg:text-2xl">
									<p id="name_current" class=""></p>
									<div class="">
										<button id="ready_current" type="button" class="rounded"></button>
									</div>
								</li>
								<li id="player_2" class="flex flex-row justify-between items-center w-11/12 h-2/12 font-on_paper sm:text-xl md:text-xl lg:text-2xl">
									<p id="name_other" class=""></p>
									<p id="ready_other"class="rounded"></p>
								</li>
							</ul>
							<div class="">
								<p id="wait" class="inset-x-1/2 text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl"></p>
							</div>
						</div>
						<button id="quit_waiting" type="button" class="absolute right-2 bottom-0 font-on_paper hover:bg-button_red/50 rounded-[10px]">
							Quit the waiting room
						</button>
                    </div>
				</div>
			</div>
		</div>`;
	}

	handleRedirection = async () => {
		const redir_modal = document.getElementById('redir-modal');
		if (redir_modal) {
			redir_modal.parentNode?.removeChild(redir_modal);
		}
		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game) {
				if (!game.game.guest || game.game.guest == '') { // normal mode
					if (game.game.status == 'on') {
						partialsArray.redirectionModal(
							`You have a game playing! Click here to be redirected to the game.`, 
							() => {
								navigateTo('/game');
							}
						)
					}
				} else {
					if (game.game.status == 'on') { // guest mode
						partialsArray.redirectionModal(
							`You have a game playing! Click here to be redirected to the game.`, 
							() => {
								navigateTo('/local_game');
							}
						)
					} else if (game.game.status == 'hold') {
						partialsArray.redirectionModal(
							`You have a game waiting! Click here to be redirected to the waiting room.`, 
							() => {
								navigateTo('/local_guest');
							}
						)
					}
				}
			} else if (game.tournament) {
				if (game.tournament.status == 'hold') {
					partialsArray.redirectionModal(
						`You have a tournament waiting! Click here to be redirected to the tournament room.`, 
						() => {
							navigateTo('/show/' + game.tournament.id);
						}
					)
				} else if (game.tournament.status == 'on') {
					partialsArray.redirectionModal(
						`You have a tournament playing! Click here to be redirected to the tab of the tournament.`, 
						() => {
							navigateTo('/tableau/' + game.tournament.id);
						}
					)
				}
			}
		}
	}

	/* GET ELEMENTS FOR THE PAGE */
	fillPage = async () => {
		const name_current = document.getElementById("name_current") as HTMLElement;
		const ready_current = document.getElementById("ready_current") as HTMLElement;
		const name_other = document.getElementById("name_other") as HTMLElement;
		const ready_other = document.getElementById("ready_other") as HTMLElement;
		
		if (!name_current || !ready_current || !name_other || !ready_other) {
			return console.error("ERROR when getting elements from html in view WaitingRoom.");
		}
		const res = await fetch("/api/plays/active");
		if (res.status == 200) {
			const gameData = await res.json();
			if (!gameData.game.guest || gameData.game.guest == '') {
				name_current.textContent = gameData.currentPlayer.username;
				if (gameData.currentPlay.ready_play) { 
					ready_current.textContent = "You are ready !";
					ready_current.classList.add("bg-button_green/50");
					ready_current.classList.add("hover:bg-button_green");
					ready_current.title = "Set as not ready"
				} else {
					ready_current.textContent = "Are you ready ?";
					ready_current.title = "Set as ready"
					ready_current.classList.add("bg-button_red/50");
					ready_current.classList.add("hover:bg-button_red");
				}
	
				name_other.textContent = gameData.otherPlayer.username;
				if (gameData.otherPlay.accepted) { 
					if (gameData.otherPlay.ready_play) {
						ready_other.textContent = "Ready !";
					} else {
						ready_other.textContent = "Not ready";
					}
				} else {
					ready_other.textContent = "challenge not accepted yet";
				}
			} else {
				partialsArray.alertModal(
					`You don't have a game to wait for right now.`, 
					() => {
						navigateTo('/');
					}
				);
			}
		} else {
			partialsArray.alertModal(
				`You don't have a game to wait for right now.`, 
				() => {
					navigateTo('/');
				}
			);
		}
	}

	handleReadyModal = async () => {
		const ready_current = document.getElementById("ready_current") as HTMLElement;

		const res = await fetch("/api/plays/active");
		if (res.status == 200) {
			const gameData = await res.json();
			const play = gameData.currentPlay;

			partialsArray.confirmModal(
				"Are you ready ?", 
				async () => {
					if (!play.ready_play) {
						await fetch(`/api/play/ready/${play.id}`, {
							method: 'PUT',
							headers: { "Content-Type": "application/json" },
							body: JSON.stringify({
								ready: true
							}),
						});
						ready_current.textContent = "You are ready !";
						ready_current.classList.remove("bg-button_red/50");
						ready_current.classList.remove("hover:bg-button_red");
						ready_current.classList.add("bg-button_green/50");
						ready_current.classList.add("hover:bg-button_green");
						socket.emit("ready_info", {
							to: gameData.otherPlayer,
							ready: true,
						});
					}
				},
				async () => {
					if (play.ready_play) {
						await fetch(`/api/play/ready/${play.id}`, {
							method: 'PUT',
							headers: { "Content-Type": "application/json" },
							body: JSON.stringify({
								ready: false
							}),
						});
						ready_current.textContent = "You are not ready !";
						ready_current.title = "Set as ready"
						ready_current.classList.remove("hover:bg-button_green");
						ready_current.classList.remove("bg-button_green/50");
						ready_current.classList.add("bg-button_red/50");
						ready_current.classList.add("hover:bg-button_red");
						socket.emit("ready_info", {
							to: gameData.otherPlayer,
							ready: false,
						});
					}
				},
				() => {}
			);
		}

	}

	handleQuitModal = async () => {
		const res_user = await fetch("/api/user");
		if (res_user.status != 200) { return; }
		const user = await res_user.json();
		if (!user.user) {return; }

		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.tournament) {
				return ;
			}
		}

		const res = await fetch("/api/plays/active");
		if (res.status == 200) {
			const gameData = await res.json();
			partialsArray.confirmModal(
				`Do you want to quit the challenge against '${gameData.otherPlayer.username}' ? (If you are part of a tournament, the other player will win)`, 
				async () => {
					await fetch(`/api/deleteGame/${gameData.game.id}`, {
						method: 'DELETE',
						headers: { "Content-Type": "application/json" },
						body: JSON.stringify({
							player_1_id: gameData.currentPlayer.id, 
							player_2_id: gameData.otherPlayer.id,
						}),
					});
					socket.emit("quit_challenge", {
						user_quitter: gameData.currentPlayer,
						friend_left: gameData.otherPlayer,
						in_tour: null
					});
					navigateTo('/');
				},
				() => {},
				() => {}
			);
		}
	}

	showCountdown = async (seconds: number) => {
		const wait_launch = document.getElementById("wait");
		const ready_current = document.getElementById("ready_current") as HTMLButtonElement;
		if (ready_current) {
			ready_current.disabled = true;
			ready_current.classList.add("opacity-50", "cursor-not-allowed");
			ready_current.classList.remove("hover:bg-button_green");
		}
		for (let i = seconds; i > 0; i--) {
			if (wait_launch) 
				wait_launch.textContent = `Game starts in ${i}...`;
			await new Promise(res => setTimeout(res, 1000));
		}
		if (wait_launch) {
			wait_launch.textContent = "Game is starting!";
		}
	}

	private opponentDisconnected = false;

	handleWebsocketsWaitingRoom = async () => {
		const ready_other = document.getElementById("ready_other") as HTMLElement;

		/* WEBSOCKET TO GET WHEN THE FRIEND ACCEPTS THE CHALLENGE  */
		socket.on('challenge_result', async ({ friend_challenged, user_challenger, game, accepted }) => {
			const res = await fetch("/api/plays/active");
			if (res.status == 200) {
				const gameData = await res.json();
				if (user_challenger.id != gameData.currentPlayer.id || game != gameData.game.id)
					return console.error("error websocket in challenge_result");
				if (accepted) {
					ready_other.textContent = "Not ready";
				} else {
					const res = await fetch(`/api/deleteGame/${gameData.game.id}`, {
						method: 'DELETE',
						headers: { "Content-Type": "application/json" },
						body: JSON.stringify({
							player_1_id: gameData.currentPlayer.id, 
							player_2_id: gameData.otherPlayer.id,
						}),
					});
					if (res.ok) {
						partialsArray.alertModal(
							`Your challenge was not accepted by  ${friend_challenged.username}`, 
							() => {}
						);
						navigateTo('/');
					}
				}
			}
		});

		/* WEBSOCKET TO GET WHEN THE OTHER QUIT THE CHALLENGE  */
		socket.on('quit_challenge_result', async ({ user_quitter, friend_left, in_tour }) => {
			const res = await fetch("/api/user");
			if (res.status == 200) {
				const user = await res.json();
				if (user.user.id != friend_left.id) {
					return console.error("error websocket in quit_challenge_result");
				}
				partialsArray.alertModal(
					`${user_quitter.username} quit the challenge.`, 
					() => {}
				);
				if (in_tour) {
					navigateTo('/tableau/' + in_tour);
				} else {
					navigateTo('/');
				}
			}
		});

		/* WEBSOCKET TO GET WHEN THE OTHER IS READY OR NOT  */
		socket.on('ready_info_result', async ({ to, ready }) => {
			const res = await fetch("/api/plays/active");
			if (res.status == 200) {
				const gameData = await res.json();
				if (gameData.currentPlayer.id != to.id) {
					return console.error("error websocket in ready_info_result");
				}
				if (ready) {
					ready_other.textContent = "Ready !";
					if (gameData.currentPlay.ready_play) {
						socket.emit('ready_lauch_game', gameData.game, gameData.currentPlayer, gameData.otherPlayer)
					}
				} else {
					ready_other.textContent = "Not ready";
				}
			}
		});
		
		socket.on('ready_lauch_game_ok', async (game, me) => {
			socket.off('ready_lauch_game_ok');
			const res = await fetch("/api/plays/active");
			if (res.status == 200) {
				const gameData = await res.json();
				if (me.id != gameData.currentPlayer.id || game.id != gameData.game.id) {
					return console.error("error websocket in ready_lauch_game_ok");
				}
				if (gameData.currentSide == "right") {
					await fetch(`/api/gameStart/${game.id}`, { method: 'PUT' });
				}
				await this.showCountdown(3);
				socket.emit("join_room", `game${gameData.game.id}`);
				if (this.opponentDisconnected) return;
				if (gameData.currentSide == "right") {
					socket.emit('lauch_game', gameData.game, gameData.currentPlayer, gameData.otherPlayer);
				} else {
					socket.emit('lauch_game', gameData.game, gameData.otherPlayer, gameData.currentPlayer);
				}
				navigateTo('/game');
			}
		});

		socket.on('websocket_disconnection', async (userId, reason) => {
			const res_user = await fetch("/api/user");
			if (res_user.status != 200) { return; }
			const user = await res_user.json();
			if (!user.user) {return; }
			const res = await fetch('/api/plays/active');
			if (res.status === 200) {
				const gameData = await res.json();
				
				if ((gameData.otherPlayer.id.toString() == userId && (!gameData.otherPlay.accepted || gameData.game.status == 'on')) && !gameData.game.tournament_id) {
					const res = await fetch(`/api/deleteGame/${gameData.game.id}`, {
						method: 'DELETE',
						headers: { "Content-Type": "application/json" },
						body: JSON.stringify({
							player_1_id: gameData.currentPlayer.id, 
							player_2_id: gameData.otherPlayer.id,
						}),
					});
					if (res.ok) {
						this.opponentDisconnected = true;
						socket.emit("leave_room", `game${gameData.game.id}`);
						if (!gameData.otherPlay.accepted) {
							partialsArray.alertModal(
								`Your challenge was not accepted by  ${gameData.otherPlayer.username}, because of a server disconnection (${reason}).`, 
								() => {
									navigateTo('/');
								}
							);
						} else if (gameData.game.status == 'on') {
							partialsArray.alertModal(
								`Your opponent was disconnected from the server: ${reason}. (You won the game)`, 
								() => {
									navigateTo('/');
								}
							);
						}
					}
				} else if ((gameData.otherPlayer.id.toString() == userId && (!gameData.otherPlay.accepted || gameData.game.status == 'on')) && gameData.game.tournament_id) {
					if (gameData.otherPlayer.id == user.user.id) {
						let scoreL = 0;
						let scoreR = 0;
						if (gameData.currentSide == 'left') { 
							scoreL = 10; 
						} else { 
							scoreR = 10; 
						}
						await fetch(`/api/gameFinished/${gameData.game.id}`, {
							method: "PUT",
							headers: { "Content-Type": "application/json" },
							body: JSON.stringify({
								scoreR: scoreR,
								scoreL: scoreL,
								end_at: Date.now(),
							}),
						});
						partialsArray.alertModal(
							`Your opponent was disconnected from the server: ${reason}. (You won the game)`, 
							() => {
								navigateTo('/tableau/' + gameData.game.tournament_id);
								socket.emit('update_tour', gameData.game.id_tournament, gameData.game.id);
							}
						);
					}
				}
			}
			socket.off('websocket_disconnection');
		});

		socket.on('handle_participation_logout', async (user) => {
			const res = await fetch('/api/plays/active');
			if (res.status === 200) {
				const gameData = await res.json();
				
				if (gameData.otherPlayer.id.toString() == user.id && !gameData.game.tournament_id) {
					const res = await fetch(`/api/deleteGame/${gameData.game.id}`, {
						method: 'DELETE',
						headers: { "Content-Type": "application/json" },
						body: JSON.stringify({
							player_1_id: gameData.currentPlayer.id, 
							player_2_id: gameData.otherPlayer.id,
						}),
					});
					if (res.ok) {
						partialsArray.alertModal(
							`${user.username} quit the challenge. They logged out.`, 
							() => {
								navigateTo('/');
							}
						);
					}
				} else if (gameData.otherPlayer.id.toString() == user.id && gameData.game.tournament_id) {
					if (gameData.otherPlayer.id == user.id) {
						let scoreL = 0;
						let scoreR = 0;
						if (gameData.currentSide == 'left') { 
							scoreL = 10; 
						} else { 
							scoreR = 10; 
						}
						await fetch(`/api/gameFinished/${gameData.game.id}`, {
							method: "PUT",
							headers: { "Content-Type": "application/json" },
							body: JSON.stringify({
								scoreR: scoreR,
								scoreL: scoreL,
								end_at: Date.now(),
							}),
						});
						partialsArray.alertModal(
							`Your opponent was disconnected from the server. (You won the game)`, 
							() => {
								navigateTo('/tableau/' + gameData.game.tournament_id);
								socket.emit('update_tour', gameData.game.id_tournament, gameData.game.id);
							}
						);
					}
				}
			}
			socket.off('handle_participation_logout');
		});
	}

	checkOpponentConnection = async () => {
		const res = await fetch("/api/plays/active");
		if (res.status == 200) {
			const gameData = await res.json();
			if (gameData.otherPlayer.online == false) {
				let scoreL = 0;
				let scoreR = 0;
				if (gameData.currentSide == 'left') { 
					scoreL = 10; 
				} else { 
					scoreR = 10; 
				}
				await fetch(`/api/gameFinished/${gameData.game.id}`, {
					method: "PUT",
					headers: { "Content-Type": "application/json" },
					body: JSON.stringify({
						scoreR: scoreR,
						scoreL: scoreL,
						end_at: Date.now(),
					}),
				});
				partialsArray.alertModal(
					`Your opponent is not connected. (You won the game)`, 
					() => {
						navigateTo('/tableau/' + gameData.game.tournament_id);
						socket.emit('update_tour', gameData.game.id_tournament, gameData.game.id);
					}
				);
			}
		}
	}

	async onMounted() {
		partialsArray.homeModal();
		socket.off('websocket_disconnection');
		socket.off('handle_participation_logout');

		const ready_current = document.getElementById("ready_current") as HTMLElement;
		const quit_waiting = document.getElementById('quit_waiting') as HTMLElement;
		
		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.tournament) {
				quit_waiting.classList.add('hidden');
			}
		}
		
		await this.fillPage();
		await this.checkOpponentConnection();

		/* CLICK TO BE READY OR NOT READY */
		ready_current.onclick = async (event) => {
			event.preventDefault();
			await this.handleReadyModal();
		}
		
		/* QUIT THE WAITING ROOM AND THE CHALLENGE BEFORE START OF THE GAME */
		quit_waiting.onclick = async (event) => { 
			event.preventDefault();
			await this.handleQuitModal();
		}
		
		/* ALL WEBSOCKETS RECEPTION MANAGEMENT */
		await this.handleWebsocketsWaitingRoom();

		/* IF YOU HAVE A GAME ON */
		await this.handleRedirection()
	};
}