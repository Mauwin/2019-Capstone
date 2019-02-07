// Motor
    // Motor data sheet: http://support.robotis.com/en/product/actuator/dynamixel/ax_series/dxl_ax_actuator.htm
    // RS 485 data sheet: https://www.sparkfun.com/datasheets/Components/General/sp3485CN-LTR.pdf
    // level converter data sheet: https://cdn.sparkfun.com/datasheets/BreakoutBoards/BSS138.pdf
#include "DynamixelControl.h"
#include <Servo.h>

// sensors
#include <Wire.h>
#include <LIDARLite.h>

#define front A16
#define back A14
#define left A18
#define right A20

int sensorPins[] = {2,3,4,5}; // Array of pins connected to the sensor Power Enable lines
unsigned char addresses[] = {0x70,0x68,0x64, 0x72};

LIDARLite myLidarLite;

Servo myservo;
DynamixelControl3 DmC;
  byte Left = 40;
  byte Right = 20;
  byte Front = 10;
  byte Back = 30;

  int rate = 550;
  
  void setup(){  

  

  // sensor set up
  Serial.begin(9600);
  myLidarLite.begin();
  myLidarLite.changeAddressMultiPwrEn(4,sensorPins,addresses,false);

    
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
 //myservo.write(55);
 //driveForward();
 /*delay(2100);
 halt();
 driveRight();
 delay(1000);
 halt();
 delay(100);
 /*DmC.turnVelocity(Right, CCW, 350);
 DmC.turnVelocity(Left, CCW, 350);
 DmC.turnVelocity(Front, CCW, 350);
 DmC.turnVelocity(Back, CCW, 350);*/
 /*delay(20);
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
 myservo.write(145);*/
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
  DmC.turnVelocity(Right, CW, rate);
  DmC.turnVelocity(Left, CCW, rate);
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
  DmC.turnVelocity(Right, CCW, rate);
  DmC.turnVelocity(Left, CW, rate);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
  } // when done stop
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// Drive Right a given distance
void driveRightDist(int dist) {
  dist = ((dist / 5) * 3); // convets distance given to loops needed
  for ( int i = 0; i < dist; i++) {
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CCW, rate);
  DmC.turnVelocity(Back, CW, rate);
  } // when done stop
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CW, 0);
  DmC.turnVelocity(Back, CCW, 0);
}
// Drive left a given distance
void driveLeftDist(int dist) {
  dist = ((dist / 5) * 3); // convets distance given to loops needed
  for ( int i = 0; i < dist; i++) {
  DmC.turnVelocity(Right, CCW, 0);
  DmC.turnVelocity(Left, CW, 0);
  DmC.turnVelocity(Front, CW, rate);
  DmC.turnVelocity(Back, CCW, rate);
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
  DmC.turnVelocity(Right, CCW, rate);
  DmC.turnVelocity(Left, CCW, rate);
  DmC.turnVelocity(Front, CCW, rate);
  DmC.turnVelocity(Back, CCW, rate);
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
    DmC.turnVelocity(Right, CW, rate);
    DmC.turnVelocity(Left, CW, rate);
    DmC.turnVelocity(Front, CW, rate);
    DmC.turnVelocity(Back, CW, rate);
    } // when done stop
    DmC.turnVelocity(Right, CW, 0);
    DmC.turnVelocity(Left, CW, 0);
    DmC.turnVelocity(Front, CW, 0);
    DmC.turnVelocity(Back, CW, 0);
}

// Sharp IR
float ShortF(){
  float val = analogRead(front);
  val = ((6255.4* pow(val,-1.102)));
  return val;
}
float ShortB(){
  float val = analogRead(back);
  val = ((6255.4* pow(val,-1.102)));
  return val;
}
float ShortL(){
  float val = analogRead(left);
  val = ((6255.4* pow(val,-1.102)));
  return val;
}
float ShortR(){
  float val = analogRead(right);
  val = ((6255.4* pow(val,-1.102)));
  return val;
}

// Garmin 
float GarminFL(){
  float val = (myLidarLite.distance(true,true,0x68));
  return val;
}
float GarminFR(){
  float val = (myLidarLite.distance(true,true,0x72));
  return val;
}
float GarminBL(){
  float val = (myLidarLite.distance(true,true,0x64));
  return val;
}
float GarminBR(){
  float val = (myLidarLite.distance(true,true,0x70));
  return val;
}

