class UserProfile extends HTMLElement {
    constructor() {
        super();
        this.attachShadow({ mode: "open" }); // Isolation du style
    }

	connectedCallback() {
		this.shadowRoot.innerHTML = `         
			<iframe id="uploadsFrame" src="/testHTTP/testviewcookie.html" width="100%" height="100%"></iframe>
		`;
		window.addEventListener("message", (event) => {
			if (event.data.action === "updated") {
				this.refresh();
			}
		});
	}
	refresh() {
		this.shadowRoot.getElementById("uploadsFrame").contentWindow.location.reload();
	}
}


// Déclarer le composant dans le DOM
customElements.define("user-profil-section", UserProfile);
