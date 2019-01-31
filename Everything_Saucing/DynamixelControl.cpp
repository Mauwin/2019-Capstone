#include "Arduino.h"
#include "DynamixelControl.h"
//--------------------------------------------------------------------------------------
DynamixelControl::DynamixelControl()
{
}
//--------------------------------------------------------------------------------------
DynamixelControl::~DynamixelControl()
{
}
//--------------------------------------------------------------------------------------
// open serial port and define direction pin
// suggested baud is 200000 after motor has been modified 
//--------------------------------------------------------------------------------------
void DynamixelControl::begin(long Baud, byte DirPin) 
{
  DirectionPin = DirPin;
  TransmitWaitFactor = TEN_MILLION_BITS / Baud; // used to wait for transmit to finish
  pinMode(DirectionPin, OUTPUT);
  Serial.begin(Baud);
  Serial.setTimeout(100);
}
//--------------------------------------------------------------------------------------
// close serial port
void DynamixelControl::end()
{
  Serial.end(); 
}

// read from Dynamixel
// results returned in Buffer
// number of bytes read returned
int DynamixelControl::readData(byte * Buffer, int Length)
{
  return Serial.readBytes((char*) Buffer, Length);
}

// utility write to Dynamixel
// Buffer contains packet and Length is length of packer
void DynamixelControl::writeData(byte * Buffer, int Length)
{
  digitalWrite(DirectionPin, XMIT); // transmit mode
  Serial.write(Buffer, Length); // write
  delayMicroseconds(TransmitWaitFactor * (Length + 1)); // wait to finish transmit
  digitalWrite(DirectionPin, RCV); // receive mode
}
//--------------------------------------------------------------------------------------
// turn LED on or off
// MID is motor ID, State = ON or OFF
//--------------------------------------------------------------------------------------
byte DynamixelControl::writeLED(byte MID, byte State)
{
  int BufferLength = BUFFER_LENGTH + LED_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = LED_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = WRITE_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = LED;
  CheckSum += Buffer[5];
  Buffer[6] = State;
  CheckSum += Buffer[6];
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
  else return Buffer[4];
}
//--------------------------------------------------------------------------------------
// enable/disable torque
// MID is motor ID, Enable is true or false
byte DynamixelControl::enableTorque(byte MID, byte Enable)
{
  int BufferLength = BUFFER_LENGTH + TORQUE_LENGTH;
  byte Buffer[BufferLength];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = TORQUE_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = WRITE_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = TORQUE_ENABLE;
  CheckSum += Buffer[5];
  Buffer[6] = Enable;
  CheckSum += Buffer[6];
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);

  if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
  else return Buffer[4];
}

// move motor to Position at Speed
// Position and Speed range: 0x0000 to 0x03FF
byte DynamixelControl::move(byte MID, int Position, int Speed)
{
  int BufferLength = BUFFER_LENGTH + MOVE_LENGTH;
  byte Buffer[BufferLength];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = MOVE_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = WRITE_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = GOAL_POSITION_L;
  CheckSum += Buffer[5];
  Buffer[6] = Position & 0xFF;
  CheckSum += Buffer[6];
  Buffer[7] = Position >> 8;
  CheckSum += Buffer[7];
  Buffer[8] = Speed & 0xFF;
  CheckSum += Buffer[8];
  Buffer[9] = Speed >> 8;
  CheckSum += Buffer[9];
  Buffer[10] = ~CheckSum;
  
  writeData(Buffer, BufferLength); 

  if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
  else return Buffer[4];

}

byte DynamixelControl::setBaud(byte MID, long Baud)
{
  int BufferLength = BUFFER_LENGTH + BAUD_LENGTH;
  byte Buffer[BufferLength];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = BAUD_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = WRITE_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = BAUD_RATE;
  CheckSum += Buffer[5];
  Buffer[6] = (2000000 / Baud) - 1;
  CheckSum += Buffer[6];
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);

  if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
  else return Buffer[4];
}

byte DynamixelControl::setID(byte MID, byte NewMID)
{
  int BufferLength = BUFFER_LENGTH + ID_LENGTH;
  byte Buffer[BufferLength];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = ID_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = WRITE_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = ID;
  CheckSum += Buffer[5];
  Buffer[6] = NewMID;
  CheckSum += Buffer[6];
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);

  if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
  else return Buffer[4];
}

