/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
* @addtogroup js
* @{
* @file       ws.js
* @brief      JavaScript for Websocket Webpage (ws.html)
* @}
***************************************************************************************************/

/* CONSTANTS **************************************************************************************/
var maxLogs = 40;   /**< Maximum Amount of Displayed and Buffered Messages */
var counter = 1;    /**< Table Position */
var enable = 1;     /**< Enables the display of Frames */
var gateway = `ws://${window.location.hostname}/ws`;     /**< GateWay for WebSocket */

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

var logMessages = [];   /**< Lawicel Message Buffer */
var canvas;             /**< Var for the LED Indicator */
var context;            /**< Context of the LED Indicator */
var websocket;          /**< Instance of WebSocket */

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/
/*****************************  WebSocket and WebPage Setup Methodes ******************************/
/**************************************************************************************************/

/**
*   Function runs when window is loaded on browser
*/
function onLoad(event) {
    initWebSocket();            /**< Init. WebSocket */
    drawCircle();               /**< Draws Circle as an LED Indicator */
    setInterval(getCMD, 10);    /**< Process a message every 10ms */
}

/**************************************************************************************************/

/**
*   Initialize WebSocket
*/
function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

/**************************************************************************************************/

/**
*   Function runs when Websocket is connected
*/
function onOpen(event) {
    console.log('Connection opened');
    websocket.send("D\r");  /**< Request Lawicel Status */
}

/**************************************************************************************************/

/**
*   Function runs when Websocket is disconnected
*/
function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000); /**< Two Seconds timeout for reconnecting Websocket*/
}

/**************************************************************************************************/

/**
*   Websocket Message Handler. Pushes received messages to queue
*   @param event     Message Received by Websocket (event.data)
*/
function onMessage(event) {
    if (logMessages.length >= maxLogs) {
        logMessages.shift();
    }
    logMessages.push(event.data);
}


/**************************************************************************************************/
/****************************** LED Indicator Methodes ********************************************/
/**************************************************************************************************/

/**
*   Draws Circle as an LED Indicator
*/
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

/**************************************************************************************************/

/**
*   Blink Indicator RED for 150ms when a command is not valid
*/
function errorBlink() {
    context.fillStyle = "red";
    context.fill();
    setTimeout(() => {
        context.fillStyle = "black";
        context.fill();
    }, 150);
}

/**************************************************************************************************/

/**
*   Blink Indicator GREEN for 150ms when a command is accepted
*/
function okBlink() {
    context.fillStyle = "green";
    context.fill();
    setTimeout(() => {
        context.fillStyle = "black";
        context.fill();
    }, 150);
}


/**************************************************************************************************/
/****************************** Receive Lawicel Message *******************************************/
/**************************************************************************************************/

/**
*   Decodes Lawicel Command
*/
function getCMD() {
    if ((0 != logMessages.length) && (websocket.readyState === WebSocket.OPEN)) {
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

/**************************************************************************************************/

/**
*   Decodes a PID Response from OBD Bus
*/
function decodePIDResponse(frame) {
    console.log(frame.ID.toUpperCase());
    console.log('PID:' + frame.BYTES[2].toUpperCase());
    if (0x0D == parseInt(frame.BYTES[2], 16)) {
        console.log('Speed: ' + parseInt(frame.BYTES[3], 16) + ' km/h')
    }
    else if (0xA6 == parseInt(frame.BYTES[2], 16)) {
        var sum = 0;

        sum += (parseInt(frame.BYTES[3], 16) * (2 ^ 24));
        sum += (parseInt(frame.BYTES[4], 16) * (2 ^ 16));
        sum += (parseInt(frame.BYTES[5], 16) * (2 ^ 8));
        sum += (parseInt(frame.BYTES[6], 16) * (2 ^ 1));

        console.log('Odometer: ' + sum + ' km')

    }
    else {
        console.log('Data0: ' + frame.BYTES[3] + 'h');
        console.log('Data1: ' + frame.BYTES[4] + 'h');
        console.log('Data2: ' + frame.BYTES[5] + 'h');
        console.log('Data3: ' + frame.BYTES[6] + 'h');
    }
}


/**************************************************************************************************/
/********************************* Send Lawicel Message *******************************************/
/**************************************************************************************************/

/**
*   Sends Lawicel Command found in the input text box
*/
function sendCMD() {
    var input = document.getElementById("LawicelCMD").value;
    if ("" != input) {
        input += '\r';
        console.log(input);
        websocket.send(input);
        websocket.send('D\r');
        document.getElementById("LawicelCMD").value = "";
    }
}

/**************************************************************************************************/

/**
*   Sends CAN Frame described in the Data Table
*/
function sendFrame() {
    if (document.getElementById("FRAME_ID").value != "") {
        var input = "";
        var extInput = document.getElementById("FRAME_EXT").checked;
        var rtrInput = document.getElementById("FRAME_RTR").checked;
        if (true == extInput) {
            if (true == rtrInput) {
                input += 'R';
            } else {
                input += 'T';
            }
        } else {
            if (true == rtrInput) {
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


/**************************************************************************************************/
/****************************** Display Message Information ***************************************/
/**************************************************************************************************/

/**
*   Displays Received CAN Frames in a Table
*/
function displayMessages() {

    if (1 == enable) {
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

        if ("-" == frame.RTR) {

            var position = 0;
            var byte = 0;
            frame.DATA.toUpperCase();

            while (position < (frame.DLC * 2)) {
                frame.BYTES[byte] = frame.DATA.substr(position, 2);
                byte++;
                position = position + 2;
            }
        }

        if (0x7E8 <= parseInt(frame.ID, 16) && parseInt(frame.ID, 16) <= 0x7EF) {
            decodePIDResponse(frame);
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

/**************************************************************************************************/

/**
*   Displays System Data
*/
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

/**************************************************************************************************/

/**
*   Toggles Pause for the display of Frames
*/
function toggle() {
    enable = !enable;
    if (1 == enable) {
        document.getElementById("PauseBtn").innerHTML = "Pause";
        console.log("Display Resumed");
    } else {
        document.getElementById("PauseBtn").innerHTML = "Play";
        console.log("Display Paused");
    }
}