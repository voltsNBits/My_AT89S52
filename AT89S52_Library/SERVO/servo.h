/*------------------------------------------------------------------------------------------------------
                                            SERVO.H (v1.00)
--------------------------------------------------------------------------------------------------------
                                'A Header File for a 180deg Servo Driver' 
--------------------------------------------------------------------------------------------------------*/

#ifndef _LCD_H
#define _LCD_H

#include "device.h"

// ----- ASSIGN SERVO SIGNAL PIN -----
sbit SERVO_SIGNAL=P1^1;

// ----- PUBLIC FUNCTION PROTOTYPES -----
void Servo_Init(void);
void Servo_Pulse_Range(uint16_t, uint16_t);
void Servo_Set_Angle(uint8_t);
void Servo_Generate_Pulse(void); //must be called every 20ms
//uint8_t Servo_Get_Angle(void);

#endif

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/