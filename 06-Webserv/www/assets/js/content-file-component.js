class ContentFile extends HTMLElement {
    constructor() {
        super();
        this.attachShadow({ mode: "open" }); // Isolation du style
    }

	connectedCallback() {
		this.shadowRoot.innerHTML = `         
			<iframe id="uploadsFrame" width="100%" height="100%"></iframe>
		`;
		window.addEventListener("message", (event) => {
			if (event.data.action === "updated") {
				this.refresh(event.data.filename);
			}
		});
	}
	refresh(filename) {
		this.shadowRoot.getElementById("uploadsFrame").contentWindow.location.replace(filename);
	}
}


// Déclarer le composant dans le DOM
customElements.define("content-file-section", ContentFile);
