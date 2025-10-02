class testput extends HTMLElement {
	constructor() {
		super();
		this.attachShadow({ mode: "open" }); // Isolation du style
	}

	connectedCallback() {
		this.shadowRoot.innerHTML = `         
			<iframe src="/testHTTP/testPUT.html" width="100%" height="100%"></iframe>
		`;
	}
}

// Déclarer le composant dans le DOM
customElements.define("test-put-section", testput);
