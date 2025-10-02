import AView from "./AView.js";
import { partialsArray } from "./partials/ui.js";
import { navigateTo } from "../index.js"

export default class extends AView {
	constructor() {
		super();
		this.setTitle("Dashboard");
	}

	async getHTML() {

        return `
            <div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

                <!-- Image avec le titre -->
                <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                    <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                    <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
                        <h1>PROFIL</h1>
                    </div>
                </div>

                <!-- Bloc des deux images -->
                <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">

                <div class="flex flex-col md:flex-row items-stretch gap-6">

                        <!-- Image 1 -->
                        <div class="relative h-full w-full md:w-1/2 flex items-center justify-center">
                            <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />

                            <div class="absolute inset-0 z-10 h-full flex flex-col items-center justify-end px-6 pt-ratio w-full">
                              <div class="flex flex-row w-full">
                                <div class="h-1/5 w-full flex justify-center items-center mt-8">
                                    <p id="user-profil" class=" text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl"></p>
                                </div>
                                <div class="avatar"></div>
                              </div>
                                <div class="w-full h-4/5 flex flex-col justify-evenly">
                                    <div class="pl-test">
                                      <div class="flex items-center justify-between w-full">
                                        <label class="font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-2">
                                          Edit Avatar:
                                        </label>
                                        <img id="edit-icon0" src="/assets/pen.png" alt="pen" class="w-6 h-6 object-contain z-10 mr-2 hover:bg-arcade-clair rounded-[18px] cursor-pointer"/>
                                      </div>
                                      <form id="change-avatar" class="flex items-center justify-between w-full">
                                        <input class="hidden" id="new-avatar" type="file" name="avatar">
                                        <label for="new-avatar" class="avatar-input hidden cursor-pointer bg-yellow-500 hover:bg-yellow-700 text-white font-bold px-4 py-1 rounded block w-3/5 px-3">
                                          Browse Avatar
                                        </label>
                                        <button class="avatar-input hidden bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded focus:outline-none focus:shadow-outline font-paper" type="submit">Upload</button>
                                      </form>
                                    </div>
                                    <div class="pl-test">
                                      <div class="flex items-center justify-between w-full">
                                        <label class="font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-2">
                                          Edit Username:
                                        </label>
                                        <img id="edit-icon1" src="/assets/pen.png" alt="pen" class="w-6 h-6 object-contain z-10 mr-2 hover:bg-arcade-clair rounded-[18px] cursor-pointer"/>
                                      </div>
                                      <form id="change-username" class="flex items-center justify-between w-full">
                                        <input class="user-input hidden block w-2/3 px-3 text-gray-700 bg-wall rounded" id="new-username" type="text" placeholder="Edit Username">
                                        <button class="user-input hidden bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded focus:outline-none focus:shadow-outline font-paper" type="submit">Save</button>
                                      </form>
                                    </div>
                                    <div class="pl-test">
                                        <div class="flex items-center justify-between w-full">
                                          <label class="font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-2">
                                              Edit email:
                                          </label>
                                          <img id="edit-icon2" src="/assets/pen.png" alt="pen" class="w-6 h-6 object-contain z-10 mr-2 hover:bg-arcade-clair rounded-[18px] cursor-pointer"/>
                                        </div>
                                        <form id="change-email" class="flex items-center justify-between w-full">
                                          <input class="email-input hidden block w-2/3 px-3 text-gray-700 bg-wall rounded" id="new-email" type="text" placeholder="Edit Email">
                                          <button class="email-input hidden bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded focus:outline-none focus:shadow-outline font-paper" type="submit">Save</button>
                                        </form>
                                    </div>
                                    <div class="pl-test">
                                        <div class="flex items-center justify-between w-full">
                                            <label class="font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-2" for="password">
                                                Edit password
                                            </label>
                                            <img id="edit-icon3" src="/assets/pen.png" alt="pen" class="w-6 h-6 object-contain z-10 mr-2 hover:bg-arcade-clair rounded-[18px] cursor-pointer"/>
                                        </div>
                                         <form id="change-password" class="flex items-center justify-between w-full">
                                           <input class="password-input hidden block w-2/3 px-3 text-gray-700 bg-wall rounded" id="new-password" type="password" placeholder="******************">
                                          <button class="password-input hidden bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded focus:outline-none focus:shadow-outline font-paper" type="submit">Save</button>
                                        </form>
                                    </div>
									<div class="pl-test">
										<div class="flex items-center justify-between w-full">
											<label class="font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-2">
												Two-Factor Auth:
											</label>
											<div class="relative mr-2">
												<label class="flex items-center cursor-pointer">
													<div class="relative">
														<input type="checkbox" id="toggle-2fa" class="sr-only peer">
														<div class="block bg-gray-300 w-10 h-6 rounded-full peer peer-checked:bg-button_green"></div>
														<div class="dot absolute left-1 top-1 bg-white w-4 h-4 rounded-full transition peer peer-checked:translate-x-full"></div>
													</div>
												</label>
											</div>
										</div>
								</div>
                              </div>
                            </div>
                        </div>


                        <!-- Séparateur "OR" -->
                        <div class="md:flex items-center justify-center px-4">
                            <p class="font-on_paper text-center sm:text-3xl md:text-3xl lg:text-4xl"></p>
                        </div>

                        <!-- Image 2 -->
                        <div class="relative h-full w-full md:w-1/2 flex items-center justify-center">
                            <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />

                            <div class="absolute inset-0 z-10 h-full flex flex-col items-center justify-end px-6 pt-ratio w-full">
                              <div class="flex flex-row w-full">
                                <div class="h-1/5 w-full flex justify-center items-center mt-8">
                                    <p id="user-stats" class="font-on_paper sm:text-3xl md:text-3xl lg:text-4xl"></p>
                                </div>
                              </div>
                              <div class="w-full h-4/5 flex flex-col justify-evenly">
                                  <div class="pl-test">
                                      <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl ml-2">
                                          <!-- Number of Games played: -->
                                          <p id="play-count"></p>
                                      </label>
                                  </div>
                                  <div class="pl-test">
                                      <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl ml-2">
                                          <!-- Number of Games Won: -->
                                          <p id="win-count"></p>
                                      </label>
                                  </div>
                                  <div class="pl-test">
                                      <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl mt-6 ml-2">
                                          <!-- Number of Games Lost:  -->
                                          <p id="lost-count"></p>
                                      </label>
                                  </div>
                                  <div class="pl-test">
                                    <div class="flex justify-between items-center mt-6  mr-2">
                                      <p id="friends-count" class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl">
                                        <!-- Number of Friends -->
                                      </p>
                                      <a data-link href="/friends" class="font-on_paper sm:text-xl md:text-xl lg:text-xl hover:bg-arcade-clair rounded-[10px] px-2">
                                        more
                                      </a>
                                    </div>
                                  </div>
                                  <!-- Game History:  -->
                                  <div class="pl-test">
                                      <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl mt-6 ml-2">
                                        <p id="see-game-history">Game History</p>
                                        <div id="game-history" class="hidden absolute inset-0 bg-cork  px-5 pt-5 flex flex-col overflow-y-auto w-full h-full md:w-full md:h-full">
                                        <div id="match-history-container" class="space-y-4 mt-6 text-left max-w-3xl mx-auto">
                                          <h2 class="text-xl font-bold bg-cork bg-opacity-90 py-2 text-center w-full">Your Match History</h2>
                                          <div id="match-history-list" class="divide-y divide-gray-600"></div>
                                          <p id="quit-game_history" class="self-start cursor-pointer underline mt-4 mb-6">Back To General</p>
                                        </div>
                                      </div>
                                    </label>
                                  </div>



                                  <div class="pl-test">
                                      <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl mt-6 ml-2">
                                        <p id="see-more-stats">See More Stats</p>
                                        <div id="stats" class="hidden absolute inset-0 bg-cork z-50 px-5 pt-5 flex flex-row items-center justify-between  w-full h-full  max-w-full max-h-full md:flex-col md:w-full md:h-full">
                                          <canvas id="canvas-bar" class="w-full h-auto"></canvas>
                                          <canvas id="canvas-pie" class="w-full h-auto"></canvas>
                                          <p id="back-to-dashboard" class="self-start cursor-pointer underline mt-0">Back To General</p>
                                        </div>
                                      </label>
                                  </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

            </div>

            <script src="dashboard.js"></script>
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
    await this.handleRedirection();

    partialsArray.homeModal();
    const resUser = await fetch("/api/getUser");
    if (resUser.ok) {
      const data = await resUser.json();
      const profilElem = document.getElementById("user-profil") as HTMLFormElement;
      if (profilElem && data.username) {
        const capitalizedUsername = data.username.charAt(0).toUpperCase() + data.username.slice(1);
        profilElem.textContent = capitalizedUsername;
      }
      const avatarElement = document.querySelector('.avatar') as HTMLDivElement;
      if (avatarElement) {
        avatarElement.innerHTML = `<img src="${data.avatar}" alt="Avatar" class="w-18 h-16 rounded-full">`;
      }

      const username = data.username;
      const formattedUsername = username.charAt(0).toUpperCase() + username.slice(1);

      const userStatsElem = document.getElementById('user-stats');
      if (userStatsElem) userStatsElem.textContent = `${formattedUsername}'s Stats`;

      const friendsCountElem = document.getElementById('friends-count');
      if (friendsCountElem) friendsCountElem.textContent = `Number of Friends: ${data.friendsCount}`;

	  const tfa = document.getElementById('toggle-2fa') as HTMLInputElement;
	  if (data.tfa) { tfa.checked = true }
      }