// Main Loop
void loop(){
FindCenter();
FindEdge(1);
driveForwardDist(10);
FindEdge(2);
driveLeftDist(10);
FindEdge(3);
driveBackDist(10);
FindEdge(4);
GoToPoint(64,116,1);
GoToPoint(115,76,2);
GoToPoint(68,117,3);
GoToPoint(112,65,4);
GoToPoint(64,116,1);
GoToPoint(115,76,2);
GoToPoint(68,117,3);
GoToPoint(112,65,4);
rate = 0;
GetLoc();
}

// Movement break down
void Allign(){
  rate = 100;
  bool alligned = false;
  while(alligned == false){
    float x = GarminBR();
    float y = GarminBL();
    Serial.print("X: ");
    Serial.println(x);
    Serial.print("Y: ");
    Serial.println(y);
    turnRight(1);
    float x1 = GarminBR();
    float y1 = GarminBL();
    Serial.print("X1: ");
    Serial.println(x1);
    Serial.print("Y1: ");
    Serial.println(y1);
    turnLeft(2);
    float x2 = GarminBR();
    float y2 = GarminBL();
    Serial.print("X2: ");
    Serial.println(x2);
    Serial.print("Y2: ");
    Serial.println(y2);
    if(x < x1 && x < x2){
      turnRight(1);
      alligned = true;
    }
    else if(x1 < x && x1 < x2){
      turnRight(2);
    }
  }
  rate = 550;
}
void FindCenter(){
  while (ShortF() > 20){
  Serial.println(ShortF());
  driveForward();
  }
  halt();
}
void FindEdge(int side){
  // side 1 = front
  // side 2 = left
  // side 3 = back
  // side 4 = right
  if (side == 1){
    driveRight();
    while (ShortF() < 20){
      Serial.println(ShortF());
    }
    halt();
    driveRightDist(4);
    halt();
  }
  if (side == 2){
    driveForward();
    while (ShortL() < 20){
      Serial.println(ShortF());
    }
    halt();
    driveForwardDist(4);
    halt();
  }
  if (side == 3){
    driveLeft();
    while (ShortB() < 20){
      Serial.println(ShortF());
    }
    halt();
    driveLeftDist(3);
    halt();
  }
  if (side == 4){
    driveBack();
    while (ShortR() < 20){
      Serial.println(ShortF());
    }
    halt();
  }

  halt();
}
void GetLoc(){
  // 10 cm offest to center
  float x = GarminBL() + 10; // reference x
  float x1 = (GarminFR() + 10);
  float y = (GarminFL() + 10);
  float y1 = GarminBR() + 10; // reference Y
  Serial.print("Fl, X: ");
  Serial.println(x);
  Serial.print("Fl, X1: ");
  Serial.println(x1);
  Serial.print("Fl, Y: ");
  Serial.println(y);
  Serial.print("Fl, Y1: ");
  Serial.println(y1);
  float xavg = (x + x1)/2;
  float yavg = (y + y1)/2;
  float xdist = xavg * 2;
  float ydist = yavg * 2;
  Serial.print("X avrg: ");
  Serial.println(xavg);
  Serial.print("Y Avrg: ");
  Serial.println(yavg);
  Serial.print("X Dist: ");
  Serial.println(xdist);
  Serial.print("Y Dist: ");
  Serial.println(ydist);
  //return(xavg, yavg);
}
void GoToPoint(float xx, float yy, int zone){
  if (zone == 1){
    float x = GarminBL() + 10; // reference x
    float y1 = GarminBR() + 10; // reference Y
    driveBack();
    while (x > xx || y1 > yy){
      x = GarminBL() + 10; // reference x
      y1 = GarminBR() + 10; // reference Y
    }
    halt();
  }
if (zone == 2){
  float x1 = (GarminFR() + 10);
  float y1 = GarminBR() + 10; // reference Y
  driveRight();
  while (x1 > xx || y1 > yy){
    x1 = (GarminFR() + 10);
    y1 = GarminBR() + 10; // reference Y
  }
    halt();
}
if (zone == 3){
  float x1 = (GarminFR() + 10);
  float  y = (GarminFL() + 10);
  driveForward();
  while (x1 > xx || y > yy){
    x1 = (GarminFR() + 10);
    y = (GarminFL() + 10);
    }
    halt();
}
if (zone == 4){
    float x = GarminBL() + 10; // reference x
    float y = (GarminFL() + 10);
    driveLeft();
    while (x > xx || y > yy){
      x = GarminBL() + 10; // reference x
      y = (GarminFL() + 10);
    }      
    halt();                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
  }
}

