import AView from "./AView.js";
import { partialsArray } from "./partials/ui.js";
import { navigateTo } from "../index.js"
import { socket } from "../index.js";

export default class extends AView {
	constructor() {
		super();
		this.setTitle("Tableau");
	}

	async getHTML() {
		return `
            <!-- Conteneur général -->
            <div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall">

                <!-- Image du rec avec titre -->

              <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                  <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                  <div id="tournament-name" class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl"></div>

              </div>

              <div class="h-full w-full flex flex-col gap-5 items-center justify-center">
                  <div class="bg-cork border-8 rounded-xl border-wood ">

                    <!-- Wrapper pour image + overlay -->
                    <div class="relative w-4/5 max-w-[900px] mx-auto">

                      <!-- Image -->
                      <img src="/assets/large_paper.png"
                          alt="Background"
                          class="w-full h-auto object-contain mb-6" />

                      <!-- Liste des matchs en overlay -->
                      <div class="wrapper absolute inset-0 flex flex-row gap-10 items-center justify-center">
                        <div id="games-list" class="flex flex-col gap-4 font-principal text-black text-md text-center mt-6 pt-6">
                          <div id="match-1" class="">Matchs 1:
                          </div>
                          <div id="match-2" class="">Matchs 2:
                          </div>
                          <div id="match-3" class="">Matchs 3:
                          </div>
                        </div>
                        <div class="flex flex-col gap-4 font-principal text-black text-md text-center mt-6 pt-6">
                          <div id="go_game" class="p-2 text-black text-md text-center p-1 bg-button_green/50 hover:bg-button_green h-fit rounded">
                            Go to your next game
                          </div>
                          <div id="players-list-points" class="flex flex-col gap-4 font-principal text-black text-md text-center mt-6 pt-6">
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                  <div class="relative h-fit flex justify-center">
                    <a id="quit_tour" class="absolute hover:bg-button_red font-principal bg-button_red/50 rounded-[10px]">
                      Stop the tournament
                    </a>
                  </div>
                </div>
            </div>
            `;
	}
  
  fillPage = async () => {
    const showRes = await fetch('/api/show/' + currentTourId);
    if (!showRes.ok) {
        return navigateTo('/');
    }
    const showData = await showRes.json();
    if (!showData.tournament) {
        return navigateTo('/');
    }
    const nameElem = document.getElementById('tournament-name') as HTMLElement;
    if (nameElem)
      nameElem.textContent = showData.tournament.name;
  }

  handleQuitTour = async () => {
		const quit_tour = document.getElementById('quit_tour');
		if (quit_tour) {
			quit_tour.onclick = async (event) => {
				event.preventDefault();
        partialsArray.confirmModal(
          `Do you want to stop the tournament ? It will delete the tournament for everyone.`, 
          async () => {
            const response = await fetch('/api/deleteTournament/' + currentTourId, {
              method: "DELETE"
            });
            if (response.ok) {
              socket.emit('delete_tour', currentTourId);
              navigateTo('/tournament');
            }
          },
          () => {},
          () => {}
        );
			}
		}
	}

  deletedWebsocketTourHandler = async (tour_data: any) => {
		partialsArray.alertModal(
			`The tournament ${tour_data.id} was deleted`, 
			() => {
				return navigateTo('/');
			}
		);
	}

