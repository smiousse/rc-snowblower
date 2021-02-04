const simulate = true;
const debug = true;

if(!simulate){
  const Gpio = require('onoff').Gpio;
}

const BUTTON_A = "button_1_1";
const BUTTON_B = "button_2_1";
const BUTTON_X = "button_0_1";
const BUTTON_Y = "button_3_1";
const BUTTON_R = "button_5_1";
const BUTTON_L = "button_4_1";
const BUTTON_SELECT = "button_8_1";
const BUTTON_START = "button_9_1";

const AXIS_LEFT = "axis_0_-32767";
const AXIS_RIGHT = "axis_0_32767";
const AXIS_TOP = "axis_1_-32767";
const AXIS_BOTTOM = "axis_1_32767";

const ACTION_SB_FORWARD = "action_snowblower_forward";
const ACTION_SB_BACKWARD = "action_snowblower_backward";
const ACTION_SB_LEFT = "action_snowblower_left";
const ACTION_SB_RIGHT = "action_snowblower_right";
const ACTION_SB_UP = "action_snowblower_up";
const ACTION_SB_DOWN = "action_snowblower_down";
const ACTION_SF_LEFT = "action_snowfall_left";
const ACTION_SF_RIGHT = "action_snowfall_right";

var buttonMapping = {};
buttonMapping[BUTTON_X] = ACTION_SB_FORWARD;
buttonMapping[BUTTON_B] = ACTION_SB_BACKWARD;
buttonMapping[BUTTON_Y] = ACTION_SB_LEFT;
buttonMapping[BUTTON_A] = ACTION_SB_RIGHT;
buttonMapping[AXIS_LEFT] = ACTION_SF_LEFT;
buttonMapping[AXIS_RIGHT] = ACTION_SF_RIGHT;
buttonMapping[AXIS_TOP] = ACTION_SB_UP;
buttonMapping[AXIS_BOTTOM] = ACTION_SB_DOWN;


var snowBlowerDirection = new MultiDirectionalMotor('snowBlowerDirection', 2, 3, 4, 17);
var snowBlowerUpDown = new BiDirectionalMotor('snowblowerUpDown', 27, 22);
var snowFallLeftRight = new MultiDirectionalMotor('snowFallLeftRight', 18, 23);

allMotorStop();

var joystick = new (require('joystick'))(0, 3500, 350);
joystick.on('button', onButtonPress);
joystick.on('axis', onButtonPress);


function onButtonPress(buttonInfo){

  var buttonMappingkey = buttonInfo.type + '_' + buttonInfo.number + '_' + buttonInfo.value;

  if(debug){
    console.log("[onButtonPress] buttonMappingkey = " + buttonMappingkey);
  }

  var action = buttonMapping[buttonMappingkey];

  if(action){
    if(debug){
      console.log("[onButtonPress] action = " + action);
    }
  
    switch (action) {
      case ACTION_SB_FORWARD:
        snowBlowerDirection.forward();
        break;
      case ACTION_SB_BACKWARD:
        snowBlowerDirection.reverse();
        break;
      case ACTION_SB_LEFT:
        snowBlowerDirection.left();
        break;
      case ACTION_SB_RIGHT:
        snowBlowerDirection.right();
        break;
      case ACTION_SB_UP:
        snowBlowerUpDown.forward();
        break;
      case ACTION_SB_DOWN:
        snowBlowerUpDown.reverse();
        break;
      case ACTION_SF_LEFT:
        snowFallLeftRight.forward();
        break;
      case ACTION_SF_RIGHT:
        snowFallLeftRight.reverse();
        break;
    
      default:
        allMotorStop();
        break;
    }
  } else {
    allMotorStop();
  }

}

function allMotorStop(){
  snowBlowerDirection.stop();
  snowBlowerUpDown.stop();
  snowFallLeftRight.stop();
}

function MultiDirectionalMotor(name, motorLeftForwardPin, motorLeftReversePin, motorRightForwardPin, motorRightReversePin) {

  this.name = name;
  if(!simulate){
    this.motorLeftForward = new Gpio(motorLeftForwardPin, 'out');
    this.motorLeftReverse = new Gpio(motorLeftReversePin, 'out');
    this.motorRightForward = new Gpio(motorRightForwardPin, 'out');
    this.motorRightReverse = new Gpio(motorRightReversePin, 'out');
  }


  this.forward = function () {
    if(debug){
      console.log("[" + name + "] go forward");
    }
    if(!simulate){
      motorLeftForward.writeSync(1);
      motorRightForward.writeSync(1);

      motorLeftReverse.writeSync(0);
      motorRightReverse.writeSync(0);
    }
  }

  this.reverse = function() {
    if(debug){
      console.log("[" + name + "] go reverse");
    }

    if(!simulate){
      motorLeftForward.writeSync(0);
      motorRightForward.writeSync(0);

      motorLeftReverse.writeSync(1);
      motorRightReverse.writeSync(1);
    }
  }

  this.left = function() {
    if(debug){
      console.log("[" + name + "] go left");
    }
    if(!simulate){
      motorLeftForward.writeSync(1);
      motorRightForward.writeSync(0);

      motorLeftReverse.writeSync(0);
      motorRightReverse.writeSync(1);
    }
  }

  this.right = function() {
    if(debug){
      console.log("[" + name + "] go right");
    }
    if(!simulate){
      motorLeftForward.writeSync(1);
      motorRightForward.writeSync(0);

      motorLeftReverse.writeSync(0);
      motorRightReverse.writeSync(1);
    }
  }

  this.stop = function() {
    if(debug){
      console.log("[" + name + "] stop");
    }
    if(!simulate){
      motorLeftForward.writeSync(0);
      motorRightForward.writeSync(0);
      motorLeftReverse.writeSync(0);
      motorRightReverse.writeSync(0);
    }
  }

}

function BiDirectionalMotor(name, motorForwardPin, motorReversePin) {

  this.name = name;
  if(!simulate){
    this.motorForward = new Gpio(motorForwardPin, 'out');
    this.motorReverse = new Gpio(motorReversePin, 'out');
  }


  this.forward = function () {
    if(debug){
      console.log("[" + name + "] go forward");
    }

    if(!simulate){
      motorForward.writeSync(1);
      motorReverse.writeSync(0);
    }
  }

  this.reverse = function() {
    if(debug){
      console.log("[" + name + "] go reverse");
    }
    if(!simulate){
      motorForward.writeSync(0);
      motorReverse.writeSync(1);
    }
  }

  this.stop = function() {
    if(debug){
      console.log("[" + name + "] stop");
    }

    if(!simulate){
      motorForward.writeSync(0);
      motorReverse.writeSync(0);
    }
  }
}