#include <Wire.h>
#include <LIDARLite.h>

#define front A16
#define back A14
#define left A18
#define right A20

int sensorPins[] = {2,3,4,5}; // Array of pins connected to the sensor Power Enable lines
unsigned char addresses[] = {0x70,0x68,0x64, 0x72};

LIDARLite myLidarLite;


void setup() {

  Serial.begin(9600);
  myLidarLite.begin();
  myLidarLite.changeAddressMultiPwrEn(4,sensorPins,addresses,false);

}

void loop() {

  float val1 = analogRead(front);
  Serial.print("ShortRange F: ");
  Serial.print((6255.4* pow(val1,-1.102)));
  Serial.print(" | ");

  float val2 = analogRead(back);
  Serial.print("ShortRange B: ");
  Serial.print(6255.4* pow(val2,-1.102));
  Serial.print(" | ");

  float val3 = analogRead(left);
  Serial.print("ShortRange L: ");
  Serial.print(6255.4* pow(val3,-1.102));
  Serial.print(" | ");

  float val4 = analogRead(right);
  Serial.print("ShortRange R: ");
  Serial.print(6255.4* pow(val4,-1.102));
  Serial.print(" | ");

  Serial.print("       ||       ");


  Serial.print("FL: ");
  Serial.print(myLidarLite.distance(true,true,0x68));
  Serial.print(", FR: ");
  Serial.print(myLidarLite.distance(true,true,0x72));
  Serial.print(", BL: ");
  Serial.print(myLidarLite.distance(true,true,0x64));
  Serial.print(", BR: ");
  Serial.println(myLidarLite.distance(true,true,0x70));

}
