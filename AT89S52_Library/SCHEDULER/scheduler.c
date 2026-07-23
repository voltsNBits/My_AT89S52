/*----------------------------------------------------------------
                       Scheduler.C (v1.10)
------------------------------------------------------------------
	        .C file for Simple Scheduler Implementation .
------------------------------------------------------------------*/

#include "device.h"
#include "timer.h"

#include "scheduler.h"

/*----------------------------------------------------------------*
	Timer 2 Interrupt Service Routine.
	Tip: Keep The ISR code as short as possible
------------------------------------------------------------------*/
void Scheduler_ISR(void) interrupt 5{
	
	Timer_Clear_Overflow(2); // Clear T2 flag

	// ----- Application Task -----
	Scheduler_Tick_Flag = 1; 
	// ----------------------------
	
}

/*-----------------------------------------------------------------
	Configure Timer 2 to drive the Scheduler.
	Parameter gives tick interval in milliseconds.
	Max tick interval possible is ~71ms (11.0592 MHz oscillator).
------------------------------------------------------------------*/
void Scheduler_Init(const uint8_t tick_ms){
	
	uint32_t timer_count;
	uint16_t reload_value;
	
	// Request for Timer 2 access, if denied return
	if(Timer_Request(TIMER_2) != TIMER_FREE){
		return;
	}

	// Timer 2 is configured as a 16-bit timer,
	Timer2_CorT2(T2_TIMER);
	// Timer 2 is configured to automatically Reload when overflow occurs
	Timer2_Enable_AutoReload();

	// Number of timer increments required (max 65536)
	timer_count = ((uint32_t)tick_ms * (OSC_FREQ/1000)) /(uint32_t)OSC_PER_MC;

	// 16-bit reload value
	reload_value = (uint16_t) (65536UL - timer_count);

	// Load Capture Registers
	Timer2_Set_RCAP(reload_value);

    // Load Timer2 Registers
	Timer_Load(2, reload_value);  
	
	// Enable Timer2 interrupt
	Timer_Enable_Interrupt(2);

	// Start Timer 2 
	Timer_Run(2);
	
	// Enable all interrupts
	EA = 1;   
}

/*-----------------------------------------------------------------
    The System enters Idle Mode when this function is Executed.
    An interrupt signal will bring back the system into Normal Mode.
-------------------------------------------------------------------*/
void Enter_Idle_Mode(void){
   PCON |= 0x01;      
}

/*-----------------------------------------------------------------
                          END OF FILE
-------------------------------------------------------------------*/