    const toggleVisibility = (className: string) => {
      document.querySelectorAll(`.${className}`).forEach(el => {
        el.classList.toggle('hidden');
      });
    };

    // === Show Input on Pen Clicks ===
    const editAvatarBtn = document.getElementById('edit-icon0');
    if (editAvatarBtn) {
      editAvatarBtn.addEventListener('click', () => {
        toggleVisibility('avatar-input');
      });
    }

    const editUsernameBtn = document.getElementById('edit-icon1');
    if (editUsernameBtn) {
      editUsernameBtn.addEventListener('click', () => {
        toggleVisibility('user-input');
      });
    }

    const editEmailBtn = document.getElementById('edit-icon2');
    if (editEmailBtn) {
      editEmailBtn.addEventListener('click', () => {
        toggleVisibility('email-input');
      });
    }

    const editPasswordBtn = document.getElementById('edit-icon3');
    if (editPasswordBtn) {
      editPasswordBtn.addEventListener('click', () => {
        toggleVisibility('password-input');
      });
    }

    document.addEventListener('click', (event) => {
      const target = event.target as HTMLElement;

      const isInsideForm = target.closest('.user-input, .email-input, .password-input, .avatar-input');
      const isEditButton = target.closest('[id^="edit-icon"]');

      if (!isInsideForm && !isEditButton) {
        document.querySelectorAll('.user-input, .email-input, .password-input')
          .forEach(el => el.classList.add('hidden'));
      }
    });

