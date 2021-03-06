var http = require('http');
const url = require('url');
const debug = true;

const BUTTON_A = "button_1_1";
const BUTTON_B = "button_2_1";
const BUTTON_X = "button_0_1";
const BUTTON_Y = "button_3_1";

const BUTTON_A_RELEASE = "button_1_0";
const BUTTON_B_RELEASE = "button_2_0";
const BUTTON_X_RELEASE = "button_0_0";
const BUTTON_Y_RELEASE = "button_3_0";

const BUTTON_R = "button_5_1";
const BUTTON_L = "button_4_1";
const BUTTON_R_RELEASE = "button_5_0";
const BUTTON_L_RELEASE = "button_4_0";

const BUTTON_SELECT = "button_8_1";
const BUTTON_START = "button_9_1";

const AXIS_LEFT = "axis_0_-32767";
const AXIS_RIGHT = "axis_0_32767";
const AXIS_TOP = "axis_1_-32767";
const AXIS_BOTTOM = "axis_1_32767";

const AXIS_LEFT_RIGHT_RELEASE = "axis_0_0";
const AXIS_TOP_BOTTOM_RELEASE = "axis_1_0";

const ACTION_SB_FORWARD = "F";
const ACTION_SB_BACKWARD = "B";
const ACTION_SB_LEFT = "L";
const ACTION_SB_RIGHT = "R";
const ACTION_SB_UP = "G";
const ACTION_SB_DOWN = "H";
const ACTION_SB_FORWARD_RIGHT = "M";
const ACTION_SB_FORWARD_LEFT = "N";
const ACTION_SB_BACKWARD_RIGHT = "O";
const ACTION_SB_BACKWARD_LEFT = "P";
const ACTION_SF_LEFT = "D";
const ACTION_SF_RIGHT = "C";
const ACTION_SPEED_UP = "Y";
const ACTION_SPEED_DOWN = "X";
const ACTION_SPEED_RESET = "U";
const ACTION_SB_STOP = "S";
const ACTION_SF_STOP = "T";
const ACTION_UD_STOP = "V";

var buttonMapping = {};
buttonMapping[BUTTON_X] = ACTION_SB_FORWARD;
buttonMapping[BUTTON_B] = ACTION_SB_BACKWARD;
buttonMapping[BUTTON_Y] = ACTION_SB_LEFT;
buttonMapping[BUTTON_A] = ACTION_SB_RIGHT;
buttonMapping[BUTTON_R] = ACTION_SB_BACKWARD_RIGHT;
buttonMapping[BUTTON_L] = ACTION_SB_BACKWARD_LEFT;

buttonMapping[BUTTON_X_RELEASE] = ACTION_SB_STOP;
buttonMapping[BUTTON_B_RELEASE] = ACTION_SB_STOP;
buttonMapping[BUTTON_Y_RELEASE] = ACTION_SB_STOP;
buttonMapping[BUTTON_A_RELEASE] = ACTION_SB_STOP;
buttonMapping[BUTTON_R_RELEASE] = ACTION_SB_STOP;
buttonMapping[BUTTON_L_RELEASE] = ACTION_SB_STOP;

buttonMapping[AXIS_LEFT] = ACTION_SF_LEFT;
buttonMapping[AXIS_RIGHT] = ACTION_SF_RIGHT;
buttonMapping[AXIS_TOP] = ACTION_SB_UP;
buttonMapping[AXIS_BOTTOM] = ACTION_SB_DOWN;

buttonMapping[AXIS_LEFT_RIGHT_RELEASE] = ACTION_SF_STOP;
buttonMapping[AXIS_TOP_BOTTOM_RELEASE] = ACTION_UD_STOP;

buttonMapping[BUTTON_SELECT] = ACTION_SPEED_UP;
buttonMapping[BUTTON_START] = ACTION_SPEED_DOWN;
//buttonMapping[BUTTON_SELECT] = ACTION_SPEED_RESET;

var urlPathMapping = {};
urlPathMapping["/snowblower/action/move_forward"] = ACTION_SB_FORWARD;
urlPathMapping["/snowblower/action/move_backward"] = ACTION_SB_BACKWARD;
urlPathMapping["/snowblower/action/move_left"] = ACTION_SB_LEFT;
urlPathMapping["/snowblower/action/move_right"] = ACTION_SB_RIGHT;
urlPathMapping["/snowblower/action/sf_left"] = ACTION_SF_LEFT;
urlPathMapping["/snowblower/action/sf_right"] = ACTION_SF_RIGHT;
urlPathMapping["/snowblower/action/sb_up"] = ACTION_SB_UP;
urlPathMapping["/snowblower/action/sb_down"] = ACTION_SB_DOWN;
urlPathMapping["/snowblower/action/speed_up"] = ACTION_SPEED_UP;
urlPathMapping["/snowblower/action/speed_down"] = ACTION_SPEED_DOWN;
urlPathMapping["/snowblower/action/speed_reset"] = ACTION_SPEED_RESET;

var joystick = new (require('joystick'))(0, 3500, 350);
joystick.on('button', onButtonPress);
joystick.on('axis', onButtonPress);


// Init rc communication stuff
const nrf24=require("nrf24"); // Load de module
// Init the radio
var rf24= new nrf24.nRF24(22, 0);

console.log("begin->",rf24.begin(true));
// Configure the radio
rf24.config({
  PALevel: nrf24.RF24_PA_LOW
});

http.createServer(function (req, res) { 
  dispatch(req, res);  
}).listen(8080);

function dispatch(req, res){
  if(debug){
    console.log('req.url = ' + req.url);
  }
  const queryObject = url.parse(req.url,true).query;
  const pathObject = url.parse(req.url,true).pathname;

  if(queryObject.key != 'Up6KjbnEV4Hgfo75YM393QdQsK3Z0aTNBz0DoirrW'){
    res.writeHead(403, {'Content-Type': 'text/html'});
    res.end();
  } else {
    sendAction(urlPathMapping[pathObject]);    
  }
}

function sendAction(action){
  if(action){
    console.log("[sendAction] action = " + action);

    rf24.useWritePipe("0x65646f4e31",true); // Select the pipe address to write with Autock
    rf24.write(Buffer.from(action));
  }
}

function onButtonPress(buttonInfo){
  var buttonMappingkey = buttonInfo.type + '_' + buttonInfo.number + '_' + buttonInfo.value;
  if(debug){
    console.log("[onButtonPress] buttonMappingkey = " + buttonMappingkey);
  }
  sendAction(buttonMapping[buttonMappingkey]);
}