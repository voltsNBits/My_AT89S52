/*------------------------------------------------------------------------------------------------------
                                            TIMER.H (v1.00)
--------------------------------------------------------------------------------------------------------
                            'A Header File for a Timer Operations in AT89S52' 
--------------------------------------------------------------------------------------------------------*/
#ifndef _TIMER_H
#define _TIMER_H

#include "device.h"

// ----- MACROS TO AID TIMER 0 OPERATIONS -----
#define TIMER0_M0 0x00
#define TIMER0_M1 0x01
#define TIMER0_M2 0x02
#define TIMER0_M3 0x03

#define T0_COUNTER   0x04
#define T0_GATE      0x08

// ----- MACROS TO AID TIMER 1 OPERATIONS -----
#define TIMER1_M0 0x00
#define TIMER1_M1 0x10
#define TIMER1_M2 0x20
#define TIMER1_M3 0x30

#define T1_COUNTER   0x40
#define T1_GATE      0x80

// ----- MACROS TO AID TIMER 2 OPERATIONS -----
#define T2_TIMER 0
#define T2_COUNTER 1

// ----- PUBLIC FUNCTION PROTOTYPES -----
void Timer_Load(uint8_t, uint16_t);
void Timer_Set_Mode(uint8_t, uint8_t);
void Timer_Run(uint8_t);
void Timer_Stop(uint8_t);
void Timer_Clear_Overflow(uint8_t);
bit Timer_Is_Overflowed(uint8_t);
uint16_t Timer_Read(uint8_t);

// ----- TIMER 2 SPECIFIC PUBLIC FUNCTION PROTOTYPES -----
void Timer2_CorT2(bit);
void Timer2_Set_RCAP(uint16_t);
void Timer2_Enable_AutoReload(void);
void Timer2_Enable_Capture(void);
uint16_t Timer2_Read_RCAP(void);
void Timer2_Enable_External(void);
void Timer2_Disable_External(void);
bit Timer2_Get_EXF2(void);

// ----- PUBLIC FUNCTION PROTOTYPES FOR INTERRUPT OPERATIONS -----
void Timer_Enable_Interrupt(uint8_t);
void Timer_Disable_Interrupt(uint8_t);

#endif

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/