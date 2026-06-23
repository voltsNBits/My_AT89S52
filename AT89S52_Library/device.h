/*-----------------------------------------------------------------
                          DEVICE.H (v1.00)
-------------------------------------------------------------------
                   'A Device Header for AT89S52' 
-------------------------------------------------------------------*/

#ifndef _DEVICE_H
#define _DEVICE_H

// Must include the appropriate microcontroller header file here
#include <reg52.h>

// Oscillator / resonator frequency (in Hz) 
#define OSC_FREQ (11059200UL)

// Number of oscillations per Machine Cycle 
// 12 - Original 8051 / 8052 and numerous modern versions

#define OSC_PER_MC (12)

// PIN ASSIGNMENTS FOR LCD DRIVER

#define LCD_DATA_PORT P2

sbit RS=P3^0;
sbit RW=P3^1;
sbit EN=P3^2;
sbit busy = P2^7;

// Typedefs 
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

#endif

/*------------------------------------------------------------------
                         END OF FILE
--------------------------------------------------------------------*/