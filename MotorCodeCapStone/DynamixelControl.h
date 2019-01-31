
#ifndef DynamixelControl_h
#define DynamixelControl_h

// AX12 EEPROM 
#define MODEL_NUMBER_L          	0x00
#define MODEL_NUMBER_H          	0x01
#define VERSION_OF_FIRMWARE			  0x02
#define ID                        0x03
#define BAUD_RATE					        0x04
#define RETURN_DELAY_TIME      		0x05
#define CW_ANGLE_LIMIT_L        	0x06
#define CW_ANGLE_LIMIT_H        	0x07
#define CCW_ANGLE_LIMIT_L       	0x08
#define CCW_ANGLE_LIMIT_H       	0x09
#define RESERVED_1             		0x0A
#define HIGHEST_LIMIT_TEMPERATURE 0x0B
#define LOWEST_LIMIT_VOLTAGE      0x0C
#define HIGHEST_LIMIT_VOLTAGE     0x0D
#define MAX_TORQUE_L             	0x0E
#define MAX_TORQUE_H             	0x0F
#define STATUS_RETURN_LEVEL       0x10
#define ALARM_LED                	0x11
#define ALARM_SHUTDOWN           	0x12
#define RESERVED_2           		  0x13
#define DOWN_CALIBRATION_L       	0x14
#define DOWN_CALIBRATION_H       	0x15
#define UP_CALIBRATION_L         	0x16
#define UP_CALIBRATION_H         	0x17

// AX12 RAM
#define TORQUE_ENABLE            	0x18
#define LED                       0x19
#define CW_COMPLIANCE_MARGIN     	0x1A
#define CCW_COMPLIANCE_MARGIN    	0x1B
#define CW_COMPLIANCE_SLOPE      	0x1C
#define CCW_COMPLIANCE_SLOPE     	0x1D
#define GOAL_POSITION_L          	0x1E
#define GOAL_POSITION_H          	0x1F
#define MOVING_SPEED_L            0x20
#define MOVING_SPEED_H            0x21
#define TORQUE_LIMIT_L           	0x22
#define TORQUE_LIMIT_H           	0x23
#define PRESENT_POSITION_L       	0x24
#define PRESENT_POSITION_H       	0x25
#define PRESENT_SPEED_L          	0x26
#define PRESENT_SPEED_H          	0x27
#define PRESENT_LOAD_L           	0x28
#define PRESENT_LOAD_H           	0x29
#define PRESENT_VOLTAGE          	0x2A
#define PRESENT_TEMPERATURE      	0x2B
#define REGISTERED_INSTRUCTION   	0x2C
#define RESERVED_3               	0x2D
#define MOVING                   	0x2E
#define LOCK                     	0x2F
#define PUNCH_L                  	0x30
#define PUNCH_H                  	0x31

// Status Return Levels 
#define RETURN_NONE              	0x00 // no reponse
#define RETURN_READ              	0x01 // respond to READ_DATA only
#define RETURN_ALL               	0x02 // respond to all instructions

// Instruction Set 
#define PING                     	0x01 // get status packet
#define READ_DATA                	0x02 // read from control table
#define WRITE_DATA               	0x03 // write to control table
#define REG_WRITE                	0x04 // write but wait for action
#define ACTION                   	0x05 // action
#define RESET                    	0x06 // factory reset
#define SYNC_WRITE               	0x83 // multiple motors

// Others
#define START                     0xFF
#define XMIT                      HIGH
#define RCV                       LOW
#define ON                        1
#define OFF                       0
#define TEN_MILLION_BITS          10000000
#define ONE_BYTE                  1
#define TWO_BYTES                 2
#define THREE_BYTES               3
#define FOUR_BYTES                4
#define LED_LENGTH                4
#define TORQUE_LENGTH             4
#define BUFFER_LENGTH             4
#define MOVE_LENGTH               7
#define BAUD_LENGTH               4
#define ID_LENGTH                 4
#define FREE_ROTATION_LENGTH      5
#define TURN_LENGTH               5
#define STATUS_LENGTH             6
#define PING_LENGTH               2
#define RESET_LENGTH              2
#define POSITION_LENGTH           4
#define SPEED_LENGTH              4
#define LOAD_LENGTH               4
#define VOLTAGE_LENGTH            4
#define TEMPERATURE_LENGTH        4
#define READ_1_BUFFER_LENGTH      7
#define READ_2_BUFFER_LENGTH      8    
#define MAX_H                     0x03
#define MAX_L                     0xFF
#define CW                        true
#define CCW                       false

#include <inttypes.h>

class DynamixelControl 
{
  public:
	byte DirectionPin;
  int TransmitWaitFactor;
	
  DynamixelControl();
	~DynamixelControl();
  virtual int readData(byte *, int);
  virtual void writeData(byte *, int);

  virtual void begin(long Baud, byte DirectionPin);
  virtual void end();
  byte writeLED(byte, byte);
  byte enableTorque(byte, byte);
  byte move(byte, int, int = 0x03FF);
  byte setBaud(byte, long);
  byte setID(byte, byte);
  byte freeRotation(byte, bool);
  byte turnVelocity(byte, bool, int);
  byte ping(byte);
  byte reset(byte);
  int readPosition(byte);
  int readSpeed(byte);
  int readLoad(byte);
  int readVoltage(byte);
  int readTemperature(byte);
};

class DynamixelControl1: public DynamixelControl
{
  public:
	int readData(byte *, int);
	void writeData(byte *, int);
	
	
	DynamixelControl1();
	~DynamixelControl1();
  void begin(long Baud, byte DirectionPin);
  void end();
};

class DynamixelControl2: public DynamixelControl
{
	public:
	int readData(byte *, int);
	void writeData(byte *, int);

	DynamixelControl2();
	~DynamixelControl2();
  void begin(long Baud, byte DirectionPin);
  void end();
};

class DynamixelControl3: public DynamixelControl
{
  public:
	int readData(byte *, int);
	void writeData(byte *, int);
	
	DynamixelControl3();
	~DynamixelControl3();
  void begin(long Baud, byte DirectionPin);
  void end();
};

#endif

