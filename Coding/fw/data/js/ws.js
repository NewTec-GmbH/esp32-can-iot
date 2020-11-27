var logMessages = [];
var maxLogs = 40;

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener('load', onLoad);

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    var table = document.getElementById("CANLog");
    var row = null;
    var cell = null;
    var index = 0;

    logMessages.push(event);

    if (maxLogs < logMessages.length) {
        logMessages.shift();
        table.deleteRow(1);
    }

    const message = event.data.split(';');

    row = table.insertRow(-1);

    cell = row.insertCell(-1);
    cell.innerHTML = message[0];
    cell = row.insertCell(-1);
    cell.innerHTML = message[1];
    cell = row.insertCell(-1);
    cell.innerHTML = message[2];
    cell = row.insertCell(-1);
    cell.innerHTML = message[3];
    cell = row.insertCell(-1);
    cell.innerHTML = message[4];
}

function onLoad(event) {
    initWebSocket();
    initButton();
}

function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
}

function toggle() {
    websocket.send('toggle');
}