    // === Submit Username ===
    try {
      const form = document.getElementById('change-username') as HTMLFormElement;

      form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const input = document.getElementById('new-username') as HTMLInputElement;
        const newUsername = input.value.trim();

        if (!newUsername) {
          alert("New Username cannot be blank.");
          return;
        }

        try {
          const res = await fetch('/api/updateUser', {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ username: newUsername }),
          });

          if (!res.ok) throw new Error('Error updating username');
          const data = await res.json();
          document.getElementById('user-profil')!.textContent = data.username;
          input.value = '';
          toggleVisibility('user-input');
        } catch (err) {
          console.error(err);
          alert('Échec de la mise à jour du username');
        }
      });
    } catch (err) {
      console.error('Erreur form username:', err);
    }

    // === Submit Email ===
    try {
      const form = document.getElementById('change-email') as HTMLFormElement;

      form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const input = document.getElementById('new-email') as HTMLInputElement;
        const newemail = input.value.trim();

        if (!newemail) {
          alert("New email cannot be blank.");
          return;
        }

        try {
          const res = await fetch('/api/updateUser', {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ email: newemail }),
          });

          if (!res.ok) throw new Error('Erreur email');
          await res.json();
          input.value = '';
          toggleVisibility('email-input');
        } catch (err) {
          console.error(err);
          alert('Échec de la mise à jour de l’email');
        }
      });
    } catch (err) {
      console.error('Erreur form email:', err);
    }

    // === Submit Password ===
    try {
      const form = document.getElementById('change-password') as HTMLFormElement;

      form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const input = document.getElementById('new-password') as HTMLInputElement;
        const newpassword = input.value.trim();

        if (!newpassword) {
          alert("Password cannot be blank.");
          return;
        }

        try {
          const res = await fetch('/api/updateUser', {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ password: newpassword }),
          });

          if (!res.ok) throw new Error('Erreur password');
          await res.json();
          input.value = '';
          toggleVisibility('password-input');
        } catch (err) {
          console.error(err);
          alert('Échec de la mise à jour du mot de passe');
        }
      });
    } catch (err) {
      console.error('Erreur form password:', err);
    }

    // === Charger Avatar ===
    try {
      const form = document.getElementById('change-avatar') as HTMLFormElement;
      form.addEventListener('submit', async (event) => {
        event.preventDefault();
        const input = document.getElementById('new-avatar') as HTMLInputElement;
        const file = input.files?.[0];
        if (!file) {
          alert("Please select an avatar file.");
          return;
        }
        const formData = new FormData(form);
        try {
          const res = await fetch('/api/user/avatar', {
            method: 'PUT',
            body: formData,
          });

          if (!res.ok) {
            throw new Error('Error when trying to update avatar');
          }

          const data = await res.json();
          console.log('Avatar updated:', data);
          input.value = '';

          const avatarElement = document.querySelector('.avatar img') as HTMLImageElement;
          if (avatarElement) {
            avatarElement.src = data.avatar + '?t=' + Date.now();
          }
        }
        catch (err) {
          console.error('Erreur:', err);
          alert('Failed to update avatar');
        }
      });
    } catch (err) {
      console.error('Erreur onMounted:', err);
    }

	// Toggle tfa
	const tfa = document.getElementById('toggle-2fa') as HTMLInputElement;

	tfa.addEventListener("change", async () => {
		try {
			const res = await fetch("/api/user/tfa", { method: "PUT" })
			if (!res.ok) throw new Error('Erreur réseau');
		} catch (err) {
			console.error('Erreur fetch:', err);
		}
	})

    // stats
    try {
      const res = await fetch('/api/userStats');
      if (!res.ok) throw new Error('Erreur réseau');
      const data = await res.json();

      // Games Played
      const playCountElem = document.getElementById('play-count');
      if (playCountElem) {
        playCountElem.textContent = `Number of Games Played: ${data.playCount}`;
      }

      // Games Won
      const winCountElem = document.getElementById('win-count');
      if (winCountElem) {
        winCountElem.textContent = `Number of Games Won: ${data.winCount}`;
      }

      // Games Lost
      const lostCountElem = document.getElementById('lost-count');
      if (lostCountElem) {
        lostCountElem.textContent = `Number of Games Lost: ${data.lostCount}`;
      }

    } catch (err) {
      console.error('Erreur lors de la récupération des stats:', err);
    }
    await gameHistory();
    await drawGraphs();
  }
}

