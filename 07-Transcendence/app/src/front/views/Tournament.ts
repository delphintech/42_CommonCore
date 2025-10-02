import { partialsArray } from "./partials/ui.js";
import { navigateTo } from "../index.js"
import AView from "./AView.js";
import { socket } from "../index.js";

export default class extends AView {
    constructor() {
        super();
		this.setTitle("Tournament");
	}

    async getHTML() {
        return `
        <div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

            <!-- Image avec le titre -->
            <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
                    <h1>TOURNAMENTS</h1>
                </div>
            </div>

            <!-- Bloc des deux images -->
            <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
                <div class="flex flex-col md:flex-row items-stretch gap-6">

                    <!-- Image 1 -->
                    <div class="relative h-full w-full md:w-1/2">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain" />

                        <div class="absolute top-[16%] z-10 h-full w-full">

                            <div id="new_tournament" class="create-div hidden text-center bottom-0 w-full h-3/5 flex flex-col justify-around items-center">
                                <div id="create-tournament" class=" w-1/2 h-auto top-1/2 bg-green-500 hover:bg-green-700 text-white font-bold cursor-pointer rounded sm:text-1xl md:text-1xl lg:text-2xl font-paper px-4 py-1">
                                    Create new tournament
                                </div>
                                <form id="create-tournament-form" class="tournament-input hidden flex flex-col items-center h-full w-full">
                                    <p class="tournament-input hidden font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-2 mb-6">Name:</p>
                                    <input class="block w-3/5 px-4 py-1 text-gray-700 bg-wall rounded mb-6" id="tournament-name" type="text" placeholder="Tournament name" name="name" required>
                                    <div id="error-div" class="text-red-500 hover:text-red-700 mb-6"></div>
                                    <button class="bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded focus:outline-none focus:shadow-outline font-paper" type="submit">Save</button>
                                </form>
                            </div>

                            <div class="text-center bottom-0 w-full h-3/5 flex flex-col justify-around items-center">
                                <div class="hidden show-div font-on_paper sm:text-3xl md:text-3xl lg:text-4xl mb-6">You are already in a tournament</div>
                                <div class="go-to-tournament hidden text-center w-1/2 md:h-2/5 sm:h-1/5 bg-green-500 hover:bg-green-700 text-white font-bold rounded sm:text-1xl md:text-1xl lg:text-2xl font-paper px-4 py-1">
                                    Go to your tournament page
                                </div>

                            </div>
                        </div>
                    </div>

                    <!-- Séparateur "OR" -->
                    <div class="md:flex items-center justify-center px-4">
                        <p class="font-on_paper text-center sm:text-3xl md:text-3xl lg:text-4xl">OR</p>
                    </div>

                    <!-- Image 2 -->
                    <div class="relative h-full w-full md:w-1/2 flex items-center justify-center">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />

                        <div class="absolute top-[16%] z-10 h-full w-full">
                            <p class="text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl">Join</p>
                            <p class="nb-of-tournaments text-center font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-4 "></p>
                            <div class="list-inside h-full mt-4 ml-4 flex flex-row justify-center text-center font-on_paper sm:text-xl md:text-xl lg:text-2xl">
                                <ul class="list w-4/5 max-h-64 h-auto overflow-y-auto"></ul>
                            </div>

                        </div>
                    </div>

                </div>
            </div>
        </div>
        `
    };

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

    async onMounted() {
        try {
            partialsArray.homeModal();
            await toggleView();
            await printTournamentsListAndCount();
            await this.handleRedirection();

        } catch (error) {
            console.error("Error during Home view mounting:", error);
        };
    }
}

// 1 je suis available donc create tournamet
// 2 je suis unavailable ET admin donc go to my tournament
// 3 je suis unavailabe mais PAS admin donc pas de go to tournament

let currentStatus: string;
let currentUser: any;

async function toggleView() {
    try {
        const response = await fetch('/api/userData');
        if (!response.ok) {
            return;
        }
        const { status, isAdmin, tournamentId, user } = await response.json();
        if (!user || !user.id)
            return;

        currentStatus = status;
        currentUser = user;

        const createDiv = document.querySelector('.create-div') as HTMLElement;
        const showDiv = document.querySelector('.show-div') as HTMLElement;
        const goToDiv = document.querySelector('.go-to-tournament') as HTMLElement;

        createDiv.classList.add('hidden');
        showDiv.classList.add('hidden');
        goToDiv.classList.add('hidden');

        if (status === 'available') {
            createDiv.classList.remove('hidden');
            await showForm();
            await createTournament();
        }
        else if (status === 'unavailable' && isAdmin) {
            showDiv.classList.remove('hidden');
            goToDiv.classList.remove('hidden');
            await goToMyTounament(tournamentId);
        }
        else if (status === 'unavailable' && !isAdmin) {
            showDiv.classList.remove('hidden');
            goToDiv.classList.remove('hidden');
            await goToMyTounament(tournamentId);
        }

    } catch (error) {
        console.error('Error toggling view:', error);
    }
}