byte DynamixelControl::freeRotation(byte MID, bool Free)
{
  int BufferLength = BUFFER_LENGTH + FREE_ROTATION_LENGTH;
  byte Buffer[BufferLength];
  byte CheckSum = 0;
  if (Free)
  {
    Buffer[0] = START;
    Buffer[1] = START;
    Buffer[2] = MID;
    CheckSum += Buffer[2];
    Buffer[3] = FREE_ROTATION_LENGTH;
    CheckSum += Buffer[3];
    Buffer[4] = WRITE_DATA;
    CheckSum += Buffer[4];
    Buffer[5] = CCW_ANGLE_LIMIT_L;
    CheckSum += Buffer[5];
    Buffer[6] = 0;
    CheckSum += Buffer[6];
    Buffer[7] = 0;
    CheckSum += Buffer[7];
    Buffer[8] = ~CheckSum;
    
    writeData(Buffer, BufferLength);

    if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
    else return Buffer[4];

  } 
  else
  {
    turnVelocity(MID, true, 0);
    Buffer[0] = START;
    Buffer[1] = START;
    Buffer[2] = MID;
    CheckSum += Buffer[2];
    Buffer[3] = FREE_ROTATION_LENGTH;
    CheckSum += Buffer[3];
    Buffer[4] = WRITE_DATA;
    CheckSum += Buffer[4];
    Buffer[5] = CCW_ANGLE_LIMIT_L;
    CheckSum += Buffer[5];
    Buffer[6] = MAX_L;
    CheckSum += Buffer[6];
    Buffer[7] = MAX_H;
    CheckSum += Buffer[7];
    Buffer[8] = ~CheckSum;
    
    writeData(Buffer, BufferLength); 

    if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
    else return Buffer[4];    
  } 
 
}

byte DynamixelControl::turnVelocity(byte MID, bool Direction, int Speed)
{
  int BufferLength = BUFFER_LENGTH + TURN_LENGTH;
  byte Buffer[BufferLength];
  byte CheckSum = 0;
  if (Direction)
  {
    Buffer[0] = START;
    Buffer[1] = START;
    Buffer[2] = MID;
    CheckSum += Buffer[2];
    Buffer[3] = TURN_LENGTH;
    CheckSum += Buffer[3];
    Buffer[4] = WRITE_DATA;
    CheckSum += Buffer[4];
    Buffer[5] = MOVING_SPEED_L;
    CheckSum += Buffer[5];
    Buffer[6] = Speed & 0xFF;
    CheckSum += Buffer[6];
    Buffer[7] = (Speed >> 8) + 4;
    CheckSum += Buffer[7];
    Buffer[8] = ~CheckSum;
    
    writeData(Buffer, BufferLength);
    
    if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
    else return Buffer[4]; 
  } 
  else
  {
    Buffer[0] = START;
    Buffer[1] = START;
    Buffer[2] = MID;
    CheckSum += Buffer[2];
    Buffer[3] = TURN_LENGTH;
    CheckSum += Buffer[3];
    Buffer[4] = WRITE_DATA;
    CheckSum += Buffer[4];
    Buffer[5] = MOVING_SPEED_L;
    CheckSum += Buffer[5];
    Buffer[6] = Speed & 0xFF;
    CheckSum += Buffer[6];
    Buffer[7] = (Speed >> 8);
    CheckSum += Buffer[7];
    Buffer[8] = ~CheckSum;
    
    writeData(Buffer, BufferLength);
    
    if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
    else return Buffer[4]; 
  } 
 
}
//---------------------------------------------------------------
byte DynamixelControl::ping(byte MID)
{
  int BufferLength = BUFFER_LENGTH + PING_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = PING_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = PING;
  CheckSum += Buffer[4];
  Buffer[5] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
  else return Buffer[4];
    
}
//---------------------------------------------------------------
byte DynamixelControl::reset(byte MID)
{
  int BufferLength = BUFFER_LENGTH + RESET_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = RESET_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = RESET;
  CheckSum += Buffer[4];
  Buffer[5] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, STATUS_LENGTH) != STATUS_LENGTH) return 0xFF;
  else return Buffer[4];
    
}
//---------------------------------------------------------------
int DynamixelControl::readPosition(byte MID)
{
  int BufferLength = BUFFER_LENGTH + POSITION_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = POSITION_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = READ_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = PRESENT_POSITION_L;
  CheckSum += Buffer[5];
  Buffer[6] = TWO_BYTES;
  CheckSum += Buffer[6];  
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, READ_2_BUFFER_LENGTH) != READ_2_BUFFER_LENGTH) return -1;
  else if (Buffer[4] != 0x00) return (0xFF00 | Buffer[4]);
  else return (Buffer[6] << 8 | Buffer[5]);    
}
//---------------------------------------------------------------
int DynamixelControl::readSpeed(byte MID)
{
  int BufferLength = BUFFER_LENGTH + SPEED_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = SPEED_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = READ_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = PRESENT_SPEED_L;
  CheckSum += Buffer[5];
  Buffer[6] = TWO_BYTES;
  CheckSum += Buffer[6];  
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, READ_2_BUFFER_LENGTH) != READ_2_BUFFER_LENGTH) return -1;
  else if (Buffer[4] != 0x00) return (0xFF00 | Buffer[4]);
  else return (Buffer[6] << 8 | Buffer[5]);    
}
//---------------------------------------------------------------
int DynamixelControl::readLoad(byte MID)
{
  int BufferLength = BUFFER_LENGTH + LOAD_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = LOAD_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = READ_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = PRESENT_LOAD_L;
  CheckSum += Buffer[5];
  Buffer[6] = TWO_BYTES;
  CheckSum += Buffer[6];  
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, READ_2_BUFFER_LENGTH) != READ_2_BUFFER_LENGTH) return -1;
  else if (Buffer[4] != 0x00) return (0xFF00 | Buffer[4]);
  else return (Buffer[6] << 8 | Buffer[5]);    
}
//---------------------------------------------------------------
int DynamixelControl::readVoltage(byte MID)
{
  int BufferLength = BUFFER_LENGTH + VOLTAGE_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = VOLTAGE_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = READ_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = PRESENT_VOLTAGE;
  CheckSum += Buffer[5];
  Buffer[6] = ONE_BYTE;
  CheckSum += Buffer[6];  
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, READ_1_BUFFER_LENGTH) != READ_1_BUFFER_LENGTH) return -1;
  else if (Buffer[4] != 0x00) return (0xFF00 | Buffer[4]);
  else return Buffer[5];    
}
//---------------------------------------------------------------
int DynamixelControl::readTemperature(byte MID)
{
  int BufferLength = BUFFER_LENGTH + TEMPERATURE_LENGTH;
  byte Buffer[16];
  byte CheckSum = 0;
  
  Buffer[0] = START;
  Buffer[1] = START;
  Buffer[2] = MID;
  CheckSum += Buffer[2];
  Buffer[3] = TEMPERATURE_LENGTH;
  CheckSum += Buffer[3];
  Buffer[4] = READ_DATA;
  CheckSum += Buffer[4];
  Buffer[5] = PRESENT_TEMPERATURE;
  CheckSum += Buffer[5];
  Buffer[6] = ONE_BYTE;
  CheckSum += Buffer[6];  
  Buffer[7] = ~CheckSum;
  
  writeData(Buffer, BufferLength);
  
  if(readData(Buffer, READ_1_BUFFER_LENGTH) != READ_1_BUFFER_LENGTH) return -1;
  else if (Buffer[4] != 0x00) return (0xFF00 | Buffer[4]);
  else return Buffer[5];    
}
//---------------------------------------------------------------
DynamixelControl1::DynamixelControl1()
{
}

