import { navigateTo } from "../../index.js"
import { socket } from "../../index.js";
import { partialsArray } from "./ui.js";

export async function inputModal (title: string, label: string, onSend: (input: string) => void) {
   let modal = document.getElementById('input-modal');
	if (!modal) {
		modal = document.createElement('div');
		modal.id = 'input-modal';
		modal.className = 'fixed inset-0 z-[9999] flex items-center justify-center bg-black bg-opacity-50';
		document.body.appendChild(modal);
	}

	modal.innerHTML = `<div class="popup relative p-4">
		<div class="relative bg-cork_light rounded-lg shadow-lg border-wood border-4">
			<!-- Header -->
			<div class="flex items-center justify-between p-4 md:p-5 border-b border-gray-200 dark:border-gray-600 rounded-t">
				<h3 class="text-lg font-principal font-bold text-gray-900">
					${title}
				</h3>
				<button id="close-input" type="button" class="text-gray-600 bg-transparent hover:bg-gray-200 hover:text-gray-900 rounded-lg text-md h-8 w-8 inline-flex justify-center items-center ml-1">
					<i class="fa-solid fa-xmark"></i>
				</button>
			</div>

			<!-- Body -->
			<div class="p-4 md:p-5 flex flex-col gap-6">

					<!-- Enter alias -->
					<div id="alias-div" class="flex flex-col gap-2">
						<label for="alias" class="text-sm font-principal text-gray-700">
							${label}:
						</label>
						<div class="flex gap-2">
							<input id="alias" type="text" placeholder="alias" class="w-full font-principal text-sm py-2 px-3 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent" />
							<button id="send-alias" type="button" class="text-white bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-principal font-bold rounded-lg text-sm px-4 py-2 dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800">
								Send
							</button>
						</div>
					</div>
			</div>
		</div>
	</div>`

	// Handle modal events
	modal.addEventListener("click", async (event) => {
		const target = event.target as HTMLElement;
		const aliasDiv = document.getElementById("alias-div") as HTMLElement

		if (target.id == "close-input") { // close modal
			modal.parentNode?.removeChild(modal);
		}
		else if (target.id == "send-alias") { // send sms
			const input = document.getElementById("alias") as HTMLInputElement
			const alias = input.value
			if (!alias) {
				return partialsArray.alertModal("Please enter an alias", () => {})
			}
			event.preventDefault()
			onSend(alias)
			modal.parentNode?.removeChild(modal);
		}
	})
}