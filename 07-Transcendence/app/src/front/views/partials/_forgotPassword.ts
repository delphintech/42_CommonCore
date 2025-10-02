import { navigateTo } from "../../index.js"
import { socket } from "../../index.js";
import { partialsArray } from "./ui.js";


export default async () => {
   let modal = document.getElementById('forgot-modal');
    if (!modal) {
        modal = document.createElement('div');
        modal.id = 'forgot-modal';
        modal.className = 'fixed inset-0 z-[9999] flex items-center justify-center bg-black bg-opacity-50';
        document.body.appendChild(modal);
    }

    modal.innerHTML = `<div class="popup relative p-4">
		<div class="relative bg-cork_light rounded-lg shadow-lg border-wood border-4">
			<!-- Header -->
			<div class="flex items-center justify-between p-4 md:p-5 border-b border-gray-200 dark:border-gray-600 rounded-t">
				<h3 class="text-lg font-principal font-bold text-gray-900">
					Retrieve your password
				</h3>
				<button id="close-forgot" type="button" class="text-gray-600 bg-transparent hover:bg-gray-200 hover:text-gray-900 rounded-lg text-md h-8 w-8 inline-flex justify-center items-center ml-1">
					<i class="fa-solid fa-xmark"></i>
				</button>
			</div>

			<!-- Body -->
			<div class="p-4 md:p-5 flex flex-col gap-6">

					<!-- Enter login -->
					<div id="login-div" class="flex flex-col gap-2">
						<label for="phone" class="text-sm font-principal text-gray-700">
							Enter your login:
						</label>
						<div class="flex gap-2">
							<input id="login" type="text" placeholder="login" class="w-full font-principal text-sm py-2 px-3 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent" />
							<button id="send-login" type="button" class="text-white bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-principal font-bold rounded-lg text-sm px-4 py-2 dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800">
								Send
							</button>
						</div>
					</div>

					<!-- Code Input -->
					<div id="verify-div" class="hidden flex flex-col gap-2">
						<label for="code" class="text-sm font-principal font-semibold text-gray-800">
							Enter your authentication code:
						</label>
						<input id="code" type="text" maxlength="6" placeholder="••••••" class="text-center font-principal text-lg tracking-widest py-2 px-4 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent" />
						<button id="verify" type="button" class="w-full text-white font-principal font-bold justify-center bg-green-700 hover:bg-green-800 focus:ring-4 focus:outline-none focus:ring-green-300 rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-green-600 dark:hover:bg-green-700 dark:focus:ring-green-800">
							Verify
						</button>
					</div>

			</div>
		</div>
	</div>`

	// Handle modal events
	modal.addEventListener("click", async (event) => {
        const target = event.target as HTMLElement;
		const loginDiv = document.getElementById("login-div") as HTMLElement
		const verifyDiv = document.getElementById("verify-div") as HTMLElement

        if (target.id == "close-forgot") { // close modal
			modal.parentNode?.removeChild(modal);
		}
		else if (target.id == "send-login") { // send sms
			const input = document.getElementById("login") as HTMLInputElement
			const login = input.value
			if (!login) {
				return partialsArray.alertModal("Please enter a login", () => {})
			}
			const res = await fetch(`/auth/tfa/mail/${login}`)
			const data = await res.json()
			if (!res.ok) {
				return partialsArray.alertModal(data.message, () => {})
			} else {
				loginDiv.classList.add("hidden")
				verifyDiv.classList.remove('hidden')
			}
		}
		if (target.id == "verify") {
			const input = document.getElementById("code") as HTMLInputElement
			const code = input.value
			const res = await fetch('/auth/tfa/verify', {
				method: "POST",
				body: code
			})
			const data = await res.json()
			if (res.ok) {
				modal.parentNode?.removeChild(modal);
				partialsArray.notificationToast(`Welcome ${data.user.username} !`, true);
				socket.emit("join_room", 'online');
				socket.emit("logged_in", 'online', data.user);
				navigateTo('/dashboard')
			} else {
				partialsArray.alertModal(data.message, () => {})
			}
		}
	})
}

