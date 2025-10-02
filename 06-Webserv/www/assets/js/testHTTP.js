const urlForm = document.querySelector("#urlForm");
const head = document.querySelector("#testHead");
const get = document.querySelector("#testGet");
const post = document.querySelector("#testPost");
const delete_ = document.querySelector("#testDelete");

async function sendData(methodHTTP) {
  let response
   const formData = new FormData(post);
  // console.table([...formData.entries()]);
  try {
    if (methodHTTP === "POST") {
    response = await fetch(urlForm.value, {
      method: methodHTTP,
      body: formData,

    });
  }  
  else {
    response = await fetch(urlForm.value, {
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

// Take over form submission
head.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData("HEAD");
});

get.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData("GET");
});

post.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData("POST");
});

delete_.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData("DELETE");
});