DynamixelControl1::~DynamixelControl1()
{
}

int DynamixelControl1::readData(byte * Buffer, int Length)
{
  return Serial1.readBytes((char*) Buffer, Length);
}

void DynamixelControl1::writeData(byte *Buffer, int Length)
{
  digitalWrite(DirectionPin, XMIT);
  Serial1.write(Buffer, Length);
  delayMicroseconds(TransmitWaitFactor * (Length + 1));
  digitalWrite(DirectionPin, RCV);
}

void DynamixelControl1::begin(long Baud, byte DirPin)
{
  DirectionPin = DirPin;
  TransmitWaitFactor = TEN_MILLION_BITS / Baud;
  pinMode(DirectionPin, OUTPUT);
  Serial1.begin(Baud);
  Serial1.setTimeout(100);
}

void DynamixelControl1::end()
{
  Serial1.end();
}

//---------------------------------------------------------------

DynamixelControl2::DynamixelControl2()
{
}

DynamixelControl2::~DynamixelControl2()
{
}

int DynamixelControl2::readData(byte * Buffer, int Length)
{
  return Serial2.readBytes((char*)Buffer, Length);
}

void DynamixelControl2::writeData(byte *Buffer, int Length)
{
  digitalWrite(DirectionPin, XMIT);
  Serial2.write(Buffer, Length);
  delayMicroseconds(TransmitWaitFactor * (Length + 1));
  digitalWrite(DirectionPin, RCV);
}

void DynamixelControl2::begin(long Baud, byte DirPin)
{
  DirectionPin = DirPin;
  TransmitWaitFactor = TEN_MILLION_BITS / Baud;
  pinMode(DirectionPin, OUTPUT);
  Serial2.begin(Baud);
  Serial2.setTimeout(100);
}

void DynamixelControl2::end()
{
  Serial2.end();
}

//---------------------------------------------------------------

DynamixelControl3::DynamixelControl3()
{
}

DynamixelControl3::~DynamixelControl3()
{
}

int DynamixelControl3::readData(byte * Buffer, int Length)
{
  return Serial3.readBytes((char*) Buffer, Length);
}

void DynamixelControl3::writeData(byte * Buffer, int Length)
{
  digitalWrite(DirectionPin, XMIT);
  Serial3.write(Buffer, Length);
  delayMicroseconds(TransmitWaitFactor * (Length + 1));
  digitalWrite(DirectionPin, RCV);
}

void DynamixelControl3::begin(long Baud, byte DirPin)
{
  DirectionPin = DirPin;
  TransmitWaitFactor = TEN_MILLION_BITS / Baud;
  pinMode(DirectionPin, OUTPUT);
  Serial3.begin(Baud);
  Serial3.setTimeout(100);
}

void DynamixelControl3::end()
{
  Serial3.end();
}


