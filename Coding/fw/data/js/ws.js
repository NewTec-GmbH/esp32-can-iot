/*
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
*/
var logMessages = [];
var maxLogs = 40;
var counter = 1;

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
        logMessages.pop();
        table.deleteRow(-1);
    }

    var frame = {
        ID: "",
        DLC: "",
        DATA: "",
        TIMESTAMP: ""
    };

    switch (event.data[0]) {
        case "t":
            frame.ID = event.data.substr(1, 3);
            frame.DLC = event.data[4];
            frame.DATA = event.data.substr(5, frame.DLC * 2);
            frame.TIMESTAMP = event.data.substr(5 + frame.DLC * 2, event.data.length);
            break;

        case "T":
            frame.ID = event.data.substr(1, 8);
            frame.DLC = event.data[9];
            frame.DATA = event.data.substr(10, frame.DLC * 2);
            frame.TIMESTAMP = event.data.substr(10 + frame.DLC * 2, event.data.length);
            break;

        case "r":
            frame.ID = event.data.substr(1, 3);
            frame.DLC = event.data[4];
            frame.DATA = "RTR"
            frame.TIMESTAMP = event.data.substr(5, event.data.length);
            break;

        case "R":
            frame.ID = event.data.substr(1, 8);
            frame.DLC = event.data[9];
            frame.DATA = "RTR"
            frame.TIMESTAMP = event.data.substr(10, event.data.length);
            break;


        default:
            break;
    }

    row = table.insertRow(1);

    cell = row.insertCell(-1);
    cell.innerHTML = counter;
    cell = row.insertCell(-1);
    cell.innerHTML = frame.ID;
    cell = row.insertCell(-1);
    cell.innerHTML = frame.DLC;
    cell = row.insertCell(-1);
    cell.innerHTML = frame.DATA.toUpperCase();
    cell = row.insertCell(-1);
    cell.innerHTML = frame.TIMESTAMP;

    counter++;
}

function onLoad(event) {
    initWebSocket();
}