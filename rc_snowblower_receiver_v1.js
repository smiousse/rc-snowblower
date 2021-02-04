// https://mccormick.cx/news/entries/tiny-core-linux-on-raspberry-pi


const Gpio = require('onoff').Gpio;

const motorLeftForward = new Gpio(2, 'out');
const motorLeftReverse = new Gpio(3, 'out');

const motorRightForward = new Gpio(4, 'out');
const motorRightReverse = new Gpio(17, 'out');

const motorUpDownForward = new Gpio(27, 'out');
const motorUpDownReverse = new Gpio(22, 'out');

const motorSnowFallForward = new Gpio(18, 'out');
const motorSnowFallReverse = new Gpio(23, 'out');

allMotorStop();

var joystick = new (require('joystick'))(0, 3500, 350);
joystick.on('button', onButtonPress);
joystick.on('axis', onButtonPress);


function onButtonPress(buttonInfo){

  //console.log("number = " + buttonInfo.number + ", value = " + buttonInfo.value + ", type = " + buttonInfo.type);

  if(buttonInfo.type == "axis"){
    handleMotorAction(buttonInfo);
  } else if(buttonInfo.number == 0 || buttonInfo.number == 2) {
    handleUpDownAction(buttonInfo);
  } else if(buttonInfo.number == 1 || buttonInfo.number == 3) {
    handleSnowFallAction(buttonInfo);
  } else if(buttonInfo.number == 4 || buttonInfo.number == 5) {
    handleSpeedButton(buttonInfo);
  }


}

function handleMotorAction(buttonInfo){
  if(buttonInfo.number == 0 && buttonInfo.type == "axis" && buttonInfo.value > 1){
    console.log("Going left");

    motorLeftForward.writeSync(0);
    motorRightForward.writeSync(1);

    motorLeftReverse.writeSync(1);
    motorRightReverse.writeSync(0);

  } else if(buttonInfo.number == 0 && buttonInfo.type == "axis" && buttonInfo.value < -1){
    console.log("Going right");

    motorLeftForward.writeSync(1);
    motorRightForward.writeSync(0);

    motorLeftReverse.writeSync(0);
    motorRightReverse.writeSync(1);

  } else if(buttonInfo.number == 1 && buttonInfo.type == "axis" && buttonInfo.value > 1){
    console.log("Going reverse");

    motorLeftForward.writeSync(0);
    motorRightForward.writeSync(0);

    motorLeftReverse.writeSync(1);
    motorRightReverse.writeSync(1);

  } else if(buttonInfo.number == 1 && buttonInfo.type == "axis" && buttonInfo.value < -1){
    console.log("Going forward");

    motorLeftForward.writeSync(1);
    motorRightForward.writeSync(1);

    motorLeftReverse.writeSync(0);
    motorRightReverse.writeSync(0);
    
  } else if((buttonInfo.number == 0 || buttonInfo.number == 1) && buttonInfo.type == "axis" && buttonInfo.value == 0){
    console.log("STOP");
    motorLeftForward.writeSync(0);
    motorRightForward.writeSync(0);

    motorLeftReverse.writeSync(0);
    motorRightReverse.writeSync(0);
  }
}

function allMotorStop(){
  motorLeftForward.writeSync(0);
  motorRightForward.writeSync(0);

  motorLeftReverse.writeSync(0);
  motorRightReverse.writeSync(0);

  motorUpDownForward.writeSync(0);
  motorUpDownReverse.writeSync(0);

  motorSnowFallForward.writeSync(0);
  motorSnowFallReverse.writeSync(0);
}

function handleUpDownAction(buttonInfo){
  if(buttonInfo.number == 0 && buttonInfo.value == 1){
    console.log("UP");

    motorUpDownForward.writeSync(1);
    motorUpDownReverse.writeSync(0);

  } else if(buttonInfo.number == 2 && buttonInfo.value == 1){
    console.log("DOWN");

    motorUpDownForward.writeSync(0);
    motorUpDownReverse.writeSync(1);

  } else if(buttonInfo.value == 0){
    console.log("STOP");

    motorUpDownForward.writeSync(0);
    motorUpDownReverse.writeSync(0);
  }
}

function handleSnowFallAction(buttonInfo){
  if(buttonInfo.number == 1 && buttonInfo.value == 1){
    console.log("SnowFall forward");

    motorSnowFallForward.writeSync(1);
    motorSnowFallReverse.writeSync(0);

  } else if(buttonInfo.number == 3 && buttonInfo.value == 1){
    console.log("SnowFall reverse");

    motorSnowFallForward.writeSync(0);
    motorSnowFallReverse.writeSync(1);

  } else if(buttonInfo.value == 0){
    console.log("SnowFall STOP");

    motorSnowFallForward.writeSync(0);
    motorSnowFallReverse.writeSync(0);
  }
}

function handleSpeedButton(buttonInfo){
  if(buttonInfo.number == 4 && buttonInfo.value == 1){
    console.log("Decrease speed");
  } else if(buttonInfo.number == 5 && buttonInfo.value == 1){
    console.log("Increase speed");
  }
}