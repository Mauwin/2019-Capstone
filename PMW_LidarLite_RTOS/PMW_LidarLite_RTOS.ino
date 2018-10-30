#include <FreeRTOS.h>

unsigned long pulseWidth;
unsigned long dist1;
unsigned long dist2;
unsigned long dist3;
unsigned long dist4;
void setup()
{
  Serial.begin(115200); // Start serial communications

    xTaskCreatePinnedToCore(
      sensor1,               // function for task to execute
      "sensor1",             // name (only used for debugging)
      10000,                    // stack size
      NULL,                     // pointer to parameters -- for us, each task gets an ID
      1,                        // priority (0 = lowes, configMAX_PRIORITIES-1 = highest)
      NULL,                     // task handle (we're not using this)
      0                         // which core to use (0 = PRO_CPU, 1 = APP_CPU, tskNO_AFFINITY = either)
    );
    
    xTaskCreatePinnedToCore(
      sensor2,               // function for task to execute
      "sensor2",             // name (only used for debugging)
      10000,                    // stack size
      NULL,                     // pointer to parameters -- for us, each task gets an ID
      1,                        // priority (0 = lowes, configMAX_PRIORITIES-1 = highest)
      NULL,                     // task handle (we're not using this)              // task handle (we're not using this)
      0                         // which core to use (0 = PRO_CPU, 1 = APP_CPU, tskNO_AFFINITY = either)
    );
    
    xTaskCreatePinnedToCore(
      sensor4,               // function for task to execute
      "sensor4",             // name (only used for debugging)
      10000,                    // stack size
      NULL,           
      0                         // which core to use (0 = PRO_CPU, 1 = APP_CPU, tskNO_AFFINITY = either)
    );
    
    xTaskCreatePinnedToCore(
      sensor3,               // function for task to execute
      "sensor3",             // name (only used for debugging)
      10000,                    // stack size
      NULL,                     // pointer to parameters -- for us, each task gets an ID
      1,                        // priority (0 = lowes, configMAX_PRIORITIES-1 = highest)
      NULL,                 // pointer to parameters -- for us, each task gets an ID
      1,                        // priority (0 = lowes, configMAX_PRIORITIES-1 = highest)
      NULL,                     // task handle (we're not using this)
      0                         // which core to use (0 = PRO_CPU, 1 = APP_CPU, tskNO_AFFINITY = either)
    );



  // Sensor 2
  pinMode(8, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(8, LOW); // Set trigger LOW for continuous read

  pinMode(9, INPUT); // Set pin 3 as monitor pin
}

void sensor1(){
  for(;;){
      pinMode(2, OUTPUT); // Set pin 2 as trigger pin
      digitalWrite(2, LOW); // Set trigger LOW for continuous read
      pinMode(3, INPUT); // Set pin 3 as monitor pin
      dist1 = pulseIn(3, HIGH);
      if(dist1 != 0){
        dist1 = dist1 / 10;
        Serial.println(dist1);
      }
  }

}

void sensor2(){
  for(;;){
    // Sensor 2
    pinMode(4, OUTPUT); // Set pin 2 as trigger pin
    digitalWrite(4, LOW); // Set trigger LOW for continuous read
    pinMode(5, INPUT); // Set pin 3 as monitor pin
    dist2 = pulseIn(5, HIGH);
    
    if(dist2 != 0) {
      dist2 = dist2 / 10;
      Serial.println(dist2);
    }
  }
}

void sensor3(){
  for(;;){
    // Sensor 2
    pinMode(6, OUTPUT); // Set pin 2 as trigger pin
    digitalWrite(6, LOW); // Set trigger LOW for continuous read
    pinMode(7, INPUT); // Set pin 3 as monitor pin
    dist3= pulseIn(7, HIGH);
    
    if(dist3 != 0) {
      dist3 = dist3 / 10;
      Serial.println(dist3);
    }
  }
}
void sensor4(){
  for(;;){
    // Sensor 2
    pinMode(8, OUTPUT); // Set pin 2 as trigger pin
    digitalWrite(8, LOW); // Set trigger LOW for continuous read
    pinMode(9, INPUT); // Set pin 3 as monitor pin
    dist4 = pulseIn(9, HIGH);
    
    if(dist4 != 0) {
      dist4 = dist2 / 10;
      Serial.println(dist4);
    }
  }
}
void loop()
{


}
