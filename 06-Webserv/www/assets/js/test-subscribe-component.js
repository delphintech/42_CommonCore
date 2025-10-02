class TestSubscribeForm extends HTMLElement {
	constructor() {
		super();
		this.attachShadow({ mode: "open" }); // Isolation du style
	}

	connectedCallback() {
		this.shadowRoot.innerHTML = `         
			<iframe src="/testHTTP/testSubscribeForm.html" width="100%" height="100%"></iframe>
		`;
	}
}

// Déclarer le composant dans le DOM
customElements.define("test-subscribe-section", TestSubscribeForm);
