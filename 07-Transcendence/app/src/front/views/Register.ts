import AView from "./AView.js";
import { navigateTo } from "../index.js"
import { socket } from "../index.js";
import { partialsArray } from "./partials/ui.js";
import TFAModal from "./partials/_TFAModal.js"


export default class extends AView {
	constructor() { 
		super();
		this.setTitle("Register");
	}

	async getHTML() {
		return `
        <!-- Conteneur général -->
        <div class="min-h-screen w-full flex flex-col items-center justify-center bg-wall ">

            <!-- Image avec le titre -->
            <div class="relative w-4/5 max-w-[700px] h-1/5 mx-auto">
                <img src="/assets/upper_rec.svg" alt="Background" class="w-full h-full object-contain block" />
                <div class="absolute inset-0 flex items-center justify-center text-center font-principal text-red sm:text-4xl md:text-5xl lg:text-5xl">
                    <h1>REGISTER</h1>
                </div>
            </div>
    
            <!-- Bloc des deux images -->
            <div class="bg-cork border-8 rounded-xl border-wood w-[90%] max-w-[900px] p-6">
                <div class="flex flex-col md:flex-row items-stretch gap-6">

                    <!-- Image 1 -->
                    <div class="relative h-full w-full md:w-1/2 flex items-center justify-center">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain z-0" />
                        
                        <div class="absolute inset-0 z-10 h-full flex flex-col items-center justify-end px-6 pt-ratio w-full">
                            <p class="font-on_paper sm:text-3xl md:text-3xl lg:text-4xl">New Player</p>
                            <form class="w-full h-4/5 flex flex-col justify-evenly" id="registerForm" enctype="multipart/form-data">
                                <div class="pl-test">
                                    <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl ml-2">
                                        Username:
                                    </label>
                                    <input class="block w-2/3 px-3 text-gray-700 bg-wall rounded" id="username" type="text" placeholder="Username" name="username" pattern="^[a-zA-Z0-9]{4,15}$" title="Username must be between 4 and 15 long and without any special character" required>
                                </div>
                                <div class="pl-test">
                                    <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl mt-6 ml-2">
                                        Email:
                                    </label>
                                    <input class="block w-2/3 px-3 text-gray-700 bg-wall rounded" id="email" type="email" placeholder="email" name="email" pattern=".+@.+\..{2,}" title="Please enter a valid email adress" required>
                                </div>
                                <div class="pl-test">
                                    <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl mt-6 ml-2" for="password">
                                        Password
                                    </label>
                                    <input class="block w-2/3 px-3 text-gray-700 bg-wall rounded" id="password" type="password" placeholder="******************" name="password" required>
                                </div>
                                <div class="pl-test">
                                    <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl mt-6 ml-2" for="password">
                                        Confirm Password
                                    </label>
                                    <input class="block w-2/3 px-3 text-gray-700 bg-wall rounded" id="pwdConfirm" type="password" placeholder="******************" name="pwdConfirm" required>
                                </div>
								<div class="pl-test">
                                    <label class="font-on_paper sm:text-1xl md:text-1xl lg:text-2xl ml-2">
                                        Avatar
                                    </label>
                                    <input class="block w-2/3 px-3 text-gray-700 rounded" id="avatar" type="file" accept = "image/*" name="avatar">
                                </div>
                                <div class="text-center mt-2">
                                    <input class="bg-green-500 hover:bg-green-700 text-white font-bold px-4 py-1 rounded focus:outline-none focus:shadow-outline sm:text-1xl md:text-1xl lg:text-2xl font-paper" type="submit" value="Create">
                                </div>
                            </form>
                        </div>
                    </div>
                    
                    <!-- Séparateur "OR" -->
                    <div class="md:flex items-center justify-center px-4">
                        <p class="font-on_paper text-center sm:text-3xl md:text-3xl lg:text-4xl">OR</p>
                    </div>
                    
                    <!-- Image 2 -->
                    <div class="relative h-full w-4/5 md:w-1/2 flex items-center justify-center">
                        <img src="/assets/big_paper.png" alt="Background" class="w-full h-auto object-contain" />
						<div class="absolute inset-0 z-10 flex items-center justify-center p-6 flex-col gap-4 text-white sm:text-1xl md:text-1xl lg:text-2xl font-on_paper">
							<button id="google" type="button" class="w-60 h-12 bg-[#4285F4] hover:bg-[#4285F4]/90 focus:ring-4 focus:outline-none focus:ring-[#4285F4]/50 rounded-lg px-5 py-2.5 text-center inline-flex items-center justify-between mr-2 mb-2 shadow-md">
								<i class="fa-brands fa-google w-6 h-6 mr-2"></i>
								<span>Sign up with Google</span>
							</button>
							<button id="github" type="button" class="w-60 h-12 bg-gray-600 hover:bg-gray-700 focus:ring-4 focus:outline-none focus:ring-gray-500 rounded-lg px-5 py-2.5 text-center inline-flex items-center justify-between mr-2 mb-2 shadow-md">
								<i class="fa-brands fa-github w-6 h-6 mr-2"></i>
								<span>Sign up with GitHub</span>
							</button>
						</div>
                    </div>
                </div>
            </div>
        </div>

        `;
    }

	register = async () => {
		const form = document.getElementById('registerForm') as HTMLFormElement;
		form.onsubmit = async (event) => {
			event.preventDefault();
			const formData = new FormData(form);
			const data = Object.fromEntries(formData as any)

			if (!/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{8,15}$/.test(data.password)) {
				alert("Your password must be between 8 and 15 characters long and contain at least one number, one uppercase letter, one lowercase letter");
				return;
			}
			if (data.password !== data.pwdConfirm) {
				alert("Passwords do not match");
				return;
			}
			const response = await fetch('/api/register', {
				method: 'POST',
				body: formData
			});
			if (response.ok) {
                const userData = await response.json();
                partialsArray.notificationToast(`Welcome ${userData.user.username} !`, true);
                socket.emit("join_room", 'online');
                socket.emit("logged_in", 'online', userData.user);
				navigateTo('/')
			} else {
				const data = await response.json()
                partialsArray.alertModal(
                    data.message, 
                    () => {}
                );
			}
		}
	};

	remoteAuth = async () => {
		document.addEventListener("click", async (event) => {
			const target = event.target as HTMLElement;

			let provider = null
			if (target.id === "google" || target.closest("#google")) {
				provider = "google";
			} else if (target.id === "github" || target.closest("#github")) {
				provider = "github";
			}

			if (provider) {
				window.open(
					`/auth/${provider}?popup=true`,
					'OAuthLogin',
					'width=500,height=600'
				)};

			})
		window.addEventListener('message', async (event) => {
			if (event.origin !== window.location.origin) return;

			alert(event.data.message)
			if (event.data.type === 'auth-success') {
				navigateTo('/');
			} else if (event.data.type == 'auth-tfa') {
				await TFAModal()
			}
		})
}

	async onMounted() {
        partialsArray.homeModal();
		await this.register();
		await this.remoteAuth();
	}
}