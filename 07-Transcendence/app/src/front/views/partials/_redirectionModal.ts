export function redirectionModal(message: string, onRedir: () => void,) {

    let modal = document.getElementById('redir-modal');
    if (!modal) {
        modal = document.createElement('div');
        modal.id = 'redir-modal';
        modal.className = 'popup fixed bottom-8 right-8 z-[9999]';
        document.body.appendChild(modal);
    }

    const newModal = modal.cloneNode(false) as HTMLElement;
    modal.parentNode?.replaceChild(newModal, modal);
    modal = newModal;

    modal.innerHTML = `
        <div class="popup relative p-4">
            <div class="rounded text-white font-principal flex justify-center items-center opacity-100 transition-opacity duration-300 px-3 py-3 bg-arcade-obscur">
                ${message}
            </div>
        </div>
    `;

     modal.addEventListener("click", async (event) => {
        const target = event.target as HTMLElement;
        if (target.id === "redir-modal" || target.closest("#redir-modal")) {
            onRedir();
            modal.parentNode?.removeChild(modal);
        }
    })
}