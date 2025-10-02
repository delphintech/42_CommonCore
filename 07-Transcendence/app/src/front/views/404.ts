import AView from "./AView.js"
import { navigateTo } from "../index.js"
import { partialsArray } from "./partials/ui.js";

export default class extends AView {
	constructor() { 
		super();
		this.setTitle("404");
	}

		async getHTML() {
		return `
			<!-- Conteneur général -->
			<div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

				<!-- Image avec le titre -->
				<div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
					<img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
					<div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
						<h1>404</h1>
					</div>
				</div>
		
				<!-- Bloc -->
				<div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
					<div class="flex items-center justify-center gap-6 mb-4">
						<img src="/assets/404.gif" alt="Travolta" class="h-[80%] object-contain block" />
					</div>
					<div class="flex items-center justify-center w-full">
						<button data-link id="Home" class="btn bg-cork hover:bg-wood text-black font-principal text-2xl no-underline inline-block py-4 px-8 border-none rounded-[10px] cursor-pointer transition duration-300">
							Go Home
						</button>
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
					if (game.game.status == 'on') { // go to the game
						partialsArray.redirectionModal(
							`You have a game playing! Click here to be redirected to the game.`, 
							() => {
								navigateTo('/game');
							}
						)
					} else if (game.game.status == 'hold') { // go to the waiting room
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

	async onMounted() {
		partialsArray.homeModal();
		const home = document.getElementById('Home');
		home!.onclick = (event) => {
			event.preventDefault()
			navigateTo('/')
		}
		await this.handleRedirection()
	}
}