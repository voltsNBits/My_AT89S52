/*------------------------------------------------------------------------------------------------------
                                           WATCHDOG.H (v1.00)
--------------------------------------------------------------------------------------------------------
                            'A Header File for WATCHDOG Operations in AT89S52' 
--------------------------------------------------------------------------------------------------------*/
#ifndef _WDT_H
#define _WDT_H

// ----- REGISTER MAPPINGS -----
sfr WDTRST = 0xA6;
sfr AUXR   = 0x8E;

// ----- PUBLIC FUNCTION PROTOTYPES -----
void WDT_Enable(void);
void WDT_Service(void);

void WDT_Stop_In_Idle(void);
void WDT_Run_In_Idle(void);

void WDT_Enable_Reset_Out(void);
void WDT_Disable_Reset_Out(void);

#endif

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/