/*
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
*/

var logMessages = [];
var maxLogs = 40;
var counter = 1;
var enable = 1;

var canvas;
var context;

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

function initWebSocket() {
  console.log('Trying to open a WebSocket connection...');
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage;
}

function onOpen(event) {
  console.log('Connection opened');
  websocket.send("D\r");
}

function onClose(event) {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
}

function onLoad(event) {
  initWebSocket();
  drawCircle();
  setInterval(getCMD, 10);
}

function drawCircle() {
  canvas = document.getElementById("led");
  context = canvas.getContext("2d");
  context.arc(50, 50, 20, 0, Math.PI * 2, false);
  context.lineWidth = 3;
  context.strokeStyle = "black";
  context.stroke();
  context.fillStyle = "black";
  context.fill();
}

function errorBlink() {
  context.fillStyle = "red";
  context.fill();
  setTimeout(() => {
    context.fillStyle = "black";
    context.fill();
  }, 150);
}

function okBlink() {
  context.fillStyle = "green";
  context.fill();
  setTimeout(() => {
    context.fillStyle = "black";
    context.fill();
  }, 150);
}

function onMessage(event) {
  if (logMessages.length >= maxLogs) {
    logMessages.shift();
  }
  logMessages.push(event.data);
}

function getCMD() {
  if (logMessages.length != 0) {
    console.log(logMessages[0]);

    switch (logMessages[0][0]) {
      case '\r':
        okBlink();
        console.log("OK");
        break;
      case '\x07':
        errorBlink();
        console.log("Error");
        break;

      case "t":
      case "T":
      case "r":
      case "R":
        displayMessages();
        break;

      case "D":
        displaySettings();
        break;

      default:
        console.log("Unrecognized Lawicel Command");
        break;
    }
    logMessages.shift();
  }
}

function displayMessages() {

  if (enable == 1) {
    var table = document.getElementById("CANLog");
    var row = null;
    var cell = null;

    var frame = {
      ID: "",
      RTR: "-",
      DLC: "",
      DATA: "",
      BYTES: ["-", "-", "-", "-", "-", "-", "-", "-"],
      TIMESTAMP: "",
      SYSTIME: ""
    };

    switch (logMessages[0][0]) {
      case "t":
        frame.ID = logMessages[0].substr(1, 3);
        frame.DLC = logMessages[0][4];
        frame.DATA = logMessages[0].substr(5, frame.DLC * 2);
        frame.TIMESTAMP = logMessages[0].substr(5 + frame.DLC * 2, 4);
        frame.SYSTIME = logMessages[0].substr(9 + frame.DLC * 2, 6);
        break;

      case "T":
        frame.ID = logMessages[0].substr(1, 8);
        frame.DLC = logMessages[0][9];
        frame.DATA = logMessages[0].substr(10, frame.DLC * 2);
        frame.TIMESTAMP = logMessages[0].substr(10 + frame.DLC * 2, 4);
        frame.SYSTIME = logMessages[0].substr(14 + frame.DLC * 2, 6);
        break;

      case "r":
        frame.ID = logMessages[0].substr(1, 3);
        frame.RTR = "Yes";
        frame.DLC = logMessages[0][4];
        frame.TIMESTAMP = logMessages[0].substr(5, 4);
        frame.SYSTIME = logMessages[0].substr(9, 6);
        break;

      case "R":
        frame.ID = logMessages[0].substr(1, 8);
        frame.RTR = "Yes";
        frame.DLC = logMessages[0][9];
        frame.TIMESTAMP = logMessages[0].substr(10, 4);
        frame.SYSTIME = logMessages[0].substr(14, 8);
        break;

      default:
        frame.ID = undefined;
        frame.DLC = undefined;
        frame.DATA = undefined;
        frame.TIMESTAMP = undefined;
        frame.SYSTIME = undefined;
        break;
    }

    if (frame.RTR == "-") {

      var position = 0;
      var byte = 0;
      frame.DATA.toUpperCase();

      while (position < (frame.DLC * 2)) {
        frame.BYTES[byte] = frame.DATA.substr(position, 2);
        byte++;
        position = position + 2;
      }
    }

    if (maxLogs < table.rows.length) {
      table.deleteRow(-1);
    }

    row = table.insertRow(1);

    cell = row.insertCell(-1);
    cell.innerHTML = counter;
    cell = row.insertCell(-1);
    cell.innerHTML = frame.ID;
    cell = row.insertCell(-1);
    cell.innerHTML = frame.RTR;
    cell = row.insertCell(-1);
    cell.innerHTML = frame.DLC;
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[0];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[1];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[2];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[3];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[4];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[5];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[6];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.BYTES[7];
    cell = row.insertCell(-1);
    cell.innerHTML = frame.TIMESTAMP.toUpperCase();
    cell = row.insertCell(-1);
    cell.innerHTML = frame.SYSTIME;

    counter++;
  }
}