  printList = async () => {
    const res_games = await fetch('/api/game_tournament/' + currentTourId);
    if (!res_games.ok) {return}
    const games = await res_games.json();
    const comb = JSON.parse(games.tournament.combinations)

    const gamesList = document.getElementById('games-list') as HTMLElement;
    if (gamesList) {
      // Clear only the content of existing match divs, not the divs themselves
      const match1 = document.getElementById('match-1') as HTMLElement;
      const match2 = document.getElementById('match-2') as HTMLElement;
      const match3 = document.getElementById('match-3') as HTMLElement;
      
      if (match1) match1.innerHTML = 'Matchs 1:';
      if (match2) match2.innerHTML = 'Matchs 2:';
      if (match3) match3.innerHTML = 'Matchs 3:';
      
      const matchElements = [match1, match2, match3];
      
      for (const [idx, game] of comb.combinations.entries()) {
        const res_statusGame0 = await fetch('/api/game_tournament_results/' + game[0].id)
        const res_statusGame1 = await fetch('/api/game_tournament_results/' + game[1].id)
        if (!res_statusGame0.ok || !res_statusGame1.ok) { continue }
        const status0 = await res_statusGame0.json()
        const status1 = await res_statusGame1.json()
        if (!status0 || !status1) { continue }

        const matchEl = matchElements[idx];
        if (!matchEl) continue; // Skip if we don't have a matching div
        
        // Update the class based on active match
        if (games.done_games_count / 2 == idx) {
          matchEl.className = "p-2 text-black text-md text-center p-1 bg-button_green h-fit rounded flex flex-col";
          await fetch('/api/setGamesActive', {
            method: "PUT",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({
              game0: game[0].id,
              game1: game[1].id
            }),
          });
        } else {
          matchEl.className = "p-2 text-black text-md text-center p-1 bg-wood/50 h-fit rounded flex flex-col";
        }
        
        // Set the match title
        matchEl.innerHTML = `Matchs ${idx + 1}:`;
        
        // Create and append game divs
        const game0Div = document.createElement('div');
        game0Div.id = game[0].id.toString();
        game0Div.innerText = `${game[0].player1.username} vs ${game[0].player2.username} - ${status0.status}`;
        matchEl.appendChild(game0Div);

        const game1Div = document.createElement('div');
        game1Div.id = game[1].id.toString();
        game1Div.innerText = `${game[1].player1.username} vs ${game[1].player2.username} - ${status1.status}`;
        matchEl.appendChild(game1Div);
      }
    }
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
				}
			}
		}
	}

  handleGoToGame = async () => {
    const go_game = document.getElementById('go_game') as HTMLElement;
    
    const res_next_games = await fetch('/api/next_game_tournament/' + currentTourId);
    if (!res_next_games.ok || res_next_games.status == 204) {
      await this.checkEndTournament(currentTourId);
      return;
    }
    const next_games = await res_next_games.json();
    
    if (next_games.nb_next_games == 0 || next_games.next_game.status != 'hold') {
      await this.checkEndTournament(currentTourId);
      return;
    }


    if (go_game && next_games.nb_next_games != 0) {
      go_game.addEventListener("click", async () => {
        const res = await fetch(`/api/play/accept/${next_games.next_game.id}`, {
					method: 'PUT',
				});
				if (res.ok) {
					navigateTo("/waiting_room");
          socket.off("tour_info", this.updatePage);
        }
		  });
    }
  }

  checkEndTournament = async (tour_id:number) => {
    const res_user = await fetch("/api/user");
    if (res_user.status != 200) {return console.log('no current user (fetch)')}

    const current_user = await res_user.json();
    if (!current_user.user) {return console.log('no current user (json)')}

    const res_games = await fetch('/api/game_tournament/' + tour_id);
    if (!res_games.ok) {return console.log('problem game tournament (fetch)')}

    const games = await res_games.json();
    if (!games.tournament) {return console.log('problem game tournament (json)')}

    if (current_user.user.id == games.tournament.admin_id) {
      if (games.done_games_count == 6) {
        console.log('hello')
        const res_finish_tour = await fetch('/api/finish_tournament/' + tour_id, {
					method: 'PUT',
				});
        if (res_finish_tour.ok) {
          const winner = await res_finish_tour.json();
          socket.emit('finish_tour', winner.tournament.id ,winner)
        }
      }
    }
  }

  updatePage = async (tour_id:number, game_id:number) => {
    const res_games = await fetch('/api/game_tournament/' + tour_id);
    if (!res_games.ok) {return}
    const games = await res_games.json();
    if (games.done_games_count < 5) {
      await this.handleGoToGame();
    }

		await this.printList();
    await this.checkEndTournament(tour_id);
	}

  showWinner = async (tour_id:number, winner:any) => {
    partialsArray.alertModal(
			winner.message, 
			() => {
        navigateTo('/');
			}
		);
	}

  handleWebsocket = async () => {
    socket.off("tour_info", this.updatePage);
    socket.on("tour_info", this.updatePage);

    socket.off("winner_announcement", this.showWinner);
    socket.on("winner_announcement", this.showWinner);

    socket.off("deleted_tour", this.deletedWebsocketTourHandler);
    socket.on("deleted_tour", this.deletedWebsocketTourHandler);
  }

  async onMounted() {
    try {
      partialsArray.homeModal();

      await this.handleRedirection();

      await getTournamentId();
      
      await this.handleWebsocket();
      await this.fillPage();
      await this.printList();
      await this.handleGoToGame();
      await this.handleQuitTour();

    } catch (e) {
        console.log('Error on mounted Show', e);
    }
	};

  async onUnmounted() {
    socket.off("tour_info", this.updatePage);
  }
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
		console.log('Erreur getTournamentId', e);
		currentTourId = NaN;
	}
}
