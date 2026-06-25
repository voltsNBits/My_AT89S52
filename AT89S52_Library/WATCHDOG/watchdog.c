/*------------------------------------------------------------------------------------------------------
                                        WATCHDOG.C (v1.00)
--------------------------------------------------------------------------------------------------------
                            'A .C File for WATCHDOG Operations in AT89S52' 
--------------------------------------------------------------------------------------------------------*/
#include "device.h"

#include "watchdog.h"

/*-------------------------------------------------------------------
  To enable the WDT, a user must write 01EH and 0E1H in sequence to 
  the WDTRST register (SFR location 0A6H).
  Once enabled, there is no way to disable the WDT except through 
  reset (either hardware reset or WDT overflow reset).
---------------------------------------------------------------------*/
void WDT_Enable(void){
	
	WDTRST = 0x1E;
	WDTRST = 0xE1;
}

/*-------------------------------------------------------------------
  When the WDT is enabled, the 14-bit counter overflows when it 
  reaches 16383 (3FFFH), and this will reset the device.
  The software must periodically service the WDT by writing 01EH and 
  0E1H to WDTRST to avoid a WDT overflow.
  Note: WDT timeout duration = (16384*12)/OSC_FREQ sec
---------------------------------------------------------------------*/
void WDT_Service(void){
	
	WDTRST = 0x1E;
	WDTRST = 0xE1;
}

/*-------------------------------------------------------------------
  WDT halts Counting in IDLE mode.
  With WDIDLE bit enabled, the WDT will stop to count in IDLE mode 
  and resumes the count upon exit from IDLE.
---------------------------------------------------------------------*/
void WDT_Stop_In_Idle(void){
	AUXR |= 0x10; // Sets WDIDLE = 1
}

/*-------------------------------------------------------------------
  WDT continues to count in IDLE mode.
  To prevent the WDT from resetting the AT89S52 while in IDLE mode, 
  the user should always set up a timer that will periodically exit 
  IDLE, service the WDT, and reenter IDLE mode.
---------------------------------------------------------------------*/
void WDT_Run_In_Idle(void){
	AUXR &= ~0x10; // Sets WDIDLE = 0
}

/*-------------------------------------------------------------------
  RST pin is driven HIGH externally whenever the WDT overflows.
  The MCU is also internally reset.
  Note: The RESET pulse duration = 98/OSC_FREQ sec
---------------------------------------------------------------------*/
void WDT_Enable_Reset_Out(void){
	AUXR &= ~0x08; // Sets DISTRO = 0
}

/*-------------------------------------------------------------------
  RST pin acts as Input Only and is not driven HIGH (Externally) 
  when WATCHDOG Timer Overflows. 
  The MCU can still be Reset automatically whenever WATCHDOG Timer 
  Overflows due to an Internal Reset Signal. 
---------------------------------------------------------------------*/
void WDT_Disable_Reset_Out(void){
	AUXR |= 0x08; // Sets DISTRO = 1
}

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/