unsigned long pulseWidth;
unsigned long dist1;
unsigned long dist2;
unsigned long dist3;
unsigned long dist4;
void setup()
{
  Serial.begin(115200); // Start serial communications
  // Sensor 1
  pinMode(2, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(2, LOW); // Set trigger LOW for continuous read

  pinMode(3, INPUT); // Set pin 3 as monitor pin
  // Sensor 2
  pinMode(4, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(4, LOW); // Set trigger LOW for continuous read

  pinMode(5, INPUT); // Set pin 3 as monitor pin
  // Sensor 3
  pinMode(6, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(6, LOW); // Set trigger LOW for continuous read

  pinMode(7, INPUT); // Set pin 3 as monitor pin
  // Sensor 2
  pinMode(8, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(8, LOW); // Set trigger LOW for continuous read

  pinMode(9, INPUT); // Set pin 3 as monitor pin
}

void loop()
{
  dist1 = pulseIn(3, HIGH);
  dist2 = pulseIn(5, HIGH);
  dist3 = pulseIn(7, HIGH);
  dist4 = pulseIn(8, HIGH);
  if(dist1 != 0)
  {
    dist1 = dist1 / 10;
    Serial.println(dist1);
  }
  if(dist2 != 0)
  {
    dist2 = dist2 / 10;
    Serial.println(dist2);
  }
  if(dist3 != 0)
  {
    dist3 = dist3 / 10;
    Serial.println(dist3);
  }
  if(dist4 != 0)
  {
    dist4 = dist4 / 10;
    Serial.println(dist4);
  }
}

