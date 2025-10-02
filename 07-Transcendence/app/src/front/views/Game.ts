import AView from "./AView.js";
import { navigateTo, socket } from "../index.js";
import { partialsArray } from "./partials/ui.js";

export default class extends AView {
	constructor() { 
		super();
		this.setTitle("Game");
	}

	async getHTML() {
		
		return `
			<div class="py-0 px-0 bg-wall bg-scroll h-full w-full text-black relative flex flex-col gap-5 justify-center">

				<div class="relative h-fit flex justify-center">
					<img class="" src="/assets/2_players_tournaments.svg" alt="2_players_tournaments">
					<canvas id="myCanvas" class="absolute rounded-[10px] aspect-[23/15] w-game-screen-ratio-w h-game-screen-ratio-h top-1/4 font-score"></canvas>
					<div class="absolute aspect-[24/5] w-div-plate-w h-div-plate-h bottom-0 font-players lg:text-base md:text-sm sm:text-xs">
						<div class="absolute top-3/4 left-[5%] w-player-name-ration-w h-player-name-ration-h flex justify-center">
							<p id="playerLeft" class=""></p>
						</div>
						<div class="absolute top-3/4 left-[73%] w-player-name-ration-w h-player-name-ration-h flex justify-center">
							<p id="playerRight" class=""></p>
						</div>
					</div>
				</div>
				<div class="relative h-fit flex justify-center">
					<a id="quit_game" class="absolute hover:bg-button_red font-principal bg-button_red/50 rounded-[10px]">
						Quit game
					</a>
				</div>
			</div>`;
	}

