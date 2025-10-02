import AView from "./AView.js";
import { navigateTo, socket } from "../index.js"
import { partialsArray } from "./partials/ui.js";
import { updateFriendship } from "../../back/controllers/friends.controller.js";

export default class extends AView {
	constructor() { 
		super();
		this.setTitle("Friends");
	}

	async getHTML() {
		const res = await fetch('/api/friends');
		const data = await res.json()
        let list_connected = "";
        let list_not_connected = "";
		let list_pending = "";
        let friends_connected = 0
		for (const friend of data.currents) {
            if (friend.online) {
                friends_connected++;
                list_connected = list_connected + `<li id=${friend.id} data-modal-target="select-modal" data-modal-toggle="" class="flex flex-row justify-between items-center w-11/12 h-2/12 font-on_paper sm:text-xl md:text-xl lg:text-2xl hover:bg-wood/50">
                    <p class="">${friend.username}</p>
                    <div class="bg-button_green rounded size-2 sm:size-2 md:size-3 lg:size-4"></div>
                </li>`;
            }
            else {
                list_not_connected = list_not_connected + `<li id=${friend.id} data-modal-target="select-modal" data-modal-toggle="" class="flex flex-row justify-between items-center w-11/12 h-2/12 font-on_paper text-gray-600 sm:text-xl md:text-xl lg:text-2xl hover:bg-wood/50">
                    <p class="">${friend.username}</p>
                    <div class="bg-button_red rounded size-2 sm:size-2 md:size-3 lg:size-4"></div>
                </li>`;
            }
        }
		for (const friend of data.pendings) {
			list_pending += `<li data-modal-target="select-modal" data-modal-toggle="" class="w-full flex flex-row justify-between items-center h-2/12 font-on_paper sm:text-xl md:text-xl lg:text-2xl hover:bg-wood/50">
                    <p class="">${friend.username}</p>
                    <button id=${friend.id} data-username=${friend.username} class="bg-button_green/50 hover:bg-button_green">Reply</button>
                </li>`
		}
		
		return `
			<div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

				<!-- Popup Modal -->
				<div id="select-modal" tabindex="-1" aria-hidden="true" class="hidden overflow-y-auto overflow-x-hidden fixed top-50 left-50 z-50 justify-center items-center"></div>

				<!-- Image avec le titre -->
                <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                    <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                    <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-black sm:text-4xl md:text-5xl lg:text-5xl">
                        <h1>MY FRIENDS</h1>
                    </div>
                </div>
        
                <!-- Bloc des deux images -->
                <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
                    <div class="flex flex-col md:flex-row items-stretch gap-6">
                        <!-- Image 1 -->
                        <div class="relative h-full w-full md:w-1/2 flex items-center justify-center">
                            <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />
                            <div class="absolute top-[16%] z-10 h-1/5 w-full">
                                <div class="">
                                    <p class="inset-x-1/2 text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl">Friend's status</p>
                                </div>
                                <div clas="w-full">
                                    <p id="count_friends" class="text-center font-on_paper sm:text-xl md:text-xl lg:text-2xl">${friends_connected}/${data.currents.length} friend(s) connected.</p>
                                </div>
                            </div>
                            <div class="absolute top-[36%] h-3/5 w-5/6 right-0 overflow-y-scroll">
                                <ul id="listFriends" class="list-inside space-y-3">
                                    ${list_connected}
                                    ${list_not_connected}
                                </ul>
                            </div>
                        </div>

                        <!-- Image 2 -->
                        <div class="relative h-full w-full md:w-1/2">
                            <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain" />
                            <div class="absolute top-[16%] z-10 h-full w-full pr-8 pl-14">
                                <div class="">
                                    <p class="inset-x-1/2 text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl">Find a new friend</p>
                                </div>
								<div class="flex justify-center mt-4">
									<form id="new_friend" class="flex flex-col items-center w-full max-w-xl space-y-2">
										<label class="font-on_paper sm:text-xl md:text-xl lg:text-2xl ml-2 text-center">Name of the user:</label>
										<div class="flex w-full justify-center items-center gap-2">
											<input class="w-2/3 px-3 text-gray-700 bg-wall rounded" id="name" type="text" placeholder="Name" name="friend_username">
											<button class="px-4 py-2 bg-green-500 hover:bg-green-700 text-white font-bold rounded font-paper text-sm sm:text-base" type="submit">
												Add
											</button>
										</div>
										<p id="error_new" class="font-on_paper text-red-600 text-sm"></p>
									</form>
								</div>
								<div class="mt-6">
                                    <p class="inset-x-1/2 text-center font-on_paper sm:text-3xl md:text-3xl lg:text-4xl mb-6">Pending friend requests</p>
                                </div>
								<ul id="listPending" class="list-inside space-y-3 mt-2">
									${list_pending}
								</ul>
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

	// Call to Action Popup
	handleFriendModal = async () => {
		const friendList = document.getElementById("listFriends")
		let access = true;

		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game || game.tournament) {
				access = false;
			}
		}

		if (friendList) {
			friendList.addEventListener("click", async (event) => {
				const target = event.target as HTMLElement;
				const friend = target.closest("li");
				if (friend && access) {
					const response = await fetch(`/api/user/${friend.id}`);
					if (response.ok) {
						const friendData = await response.json();
						partialsArray.friendModal(friendData,
							async () => await this.challengeFriend(friendData),
							async () => await this.deleteFriend(friendData),
							() => {}
						);
					}
				} else if (!access) {
					partialsArray.notificationToast(`You are in a game or waiting room. Your possibilities are limited`, false);
				}
			})
		}
	}

	// NEW FRIENDSHIP
	addFriend = async () => {
		const form = document.getElementById("new_friend") as HTMLFormElement;
		let access = true;

		const res_game = await fetch('/api/activeGameUser');
		if (res_game.status === 200) {
			const game = await res_game.json();
			if (game.game || game.tournament) {
				access = false;
			}
		}
		if (form) {
			form.onsubmit = async (event) => {
				event.preventDefault();
				if (!access) {
					return partialsArray.notificationToast(`You are in a game or waiting room. Your possibilities are limited`, false);
				}
				const formData = new FormData(form);
				const data = Object.fromEntries(formData as any)
				const res_creation = await fetch('/api/newfriend', {
					method: "POST",
					body: formData,
				});
				const requestData = await res_creation.json();
				if (res_creation.ok) {
					socket.emit("friend_request", requestData)
					partialsArray.notificationToast(`A request has been sent to ${data.friend_username} !`, true);
				} else {
					partialsArray.alertModal( requestData.error, () => {});
				}
				form.reset()
			}
		}
	}

	// ACCEPT FRIEND
	updateFriendship = async (friend_id: string, approved: boolean) => {
		const data = { approved: approved, friend_id: friend_id }
		const res = await fetch("/api/friendship", {
			method: 'PUT',
			headers: { "Content-Type": "application/json" },
			body: JSON.stringify(data),
		});
		if (res.ok) {
			const requestData = await res.json()
			socket.emit('friend_response', requestData);
			navigateTo('/friends')
		}
	}

	acceptFriend = async () => {
		const friendList = document.getElementById("listPending")

		if (friendList) {
			friendList.addEventListener("click", async (event) => {
				const target = event.target as HTMLElement;
				const friend = target.closest("button");
				if (friend) {
					const friend_username = friend.dataset.username
					partialsArray.confirmModal(`Accept ${friend_username}'s invitation ?'`,
						async () => this.updateFriendship(friend.id, true),
						async () => this.updateFriendship(friend.id, false),
						() => {})
				}
			})
		}
	}

	// DELETE FRIENDSHIP
	deleteFriend = async (friend: { id: number; username: string; online: boolean }) => {
		partialsArray.confirmModal(
			`Do you want to unfriend '${friend.username}' ?`, 
			async () => {
				const res = await fetch(`/api/friend/${friend.id}`, {
					method: "DELETE"
				});
				if (res.ok) {
					const data = await res.json()
					socket.emit("unfriend", data, false);
					navigateTo('/friends')
				}
			},
			() => {},
			() => {}
		);
	}


	// CREATE GAME
	challengeFriend = async (friend: { id: number; username: string; online: boolean }) => {
		// TODO: check if friend is available (not already in game or tournament)
		if (!friend.online) {
			return
		}

		partialsArray.confirmModal(
			`Do you want to challenge '${friend.username}' ?`, 
			async () => {
				const res = await fetch('/api/user');
				if (res.status == 200) {
					const user_data = await res.json();
					const response = await fetch('/api/game', {
						method: "POST",
						headers: { "Content-Type": "application/json" },
						body: JSON.stringify({ 
							playerR: user_data.user.id, 
							playerL: friend.id
						}),
					});
					if (response.status == 201) {
						const game_data = await response.json();
						socket.emit("challenge_friend", {
							friend_challenged: friend,
							user_challenger: user_data.user,
							game: game_data.game_id
						});
						navigateTo(`/waiting_room`);
					}
				}
			},
			() => {},
			() => {}
		);
	}

	async onMounted() {
		partialsArray.homeModal();

		await this.handleFriendModal()
		await this.addFriend()
		await this.handleRedirection()
		await this.acceptFriend()
	};
}