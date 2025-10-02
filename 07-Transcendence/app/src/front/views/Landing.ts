import AView from "./AView.js";
import { navigateTo } from "../index.js"
import { socket } from "../index.js";
import { partialsArray } from "./partials/ui.js";

export default class extends AView {
	constructor() {
		super();
		this.setTitle("Landing");
	}

	async getHTML() {
		const res = await fetch('/api/user', {
			method: 'GET',
		});
		let element = "";
		if (res.status == 204) { // Anonymous landing
			element = `<div id="not-login" class="absolute w-full h-full font-on_paper lg:text-5xl md:text-4xl sm:text-3xl text-black">
							<a data-link href="/login" class="absolute btn hover:bg-arcade-clair rounded-[10px] left-[20%] top-[20%]">
								Login
							</a>
							<a data-link href="/register" class="absolute btn hover:bg-arcade-clair rounded-[10px] left-[20%] top-[40%]">
								Register
							</a>
						</div>`;
		} else {
			element = `<div id="user-loged-in" class="absolute w-full h-full font-on_paper lg:text-5xl md:text-4xl sm:text-3xl text-black">
							<a data-link href="/start_game" class="absolute btn hover:bg-arcade-clair rounded-[10px] left-[20%] top-[20%]">
								Start game
							</a>
							<a data-link href="/friends" class="absolute btn hover:bg-arcade-clair rounded-[10px] left-[20%] top-[35%]">
								Friends
							</a>
							<a data-link href="/tournament" class="absolute btn hover:bg-arcade-clair rounded-[10px] left-[20%] top-[50%]">
								Tournament
							<a data-link href="/dashboard" class="absolute btn hover:bg-arcade-clair rounded-[10px] left-[20%] top-[65%]">
								Profil
							</a>
							<a data-link href="/" id="logout" class="absolute btn hover:bg-arcade-clair rounded-[10px] left-[20%] top-[80%]">
								Logout
							</a>
						</div>`;
		}

		return `
		<!-- Conteneur général -->
        <div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

            <!-- Image avec le titre -->
            <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
                    <h1>PONG</h1>
                </div>
            </div>

            <!-- Bloc des deux images -->
            <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
                <div class="flex flex-col items-center">

                    <!-- Image 1 -->
                    <div class="relative h-full w-full md:w-1/2 flex items-center justify-center">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />
						${element}
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
		const res = await fetch('/api/user', {
			method: 'GET',
		});
		if (res.status != 204) {
			await this.handleRedirection()
			const user = await res.json();
			const logout = document.getElementById('logout');
			if (logout) {
				logout.onclick = async (event) => {
					event.preventDefault();
					const response = await fetch('/api/logout', {
						method: 'POST',
						credentials: "include"
					});
					if (response.status == 204) {
						socket.emit("leave_room", 'online');
						socket.emit("logged_out", 'online', user.user);
						partialsArray.notificationToast(`See you Later ${user.user.username} !`, false);
						navigateTo('/');
						const redir_modal = document.getElementById('redir-modal');
						if (redir_modal) {
							redir_modal.parentNode?.removeChild(redir_modal);
						}
					} else {
						partialsArray.alertModal(
							'Oups, something went wrong !', 
							() => {}
						);
					}
				}
			}
		}
	};
}
