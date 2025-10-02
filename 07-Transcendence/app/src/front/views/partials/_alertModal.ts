export function alertModal(
    message: string,
    onOk: () => void
) {
    let modal = document.getElementById('alert-modal');
    if (modal) {
        modal.remove();
    }
    modal = document.createElement('div');
    modal.id = 'alert-modal';
    modal.className = 'hidden fixed inset-0 z-[9999] flex items-center justify-center bg-black bg-opacity-50';
    document.body.appendChild(modal);

    /* const newModal = modal.cloneNode(false) as HTMLElement;
    modal.parentNode?.replaceChild(newModal, modal);
    modal = newModal; */

    modal.innerHTML = `
        <div class="popup relative p-4">
            <div class="relative bg-cork_light rounded-lg shadow-lg border-wood border-4">
                <div class="flex items-center justify-between p-4 md:p-5 border-b border-gray-200 dark:border-gray-600 rounded-t">
                    <h3 class="text-lg font-principal font-bold text-gray-900">${message}</h3>
                    <button id="close" type="button" class="text-gray-600 bg-transparent hover:bg-gray-200 hover:text-gray-900 rounded-lg text-md h-8 w-8 inline-flex justify-center items-center ml-1">
                        <i class="fa-solid fa-xmark"></i>
                    </button>
                </div>
                <div class="p-4 md:p-5 flex justify-center">
                    <button id="ok" type="button" class="w-1/2 text-white font-principal font-bold justify-center bg-green-700 hover:bg-green-800 focus:ring-4 focus:outline-none focus:ring-green-300 rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-green-600 dark:hover:bg-green-700 dark:focus:ring-green-800">
                        Ok
                    </button>
                </div>
            </div>
        </div>
    `;

    modal.classList.remove("hidden");

    // Attach event listeners to the modal and delete the dskjgfksdjg
    modal.addEventListener("click", async (event) => {
        const target = event.target as HTMLElement;
        if (target.id === "ok" || target.closest("#ok") || target.id === "close" || target.closest("#close")) {
            onOk();
            modal.remove();
        }
    })
}