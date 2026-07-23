/*-----------------------------------------------------------------
                        Scheduler.H (v1.00)
-------------------------------------------------------------------
             Header file for Scheduler Implementation
-------------------------------------------------------------------*/

#ifndef AT89S52_SCHEDULER_H
#define AT89S52_SCHEDULER_H

#include "device.h"

// ----- Public Flag variable ----------------------
extern volatile bit Scheduler_Tick_Flag;

// ------ Public function prototypes -----------
void Scheduler_Init(const uint8_t);
void Enter_Idle_Mode(void);

#endif

/*-----------------------------------------------------------------
                     END OF FILE
-------------------------------------------------------------------*/