/* ---------- Game History ---------------- */

async function gameHistory() {
  const seeMore = document.getElementById('see-game-history') as HTMLElement;
  const gameElem = document.getElementById('game-history') as HTMLElement;
  const quitBtn = document.getElementById('quit-game_history') as HTMLElement;

  if (!seeMore || !gameElem || !quitBtn) return;

  seeMore.addEventListener('click', async () => {
    gameElem.classList.remove('hidden');

    try {
      // 1. Récupérer les stats du user (avec ses plays)
      const res = await fetch('/api/userStats');
      if (!res.ok) throw new Error('Erreur réseau');
      const data = await res.json();
      const { plays } = data;

      // 2. Récupérer la liste des opponents
      const opponentsRes = await fetch('/api/opponents');
      if (!opponentsRes.ok) throw new Error('Erreur réseau opponents');
      const opponentsData = await opponentsRes.json();

      // Construire un dictionnaire game_id => opponent username
      const opponentsMap = new Map<number, string>();
      opponentsData.opponents.forEach((opp: { game_id: number; opponent_username: string }) => {
        opponentsMap.set(opp.game_id, opp.opponent_username);
      });

      const container = document.getElementById('match-history-list') as HTMLElement;
      container.innerHTML = '';

      plays.forEach((play: { win: boolean; side: string; score: number; createdAt: string; game_id: number }) => {
        const date = new Date(play.createdAt);
        const dateStr = date.toLocaleDateString();
        const timeStr = date.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
        const formattedDate = `${dateStr} ${timeStr}`;

        const result = play.win ? '✅ Win' : '❌ Loss';
        const side = play.side === 'left' ? 'Left' : 'Right';
        const vs = opponentsMap.get(play.game_id) || 'Guest';

        const row = document.createElement('div');
        row.classList.add('my-4', 'py-4');
        row.innerHTML = `
          <p><strong>Game vs:</strong> ${vs}</p>
          <p><strong>Result:</strong> ${result}</p>
          <p><strong>Score:</strong> ${play.score}</p>
          <p><strong>Side:</strong> ${side}</p>
          <p><strong>Date:</strong> ${formattedDate}</p>
        `;
        container.appendChild(row);
      });

    } catch (e) {
      console.error('Error loading match history:', e);
    }
  });

  quitBtn.addEventListener('click', () => {
    gameElem.classList.add('hidden');
  });
}

