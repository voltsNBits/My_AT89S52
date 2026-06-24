/*------------------------------------------------------------------------------------------------------
                                             UART.C (v1.00)
--------------------------------------------------------------------------------------------------------
                                'A .C File for UART Operations in AT89S52' 
--------------------------------------------------------------------------------------------------------*/
#include "device.h"

#include "timer.h"
#include "uart.h"

/*-------------------------------------------------------------------
  A Default Init Function where timer 1 is used as baud generator 
  with 9600 baud and SMOD = 0
---------------------------------------------------------------------*/
void Uart_Init(void){
  UartT1_SMOD(0);
	UartT1_Set_Baud(1,9600);
	Uart_Enable_Reception();
}

/*-------------------------------------------------------------------
  Sets or Resets SMOD bit which doubles the Original Baud Rate
---------------------------------------------------------------------*/
void UartT1_SMOD(bit smod){
    PCON = (PCON & 0x7F)|((uint8_t)smod<<7);
}

/*-------------------------------------------------------------------
  Returns the value of SMOD bit 
---------------------------------------------------------------------*/
bit UartT1_Get_SMOD(void){
	return (PCON>>7) & 0x01;
}

/*-------------------------------------------------------------------
  UART mode and baud rate are given as Arguments.
  According to the Arguments The Timer 1 is set to operate in 
  required UART mode and the Timer registers (TH1 and TL1) are loaded 
  according to the provided baud rate
  Note: For Mode 0 and 2 the Argument 'baud_rate' is ignored.
---------------------------------------------------------------------*/
void UartT1_Set_Baud(uint8_t uart_mode, uint16_t baud_rate){
	
	uint8_t reload_value;
	bit SMOD;
	// Set Timer1 to mode 2
	Timer_Set_Mode(1,TIMER1_M2);
	SMOD = UartT1_Get_SMOD();
	
	switch (uart_mode){ 
		/* Mode 0: In this mode (considering: OSC_FREQ=11059200UL Hz)
		   Baud Rate = OSC_FREQ/12 = 921600 Baud */
  	    case 0: SM0=0; SM1=0;
  		    break;
		
		// ----- Considering Timer 1 is used only in Mode 2 for Baud Generation -----
		/* Mode 1: In this mode (considering:OSC_FREQ=11059200UL Hz)
		   Baud Rate = ((2^SMOD)*OSC_FREQ)/(32*12*[256-(TH1)]) Baud */
  	    case 1: SM0=0; SM1=1;
		        reload_value = 256 - ((((1UL+(uint8_t)SMOD)*OSC_FREQ) +((384UL*baud_rate)/2))/(384UL*baud_rate));
		        Timer_Load(1,reload_value);
  		    break;
		// --------------------------------------------------------------------------
		
		/* Mode 2: In this mode (considering:OSC_FREQ=11059200UL Hz)
		   Baud Rate = ((2^SMOD)*OSC_FREQ)/64 
		    If SMOD=0 : Baud Rate = 172800 Baud
		    If SMOD=1 : Baud Rate = 345600 Baud */
  	    case 2: SM0=1; SM1=0;
  		    break;
		
		// ----- Considering Timer 1 is used only in Mode 2 for Baud Generation -----
		/* Mode 3: In this mode (considering:OSC_FREQ=11059200UL Hz)
		   Baud Rate = ((2^SMOD)*OSC_FREQ)/(32*12*[256-(TH1)]) Baud */
  	    case 3: SM0=1; SM1=1;
		        reload_value = 256 - ((((1UL+(uint8_t)SMOD)*OSC_FREQ) +((384UL*baud_rate)/2))/(384UL*baud_rate));
		        Timer_Load(1,reload_value);
  		    break;
		// --------------------------------------------------------------------------
		
  	    default:
  		    break;
  }
}

/*-------------------------------------------------------------------
  Loads Capture registers and Timer2 registers (TH2,TL2) according 
  to the Required Baud Rate
---------------------------------------------------------------------*/
void UartT2_Set_Baud(uint16_t baud_rate){
	
	uint16_t rcap2;
	
	rcap2 = 65536UL - (OSC_FREQ/(32UL*baud_rate));
	Timer2_Set_RCAP(rcap2);
	Timer_Load(2,rcap2);
}

/*-------------------------------------------------------------------
  Enables the AT89S52 to perform reception 
---------------------------------------------------------------------*/
void Uart_Enable_Reception(void){
	REN = 1;
}

/*-------------------------------------------------------------------
  Loads the byte into SBUF and waits until transmission completes.
  Note: This is a blocking function.
        Execution waits until transmission completes.
---------------------------------------------------------------------*/
void Uart_Send_Byte(uint8_t byte){
	
	SBUF = byte;
	while(TI==0);
	Uart_Clear_TX_Flag();
}

/*-------------------------------------------------------------------
  Checks if Reception is completed using the RI Flag.
  Returns the Received byte stored in SBUF register.
  Note: This is a blocking function.
        Execution waits until reception completes.
---------------------------------------------------------------------*/
uint8_t Uart_Read_Byte(void){
	
	uint8_t byte;
	
	while(RI==0);
	byte = SBUF;
	Uart_Clear_RX_Flag();
	
	return byte;
}

/*-------------------------------------------------------------------
  Returns the TI Flag
---------------------------------------------------------------------*/
bit Uart_TX_Completed(void){
	return TI;
}

/*-------------------------------------------------------------------
  Returns the RI Flag
---------------------------------------------------------------------*/
bit Uart_RX_Completed(void){
	return RI;
}

/*-------------------------------------------------------------------
  Clears the TI Flag
---------------------------------------------------------------------*/
void Uart_Clear_TX_Flag(void){
	TI = 0;
}

/*-------------------------------------------------------------------
  Clears the RI Flag
---------------------------------------------------------------------*/
void Uart_Clear_RX_Flag(void){
	RI = 0;
}

/*-------------------------------------------------------------------
  Function to Set or Clear the 9th bit that will be transmitted 
  in Modes 2 and 3
---------------------------------------------------------------------*/
void Uart_TB8(bit transmit_bit){
	TB8 = transmit_bit;
}

/*------------------------------------------------------------------- 
  In mode 0, RB8 is not used.
  In mode 1, if SM2 = 0, RB8 is the stop bit that was received.
  In modes 2 & 3, is the 9th data bit that was received.
---------------------------------------------------------------------*/
bit Uart_Get_RB8(void){
	return RB8;
}

/*-------------------------------------------------------------------
  Receive clock flag. 
  When set, causes the serial port to use Timer 2 overflow pulses for 
  its receive clock in UART Modes 1 and 3. 
  RCLK = 0 causes Timer 1 overflow to be used for the receive clock.
  Note : The baud rates for transmit and receive can be 
         simultaneously different. 
---------------------------------------------------------------------*/
void Uart_RCLK(bit rclk_state){
	RCLK = rclk_state;
}

/*-------------------------------------------------------------------
  Transmit clock flag. 
  When set, causes the serial port to use Timer 2 overflow pulses for 
  its transmit clock in UART Modes 1 and 3. 
  TCLK = 0 causes Timer 1 overflows to be used for the transmit clock.
  Note : The baud rates for transmit and receive can be 
         simultaneously different.
---------------------------------------------------------------------*/
void Uart_TCLK(bit tclk_state){
	TCLK = tclk_state;
}

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/