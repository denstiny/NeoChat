function check_login_status(res,sig) {
    console.log(JSON.stringify(res))
    if(res.status === 200) {
        let content = JSON.parse(res.content)
        if(content.message_type === "login" ) {
            sig(true)
            return
        }
    }
    sig(false)
}

function request(headerArgs,callback,sig) {
    console.log("send login to server")
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
            print('HEADERS_RECEIVED');
        } else if(xhr.readyState === XMLHttpRequest.DONE) {
            let res = {
                status: xhr.status,
                headers: xhr.getAllResponseHeaders(),
                content : xhr.response
            }
            callback(res,sig)
        }
    }
    xhr.open("POST", "http://127.0.0.1:6667");
    for(var key in headerArgs) {
        xhr.setRequestHeader(key,headerArgs[key])
    }
    xhr.send();
}
