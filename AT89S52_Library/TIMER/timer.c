/*------------------------------------------------------------------------------------------------------
                                             TIMER.C (v1.00)
--------------------------------------------------------------------------------------------------------
                                'A .C File for Timer Operations in AT89S52' 
		NOTE : The caller must succesfully acquire the timer using Timer_Request() before calling 
		           any other Timer_* APIs. Failure to do so results in Undefined behaviour
--------------------------------------------------------------------------------------------------------*/
#include "device.h"
#include "timer.h"

// ----- PRIVATE FUNCTION PROTOTYPES -----
static void Timer_Load16(TIMER_ID, uint16_t);
static void Timer_Load8(TIMER_ID, uint8_t);
static Timer_Status timer_status[3] = {
    TIMER_FREE,
    TIMER_FREE,
    TIMER_FREE
};

static void Timer_Load16(TIMER_ID timer, uint16_t load_value){
	
	switch (timer){
  	    case TIMER_0: TH0 = (uint8_t)(load_value>>8);      //Higher 8 bits
	                  TL0 = (uint8_t)(load_value & 0xFF);  //Lower 8 bits
  		    break;
  	    case TIMER_1: TH1 = (uint8_t)(load_value>>8);      //Higher 8 bits
	                  TL1 = (uint8_t)(load_value & 0xFF);  //Lower 8 bits
  		    break;
	    case TIMER_2: TH2 = (uint8_t)(load_value>>8);      //Higher 8 bits
	                  TL2 = (uint8_t)(load_value & 0xFF);  //Lower 8 bits
  		    break;
  	    default:
  		    break;
    }
}

static void Timer_Load8(TIMER_ID timer, uint8_t load_value){
	
	switch (timer){
  	    case TIMER_0: TL0 = load_value;  //Lower 8 bits
		              TH0 = load_value;
  		    break;
  	    case TIMER_1: TL1 = load_value;  //Lower 8 bits
		              TH1 = load_value;
  		    break;
	    case TIMER_2: TL2 = load_value;  //Lower 8 bits
		              TH2 = load_value;
  		    break;
  	    default:
  		    break;
    }
}

/*-------------------------------------------------------------------
  Loads the THx,TLx Registers as per the given parameters.
  Parameter 1: timer      - selects the timer 
  Parameter 2: load_value - Stores load value
  Note: supports only Timer Mode 1 and Mode 2.
---------------------------------------------------------------------*/
void Timer_Load(TIMER_ID timer, uint16_t load_value){
	
	uint8_t mode;
	switch (timer){
  	    case TIMER_0: mode = (TMOD & 0x03); 
			    switch (mode){
			        case 1: Timer_Load16(timer, load_value);
				        break;
			        case 2: Timer_Load8(timer, load_value);
				        break;
			    }
  		    break;
  	    case TIMER_1: mode = ((TMOD>>4) & 0x03); 
			    switch (mode){
			        case 1: Timer_Load16(timer, load_value);
				        break;
			        case 2: Timer_Load8(timer, load_value);
				        break;
			    }
  		    break;
	    case TIMER_2: Timer_Load16(timer, load_value);
		    break;                                                                                                                                                                        
  	    default:
  		    break;
    }
}

/*-------------------------------------------------------------------
  Sets Timer Mode for Timer 0 and Timer 1 as per the given parameters
---------------------------------------------------------------------*/
void Timer_Set_Mode(TIMER_ID timer, uint8_t mode){
	
	switch (timer){
  	    case TIMER_0: TMOD &= 0xF0;
	            TMOD |= mode;
  		    break;
  	    case TIMER_1: TMOD &= 0x0F;
	            TMOD |= mode;
  		    break;
     /*		
		case TIMER_2: 
  		    break;
     */
  	    default:
  		    break;
    }
}

/*-------------------------------------------------------------------
  Starts Timer by Setting TRx = 1.
  Function Parameter decides which timer is made to Start Counting.
---------------------------------------------------------------------*/
void Timer_Run(TIMER_ID timer){
	
	switch (timer){
  	    case TIMER_0: TR0=1;
  		    break;
  	    case TIMER_1: TR1=1;
  		    break;
	    case TIMER_2: TR2=1;
  		    break;
  	    default:
  		    break;
    }
}

/*-------------------------------------------------------------------
  Stops Timer by Clearing TRx = 0.
  Function Parameter decides which timer is stopped.
---------------------------------------------------------------------*/
void Timer_Stop(TIMER_ID timer){
	
	switch (timer){
  	    case TIMER_0: TR0=0;
  		    break;
  	    case TIMER_1: TR1=0;
  		    break;
	    case TIMER_2: TR2=0;
  		    break;
  	    default:
  		    break;
    }
}

/*-------------------------------------------------------------------
  Clears Timer Overflow Flag, TFx.
  Function Parameter decides which timer Overflow is Cleared.
  Note: For Timer2, both TF2 and EXF2 are cleared.
---------------------------------------------------------------------*/
void Timer_Clear_Overflow(TIMER_ID timer){
	
	switch (timer){
  	    case TIMER_0: TF0=0;
  		   break;
  	    case TIMER_1: TF1=0;
  		   break;
	    case TIMER_2: TF2=0;EXF2=0;
  		   break;
  	    default:
  		   break;
    }
}