/* ---------- GRAPHS ---------------- */

async function drawGraphs() {
  const stats = document.getElementById('stats') as HTMLElement;
  const seeMore = document.getElementById('see-more-stats') as HTMLElement;
  const backTo = document.getElementById('back-to-dashboard') as HTMLElement;

  let scores: number[] = [];
  let winLooseRatio: boolean[] = [];

  seeMore.addEventListener('click', async () => {
    stats.classList.remove('hidden');

      try {
        const res = await fetch('/api/userStats');
        if (!res.ok) throw new Error('Erreur stats');
        const data = await res.json();
        scores = data.scores || [];
        winLooseRatio = data.winLooseRatio || [];
        barChart(scores);
        pieChart(winLooseRatio);

      } catch (err) {
        console.error('Erreur chargement des stats graphiques:', err);
      }

  });

  backTo.addEventListener('click', () => {
    stats.classList.add('hidden');
  });
}

function barChart(scores: number[]) {
  const canvas = document.getElementById('canvas-bar') as HTMLCanvasElement;
  const ctx = canvas.getContext('2d')!;

  const cssWidth = 800;
  const cssHeight = 600;
  const dpr = window.devicePixelRatio || 1;

  canvas.width = cssWidth * dpr;
  canvas.height = cssHeight * dpr;
  canvas.style.width = '100%';
  canvas.style.height = 'auto';
  ctx.scale(dpr, dpr);

  const paddingLeft = 40;
  const paddingBottom = 20;
  const paddingTop = 20;
  const paddingRight = 20;

  const chartWidth = cssWidth - paddingLeft - paddingRight;
  const chartHeight = cssHeight - paddingTop - paddingBottom;

  const maxScore = 10;
  const scaleY = chartHeight / maxScore;

  const barWidth = 45;
  const gap = 35;
  let curX = paddingLeft + gap;

  function getColor(score: number): string {
    if (score === 10) return 'green';
    if (score === 0) return 'red';
    return 'orange';
  }

  // Fond
  ctx.fillStyle = '#eee';
  ctx.fillRect(0, 0, cssWidth, cssHeight);

  // Axes
  ctx.strokeStyle = 'black';
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(paddingLeft, paddingTop);
  ctx.lineTo(paddingLeft, cssHeight - paddingBottom);
  ctx.lineTo(cssWidth - paddingRight, cssHeight - paddingBottom);
  ctx.stroke();

  // Y ticks
  ctx.fillStyle = 'black';
  ctx.font = '12px sans-serif';
  ctx.textBaseline = 'middle';
  ctx.textAlign = 'right';

  for (let i = 0; i <= maxScore; i++) {
    const y = cssHeight - paddingBottom - i * scaleY;
    ctx.fillText(i.toString(), paddingLeft - 5, y);

    ctx.strokeStyle = '#ccc';
    ctx.beginPath();
    ctx.moveTo(paddingLeft, y);
    ctx.lineTo(cssWidth - paddingRight, y);
    ctx.stroke();
  }

  // Y Label
  ctx.save();
  ctx.translate(paddingLeft - 30, cssHeight / 2);
  ctx.rotate(-Math.PI / 2);
  ctx.textAlign = 'center';
  ctx.font = '16px sans-serif';
  ctx.fillStyle = 'black';
  ctx.fillText('Points', 0, 0);
  ctx.restore();

  // X Label
  ctx.textAlign = 'center';
  ctx.font = '16px sans-serif';
  ctx.fillStyle = 'black';
  ctx.fillText('Games', paddingLeft + chartWidth / 2, cssHeight - 5);

  // Bars
  scores.forEach((score, idx) => {
    const barHeight = score * scaleY;
    const x = curX + idx * (barWidth + gap);
    const y = cssHeight - paddingBottom - barHeight;

    ctx.fillStyle = getColor(score);
    ctx.fillRect(x, y, barWidth, barHeight);
  });
}

