// Motor
    // Motor data sheet: http://support.robotis.com/en/product/actuator/dynamixel/ax_series/dxl_ax_actuator.htm
    // RS 485 data sheet: https://www.sparkfun.com/datasheets/Components/General/sp3485CN-LTR.pdf
    // level converter data sheet: https://cdn.sparkfun.com/datasheets/BreakoutBoards/BSS138.pdf
#include "DynamixelControl.h"
DynamixelControl3 DmC;
byte FrontLeft = what ever;
byte FrontRight = what ever;
byte BackLeft = what ever;
byte BackRight = what ever;
// Motor setup
  DmC.begin(200000, 6);
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
  DmC.writeLED(Right, ON);
  DmC.writeLED(Left, ON);
  DmC.writeLED(Front, ON);
  DmC.writeLED(Back, ON);
// drive forward constantly
void driveForward() {
  DmC.turnVelocity(Right, CW, 1023);
  DmC.turnVelocity(Left, CCW, 1023);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// drive back constantly
void driveBack() { 
  DmC.turnVelocity(Right, CCW, 1023);
  DmC.turnVelocity(Left, CW, 1023);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
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
// stops the robots movement
void stopper(){
  DmC.turnVelocity(Right, CW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CW, 0);
}
// drives constantly at 1/3 max speed
void driveSlow(){
  DmC.turnVelocity(Right, CW, 400);
    DmC.turnVelocity(Left, CCW, 400);
    DmC.turnVelocity(Front, CW, 0);
    DmC.turnVelocity(Back, CW, 0);
}
// drive each wheel for given input forward
void driveCustom(int right, int left){
  DmC.turnVelocity(Right, CW, right);
  DmC.turnVelocity(Left, CCW, left);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}

