import { navigateTo } from "../../index.js"
import { socket } from "../../index.js";
import { partialsArray } from "./ui.js";

export default async () => {
   let modal = document.getElementById('2fa-modal');
    if (!modal) {
        modal = document.createElement('div');
        modal.id = '2fa-modal';
        modal.className = 'fixed inset-0 z-[9999] flex items-center justify-center bg-black bg-opacity-50';
        document.body.appendChild(modal);
    }

	const res = await fetch("/auth/tfa/qrcode")
	if (!res.ok) {
		alert("unable to fetch the qrcode")
	}
	const data = await res.json()

    modal.innerHTML = `<div class="popup relative p-4">
		<div class="relative bg-cork_light rounded-lg shadow-lg border-wood border-4">
			<!-- Header -->
			<div class="flex items-center justify-between p-4 md:p-5 border-b border-gray-200 dark:border-gray-600 rounded-t">
				<h3 class="text-lg font-principal font-bold text-gray-900">
					Two-Factor Authentication
				</h3>
				<button id="close-2fa" type="button" class="text-gray-600 bg-transparent hover:bg-gray-200 hover:text-gray-900 rounded-lg text-md h-8 w-8 inline-flex justify-center items-center ml-1">
					<i class="fa-solid fa-xmark"></i>
				</button>
			</div>

			<!-- Body -->
			<div class="p-4 md:p-5 flex flex-col gap-6">

				<!-- Code Input -->
				<div class="flex flex-col gap-2">
					<label for="code" class="text-sm font-principal font-semibold text-gray-800">
						Enter your authentication code:
					</label>
					<input id="code" type="text" maxlength="6" placeholder="••••••" class="text-center font-principal text-lg tracking-widest py-2 px-4 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent" />
				</div>

				<!-- Resend Options -->
				<div class="flex flex-col gap-4">

					<!-- Authenticator App QR Code -->
					<div class="flex flex-col gap-2 items-center">
						<div class="flex items-center justify-between w-full">
							<p class="text-sm font-principal text-gray-700">Use your authenticator app:</p>
							<button id="refresh-qr" class="text-blue-600 hover:text-blue-800 focus:outline-none rounded-full p-1 hover:bg-gray-200" title="Generate new secret">
								<i class="fa-solid fa-arrows-rotate"></i>
							</button>
						</div>
						<div class="w-32 h-32 bg-gray-300 rounded-lg flex items-center justify-center text-gray-600 text-xs font-medium">
							<img id="qrImage" height="150" width="150" src=${data.qrcode} />
						</div>
					</div>

					<!-- SMS Option -->
					<div class="flex flex-col gap-2">
						<label for="phone" class="text-sm font-principal text-gray-700">
							Send code via SMS:
						</label>
						<div class="flex gap-2">
							<input id="phone" type="tel" placeholder="+1 234 567 8900" class="w-full font-principal text-sm py-2 px-3 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent" />
							<button id="send-sms" type="button" class="text-white bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-principal font-bold rounded-lg text-sm px-4 py-2 dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800">
								Send
							</button>
						</div>
					</div>

					<!-- Email Option -->
					<div class="flex flex-col gap-2">
						<p class="text-sm font-principal text-gray-700">Or receive the code by email:</p>
						<button id="send-email" type="button" class="w-full text-white font-principal font-bold justify-center bg-indigo-700 hover:bg-indigo-800 focus:ring-4 focus:outline-none focus:ring-indigo-300 rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-indigo-600 dark:hover:bg-indigo-700 dark:focus:ring-indigo-800">
							Send Code to Email
						</button>
					</div>
				</div>

				<!-- Action Buttons -->
				<div class="flex flex-col gap-4 pt-2">
					<button id="verify" type="button" class="w-full text-white font-principal font-bold justify-center bg-green-700 hover:bg-green-800 focus:ring-4 focus:outline-none focus:ring-green-300 rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-green-600 dark:hover:bg-green-700 dark:focus:ring-green-800">
						Verify
					</button>
					<button id="cancel-2fa" type="button" class="w-full text-white font-principal font-bold justify-center bg-red-700 hover:bg-red-800 focus:ring-4 focus:outline-none focus:ring-red-300 rounded-lg text-sm px-5 py-2.5 text-center inline-flex dark:bg-red-600 dark:hover:bg-red-700 dark:focus:ring-red-800">
						Cancel
					</button>
				</div>
			</div>
		</div>
	</div>`

	// Handle modal events
	modal.addEventListener("click", async (event) => {
        const target = event.target as HTMLElement;
        if (target.id == "cancel-2fa" || target.id == "close-2fa") { // close modal
			modal.parentNode?.removeChild(modal);
		}
		else if (target.id == "refresh-qr") { // refresh qrcopde
			const res = await fetch("/auth/tfa/refresh")
			if (!res.ok) {
				alert("unable to fetch the qrcode")
			}
			const data = await res.json()
			const qrImage = document.getElementById("qrImage") as HTMLImageElement;
            qrImage.src = data.qrcode;
		}
		else if (target.id == "send-sms") { // send sms
			const input = document.getElementById("phone") as HTMLInputElement
			const phone = input.value
			const res = await fetch('/auth/tfa/sms', {
				method: "POST",
				body: phone
			})
			const data = await res.json()
			partialsArray.alertModal(data.message, () => {})
		} else if (target.id == "send-email") { // send mail
			const res = await fetch('/auth/tfa/mail/')
			const data = await res.json()
			partialsArray.alertModal(data.message, () => {})
		} else if (target.id == "verify") { // verify code
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
				navigateTo('/')
			} else {
				partialsArray.alertModal(data.message, () => {})
			}
		}
    })
}

