#include "MdMotorWithController.h"

//Array, used to store the data of pattern, can be calculated by yourself or obtained from the modulus tool
unsigned char start01[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char front[] = {0x00,0x00,0x00,0x00,0x08,0x0c,0xfe,0xff,0xfe,0x0c,0x08,0x00,0x00,0x00,0x00,0x00};
unsigned char back[] = {0x00,0x00,0x00,0x00,0x10,0x30,0x7f,0xff,0x7f,0x30,0x10,0x00,0x00,0x00,0x00,0x00};
unsigned char left[] = {0x00, 0x00, 0x00, 0x18, 0x3c, 0x7e, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00};
unsigned char right[] = {0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x7e, 0x3c, 0x18, 0x00, 0x00, 0x00};
unsigned char STOP01[] = {0x2E,0x2A,0x3A,0x00,0x02,0x3E,0x02,0x00,0x3E,0x22,0x3E,0x00,0x3E,0x0A,0x0E,0x00};
unsigned char clear[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

#define SCL_Pin  A5  //Set clock pin to A5
#define SDA_Pin  A4  //Set data pin to A4

#define ML_Ctrl 13  //define direction control pin of left motor
#define ML_PWM 11   //define PWM control pin of left motor
#define MR_Ctrl 12  //define direction control pin of right motor
#define MR_PWM 3    //define PWM control pin of right motor

MdMotorWithController robot("robot", ML_Ctrl, MR_Ctrl, ML_PWM, MR_PWM, 2);

char bluetooth_val = 'S'; //save the value of Bluetooth reception

void setup() {

  Serial.begin(9600); // Serial for debug

  pinMode(SCL_Pin,OUTPUT);
  pinMode(SDA_Pin,OUTPUT);
  matrix_display(clear);    //Clear the display
  matrix_display(start01);  //display start pattern

  robot.init();

}

void loop() {
  
  if (Serial.available()){
    bluetooth_val = Serial.read();
    Serial.println(bluetooth_val);
  }
  
  switch (bluetooth_val){
    case 'F': // snowblower forward
      robot.forward();
      matrix_display(front);
      break;
   case 'B': // snowblower backward
      robot.reverse();
      matrix_display(back);
      break;
   case 'L': // snowblower turn left
      robot.fullLeft();
      matrix_display(left);
      break;
   case 'R': // snowblower turn right
      robot.fullRight();  
      matrix_display(right);
      break;  
   case 'M': // Snowblower forward and right
      robot.forwardRight();
      matrix_display(right);
      break;
   case 'N': // Snowblower forward and left
      robot.forwardLeft();
      matrix_display(left);
      break;
   case 'O': // Snowblower reverse and right
      robot.reverseRight();
      matrix_display(right);
      break;
   case 'P': // Snowblower reverse and left
      robot.reverseLeft();
      matrix_display(left);
      break;      
   case 'S': // snowblower stop
      robot.stop();
      matrix_display(STOP01);      
      break;
   case '1': 
      robot.setSpeed(10);  
      bluetooth_val = '0';
      break;
   case '2': 
      robot.setSpeed(40); 
      bluetooth_val = '0'; 
      break;
   case '3': 
      robot.setSpeed(70); 
      bluetooth_val = '0';  
      break;
   case '4': 
      robot.setSpeed(100);
      bluetooth_val = '0';   
      break;
   case '5': 
      robot.setSpeed(130);  
      bluetooth_val = '0'; 
      break;
   case '6': 
      robot.setSpeed(160); 
      bluetooth_val = '0';  
      break;
   case '7':
      robot.setSpeed(190);  
      bluetooth_val = '0'; 
      break;
   case '8': 
      robot.setSpeed(220); 
      bluetooth_val = '0';  
      break;
   case '9': 
      robot.setSpeed(248);
      bluetooth_val = '0';   
      break;
      /*
   case 'G': // Snowblower up  
      upDown.forward();
      break;
   case 'H': // Snowblower down  
      upDown.reverse();
      break;
   case 'D': // Snowfall left
      snowfall.forward();
      break;
   case 'C': // Snowfall right      
      snowfall.reverse();
      break;
   case 'T': // Snowfall stop
      snowfall.stop();
      break;
   case 'V': // Snowblower UpDown stop
      upDown.stop();
      break;*/
  }
   
}

/**************The function of dot matrix****************/
//this function is used for dot matrix display
void matrix_display(unsigned char matrix_value[])
{
  IIC_start();
  IIC_send(0xc0);  //Choose address
  
  for(int i = 0;i < 16;i++) //pattern data has 16 bits
  {
     IIC_send(matrix_value[i]); //data to convey patterns
  }
  IIC_end();   //end to convey data pattern
  
  IIC_start();
  IIC_send(0x8A);  //display control, set pulse width to 4/16
  IIC_end();
}
//The condition starting to transmit data
void IIC_start()
{
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
}
//transmit data
void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)  //Each byte has 8 bits
  {
      digitalWrite(SCL_Pin,LOW);  //pull down clock pin SCL Pin to change the signals of SDA      
      delayMicroseconds(3);
      if(send_data & 0x01)  //set high and low level of SDA_Pin according to 1 or 0 of every bit
      {
        digitalWrite(SDA_Pin,HIGH);
      }
      else
      {
        digitalWrite(SDA_Pin,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(SCL_Pin,HIGH); //pull up clock pin SCL_Pin to stop transmitting data
      delayMicroseconds(3);
      send_data = send_data >> 1;  // Detect bit by bit, so move the data right by one
  }
}
//The sign that data transmission ends
void IIC_end()
{
  digitalWrite(SCL_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
}
/*************the function to run motor**************/
