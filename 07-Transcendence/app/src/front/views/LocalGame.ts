import AView from "./AView.js";
import { navigateTo, socket } from "../index.js";
import { partialsArray } from "./partials/ui.js";

export default class extends AView {
	constructor() { 
		super();
		this.setTitle("LocalGame");
	}

	async getHTML() {
		
		return `
			<div class="py-0 px-0 bg-wall bg-scroll h-full w-full text-black relative flex flex-col justify-center">

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
				if (!game.game.guest || game.game.guest == '') {
					return partialsArray.alertModal(
						`You don't have a local game playing right now.`, 
						() => {
								navigateTo('/');
						}
					);
				}
				const res_gameData = await fetch(`/api/gameDataGuest/${game.game.id}`);
				if (res_gameData.ok) {
					const gameData = await res_gameData.json();
					playerLeft.textContent = gameData.playerLeft;
					playerRight.textContent = gameData.playerRight;
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
				navigateTo('/');
			}
		);
		socket.off('re_connection_game');
	}

	private removePaddleListeners?: () => void;

	sendPaddleMove = async (my_room: number) => {
		if (this.removePaddleListeners) 
			this.removePaddleListeners();

		const keydownHandler = (e: KeyboardEvent) => {
			if (e.key === 'w')
				socket.emit('paddle_move', my_room, 'left', 'up', true);
			if (e.key === 's')
				socket.emit('paddle_move', my_room, 'left', 'down', true);
			if (e.key === 'ArrowUp')
				socket.emit('paddle_move', my_room, 'right', 'up', true);
			if (e.key === 'ArrowDown')
				socket.emit('paddle_move', my_room, 'right', 'down', true);
		}

		const keyupHandler = (e: KeyboardEvent) => {
			if (e.key === 'w')
				socket.emit('paddle_move', my_room, 'left', 'up', false);
			if (e.key === 's')
				socket.emit('paddle_move', my_room, 'left', 'down', false);
			if (e.key === 'ArrowUp')
				socket.emit('paddle_move', my_room, 'right', 'up', false);
			if (e.key === 'ArrowDown')
				socket.emit('paddle_move', my_room, 'right', 'down', false);
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

	handleWebsocketGame = async (canvas:HTMLCanvasElement, ctx:CanvasRenderingContext2D) => {
		/* WHEN THE CLIENT ARRIVE ON THE PAGE AFTER THE WAITING ROOM */
		socket.on('lauch_guest_game_ok', async (game) => {
			socket.off('lauch_guest_game_ok');
			socket.emit('in_game', game.id, canvas.width, canvas.height);
			
			const res = await fetch('/api/user', {
				method: 'GET',
			});
			if (res.status != 204) {
				await this.sendPaddleMove(game.id);
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
			const res_finish_game = await fetch(`/api/gameGuestFinished/${state.game}`, {
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
			}
		});
	}

	handleWebsocketConnection = async () => {
		// /* WHEN THE CLIENT RECONNECT TO THE APP */
		// socket.on('re_connection_game', async (userId) => {
		// 	const res = await fetch('/api/user');
		// 	if (res.ok) {
		// 		const user = await res.json();
		// 		if (user.user.id == userId) {
		// 			const res_game = await fetch('/api/activeGameUser');
		// 			if (res_game.status === 200) {
		// 				const game = await res_game.json();
		// 				const res_delete = await fetch(`/api/deleteGameGuest/${game.game.id}`, {
		// 					method: 'DELETE'
		// 				});
		// 				if (res_delete.ok) {
		// 					partialsArray.alertModal(
		// 						`You were disconnected from the server.`, 
		// 						() => {
		// 							navigateTo('/');
		// 							socket.off('re_connection_game');
		// 						}
		// 					);
		// 				}
		// 			} else {
		// 				partialsArray.alertModal(
		// 					`You were disconnected from the server.\n`, 
		// 					() => {
		// 						navigateTo('/');
		// 						socket.off('re_connection_game');
		// 					}
		// 				);
		// 			}
		// 		}
		// 	}
		// });
	}

	handleQuitGame = async () => {
		const quit_game = document.getElementById('quit_game');
		if (quit_game) {
			quit_game.onclick = async (event) => {
				event.preventDefault();
				const res_game = await fetch('/api/activeGameUser');
				if (res_game.status === 200) {
					const gameData = await res_game.json();
					if (gameData.game) {
						partialsArray.confirmModal(
							`Do you want to quit the game against '${gameData.game.guest}' ? The game will be deleted.`, 
							async () => {
								await fetch(`/api/deleteGameGuest/${gameData.game.id}`, {
									method: 'DELETE'
								});
								socket.emit("leave_room", `game${gameData.game.id}`);
								socket.off('re_connection_game');
								socket.off('game_state');
								navigateTo('/');
							},
							() => {},
							() => {}
						);
					}
				}
			}
		}
	}

	// attention different en tournoi
	async onMounted() {
		socket.off('game_state');
		
		const canvas = document.getElementById("myCanvas") as HTMLCanvasElement ;
		if (!canvas) 
			return (console.error("ERROR CANVAS"));
		canvas.width = 710;
		canvas.height = 450;
		const ctx = canvas.getContext("2d") as CanvasRenderingContext2D;
		if (!ctx) 
			return (console.error("ERROR CTX"));
		
		await this.handleWebsocketGame(canvas, ctx);
		await this.handleWebsocketConnection();
		await this.fillPage();
		await this.handleQuitGame();
    }
}
