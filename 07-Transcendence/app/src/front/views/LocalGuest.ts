import AView from "./AView.js";
import { navigateTo } from "../index.js"
import { socket } from "../index.js";
import { partialsArray } from "./partials/ui.js";

export default class extends AView {
	constructor() { 
		super();
		this.setTitle("Local Guest");
	}

	async getHTML() {

		return `
		 <!-- Conteneur général -->
        <div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

            <!-- Image avec le titre -->
            <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
                    <h1>Challenge a guest</h1>
                </div>
            </div>
    
            <!-- Bloc des deux images -->
            <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
                <div class="flex flex-col items-center">

                    <!-- Image 1 -->
                    <div class="relative h-full w-full md:w-1/2 flex flex-col items-center justify-center">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />
						<div class="absolute top-[26%] h-3/5 w-5/6 right-0 overflow-y-scroll">
							<div class="flex flex-col gap-6">
								<div class="flex flex-row justify-between items-center w-11/12 h-2/12 font-on_paper sm:text-xl md:text-xl lg:text-2xl">
									<p id="name_current" class=""></p>
									<p id="side_current" class="">right</p>
								</div>
								<div class="flex flex-row justify-between items-center w-11/12 h-2/12 font-on_paper sm:text-xl md:text-xl lg:text-2xl">
									<p id="name_guest" class=""></p>
									<p id="side_guest" class="">left</p>
								</div>
								<div class="flex flex-row justify-between items-center w-11/12 h-2/12 font-on_paper sm:text-xl md:text-xl lg:text-2xl">
									<p id="start_game" class="bg-button_green/50 hover:bg-button_green rounded p-2">Start the game</p>
									<p id="change_side" class="bg-button_green/50 hover:bg-button_green rounded p-2">Change sides</p>
								</div>
							</div>
							<div class="">
								<p id="wait" class="inset-x-1/2 text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl"></p>
							</div>
						</div>
						<button id="quit_waiting" type="button" class="absolute right-2 bottom-0 font-on_paper hover:bg-button_red/50 rounded-[10px]">
							Quit the room
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
					} else if (game.game.status == 'hold') {
						partialsArray.redirectionModal(
							`You have a game waiting! Click here to be redirected to the waiting room.`, 
							() => {
								navigateTo('/waiting_room');
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
					}
				}
			}
		}
	}

	/* GET ELEMENTS FOR THE PAGE */
	fillPage = async () => {
		const name_current = document.getElementById("name_current") as HTMLElement;
		const name_guest = document.getElementById("name_guest") as HTMLElement;
		if (!name_current || !name_guest) {
			return console.error("ERROR when getting elements from html in view LocalGuest.");
		}

		const res = await fetch('/api/user');
		if (res.status === 200) {
			const user = await res.json();
			name_current.textContent = user.user.username;
		}

		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game) {
				if (game.game.guest) {
					name_guest.textContent = game.game.guest;
				} else {
					partialsArray.alertModal(
						`You don't have a game with a guest to wait for right now.`, 
						() => {
							navigateTo('/');
						}
					);
				}
			} else {
				partialsArray.alertModal(
					`You don't have a game with a guest to wait for right now.`, 
					() => {
						navigateTo('/');
					}
				);
			}
		}
	}

	handleQuitModal = async () => {
		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game) {
				partialsArray.confirmModal(
					`Do you want to quit the room ?`, 
					async () => {
						await fetch(`/api/deleteGameGuest/${game.game.id}`, {
							method: 'DELETE'
						});
						navigateTo('/');
					},
					() => {},
					() => {}
				);
			}
		}
	}

	showCountdown = async (seconds: number) => {
		const wait_launch = document.getElementById("wait");
		
		for (let i = seconds; i > 0; i--) {
			if (wait_launch) 
				wait_launch.textContent = `Game starts in ${i}...`;
			await new Promise(res => setTimeout(res, 1000));
		}
		if (wait_launch) {
			wait_launch.textContent = "Game is starting!";
		}
	}

	handleChangeSides = async () => {
		const side_current = document.getElementById("side_current") as HTMLElement;
		const side_guest = document.getElementById("side_guest") as HTMLElement;
		if (!side_current || !side_guest) {
			return console.error("ERROR when getting elements from html in view LocalGuest.");
		}
		
		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game) {
				const res_change_side = await fetch(`/api/change_side_game/${game.game.id}`, {method: 'PUT'});
				if (res_change_side.ok) {
					const new_sides = await res_change_side.json();
					if (new_sides) {
						side_current.textContent = new_sides.current_side;
						side_guest.textContent = new_sides.guest_side;
					}
				}
			}
		}
	}

	handleStartGame = async () => {
		const quitBtn = document.getElementById('quit_waiting') as HTMLButtonElement;
		if (quitBtn) {
			quitBtn.disabled = true;
			quitBtn.classList.add("opacity-50", "cursor-not-allowed");
		}
		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game) {
				await fetch(`/api/gameStart/${game.game.id}`, { method: 'PUT' });
				await this.showCountdown(3);
				socket.emit('join_room', `game${game.game.id}`);
				socket.emit('lauch_guest_game', game.game);
				navigateTo('/local_game');
			}
		}
	}

	async onMounted() {
		partialsArray.homeModal();
		await this.fillPage();
		
		/* IF YOU HAVE A GAME ON */
		await this.handleRedirection();

		/* QUIT THE WAITING Guest AND THE CHALLENGE BEFORE START OF THE GAME */
		const quit_localGuest = document.getElementById('quit_waiting') as HTMLElement;
		if (!quit_localGuest) { return console.error("ERROR when getting elements from html in view LocalGuest."); }
		quit_localGuest.onclick = async (event) => { 
			event.preventDefault();
			await this.handleQuitModal();
		}

		/* BUTTON TO CHANGE SIDES ON THE KEYBOARD */
		const changeSide = document.getElementById('change_side') as HTMLElement;
		if (!changeSide) { return console.error("ERROR when getting elements from html in view LocalGuest."); }
		changeSide.onclick = async (event) => { 
			event.preventDefault();
			await this.handleChangeSides();
		}

		const startGame = document.getElementById('start_game') as HTMLElement;
		if (!startGame) { return console.error("ERROR when getting elements from html in view LocalGuest."); }
		startGame.onclick = async (event) => { 
			event.preventDefault();
			await this.handleStartGame();
		}
	};
}
