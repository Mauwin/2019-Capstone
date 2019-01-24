/* =============================================================================
  LIDAR-Lite v2: Change the I2C address of multiple sensors with PWR_EN line

  This example demonstrates how to chage the i2c address of multiple sensors.

  The library is in BETA, so subscribe to the github repo to recieve updates, or
  just check in periodically:
  https://github.com/PulsedLight3D/LIDARLite_v2_Arduino_Library

  To learn more read over lidarlite.cpp as each function is commented
=========================================================================== */

#include <Wire.h>
#include <LIDARLite.h>

int sensorPins[] = {2,3,4,5}; // Array of pins connected to the sensor Power Enable lines
unsigned char addresses[] = {0x70,0x68,0x64, 0x72};

LIDARLite myLidarLite;

void setup() {
  Serial.begin(115200);
  myLidarLite.begin();
  myLidarLite.changeAddressMultiPwrEn(4,sensorPins,addresses,false);
}

void loop() {
  
  Serial.print("FL: ");
  Serial.print(myLidarLite.distance(true,true,0x68));
  Serial.print(", FR: ");
  Serial.print(myLidarLite.distance(true,true,0x72));
  Serial.print(", BL: ");
  Serial.print(myLidarLite.distance(true,true,0x70));
  Serial.print(", BR: ");
  Serial.println(myLidarLite.distance(true,true,0x64));
}
