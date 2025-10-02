const form = document.querySelector("#userInfoForm");

async function sendData() {
  // FormData 
  const formData = new FormData(form);
  try {
    const response = await fetch("http://127.0.0.1:4243/cgi-bin/", {
      method: "POST",
	  multipart: true,
      // Set the FormData instance as the request body
      body: formData,
    });
    if (response.ok) {
      const result = await response.text(); // Assuming the response is HTML
    console.log(response.text());
      document.querySelector("#response").innerHTML = result;
    } else {
      console.error("Erreur lors de l'envoi du formulaire");
    }
  } catch (e) {
    console.error(e);
  }
}

// Take over form submission
form.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData();
});