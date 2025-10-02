export function notificationToast(message: string, type: boolean, duration = 3000) {
    
	// Create toast container if it doesn't exist
    let container = document.getElementById('toast-notification-container');
    if (!container) {
        container = document.createElement('div');
        container.id = 'toast-notification-container';
        container.className = 'popup fixed top-8 right-8 z-[9999]';
        document.body.appendChild(container);
    }

    // Create toast element
    const toast = document.createElement('div');

    toast.className = "rounded text-white font-principal flex justify-center items-center opacity-100 transition-opacity duration-300 px-3 py-3";
	if (type) {
        toast.textContent = message;
		toast.classList.add("bg-button_green/50");
	} else {
        toast.textContent = message;
		toast.classList.add("bg-button_red/50");
	}
    
    container.appendChild(toast);

    // Remove after duration
    setTimeout(() => {
        toast.style.opacity = '0';
        setTimeout(() => container!.removeChild(toast), 500);
    }, duration);
}