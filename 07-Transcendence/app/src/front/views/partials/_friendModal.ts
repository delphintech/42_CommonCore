export function friendModal(
    friend: { id: number; username: string; online: boolean },
    onChallenge: () => void,
    onUnfriend: () => void,
    onCancel: () => void
) {
    let modal = document.getElementById('friend-modal');
    if (!modal) {
        modal = document.createElement('div');
        modal.id = 'friend-modal';
        modal.className = 'hidden fixed inset-0 z-[9999] flex items-center justify-center bg-black bg-opacity-50';
        document.body.appendChild(modal);
    }

	const newModal = modal.cloneNode(false) as HTMLElement;
    modal.parentNode?.replaceChild(newModal, modal);
    modal = newModal;

	let challengeClass: string
	let titleClass: string
	if (friend.online) {
		challengeClass = "rounded-lg flex flex-col items-center justify-between cursor-pointer w-full bg-green-500 hover:bg-green-700 mb-2"
		titleClass = ""
	} else {
		challengeClass = "rounded-lg flex flex-col items-center justify-between cursor-pointer w-full bg-gray-600 text-gray-400 mb-2"
		titleClass = "You can't challenge your friend: they are offline."
	}

    modal.innerHTML = `
        <div id="${friend.id}" class="popup relative p-4">
			<div class="relative bg-cork_light rounded-lg shadow-lg border-wood border-4">
				<!-- Modal header -->
				<div class="flex items-center justify-between p-4 md:p-5 border-b border-gray-200 dark:border-gray-600 rounded-t">
					<h3 class="text-lg font-principal font-bold text-gray-900">
						What do you want to do ?
					</h3>
					<button id="close" type="button" class="text-gray-600 bg-transparent hover:bg-gray-200 hover:text-gray-900 rounded-lg text-md h-8 w-8 inline-flex justify-center items-center ml-1" data-modal-toggle="select-modal">
						<i class="fa-solid fa-xmark"></i>
					</button>
				</div>

				<!-- Modal body -->
				<div class="p-4 md:p-5">
					<button id="challenge" data-modal-target="confirm-modal" data-modal-toggle="" title="${titleClass}" class="${challengeClass}">
						<div class="text-white text-lg font-principal font-bold text-center">Challenge</div>
						<div class="text-gray-200 font-principal">Play against ${friend.username}</div>
					</button>
					<button id="unfriend" data-modal-target="confirm-modal" data-modal-toggle="" class="w-full text-white font-principal justify-center bg-red-700 hover:bg-red-800 focus:ring-4 focus:outline-none focus:ring-red-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-red-600 dark:hover:bg-red-700 dark:focus:ring-red-800">
						Unfriend
					</button>
				</div>
			</div>
		</div>
    `;

    modal.classList.remove("hidden");

    /* // Attach event listeners to the modal and delete the 
    modal.addEventListener("click", async (event) => {
        const target = event.target as HTMLElement;
        if (target.id === "challenge" || target.closest("#challenge")) {
            onChallenge();
            modal.parentNode?.removeChild(modal);
        } else if (target.id === "unfriend" || target.closest("#unfriend")) {
            onUnfriend();
            modal.parentNode?.removeChild(modal);
        } else if (target.id === "close" || target.closest("#close")) {
            onCancel();
            modal.parentNode?.removeChild(modal);
        }
    }) */
   // Define the event handler
    const handleModalClick = async (event: Event) => {
        const target = event.target as HTMLElement;
        if (target.id === "challenge" || target.closest("#challenge")) {
            onChallenge();
            modal.parentNode?.removeChild(modal);
        } else if (target.id === "unfriend" || target.closest("#unfriend")) {
            onUnfriend();
            modal.parentNode?.removeChild(modal);
        } else if (target.id === "close" || target.closest("#close")) {
            onCancel();
            modal.parentNode?.removeChild(modal);
        }
    };

    // Add the event listener
    modal.addEventListener("click", handleModalClick);
}