/*-------------------------------------------------------------------
  Returns current TFx state.
  Function Parameter decides which timer Overflow Flag is returned.
---------------------------------------------------------------------*/
bit Timer_Is_Overflowed(TIMER_ID timer){
	
	switch (timer){
  	    case TIMER_0: return TF0;
  		    break;		
  	    case TIMER_1: return TF1;
  		    break;	
	    case TIMER_2: return TF2;
  		    break;
  	    default: return 0;
  		    break;
    }
}

/*-------------------------------------------------------------------
  Reads the count value of THx,TLx at the movement this function is called
---------------------------------------------------------------------*/
uint16_t Timer_Read(TIMER_ID timer){
	  
    switch(timer){
		// Timer in Mode2 returns THx(reload value):TLx raw register contents
        case TIMER_0: return ((uint16_t)TH0 << 8) | TL0;
            break;
        case TIMER_1: return ((uint16_t)TH1 << 8) | TL1;
            break;	
        case TIMER_2: return ((uint16_t)TH2 << 8) | TL2;
            break;
        default:return 0;
			break;
    }
}


/*-------------------------------------------------------------------
  Sets Timer 2 in either Timer Mode or Counter Mode
  From timer.h:	#define   T2_TIMER 0
				#define T2_COUNTER 1
---------------------------------------------------------------------*/
void Timer2_CorT2(bit mode){
	
	C_T2 = mode;
}

/*-------------------------------------------------------------------
  Stores required values in Capture Registers for Auto-Reload purpose
  Note: When Timer2 is used as a baud-rate generator, TR2 should be
        cleared before writing to RCAP2H and RCAP2L.
---------------------------------------------------------------------*/
void Timer2_Set_RCAP(uint16_t load_value){
	
	RCAP2H = (uint8_t)(load_value>>8);      //Higher 8 bits
	RCAP2L = (uint8_t)(load_value & 0xFF);  //Lower 8 bits
}

/*-------------------------------------------------------------------
  Enables Timer 2 to perform AutoReload
---------------------------------------------------------------------*/
void Timer2_Enable_AutoReload(void){
	
	CP_RL2 = 0;
}

/*-------------------------------------------------------------------
  Enables Timer 2 to perform Capture
---------------------------------------------------------------------*/
void Timer2_Enable_Capture(void){
	
	CP_RL2 = 1;
}

/*-------------------------------------------------------------------
  The values in TH2 and TL2 can be Captured by driving 
  T2EX LOW (falling edge)  [Given that EXEN2 is SET].
  The Captured values can be read using this function
---------------------------------------------------------------------*/
uint16_t Timer2_Read_RCAP(void){
	
	return ((uint16_t)RCAP2H << 8) | RCAP2L;
}

/*-------------------------------------------------------------------
   Allows a capture or reload to occur as a result of a negative 
   transition on T2EX if Timer 2 is not being used to clock the 
   serial port.
   When enabled, a falling edge on T2EX causes:
      Capture mode: TH2 and TL2 are copied into RCAP2H and RCAP2L.
      Auto-reload mode: RCAP2H and RCAP2L are reloaded into TH2 and TL2.
---------------------------------------------------------------------*/
void Timer2_Enable_External(void){
	
	EXEN2 = 1;
}

/*-------------------------------------------------------------------
  Causes Timer 2 to ignore events at T2EX.
---------------------------------------------------------------------*/
void Timer2_Disable_External(void){
	
	EXEN2 = 0;
}

/*-------------------------------------------------------------------
  Return the state of EXF2 Flag.
  Timer 2 external flag set when either a capture or reload is caused 
  by a negative transition on T2EX and EXEN2 = 1. 
  When Timer 2 interrupt is enabled, EXF2 = 1 will cause the CPU to 
  vector to the Timer 2 interrupt routine. EXF2 must be cleared by software. 
---------------------------------------------------------------------*/
bit Timer2_Get_EXF2(void){
	
	return EXF2;
}

/*-------------------------------------------------------------------
  Enable Timer Interrupt.
  Function Parameter decides which timer Interrupt is Enabled.
---------------------------------------------------------------------*/
void Timer_Enable_Interrupt(TIMER_ID timer){
	
	switch (timer){
   	    case TIMER_0: ET0 = 1;
   		    break;
   	    case TIMER_1: ET1 = 1;
   		    break;
	    // Responds to both TF2 and EXF2 Flags
	    case TIMER_2: ET2 = 1;
   		    break;
   	    default:
   		    break;
    }
}

/*-------------------------------------------------------------------
  Disable Timer Interrupt.
  Function Parameter decides which timer Interrupt is Disabled.
---------------------------------------------------------------------*/
void Timer_Disable_Interrupt(TIMER_ID timer){
	
	switch (timer){
   	    case TIMER_0: ET0 = 0;
   		    break;
   	    case TIMER_1: ET1 = 0;
   		    break;
	    case TIMER_2: ET2 = 0;
   		    break;
   	    default:
   		    break;
    }
}

/*-------------------------------------------------------------------
  Request Timer.
  Function Parameter decides which timer is requested.
  return 1 : Request Accepted 
  return 0 : Request Denied. Timer already in use.
---------------------------------------------------------------------*/
bit Timer_Request(TIMER_ID timer)
{
    if(timer_status[timer] == TIMER_FREE){

        timer_status[timer] = TIMER_BUSY;
        return 1;
    }

    return 0;
}

/*-------------------------------------------------------------------
  Timer Release Function.
  Assigns Timer status flag to TIMER_FREE.
---------------------------------------------------------------------*/
void Timer_Release(TIMER_ID timer){

    timer_status[timer] = TIMER_FREE;
}

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/