function displaySettings() {
  var cell = document.getElementById("Sys_Auto");
  var temp = logMessages[0][1];
  var output = "";
  switch (temp) {
    case '0':
      output = "Deactivated";
      break;
    case '1':
      output = "Normal";
      break;
    case '2':
      output = "Listen Only";
      break;
    default:
      output = "Error";
      break;
  }
  cell.innerHTML = output;

  cell = document.getElementById("Sys_CBaud");
  temp = logMessages[0][3];
  switch (temp) {
    case '0':
      output = "10";
      break;

    case '1':
      output = "20";
      break;

    case '2':
      output = "50";
      break;

    case '3':
      output = "100";
      break;

    case '4':
      output = "125";
      break;

    case '5':
      output = "250";
      break;

    case '6':
      output = "500";
      break;

    case '7':
      output = "800";
      break;

    case '8':
      output = "1000";
      break;

    default:
      output = "Error";
      break;
  }
  cell.innerHTML = output;

  cell = document.getElementById("Sys_TStmp");
  temp = logMessages[0][4];
  switch (temp) {
    case '0':
      output = "Deactivated";
      break;
    case '1':
      output = "Activated";
      break;
    default:
      output = "Error";
      break;
  }
  cell.innerHTML = output;

  cell = document.getElementById("Sys_CChannel");
  temp = logMessages[0][5];
  switch (temp) {
    case '0':
      output = "Closed";
      break;
    case '1':
      output = "Normal";
      break;
    case '2':
      output = "Listen Only";
      break;
    default:
      output = "Error";
      break;
  }
  cell.innerHTML = output;
}

function sendCMD() {
  var input = document.getElementById("LawicelCMD").value;
  if (input != "") {
    input += '\r';
    console.log(input);
    websocket.send(input);
    websocket.send('D\r');
    document.getElementById("LawicelCMD").value = "";
  }
}

function sendFrame() {
  if (document.getElementById("FRAME_ID").value != "") {
    var input = "";
    var extInput = document.getElementById("FRAME_EXT").checked;
    var rtrInput = document.getElementById("FRAME_RTR").checked;
    if (extInput == true) {
      if (rtrInput == true) {
        input += 'R';
      } else {
        input += 'T';
      }
    } else {
      if (rtrInput == true) {
        input += 'r';
      } else {
        input += 't';
      }
    }

    input += document.getElementById("FRAME_ID").value;
    var frameLength = document.getElementById("FRAME_DLC").value;
    input += frameLength;

    var frameData = [
      document.getElementById("FRAME_DATA0").value,
      document.getElementById("FRAME_DATA1").value,
      document.getElementById("FRAME_DATA2").value,
      document.getElementById("FRAME_DATA3").value,
      document.getElementById("FRAME_DATA4").value,
      document.getElementById("FRAME_DATA5").value,
      document.getElementById("FRAME_DATA6").value,
      document.getElementById("FRAME_DATA7").value
    ]

    for (count = 0; count < frameLength; count++) {
      input += frameData[count];
    }

    input += '\r';
    console.log(input);
    websocket.send(input);
    websocket.send('D\r');
    document.getElementById("LawicelCMD").value = "";
  }
}

function toggle() {
  enable = !enable;
  if (enable) {
    document.getElementById("PauseBtn").innerHTML = "Pause";
    console.log("Display Resumed");
  } else {
    document.getElementById("PauseBtn").innerHTML = "Play";
    console.log("Display Paused");
  }
}