function pieChart(results: boolean[]) {
  const canvas = document.getElementById('canvas-pie') as HTMLCanvasElement;
  const ctx = canvas.getContext('2d')!;

  const cssWidth = 180;
  const cssHeight = 180;
  const dpr = window.devicePixelRatio || 1;
  canvas.width = cssWidth * dpr;
  canvas.height = cssHeight * dpr;
  canvas.style.width = cssWidth + 'px';
  canvas.style.height = cssHeight + 'px';
  ctx.scale(dpr, dpr);

  const radius = 70;
  const cx = canvas.width / (2 * dpr);
  const cy = canvas.height / (2 * dpr);

  const wins = results.filter(r => r).length;
  const losses = results.length - wins;
  const total = wins + losses;

  if (total === 0) {
    ctx.fillStyle = 'black';
    ctx.font = 'bold 12px sans-serif';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText('No stats yet', cx, cy);
    return;
  }

  const winRatio = wins / total;
  const lossRatio = losses / total;

  const winAngle = winRatio * 2 * Math.PI;
  const lossAngle = lossRatio * 2 * Math.PI;
  const textRadius = radius * 0.6;
  let startAngle = 0;

  if (wins === total) {
    ctx.beginPath();
    ctx.moveTo(cx, cy);
    ctx.fillStyle = '#006400';
    ctx.arc(cx, cy, radius, 0, Math.PI * 2);
    ctx.fill();
    ctx.closePath();

    ctx.fillStyle = 'white';
    ctx.font = 'bold 12px sans-serif';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText('Wow impressive!', cx, cy);
    return;
  }

  if (losses === total) {
    ctx.beginPath();
    ctx.moveTo(cx, cy);
    ctx.fillStyle = '#8B0000';
    ctx.arc(cx, cy, radius, 0, Math.PI * 2);
    ctx.fill();
    ctx.closePath();

    ctx.fillStyle = 'white';
    ctx.font = 'bold 12px sans-serif';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText('You really suck!', cx, cy);
    return;
  }

  // Portion Wins
  ctx.beginPath();
  ctx.moveTo(cx, cy);
  ctx.fillStyle = '#006400';
  ctx.arc(cx, cy, radius, startAngle, startAngle + winAngle);
  ctx.lineTo(cx, cy);
  ctx.fill();
  ctx.closePath();

  // Portion Losses
  ctx.beginPath();
  ctx.moveTo(cx, cy);
  ctx.fillStyle = '#8B0000';
  ctx.arc(cx, cy, radius, startAngle + winAngle, startAngle + winAngle + lossAngle);
  ctx.lineTo(cx, cy);
  ctx.fill();
  ctx.closePath();

  // Labels
  const midWinAngle = startAngle + winAngle / 2;
  const midLossAngle = startAngle + winAngle + lossAngle / 2;

  ctx.fillStyle = 'white';
  ctx.font = 'bold 12px sans-serif';
  ctx.textAlign = 'center';
  ctx.textBaseline = 'middle';

  ctx.fillText(
    'Wins',
    cx + Math.cos(midWinAngle) * textRadius,
    cy + Math.sin(midWinAngle) * textRadius
  );

  ctx.fillText(
    'Loses',
    cx + Math.cos(midLossAngle) * textRadius,
    cy + Math.sin(midLossAngle) * textRadius
  );
}

async function handleHomeIcon() {
  const homeIcon = document.getElementById("home-icon") as HTMLElement;
  if (homeIcon) {
    homeIcon.addEventListener("click", async () => {
      navigateTo('/');
    });
  }
}
