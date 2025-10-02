export function confirmModal(
    message: string,
    onConfirm: () => void,
    onReject: () => void,
    onCancel: () => void
) {
    let modal = document.getElementById('confirm-modal');
    if (!modal) {
        modal = document.createElement('div');
        modal.id = 'confirm-modal';
        modal.className = 'hidden fixed inset-0 z-[9999] flex items-center justify-center bg-black bg-opacity-50';
        document.body.appendChild(modal);
    }

    const newModal = modal.cloneNode(false) as HTMLElement;
    modal.parentNode?.replaceChild(newModal, modal);
    modal = newModal;

    modal.innerHTML = `
        <div class="popup relative p-4">
            <div class="relative bg-cork_light rounded-lg shadow-lg border-wood border-4">
                <div class="flex items-center justify-between p-4 md:p-5 border-b border-gray-200 dark:border-gray-600 rounded-t">
                    <h3 class="text-lg font-principal font-bold text-gray-900">${message}</h3>
                    <button id="close" type="button" class="text-gray-600 bg-transparent hover:bg-gray-200 hover:text-gray-900 rounded-lg text-md h-8 w-8 inline-flex justify-center items-center ml-1">
                        <i class="fa-solid fa-xmark"></i>
                    </button>
                </div>
                <div class="p-4 md:p-5 flex flex-col gap-5">
                    <button id="yes" type="button" class="w-full text-white font-principal font-bold justify-center bg-green-700 hover:bg-green-800 focus:ring-4 focus:outline-none focus:ring-green-300 rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-green-600 dark:hover:bg-green-700 dark:focus:ring-green-800">
                        Yes
                    </button>
                    <button id="no" type="button" class="w-full text-white font-principal font-bold justify-center bg-red-700 hover:bg-red-800 focus:ring-4 focus:outline-none focus:ring-red-300 rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-red-600 dark:hover:bg-red-700 dark:focus:ring-red-800">
                        No
                    </button>
                </div>
            </div>
        </div>
    `;

    modal.classList.remove("hidden");

    // Attach event listeners to the modal and delete the 
    modal.addEventListener("click", async (event) => {
        const target = event.target as HTMLElement;
        if (target.id === "yes" || target.closest("#yes")) {
            onConfirm();
            modal.parentNode?.removeChild(modal);
        } else if (target.id === "no") {
            onReject();
            modal.parentNode?.removeChild(modal);
        } else if (target.id === "close" || target.closest("#close")) {
            onCancel();
            modal.parentNode?.removeChild(modal);
        }
    })
}