	fillPage = async () => {
		const playerLeft = document.getElementById("playerLeft") as HTMLElement;
		const playerRight = document.getElementById("playerRight") as HTMLElement;

		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game) {
				const res_gameData = await fetch(`/api/gameData/${game.game.id}`);
				if (res_gameData.ok) {
					const gameData = await res_gameData.json();
					playerLeft.textContent = gameData.userLeft.username;
					playerRight.textContent = gameData.userRight.username;
				}
			} else {
				partialsArray.alertModal(
					`You don't have a game playing right now.`, 
					() => {
						navigateTo('/');
					}
				);
			}
		} else {
			partialsArray.alertModal(
				`You don't have a game playing right now.`, 
				() => {
					navigateTo('/');
				}
			);
		}		
	}

	handleAlertModal = async (winner: any) => {
		partialsArray.alertModal(
			winner.message, 
			() => {
				if (winner.game.tournament_id) {
					navigateTo(`/tableau/${winner.game.tournament_id}`);
					socket.emit('update_tour', winner.game.tournament_id, winner.game.id);
				} else {
					navigateTo('/');
				}
			}
		);
		socket.off('re_connection_game');
	}

	private removePaddleListeners?: () => void;

	sendPaddleMove = async (my_room: number, my_side:string) => {
		if (this.removePaddleListeners) 
			this.removePaddleListeners();

		const keydownHandler = (e: KeyboardEvent) => {
			if (e.key === 'w' || e.key === 'ArrowUp')
				socket.emit('paddle_move', my_room, my_side, 'up', true);
			if (e.key === 's' || e.key === 'ArrowDown')
				socket.emit('paddle_move', my_room, my_side, 'down', true);
		}

		const keyupHandler = (e: KeyboardEvent) => {
			if (e.key === 'w' || e.key === 'ArrowUp')
				socket.emit('paddle_move', my_room, my_side, 'up', false);
			if (e.key === 's' || e.key === 'ArrowDown')
				socket.emit('paddle_move', my_room, my_side, 'down', false);
		}

		document.addEventListener('keydown', keydownHandler);
		document.addEventListener('keyup', keyupHandler);

		this.removePaddleListeners = () => {
			document.removeEventListener('keydown', keydownHandler);
			document.removeEventListener('keyup', keyupHandler);
		};
	}

	drawGame = async (canvas:HTMLCanvasElement, ctx:CanvasRenderingContext2D ,ball:any, paddleR:number, paddleL:number, scoreR:number, scoreL:number) => {
		ctx.clearRect(0, 0, canvas.width, canvas.height);

		// Background
		ctx.beginPath();
		ctx.rect(50, 0, canvas.width - 100, canvas.height);
        ctx.fillStyle = "#151515";
        ctx.fill();
		ctx.closePath();

		// Ball
		ctx.beginPath();
		ctx.rect(ball.x, ball.y, 15, 15);
        ctx.fillStyle = "#FFFFFF";
        ctx.fill();
		ctx.closePath();

		// Right Paddle
		ctx.beginPath();
		ctx.rect(canvas.width - 80 - 14, paddleR as number, 14, 75);
        ctx.fillStyle = "#FFFFFF";
        ctx.fill();
		ctx.closePath();

		// Left Paddle
		ctx.beginPath();
		ctx.rect(80, paddleL as number, 14, 75);
        ctx.fillStyle = "#FFFFFF";
        ctx.fill();
		ctx.closePath();

		// Score
		await this.drawResult(canvas, ctx, scoreR, scoreL)
	}

	drawResult = async (canvas:HTMLCanvasElement, ctx:CanvasRenderingContext2D, scoreR:number, scoreL:number) => {
		ctx.font = '80px "Micro 5", monospace';
        ctx.fillStyle = "#FFFFFF";
        ctx.fillText(scoreL.toString(), canvas.width * 0.3, 70);
        ctx.fillText(scoreR.toString(), canvas.width * 0.7, 70);
	}

	deletedWebsocketTourHandler = async (tour_data: any) => {
		partialsArray.alertModal(
			`The tournament ${tour_data.id} was deleted`, 
			() => {
				return navigateTo('/');
			}
		);
	}

	handleWebsocketGame = async (canvas:HTMLCanvasElement, ctx:CanvasRenderingContext2D) => {
		socket.off("deleted_tour", this.deletedWebsocketTourHandler);
        socket.on("deleted_tour", this.deletedWebsocketTourHandler);
		
		/* WHEN THE CLIENT ARRIVE ON THE PAGE AFTER THE WAITING ROOM */
		socket.on('lauch_game_ok', async (game, playerR, playerL) => {
			socket.off('lauch_game_ok');
			socket.emit('in_game', game.id, canvas.width, canvas.height);
			
			const res = await fetch('/api/user', {
				method: 'GET',
			});
			if (res.status != 204) {
				const user = await res.json();
				if (user.user.id === playerL.id) {
					await this.sendPaddleMove(game.id, "left");
				}
				else if (user.user.id === playerR.id) { 
					await this.sendPaddleMove(game.id, "right");
				}
			}
		});

		/* EVERY UPDATE FROM APP TO DRAW THE INFO */
		socket.on('game_state', async (state) => {
			await this.drawGame(canvas, ctx, state.ball, state.paddleR, state.paddleL, state.scoreR, state.scoreL );
		});

		/* WHEN THE GAME IS FINISHED */
		socket.on('game_result', async (state) => {
			ctx.clearRect(0, 0, canvas.width, canvas.height);
			await this.drawResult(canvas, ctx, state.scoreR, state.scoreL)
			socket.emit("leave_room", `game${state.game}`);
			if (this.removePaddleListeners) 
				this.removePaddleListeners();
			const res_finish_game = await fetch(`/api/gameFinished/${state.game}`, {
				method: "PUT",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify({
					scoreR: state.scoreR,
					scoreL: state.scoreL,
					end_at: Date.now(),
				}),
			});
			if (res_finish_game.ok) {
				const winner = await res_finish_game.json();
				await this.handleAlertModal(winner)
				socket.off('game_state');
				socket.off('game_result');
			}
		});
	}

	handleWebsocketConnection = async () => {
		/* WHEN THERE IS A DECONNECTION */
		// check if the user diconnected is the player the client plays against
		socket.on('websocket_disconnection', async (userId, reason) => {
			const res = await fetch('/api/plays/active');
			if (res.status === 200) {
				const gameData = await res.json();
				
				if (gameData.otherPlayer.id.toString() == userId) {
					let scoreL = 0;
					let scoreR = 0;
					if (gameData.currentSide == 'left') { scoreL = 10; } 
					else { scoreR = 10; }
					await fetch(`/api/gameFinished/${gameData.game.id}`, {
						method: "PUT",
						headers: { "Content-Type": "application/json" },
						body: JSON.stringify({
							scoreR: scoreR,
							scoreL: scoreL,
							end_at: Date.now(),
						}),
					});
					socket.emit('disconnected_game', gameData.game.id);
					partialsArray.alertModal(
						`Your opponent was disconnected from the server: ${reason}.
						(You won the game)`, 
						() => {
							if (gameData.game.id_tournament) {
								navigateTo(`/tableau/${gameData.game.id_tournament}`);
								socket.emit('update_tour', gameData.game.id_tournament, gameData.game.id);
							} else {
								navigateTo('/');
								socket.off('game_state');
								socket.off('game_result');
							}
						}
					);
				}
			}
			socket.off('websocket_disconnection');
		});

		/* WHEN A PLAYER LOGOUT */
		// check if the player logged out is the player you play against
		socket.on('handle_participation_logout', async (user) => {
			const res = await fetch('/api/plays/active');
			if (res.status === 200) {
				const gameData = await res.json();
				
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
					socket.emit('disconnected_game', gameData.game.id);
					partialsArray.alertModal(
						`Your opponent logged out during the game.
						(You won the game)`, 
						() => {
							if (gameData.game.id_tournament) {
								navigateTo(`/tableau/${gameData.game.id_tournament}`);
								socket.emit('update_tour', gameData.game.id_tournament, gameData.game.id);
							} else {
								navigateTo('/');
							}
						}
					);
					socket.off('game_state');
					socket.off('game_result');
				}
			}
			socket.off('handle_participation_logout');
		});

		/* WHEN THE OTHER PLAYER QUIT THE GAME */
		socket.on('quit_game_result', async ({ user_quitter, friend_left }) => {
			const res = await fetch("/api/user");
			if (res.status == 200) {
				const user = await res.json();
				if (user.user.id == friend_left.id) {
					partialsArray.alertModal(
						`${user_quitter.username} quit the game. (You won the game)`, 
						() => {}
					);
					socket.off('game_state');
					socket.off('game_result');
					navigateTo('/');
				}
			}
		});
	}

	handleQuitGame = async () => {
		const quit_game = document.getElementById('quit_game');
		if (quit_game) {
			quit_game.onclick = async (event) => {
				event.preventDefault();
				const res = await fetch("/api/plays/active");
				if (res.status == 200) {
					const gameData = await res.json();
					partialsArray.confirmModal(
						`Do you want to quit the game against '${gameData.otherPlayer.username}' ?`, 
						async () => {
							let scoreL = 0;
							let scoreR = 0;
							if (gameData.currentSide == 'left') { 
								scoreR = 10; 
							} else { 
								scoreL = 10; 
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
							socket.emit("quit_game", {
								game: gameData.game,
								user_quitter: gameData.currentPlayer,
								friend_left: gameData.otherPlayer,
							});
							navigateTo('/');
						},
						() => {},
						() => {}
					);
				}
			}
		}
	}

	// attention different en tournoi
	async onMounted() {
		socket.off('handle_participation_logout');
		socket.off('websocket_disconnection');
		socket.off('game_state');
		socket.off('lauch_game_ok');
		socket.off('game_result');
		
		const canvas = document.getElementById("myCanvas") as HTMLCanvasElement ;
		if (!canvas) 
			return (console.error("ERROR CANVAS"));
		canvas.width = 710;
		canvas.height = 450;
		const ctx = canvas.getContext("2d") as CanvasRenderingContext2D;
		if (!ctx) 
			return (console.error("ERROR CTX"));
		
		await this.handleWebsocketGame(canvas, ctx)
		await this.handleWebsocketConnection()
		await this.fillPage();
		await this.handleQuitGame();
    }
}
