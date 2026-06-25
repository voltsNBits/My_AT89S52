/*------------------------------------------------------------------------------------------------------
                                            SERVO.C (v1.00)
--------------------------------------------------------------------------------------------------------
                                 'A .C File for 180deg Servo Driver' 
								Note: Makes use of Timer0 for All the timing Operations
--------------------------------------------------------------------------------------------------------*/

#include "device.h"
#include "servo.h"

// ----- PRIVATE VARIABLES -----
static uint16_t MinPulse_us;
static uint16_t MaxPulse_us;

static uint16_t load_value;
/*-------------------------------------------------------------------
   Servo Initialization Function.
   Configure the signal pin
	Initialize internal variables
	Set default position/angle
---------------------------------------------------------------------*/
void Servo_Init(void){
	
	// Set Timer0 in Mode 1
	TMOD &= 0xF0;
	TMOD |= 0x01;  
	
	SERVO_SIGNAL=0;
	
	// Default Range
	Servo_Pulse_Range(1000, 2000);
	
	// Default Angle
	Servo_Set_Angle(90);
}

/*-------------------------------------------------------------------
   Sets the max and min possible pulsewidth range for a servo.
   Different servos will have deifferent range for ex. 500 to 2500, 
   or 1000 to 2000 etc. Refer datasheet for exact possible range.
---------------------------------------------------------------------*/
void Servo_Pulse_Range(uint16_t min_us, uint16_t max_us){
	
	MinPulse_us = min_us;
	MaxPulse_us = max_us;
}

/*-------------------------------------------------------------------
   Sets the angular position of the Servo.
   Also calculates the THx and TLx load values.
   Note: Only applicable for servos with angle 0 - 180.
---------------------------------------------------------------------*/
void Servo_Set_Angle(uint8_t angle){
	
	uint32_t timer_count;
	uint16_t Pulse_Width;
	
	Pulse_Width = MinPulse_us + (((uint32_t)angle * ( MaxPulse_us-MinPulse_us))/180 );
	
	// Number of timer increments required (max 65536)
	timer_count = ((uint32_t)Pulse_Width * (OSC_FREQ/1000000)) /(uint32_t)OSC_PER_MC;

	// 16-bit reload value
	load_value = (uint16_t) (65536UL - timer_count);
	
}

/*-------------------------------------------------------------------
   Generates one burst of Pulse signal.
   To constantly hold the servo at set angle this function must be 
   called every 20ms.
	The ON state duration is dependendent on the angle given to 
	Servo_Set_Angle function
---------------------------------------------------------------------*/
void Servo_Generate_Pulse(void){ //called every 20ms
  
	TH0=(load_value>>8);
	TL0=(load_value & 0xFF);
	
	SERVO_SIGNAL=1;
	
	TF0=0;
	TR0=1;
	
	while(TF0==0);
	
	SERVO_SIGNAL=0;
	
	TR0=0;
}

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/