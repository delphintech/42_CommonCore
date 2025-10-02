export default class AView {
	constructor() {	}

	setTitle(title: string) {
		document.title = title;
	}

	async beforeMounted() {
	}

	async getHTML() {
		return "";
	}

	async onMounted() {
	}
}