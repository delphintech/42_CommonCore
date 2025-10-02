const urlForm = document.querySelector("#urlForm");
const head = document.querySelector("#testHead");
const get = document.querySelector("#testGet");
const post = document.querySelector("#testPost");
/* const put = document.querySelector("#testPut"); */
const delete_ = document.querySelector("#testDelete");

async function sendData(methodHTTP) {
  let response
   const formData = new FormData(post);
  try {
    if (methodHTTP === "POST" || methodHTTP === "PUT") {
    response = await fetch(urlForm.value, {
      method: methodHTTP,
      body: formData,

    });
  }else {
    response = await fetch(urlForm.value, {
      method: methodHTTP,
    });
  }
    const result = await response.text();
    const headerStatusCode = response.status;
    const headerStatusMessage = response.statusText;
    const headers = [...response.headers.entries()].map(([key, value]) => `${key}: ${value}`).join("\n");
      
    document.querySelector("#responseHeader").innerHTML ="<h2>" + headerStatusCode+" "+ headerStatusMessage+ "</h2>"+ headers;
    document.querySelector("#response").innerHTML =  result;
    
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
/*
put.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData("PUT");
});*/

delete_.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData("DELETE");
});

