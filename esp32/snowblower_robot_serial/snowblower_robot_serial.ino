#include "BdMotorWithRelay.h"
#include "MdMotorWithController.h"
#include <Ps3Controller.h>
#include <analogWrite.h>
#include <SoftwareSerial.h>

const int ONBOARD_LED = 2;

#define PIN_UP_DOWN_FORWARD 16 // Relay 3
#define PIN_UP_DOWN_REVERSE 17 // Relay 4

#define PIN_SNOW_FALL_FORWARD 15 // Relay 1
#define PIN_SNOW_FALL_REVERSE 14 // Relay 2

int playerLed = 0;

MdMotorWithController snowblower("robot");
BdMotorWithRelay upDown("upDown", PIN_UP_DOWN_FORWARD, PIN_UP_DOWN_REVERSE, 0);

void setup() {

  //Serial.begin(9600); // Serial for debug
  snowblower.init();
  upDown.init();
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("1a:2b:3c:01:01:01");
  //Serial.println("Ready !");
  pinMode(ONBOARD_LED, OUTPUT); 

}

void loop() {
  
  if(!Ps3.isConnected())
    return;
  delay(2000);  
}

void onConnect(){
  playerLed = (playerLed +1)%11;  
 // Serial.print("Player LED value:");
 // Serial.println(playerLed);
  Ps3.setPlayer(playerLed);

  analogWrite(ONBOARD_LED, 255);
  //Serial.println("Connected.");
}

void notify(){

  if( Ps3.event.button_down.cross ){
    snowblower.forward(true);
    //Serial.println("Snowblower -> Forward");      
  } else if( Ps3.event.button_up.cross ){
    snowblower.stop();
    //Serial.println("Snowblower -> STOP");
  }

  if( Ps3.event.button_down.circle ){
    snowblower.reverse(true);
    //Serial.println("Snowblower -> Reverse");
  } else if( Ps3.event.button_up.circle ){
    snowblower.stop();
    //Serial.println("Snowblower -> STOP");
  }

  if( Ps3.event.button_down.left ){
    if(snowblower.isForward()){
      snowblower.forwardLeft();
      //Serial.println("Snowblower -> Forward and left");
    } else if(snowblower.isReverse()){
      snowblower.reverseLeft();
      //Serial.println("Snowblower -> Reverse and left");        
    } else {
      snowblower.fullLeft();
      //Serial.println("Snowblower -> Turn left");      
    }
  } else if( Ps3.event.button_up.left ){        
    if(snowblower.isForward()){
      snowblower.forward(false);
      //Serial.println("Snowblower -> Forward");
    } else if(snowblower.isReverse()){
      snowblower.reverse(false);
      //Serial.println("Snowblower -> Reverse");        
    } else {            
      snowblower.stop();
      //Serial.println("Snowblower -> STOP");    
    }
  }  

   if( Ps3.event.button_down.right ){
    if(snowblower.isForward()){
      snowblower.forwardRight();
      //Serial.println("Snowblower -> Forward and Right");
    } else if(snowblower.isReverse()){
      snowblower.reverseRight();
      //Serial.println("Snowblower -> Reverse and Right");        
    } else {            
      snowblower.fullRight();
      //Serial.println("Snowblower -> Turn right");    
    }
  } else if( Ps3.event.button_up.right ){        
    if(snowblower.isForward()){
      snowblower.forward(false);
      //Serial.println("Snowblower -> Forward");
    } else if(snowblower.isReverse()){
      snowblower.reverse(false);
      //Serial.println("Snowblower -> Reverse");        
    } else {            
      snowblower.stop();
      //Serial.println("Snowblower -> STOP");    
    }
  }  
  
  if( Ps3.event.button_down.l1 ){
      snowblower.fullLeft();
      //Serial.println("Snowblower -> Turn left");
  } else if( Ps3.event.button_up.l1 ){
      snowblower.stop();
      //Serial.println("Snowblower -> STOP");
  }
  
  if( Ps3.event.button_down.r1 ){
      snowblower.fullRight();
      //Serial.println("Snowblower -> Turn right");
  } else if( Ps3.event.button_up.r1 ){
      snowblower.stop();
      //Serial.println("Snowblower -> STOP");
  }  


  if( Ps3.event.button_down.start){
      snowblower.stop();
      //Serial.println("Snowblower -> STOP");
  }
  
  if( Ps3.event.button_down.up ){
      upDown.forward();
      //Serial.println("Snowblower -> UP ");
  } else if( Ps3.event.button_up.up ){
      upDown.stop();
     // Serial.println("Snowblower -> UpDown STOP");
  }

  
  if( Ps3.event.button_down.down ){
      upDown.reverse();
      //Serial.println("Snowblower -> DOWN");
  } else if( Ps3.event.button_up.down ){
      upDown.stop();
      //Serial.println("Snowblower -> UpDown STOP");
  }

  if( Ps3.event.button_down.square || Ps3.event.button_down.l2){
      snowblower.increaseSpeed();
      //Serial.println("Snowblower -> Increase Speed");
  }

  if( Ps3.event.button_down.triangle  || Ps3.event.button_down.r2){
      snowblower.decreaseSpeed();
      //Serial.println("Snowblower -> Decrease Speed");
  } 

  if( Ps3.event.button_down.select ){
      snowblower.resetSpeed();
     // Serial.println("Snowblower -> Reset Speed");
  }

  
}
