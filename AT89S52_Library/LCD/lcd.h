/*------------------------------------------------------------------------------------------------------
                                             LCD.H (v1.10)
--------------------------------------------------------------------------------------------------------
                                'A Header File for 16x02A LCD Driver' 
--------------------------------------------------------------------------------------------------------*/

#ifndef AT89S52_LCD_H
#define AT89S52_LCD_H

#include "device.h"

// ----- Instruction : Clear Display -----
#define LCD_CLEAR_DISPLAY 0x01   // Clear display and reset cursor

// ----- Instruction : Return Home -----
#define LCD_RETURN_HOME 0x02     // Resets Cursor
										
// ----- Instruction : Entry Mode Set -----
#define LCD_DEC_CURSOR 0x04         // Decrements cursor(DDRAM Address) by 1 after READ or WRITE
#define LCD_DEC_SHIFT_DISPLAY 0x05  // Decrements cursor and shifts entire display after READ or WRITE
#define LCD_INC_CURSOR 0x06         // Increments cursor(DDRAM Address) by 1 after READ or WRITE
#define LCD_INC_SHIFT_DISPLAY 0x07  // Increments cursor and shifts entire display after READ or WRITE

// ----- Instruction : Display ON/OFF Control -----
#define LCD_DISPLAY_OFF 0x08    // Turns OFF Entire Display
#define LCD_DISPLAY_ON 0x0C     // Turns ON the Display
#define LCD_CURSOR_ON 0x0E      // Cursor Turns ON
#define LCD_CURSOR_BLINK 0x0F   // Blinks The Cursor

// ----- Instruction : Cursor or Display Shift -----
#define LCD_CURSOR_SHIFT_LEFT 0x10   // Shifts the Cursor to the Left
#define LCD_CURSOR_SHIFT_RIGHT 0x14  // Shifts the Cursor to the Right
#define LCD_DISPLAY_SHIFT_LEFT 0x18  // Shifts the Display to the Left
#define LCD_DISPLAY_SHIFT_RIGHT 0x1C // Shifts the Display to the Right

// ----- Instruction : Function Set -----
#define LCD_MODE_4BIT_1LINE 0x20  // Sets the LCD to 4-bit and 1-line Mode
#define LCD_MODE_4BIT_2LINE 0x28  // Sets the LCD to 4-bit and 2-line Mode
#define LCD_MODE_8BIT_1LINE 0x30  // Sets the LCD to 8-bit and 1-line Mode
#define LCD_MODE_8BIT_2LINE 0x38  // Sets the LCD to 8-bit and 2-line Mode

// ----- Instruction : Set CGRAM Address -----
#define LCD_SET_CGRAM_ADDR 0x40   // can be used to SET to any CGRAM address 
                                  // (use OR operator for specific address selection)
																		
// ----- Instruction : Set DDRAM Address -----
#define LCD_MOVE_CURSOR 0x80   // can be used to jump to any LCD address 
                               // (use OR operator for specific address selection)
#define LCD_JUMP_LINE2 0xC0    // Jump to Beggining of 2nd Line


// ----- PUBLIC FUNCTION PROTOTYPES -----
void Lcd_Init_4bit_Mode(void);
void Lcd_Init_8bit_Mode(void);

void Lcd_CMD(uint8_t);
void Lcd_DATA(unsigned char);

void Lcd_Print_String(const unsigned char *);

#endif

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/