async function goToMyTounament(tournamentId: number) {

     try {

        const goToDiv = document.querySelector('.go-to-tournament') as HTMLElement;
        goToDiv.addEventListener('click', async () => {
            navigateTo(`/show/${tournamentId}`);
        });

    } catch (e) {
        console.log('Error toggle view', e);
    }
}

async function printTournamentsListAndCount() {
    try {
        const data = await fetch('/api/tournamentsAvailable');
        if (!data.ok) { return }
        const res = await data.json();
        const tournaments = res.tournaments;
        const count = res.nb_tournaments;

        const pElem = document.querySelector('.nb-of-tournaments') as HTMLElement;
        if (pElem) {
            pElem.textContent = `${count} tournament(s) available to join`
        }

        const ul = document.querySelector('.list') as HTMLElement;
        if (ul) {
            // Clear existing list items first
            ul.innerHTML = "";

            tournaments.forEach((tournament: { name: string, player_number: number, id: number }) => {
                const liName = document.createElement('li');
                let count = tournament.player_number.toString();
                let name = tournament.name;
                name = name.charAt(0).toUpperCase() + name.slice(1);
                liName.innerHTML = `${name} - ${count} player(s)`;
                liName.classList.add('hover:bg-wood/50', 'cursor-pointer', "rounded", "p-1");
                liName.setAttribute("data-id", tournament.id.toString());

                // Clone the li element to remove any existing event listeners
                const newLiName = liName.cloneNode(true) as HTMLElement;

                newLiName.addEventListener('click', () => {
                    joinTournament(newLiName, currentStatus, currentUser);
                })
                ul.appendChild(newLiName);
            });
        }
    } catch (e) {
        console.error("Error print avalaible tournaments", e);
    }
}

async function joinTournament(liName: HTMLElement, status: string, user: any) {
    try {
        if (!liName) { return; }

        const name = liName.textContent?.split(' -')[0]?.trim().toLowerCase();
        if (!name) { return; }

        const foundId = parseInt(liName.getAttribute("data-id") || "", 10);
        if (!foundId) { return; }

        const registerRes = await fetch(`/api/registerPlayer/${foundId}`, {
            method: "POST",
            credentials: "include",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ userId: user.id })
        });
        if (registerRes.ok) {
            socket.emit('join_tour', foundId, user.id);
            navigateTo(`/show/${foundId}`);
        }
    } catch (e) {
        console.error("Error joinTournament", e);
    }
}

async function showForm() {
    const show = document.getElementById("create-tournament") as HTMLElement;
    const input = document.querySelectorAll(".tournament-input") as NodeListOf<HTMLInputElement>;
    if (!show || !input) { return; }
    show.addEventListener('click', () => {
        input.forEach(input => {
            input.classList.remove("hidden");
        })
        show.classList.add("hidden");
    });
}

async function createTournament() {
    const newTournament = document.getElementById("create-tournament-form") as HTMLInputElement;
    if (newTournament) {
        newTournament.addEventListener("submit", async (event) => {
            event.preventDefault();
            const input = document.getElementById("tournament-name") as HTMLInputElement;
            if (!input) { return; }
            const name = input.value.trim();
            input.value = "";
            
            const errorDiv = document.getElementById("error-div") as HTMLElement;
            if (errorDiv)
                errorDiv.textContent = "";

            try {
                const res = await fetch("/api/createTour", {
                    method: "POST",
                    headers: { "Content-Type": "application/json" },
                    body: JSON.stringify({ name: name })
                });
                if (res.status == 400 || res.status == 201) { 
                    const data = await res.json();
                    if (!res.ok) {
                        if (errorDiv) {
                            errorDiv.textContent = data.error;
                        }
                        return;
                    }
                    data.tournament.id; 

                    socket.emit('create_tour', data.tournament.id, currentUser.id);
                    navigateTo(`show/${data.tournament.id}`);
                }
            } catch (error) {
                console.error("Error creating tournament:", error);
            };
        });
    }
}
