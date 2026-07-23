/*------------------------------------------------------------------------------------------------------
                                             LCD.C (v1.00)
--------------------------------------------------------------------------------------------------------
                                  'A .C File for 16x02A LCD Driver' 
--------------------------------------------------------------------------------------------------------*/

#include "device.h" 
#include "lcd.h"

typedef enum{
	LCD_MODE_4BIT,
	LCD_MODE_8BIT
}LCD_Mode;

// ----- PRIVATE FUNCTION PROTOTYPES -----
static void EN_Strobe(void);
static void Lcd_cmd_4bit_Mode(uint8_t);
static void Lcd_cmd_8bit_Mode(uint8_t);
static void Lcd_data_4bit_Mode(unsigned char);
static void Lcd_data_8bit_Mode(unsigned char);
static void MS_DELAY(uint16_t);

// ----- PRIVATE FUNCTION VARIABLES -----
static LCD_Mode lcd_mode = LCD_MODE_4BIT; 

/*-------------------------------------------------------------------
  
---------------------------------------------------------------------*/
void Lcd_Init_4bit_Mode(void){
	
	EN=0;
	 
	MS_DELAY(15); // Wait for >15ms after VDD>4.5Volts
	Lcd_cmd_8bit_Mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_8BIT_1LINE&0xF0) ); // Function Set
	MS_DELAY(5);  // Wait for >4.1ms
	Lcd_cmd_8bit_Mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_8BIT_1LINE&0xF0) ); // Function Set
	MS_DELAY(1);  // Wait for >100us
	Lcd_cmd_8bit_Mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_8BIT_1LINE&0xF0) ); // Function Set
	
	// FUNCTION SET : 4 Bit MODE
	Lcd_cmd_8bit_Mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_4BIT_1LINE&0xF0) ); 

	lcd_mode = LCD_MODE_4BIT;
}

/*-------------------------------------------------------------------
  
---------------------------------------------------------------------*/
void Lcd_Init_8bit_Mode(void){
	
	EN=0;
	 
	MS_DELAY(15); // Wait for >15ms after VDD>4.5Volts
	Lcd_cmd_8bit_Mode( LCD_MODE_8BIT_1LINE ); // Function Set
	MS_DELAY(5);  // Wait for >4.1ms
	Lcd_cmd_8bit_Mode( LCD_MODE_8BIT_1LINE ); // Function Set
	MS_DELAY(1);  // Wait for >100us
	Lcd_cmd_8bit_Mode( LCD_MODE_8BIT_1LINE ); // Function Set
	
	lcd_mode = LCD_MODE_8BIT;
}

/*-------------------------------------------------------------------
  Sends a command instruction to the LCD.
  The command is transmitted using either the configured 4-bit or
  8-bit interface mode.
  Parameters : cmd - LCD instruction byte.
---------------------------------------------------------------------*/
void Lcd_CMD(uint8_t CMD){

	switch(lcd_mode){
        case LCD_MODE_4BIT:
            Lcd_cmd_4bit_Mode(CMD);
            break;

        case LCD_MODE_8BIT:
            Lcd_cmd_8bit_Mode(CMD);
            break;

        default:
            break;
    }	
}

/*-------------------------------------------------------------------
  Writes a single data byte (character) to the LCD.
  The data to be printed must be enclosed within single quotes
  For example: Lcd_DATA('A'); 
  Refer the datasheet for characters which can be printed by the LCD
  Parameters : data - ASCII character to be displayed.
---------------------------------------------------------------------*/
void Lcd_DATA(unsigned char DATA){

	switch(lcd_mode){
        case LCD_MODE_4BIT:
            Lcd_data_4bit_Mode(DATA);
            break;

        case LCD_MODE_8BIT:
            Lcd_data_8bit_Mode(DATA);
            break;

        default:
            break;
    }	
}

/*-------------------------------------------------------------------
  Prints a null-terminated string on the LCD.
  Characters are written sequentially until the null terminator
  ('\0') is encountered.
  Parameters : str - Pointer to the string to be displayed.
---------------------------------------------------------------------*/
void Lcd_Print_String(const unsigned char *str){

	while(*str != '\0'){
		Lcd_DATA(*str);
		str++;
	}
}
/*-------------------------------------------------------------------
  Generates the Enable pulse required to latch data or commands
  into the LCD controller.
---------------------------------------------------------------------*/
static void EN_Strobe(void){
	
	EN=1;
	MS_DELAY(1); // Min pulse width >230ns
	EN=0;
	MS_DELAY(1); // Min pulse width >230ns
}

/*-------------------------------------------------------------------
  Transmits an LCD command using the 4-bit interface.
  The command byte is divided into two nibbles and transmitted
  starting with the higher nibble.
  Parameters : lcd_cmd - LCD instruction byte.
---------------------------------------------------------------------*/
static void Lcd_cmd_4bit_Mode(uint8_t lcd_cmd){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RS=0;
	RW=0;
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(lcd_cmd&0xF0); // Send Higher nibble
	EN_Strobe();
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((lcd_cmd<<4)&0xF0); // Send Lower nibble
	EN_Strobe();
}

/*-------------------------------------------------------------------
  Transmits an LCD command using the 8-bit interface.
  Parameters : lcd_cmd - LCD instruction byte.
---------------------------------------------------------------------*/
static void Lcd_cmd_8bit_Mode(uint8_t lcd_cmd){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RW=0;
	LCD_DATA_PORT=lcd_cmd;
	EN_Strobe();
}

/*-------------------------------------------------------------------
  Transmits a data byte using the 4-bit interface.
  The data byte is divided into two nibbles and transmitted
  starting with the higher nibble.
  Parameters : lcd_data - Character to be displayed.
---------------------------------------------------------------------*/
static void Lcd_data_4bit_Mode(unsigned char lcd_data){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RS=1;
	RW=0;
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(lcd_data&0xF0); // Send Higher nibble 
	EN_Strobe();
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((lcd_data<<4)&0xF0); // Send Lower nibble 
	EN_Strobe();
}

/*-------------------------------------------------------------------
  Transmits a data byte using the 8-bit interface.
  Parameters : lcd_data - Character to be displayed.
---------------------------------------------------------------------*/
static void Lcd_data_8bit_Mode(unsigned char lcd_data){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RS=1;
	RW=0;
	LCD_DATA_PORT=lcd_data;
	EN_Strobe();
}

/*-------------------------------------------------------------------
  Generates an approximate blocking delay in milliseconds.
  The delay duration depends on the system clock frequency and
  compiler optimization settings.

  Parameters :  delay - Delay duration in milliseconds.
---------------------------------------------------------------------*/
static void MS_DELAY(uint16_t delay){
	
	uint16_t i,j;
	for(i=0;i<delay;i++){
		for(j=0;j<1275;j++){}
	}
}

/*
Additional functionalities that i can add:

   For your current stage, I'd add these functions:

   Lcd_Print_String()
   Lcd_Print_Number()     // unsigned int
   Lcd_Set_Cursor()
   Lcd_Clear()
   Lcd_Home()

   Once you've learned arrays and a bit more about formatting, you can add:

   Lcd_Print_Hex(0xAF);    // AF
   Lcd_Print_Bin(10);      // 00001010

   Those are surprisingly useful when debugging embedded systems.
   
*/

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/