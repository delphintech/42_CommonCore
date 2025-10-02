import AView from "./AView.js";
import { navigateTo } from "../index.js"
import { socket } from "../index.js";
import { partialsArray } from "./partials/ui.js";

export default class extends AView {
	constructor() { 
		super();
		this.setTitle("You want to play ?");
	}

	async getHTML() {
		return `
			<div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

                <!-- Image avec le titre -->
                <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
                    <h1>START A GAME</h1>
                </div>
            </div>
    
            <!-- Bloc des deux images -->
            <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
                <div class="flex flex-col items-center">

                    <!-- Image -->
                    <div class="relative h-full w-full md:w-1/2 flex items-center ">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />
                        <div class="absolute top-[10%] z-10 h-5/6 w-full flex flex-col items-center justify-around">
                            <div class="flex flex-col h-1/2 w-full justify-around items-center">
                                <p class="text-center font-on_paper sm:text-3xl md:text-4xl lg:text-5xl">Local Multiplayer</p>
								<div class="flex flex-row w-full h-full justify-around items-center justify-center">
									<button id="startGuest" class="w-1/3 h-2/5 bg-green-500 hover:bg-green-700 text-white text-center font-bold rounded sm:text-xs md:text-sm lg:text-base font-principal" type="click">
										Compete against a guest
									</button>
                                </div>
                            </div>
                            <div class="flex flex-col h-1/2 w-full justify-around items-center">
                                <p class="text-center font-on_paper sm:text-3xl md:text-4xl lg:text-5xl">Remote Multiplayer</p>
                                <div class="flex flex-row w-full h-full justify-around items-center justify-center">
                                    <a data-link href="/friends" class="w-1/3 h-2/5 bg-green-500 hover:bg-green-700 text-white text-center font-bold rounded sm:text-xs md:text-sm lg:text-base font-principal">
                                        Challenge a friend
                                    </a>
                                    <a data-link href="/tournament" class="w-1/3 h-2/5 bg-green-500 hover:bg-green-700 text-white text-center font-bold rounded sm:text-xs md:text-sm lg:text-base font-principal">
                                        Create or Join a Tournament 
                                    </a>
                                </div>
                            </div>
						</div>
                    </div>
                </div>
            </div>
		`;
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

	handleChallengeGuest = async (access:boolean) => {
		const startGuest = document.getElementById("startGuest") as HTMLElement;

		if (startGuest) {
			startGuest.onclick = async (event) => {
				event.preventDefault();
				if (!access) {
					return partialsArray.notificationToast(`You are in a game or waiting room. You can't start a game with a guest`, false);
				}
				partialsArray.inputModal('Local Challenge', "Guest's Alias",
					async (input:string) => {
						const res_game = await fetch('/api/game_guest', { 
							method: "POST",
							headers: { "Content-Type": "application/json" },
							body: JSON.stringify({ 
								guest: input
							})
						});
						if (res_game.status === 201) {
							navigateTo('/local_guest')
						} else if (res_game.status === 400) {
							const result = await res_game.json();
							return partialsArray.alertModal( result.message, () => {} );
						}
					}
				)
			}
		}
	}

	async onMounted() {
		partialsArray.homeModal();

		let access = true;
		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			access = false;
		}
        await this.handleChallengeGuest(access)
        await this.handleRedirection()
	};
}