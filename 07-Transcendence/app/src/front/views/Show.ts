import AView from "./AView.js";
import { partialsArray } from "./partials/ui.js";
import { navigateTo } from "../index.js"
import { socket } from "../index.js";

export default class extends AView {
	constructor() {
		super();
		this.setTitle("Show");
	}

	async getHTML() {
		return `
		<!-- Conteneur général -->
		<div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

		<!-- Image avec le titre -->
		<div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
			<img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
			<div id="tournament-name" class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
			</div>
		</div>

		<!-- Bloc des deux images -->
		<div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
			<div class="flex flex-col md:flex-row items-stretch gap-6">

					<!-- Image 1 -->
					<div class="relative h-full w-full h-full md:w-1/2 gap-4 flex items-center justify-center">
						<img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />

						<!-- As Admin -->
						<div class="admin-player hidden absolute z-10 h-4/5 w-full gap-8 flex flex-col items-center justify-center">
							<div id="tournament-actions" class="flex gap-2 mt-2 h-auto w-auto">
								<button id="add-player-btn" class="bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded">Add Player</button>
								<div id="players-container" class="hidden w-full max-h-64 h-auto overflow-y-auto rounded p-2 mt-8">
								</div>
                            </div>
							<div class="flex flex-col items-center justify-center">
								<button id="start-tournament-btn" class="hidden bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded">
									Start Tournament
								</button>
							</div>
							<div class="flex flex-col items-center justify-center">
								<button id="go-to-tournament-btn" class="hidden bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded">
									Go To Tournament
								</button>
							</div>
							<div class="flex flex-col items-center justify-center">
								<a id="delete-btn" data-link href="/">
                            		<button class="bg-red-500 hover:bg-red-700 text-white font-bold px-4 py-1 rounded" type="click">Delete the tournament</button>
								</a>
							</div>
						</div>

						<!-- As Regular Player -->
						<div class="regular-player hidden absolute z-10 h-4/5 w-full gap-8 flex flex-col items-center justify-center">
							<div class="flex flex-col items-center justify-center">
								<div id="msg" class="hidden text-center font-on_paper sm:text-1xl md:text-2xl lg:text-2xl px-4">
									<p>You can't register, you're already part of another tournament</p>
								</div>
                				<div id="tour-is-on" class="hidden text-center font-on_paper sm:text-1xl md:text-2xl lg:text-2xl px-4 bg-green-500  text-white font-bold py-1 rounded">
									<p>Tournament is ON</p>
								</div>
								<button id="quit-btn" class="hidden mt-4 bg-red-500 hover:bg-red-700 text-white font-bold px-4 py-1 rounded">
									Quit this tournament
								</button>
							</div>
						</div>
					</div>

					<!-- Séparateur "OR" -->
					<div class="md:flex items-center justify-center px-4">
						<p class="font-on_paper text-center sm:text-3xl md:text-3xl lg:text-4xl">OR</p>
					</div>

					<!-- Image 2 -->
                    <div class="relative h-full w-full md:w-1/2">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain" />
                        <div class="absolute top-[16%] z-10 h-1/5 w-full">
                            <div class="">
                                <p class="inset-x-1/2 text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl">Players</p>
                            </div>
                            <div class="w-full">
                                <p id="count" class="text-center font-on_paper sm:text-xl md:text-xl lg:text-2xl"></p>
                            </div>
                        </div>
                        <div class="absolute top-[36%] h-3/5 w-5/6 right-0 overflow-y-scroll">
                            <ul id="list_tournament" class="list-inside space-y-3">
                            </ul>
                        </div>
                    </div>
				</div>
			</div>
		</div>
	`
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
				if (game.tournament.status == 'on') {
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

	fillPage = async () => {
		const showRes = await fetch('/api/show/' + currentTourId);
		const statusRes = await fetch('/api/userData');
		if (!showRes.ok || !statusRes.ok) {
			partialsArray.alertModal(
				`You don't have a game playing right now.`, 
				() => {
					return navigateTo('/');
				}
			);
		}
		const showData = await showRes.json();
		const statusData = await statusRes.json();
		if (!showData.tournament || !statusData.user) {
			partialsArray.alertModal(
				`You don't have a game playing right now.`, 
				() => {
					return navigateTo('/');
				}
			);
		}

		printTournamentNameAndPlayerCount(showData.tournament);
		toggleView(statusData, showData);
		printPlayerList(showData.players, showData.tournament, statusData.user);
		await showStartBtn(showData.tournament);
	}

	joinedWebsocketTourHandler = async (tour_data: any, user_joining: number) => {
		const res_current = await fetch('/api/user', { method: 'GET' });
		if (res_current.status != 204) {
			const current_user = await res_current.json();
			if (current_user.user.id != user_joining) {
				await this.fillPage();
			}
		}
	}

	leftWebsocketTourHandler = async (tour_data: any, user_leaving: number) => {
		await this.fillPage();
	}

	deletedWebsocketTourHandler = async (tour_data: any) => {
		partialsArray.alertModal(
			`The tournament ${tour_data.id} was deleted`, 
			() => {
				return navigateTo('/');
			}
		);
	}

	startWebsocketTourHandler = async (tour_data: any) => {
		partialsArray.notificationToast(`The tournament ${tour_data.id} starts`, true);
		navigateTo(`/tableau/${currentTourId}`);
	}

	handleWebsocket = async () => {
		socket.off("joined_tour", this.joinedWebsocketTourHandler);
		socket.on("joined_tour", this.joinedWebsocketTourHandler);

		socket.off("left_tour", this.leftWebsocketTourHandler);
		socket.on("left_tour", this.leftWebsocketTourHandler);

		socket.off("deleted_tour", this.deletedWebsocketTourHandler);
        socket.on("deleted_tour", this.deletedWebsocketTourHandler);

		socket.off("tour_started", this.startWebsocketTourHandler);
        socket.on("tour_started", this.startWebsocketTourHandler);
	}

	async onMounted() {
		try {
			partialsArray.homeModal();
			await this.handleRedirection();
			await getTournamentId();
			await this.fillPage();
			await this.handleWebsocket();
		} catch (e) {
			console.error('Error on mounted Show', e);
		}
	};
}

let currentTourId: number;

async function getTournamentId() {
	try {
		const tmpId = window.location.pathname.split('/').pop();
		
		if (tmpId && !isNaN(Number(tmpId)))
			currentTourId = Number(tmpId);
		else
		currentTourId = NaN;
	
	} catch (e) {
		console.error('Erreur getTournamentId', e);
		currentTourId = NaN;
	}
}

function printTournamentNameAndPlayerCount(tournament: any) {
	const nameElem = document.getElementById('tournament-name') as HTMLElement;
	const countElem = document.getElementById('count') as HTMLElement;

	if (nameElem)
		nameElem.textContent = tournament.name;

	if (countElem)
		countElem.textContent = `${tournament.player_number} / 4`;
}

function toggleView(statusData: any, showData: any,) {
	const adminElement = document.querySelector('.admin-player') as HTMLElement;
	const regularElement = document.querySelector('.regular-player') as HTMLElement;
  	const onElem = document.getElementById('tour-is-on') as HTMLElement;
	if (!adminElement || !regularElement || ! onElem) { return }

	if (showData.tournament.status == 'on') {
		regularElement.classList.remove('hidden');
		onElem.classList.remove('hidden');
		onElem.addEventListener("click", () => {
			navigateTo(`/tableau/${showData.tournament.id}`);
		}, { once: true });
	} else if (statusData.isAdmin && (showData.tournament.admin_id === statusData.user.id)) {
		adminElement.classList.remove('hidden');
		addPlayerToTournament(statusData.availableFriends, showData, statusData);
		deleteTournament(currentTourId, showData.players);
	} else {
		regularElement.classList.remove('hidden');
		quitTournament(statusData.status, statusData.user, showData.players);
	}
}

function printPlayerList(players: any[], tournament: any, currentUser: any) {
	const ul = document.getElementById("list_tournament") as HTMLElement;
	if (!ul)
		return;
	ul.innerHTML = "";

	players.forEach((player) => {
		const li = document.createElement("li");
		if (!li)
			return;
		let name = player.username;
		if (player.id === currentUser.id)
			name = "You";
		else if (player.id === tournament.admin_id)
			name = name.charAt(0).toUpperCase() + name.slice(1) + " - Admin";
		else
			name = name.charAt(0).toUpperCase() + name.slice(1);

		li.textContent = name;
		li.classList.add("ml-4", "font-on_paper", "sm:text-xl", "md:text-xl", "lg:text-2xl");

		ul.appendChild(li);
	});
}

function addPlayerToTournament(availableFriends: any[], showData: any, statusData: any) {
	try {
		const addPlayerBtn = document.getElementById('add-player-btn') as HTMLElement;
		const playersContainer = document.getElementById("players-container") as HTMLElement;

		if (addPlayerBtn && playersContainer) {
			addPlayerBtn.addEventListener('click', () => {
				addPlayerBtn.classList.add('hidden');
				playersContainer.classList.remove('hidden');
				if (availableFriends.length === 0) {
					playersContainer.textContent = 'No friends available';
					playersContainer.classList.add("font-on_paper", "sm:text-xl", "md:text-xl", "lg:text-2xl");
					return;
				}
				renderFriends(playersContainer, availableFriends, showData, statusData);
			}, { once: true });
		}
	} catch (e) {
		console.error('Error in addPlayerToTournament:', e);
	}
}

async function refreshFriendsAvailability(playersContainer: HTMLElement, showData: any, statusData: any) {
	try {
		const res = await fetch('/api/userData');
		if (!res) { return; }
		const updatedStatusData = await res.json();
		const availableFriends = updatedStatusData.availableFriends || [];

		if (availableFriends.length === 0) {
			playersContainer.textContent = 'No more friends available';
			playersContainer.classList.add("font-on_paper", "sm:text-xl", "md:text-xl", "lg:text-2xl");
			return;
		}
		renderFriends(playersContainer, availableFriends, showData, updatedStatusData);
	} catch (e) {
		console.error("Failed to refresh friends availability:", e);
		playersContainer.textContent = "Error loading friends.";
		playersContainer.classList.add("font-on_paper", "sm:text-xl", "md:text-xl", "lg:text-2xl");
	}
}

function renderFriends(playersContainer: HTMLElement, availableFriends: any[], showData: any, statusData: any) {
	try {
		playersContainer.innerHTML = "";

		availableFriends.forEach(friend => {
			const playerDiv = document.createElement("div");
			playerDiv.textContent = friend.username;
			playerDiv.dataset.userid = friend.id.toString();
			playerDiv.id = friend.id
			playerDiv.classList.add(
				"cursor-pointer", "hover:bg-blue-100", "rounded", "p-1", "font-on_paper",
				"sm:text-xl", "md:text-xl", "lg:text-2xl"
			);
			playersContainer.appendChild(playerDiv);
		})
		// Send invitation
		playersContainer.addEventListener("click", async (event) => {
			const friendList = document.getElementById('players-container')
			const target = event.target as HTMLElement;
			if (friendList?.contains(target) && target.dataset.userid) {
				socket.emit('tour_request', { 
					tournament: showData.tournament, 
					asker: statusData.user,
					replier: { id: target.dataset.userid, username: target.innerText } })
			}
		})
		} catch (e) {
			console.error("Error adding friend to tournament:", e);
		}
}

async function showStartBtn(tournament: any) {
    try {
        if (tournament.player_number === 4) {
            const startBtn = document.getElementById("start-tournament-btn") as HTMLButtonElement;
            const addBtn = document.getElementById("add-player-btn") as HTMLElement;
			const goToBtn = document.getElementById("go-to-tournament-btn") as HTMLElement;
		    const playersContainer = document.getElementById("players-container") as HTMLElement;

            if (startBtn && playersContainer && tournament.status != 'on') {
				startBtn.classList.remove("hidden");
                playersContainer.classList.add('hidden');
                const newStartBtn = startBtn.cloneNode(true) as HTMLButtonElement;
                startBtn.parentNode?.replaceChild(newStartBtn, startBtn);

				const showRes = await fetch('/api/show/' + currentTourId);
				if (!showRes.ok) {
					navigateTo('/');
					return;
				}
				const showData = await showRes.json();
				if (!showData.tournament) {
					navigateTo('/');
					return;
				}

                newStartBtn.addEventListener("click", async  () => {
					const dataTournament = await createGamesTournament(showData.players);
					if (!dataTournament) { return }
					await createJson(dataTournament);
					try {
						const res = await fetch('/api/startTournament/' + tournament.id, { method: 'POST' });
						if (!res.ok) {
							const err = await res.json();
							alert(err.error || 'Failed to start tournament');
							return;
						}
						socket.emit('start_tour', tournament.id);
						navigateTo('/tableau/' + tournament.id);
					} catch (error) {
						console.error('Error starting tournament:', error);
						alert('An error occurred');
					}
             	}, { once: true });
            }

			if (goToBtn && tournament.status == 'on') {
				goToBtn.classList.remove('hidden');
				goToBtn.addEventListener("click", () => {
					navigateTo('/tableau/' + tournament.id);
				}, { once: true });
			}

            if (addBtn) {
                addBtn.classList.add("hidden");
            }
        }
    } catch (error) {
        console.error("Error showing start button:", error);
    }
}


async function quitTournament(statusPlayer: string, user: any, players: any) {
	try {
		const msg = document.getElementById('msg') as HTMLElement;
		const btn = document.getElementById('quit-btn') as HTMLElement;
		const isRegisteredHere = statusPlayer === "unavailable" &&
		players.some((player: any) => player.id === user.id);

		if (msg && !isRegisteredHere)
			msg.classList.remove('hidden');
		
		if (btn && isRegisteredHere) {
			btn.classList.remove('hidden');

			// Clone the button to remove all event listeners
            const newBtn = btn.cloneNode(true) as HTMLElement;
            btn.parentNode?.replaceChild(newBtn, btn);

			newBtn.addEventListener('click', async (e) => {
				e.preventDefault();
				try {
					const response = await fetch('/api/quitTournament/' + currentTourId, {
						method: "DELETE",
						credentials: "include",
						headers: { "Content-Type": "application/json" },
						body: JSON.stringify({ userId: user.id })
					});
					
					if (response.ok) {
						socket.emit('leave_tour', currentTourId, user.id)
						navigateTo('/tournament');
					} else {
						console.error("Error", await response.text());
						alert("Error when trying to quit");
					}
				} catch (err) {
					console.error("Error during quitTournament fetch:", err);
				}
			}, { once: true });
		}
	} catch (e) {
		console.error("Error setting up quit button:", e);
	}
}

async function deleteTournament(currentTourId: number, players: any[]) {
	try {
		const btn = document.getElementById('delete-btn') as HTMLButtonElement;
		if (!btn) { return; }
		btn.classList.remove('hidden');
		btn.replaceWith(btn.cloneNode(true));
		
		const newBtn = document.getElementById('delete-btn') as HTMLButtonElement;
		if (!newBtn) { return; }
		newBtn.addEventListener('click', async (e) => {
			e.preventDefault();
			newBtn.disabled = true;
			try {
				const response = await fetch('/api/deleteTournament/' + currentTourId, {
					method: "DELETE",
				});
				if (response.ok) {
					socket.emit('delete_tour', currentTourId);
					navigateTo('/tournament');
				} else {
					console.error("Error", await response.text());
					alert("Error");
				}
			} catch (err) {
				console.error("Error fetch:", err);
			}
		}, { once: true });
	} catch (e) {
		console.error("Error setting up delete button:", e);
	}
}

async function createGamesTournament(players: any[]) { 
	const games = [];

	for (let i = 0; i < players.length; i++) {
		for (let j = i + 1; j < players.length; j++) {
			const res = await fetch('/api/game_tournament/' + currentTourId, {
				method: "POST",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify({ 
					playerR: players[i].id, 
					playerL: players[j].id
				})
			});
			if (res.ok) {
				const game = await res.json();
				games.push({
					id: game.game_id,
					player1: { id: players[i].id, username: players[i].username },
					player2: { id: players[j].id, username: players[j].username }
				});
			}
		}
	}
	if (games.length != 6) { return }
	
	const combinations = [
		[games[0], games[5]],
		[games[2], games[3]],
		[games[1], games[4]]
	];
	
	return { combinations };
}

async function createJson(dataTournament: any) {
	const data = {
		tournamentId: currentTourId,
		content: dataTournament,
	};

	const res = await fetch('/api/savePairs', {
		method: 'PUT',
		headers: { 'Content-Type': 'application/json' },
		body: JSON.stringify({ data }),
	});

	if (!res.ok) {
		console.error('Failed to save pairs');
	}
}