const urlForm = document.querySelector("#urlForm");
const post = document.querySelector("#testPost");
const loginpost = document.querySelector("#testLoginPost");
const putupdateAvatarForm = document.querySelector("#updateAvatarForm");
const putupdateEmailForm = document.querySelector("#updateEmailForm");
const putupdateNameForm = document.querySelector("#updateNameForm");
const postUrl = "http://127.0.0.1:4243/cgi-bin/testphp/inscription.php";
const putUrl = "http://127.0.0.1:4243/cgi-bin/testphp/edit.php";
const loginUrl = "http://127.0.0.1:4243/cgi-bin/testphp/login.php";
async function sendData(methodHTTP) {
  let response
   const formData = new FormData(post);
  // console.table([...formData.entries()]);
  try {
    if (methodHTTP === "POST") {
    response = await fetch(postUrl, {
      method: methodHTTP,
      body: formData,

    });
  }  
  else {
    response = await fetch(postUrl, {
      method: methodHTTP,
    });
  }
    const result = await response.text();
    const headerStatusCode = response.status;
    const headerStatusMessage = response.statusText;
    const headers = [...response.headers.entries()].map(([key, value]) => `${key}: ${value}`).join("\n");
    const responseHeaders = "<h2>" + headerStatusCode+" "+ headerStatusMessage+ "</h2>"+ headers;
    window.parent.postMessage({ action: "updated", result: result, headers: responseHeaders }, "*");
  } catch (e) {
    console.log(e);
  }
}

post.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData("POST");
});


async function sendDataPUT(action) {
  let response;
 
  try {
    if (action === "updateEmail") {

    const userid = document.querySelector("#userid");
     const  formData = new FormData(putupdateEmailForm);
      const email = formData.get("email");
      response = await fetch(putUrl + "/?action="+action + "&userid="+userid.value, {
      method: "PUT",
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded'
      },
      body: `email=${encodeURIComponent(email)}`
    });
  } else if (action === "updateAvatar") {
    const userid = document.querySelector("#userid");
    const  formData  = new FormData(putupdateAvatarForm);
    const file = formData.get("avatar");
    response = await fetch(putUrl + "/?action="+action+ "&userid="+userid.value, {
      method: "PUT",
      headers: {
        'Content-Type': file.type // Ex: "image/png"
      },
      body: file
    });
  } else if (action === "updateName") {
    const userid = document.querySelector("#userid");
    const  formData  = new FormData(putupdateNameForm);
    const name = formData.get("name");
    response = await fetch(putUrl + "/?action="+action+ "&userid="+userid.value, {
      method: "PUT",
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded'
      },
      body: `name=${encodeURIComponent(name)}`
    });
  }
  
  else {
    response = await fetch(putUrl, {
      method: "GET",
    });
  }
    const result = await response.text();
    const headerStatusCode = response.status;
    const headerStatusMessage = response.statusText;
    const headers = [...response.headers.entries()].map(([key, value]) => `${key}: ${value}`).join("\n");
    const responseHeaders = "<h2>" + headerStatusCode+" "+ headerStatusMessage+ "</h2>"+ headers;
      
    window.parent.postMessage({ action: "updated", result: result, headers: responseHeaders }, "*");
  } catch (e) {
    console.log(e);
  }
}

async function sendDataPOSTLogin() {
  let response;
 
  try {

      const  formData = new FormData(loginpost);
      const login = formData.get("login");
      response = await fetch(loginUrl, {
      method: "POST",
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded'
      },
      body: `login=${encodeURIComponent(login)}`
    });
    const result = await response.text();
    const headerStatusCode = response.status;
    const headerStatusMessage = response.statusText;
    const headers = [...response.headers.entries()].map(([key, value]) => `${key}: ${value}`).join("\n");
    const responseHeaders = "<h2>" + headerStatusCode+" "+ headerStatusMessage+ "</h2>"+ headers;
      
    window.parent.postMessage({ action: "updated", result: result, headers: responseHeaders }, "*");
  } catch (e) {
    console.log(e);
  }
}
putupdateAvatarForm.addEventListener("submit", (event) => {
  event.preventDefault();
  sendDataPUT("updateAvatar");
});
putupdateEmailForm.addEventListener("submit", (event) => {
  event.preventDefault();
  sendDataPUT("updateEmail");
});
putupdateNameForm.addEventListener("submit", (event) => {
  event.preventDefault();
  sendDataPUT("updateName");
});
loginpost.addEventListener("submit", (event) => {
  event.preventDefault();
  sendDataPOSTLogin();
});