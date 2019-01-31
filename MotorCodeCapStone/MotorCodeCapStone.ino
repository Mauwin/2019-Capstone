// Motor
    // Motor data sheet: http://support.robotis.com/en/product/actuator/dynamixel/ax_series/dxl_ax_actuator.htm
    // RS 485 data sheet: https://www.sparkfun.com/datasheets/Components/General/sp3485CN-LTR.pdf
    // level converter data sheet: https://cdn.sparkfun.com/datasheets/BreakoutBoards/BSS138.pdf
#include "DynamixelControl.h"
#include <Servo.h>
Servo myservo;
DynamixelControl3 DmC;
  byte Left = 40;
  byte Right = 20;
  byte Front = 10;
  byte Back = 30;

  int rate = 700;
  
  void setup(){  
  //DmC.setID(1,40); this was used to program the motors 
  DmC.begin(1000000, 6);
  delay(10);
  DmC.enableTorque(Right, ON);
  DmC.enableTorque(Left, ON);
  DmC.enableTorque(Front, ON);
  DmC.enableTorque(Back, ON);
  DmC.freeRotation(Right, true);
  DmC.freeRotation(Left, true);
  DmC.freeRotation(Front, true);
  DmC.freeRotation(Back, true);
  DmC.turnVelocity(Right, CW, 0);
  DmC.turnVelocity(Left, CCW, 0);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
  DmC.writeLED(Right, OFF);
  DmC.writeLED(Left, OFF);
  DmC.writeLED(Front, OFF);
  DmC.writeLED(Back, OFF);
  myservo.attach(23);// flag raising 


 // test run
 myservo.write(55);
 driveForward();
 delay(2100);
 halt();
 driveRight();
 delay(1000);
 halt();
 delay(100);
 /*DmC.turnVelocity(Right, CCW, 350);
 DmC.turnVelocity(Left, CCW, 350);
 DmC.turnVelocity(Front, CCW, 350);
 DmC.turnVelocity(Back, CCW, 350);*/
 delay(20);
 halt();
 driveForward();
 delay(1800);
 halt();
 driveLeft();
 delay(1600);
 halt();
 driveBack();
 delay(2200);
 halt();
 driveRight();
 delay(1700);
 halt();
 myservo.write(145);
  }
  

// stop all movement
void halt(){
  DmC.turnVelocity(Right, CW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CW, 0);
}
// drive forward constantly
void driveForward() {
  DmC.turnVelocity(Right, CW, rate);
  DmC.turnVelocity(Left, CCW, rate);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// drive back constantly
void driveBack() { 
  DmC.turnVelocity(Right, CCW, rate);
  DmC.turnVelocity(Left, CW, rate);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// drive left constantly
void driveLeft(){
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CW, rate);
  DmC.turnVelocity(Back, CCW, rate);
}
// drive right constantly
void driveRight(){
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CCW, rate);
  DmC.turnVelocity(Back, CW, rate);
}

// drive forward a given distance
void driveForwardDist(int dist) {
  dist = ((dist / 5) * 3); // convets distance given to loops needed
  for ( int i = 0; i < dist; i++) {
  DmC.turnVelocity(Right, CW, 1023);
  DmC.turnVelocity(Left, CCW, 1023);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
  } // when done stop
  DmC.turnVelocity(Right, CW, 0);
  DmC.turnVelocity(Left, CCW, 0);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// drive backward a given distance
void driveBackDist(int dist) {
  dist = ((dist / 5) * 3); // convets distance given to loops needed
  for ( int i = 0; i < dist; i++) {
  DmC.turnVelocity(Right, CCW, 1023);
  DmC.turnVelocity(Left, CW, 1023);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
  } // when done stop
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// turn right for a given angle
void turnRight(int angle) {
  angle = (angle / 90) * 6; // convert to the proper time
  for (int i = 0; i < angle; i++) {
  DmC.turnVelocity(Right, CCW, 1023);
  DmC.turnVelocity(Left, CCW, 1023);
  DmC.turnVelocity(Front, CCW, 1023);
  DmC.turnVelocity(Back, CCW, 1023);
  } // when done stop
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CCW, 0);
  DmC.turnVelocity(Front, CCW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// turn left for a given angle
void turnLeft(int angle) {
    angle = (angle / 90) * 6; // convert to the proper time
    for (int i = 0; i < angle; i++) {
    DmC.turnVelocity(Right, CW, 1023);
    DmC.turnVelocity(Left, CW, 1023);
    DmC.turnVelocity(Front, CW, 1023);
    DmC.turnVelocity(Back, CW, 1023);
    } // when done stop
    DmC.turnVelocity(Right, CW, 0);
    DmC.turnVelocity(Left, CW, 0);
    DmC.turnVelocity(Front, CW, 0);
    DmC.turnVelocity(Back, CW, 0);
}
void loop(){
 

}

