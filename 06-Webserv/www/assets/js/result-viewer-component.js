class ResultsViewer extends HTMLElement {
    constructor() {
        super();
        this.attachShadow({ mode: "open" }); // Isolation du style
    }

	connectedCallback() {
		this.shadowRoot.innerHTML = `<iframe id="resultFrame" src="/result.html" width="100%" height="100%"></iframe>`;
		window.addEventListener("message", (event) => {
			if (event.data.action === "updated") {
				this.updateHeaderResponseView(event.data.headers);
				this.updateContentResponseView(event.data.result);
			}
		});
	}
	updateHeaderResponseView(headers) {
		let iframe =this.shadowRoot.getElementById("resultFrame");
		let iframeDoc = iframe.contentDocument || iframe.contentWindow.document;
		iframeDoc.querySelector("#responseHeader").innerHTML = headers;
	}
	updateContentResponseView(results) {
		let iframe =this.shadowRoot.getElementById("resultFrame");
		let iframeDoc = iframe.contentDocument.querySelector("#response");
		if (!results) {
			iframeDoc.srcdoc = "";
			return;
		}
		/*iframeDoc.srcdoc = results;*/
		let doc = iframeDoc.contentWindow.document;
		doc.open();
		doc.write(results);
		doc.close();
	  

	}
}


// Déclarer le composant dans le DOM
customElements.define("results-section", ResultsViewer);
