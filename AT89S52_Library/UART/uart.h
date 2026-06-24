/*------------------------------------------------------------------------------------------------------
                                            UART.H (v1.00)
--------------------------------------------------------------------------------------------------------
                             'A Header File for UART Operations in AT89S52' 
--------------------------------------------------------------------------------------------------------*/
#ifndef _UART_H
#define _UART_H

#include "device.h"

// ----- PUBLIC FUNCTION PROTOTYPES -----
void Uart_Init(void);

void UartT1_SMOD(bit);
bit UartT1_Get_SMOD(void);

void UartT1_Set_Baud(uint8_t, uint16_t);
void UartT2_Set_Baud(uint16_t);

void Uart_Enable_Reception(void);
void Uart_Send_Byte(uint8_t);
uint8_t Uart_Read_Byte(void);
bit Uart_TX_Completed(void);
bit Uart_RX_Completed(void);
void Uart_Clear_TX_Flag(void);
void Uart_Clear_RX_Flag(void); 
void Uart_TB8(bit);
bit Uart_Get_RB8(void);
void Uart_RCLK(bit);
void Uart_TCLK(bit);

#endif

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/