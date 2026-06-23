/*------------------------------------------------------------------------------------------------------
                                             LCD.C (v1.00)
--------------------------------------------------------------------------------------------------------
                                  'A .C File for 16x02A LCD Driver' 
--------------------------------------------------------------------------------------------------------*/

#include "device.h" 
#include "lcd.h"

// PRIVATE FUNCTION PROTOTYPES
void en_strobe(void);

void en_strobe(void){
	
	EN=1;
	MS_DELAY(1); // Min pulse width >230ns
	EN=0;
	MS_DELAY(1); // Min pulse width >230ns
}

void lcd_init_4bit_mode(void){
	
	 EN=0;
	 
	 MS_DELAY(15); // Wait for >15ms after VDD>4.5Volts
	 lcd_cmd_8bit_mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_8BIT_1LINE&0xF0) ); // Function Set
	 MS_DELAY(5);  // Wait for >4.1ms
	 lcd_cmd_8bit_mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_8BIT_1LINE&0xF0) ); // Function Set
	 MS_DELAY(1);  // Wait for >100us
	 lcd_cmd_8bit_mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_8BIT_1LINE&0xF0) ); // Function Set
	
	
	// FUNCTION SET : 4 Bit MODE
	 lcd_cmd_8bit_mode( (LCD_DATA_PORT&0x0F)|(LCD_MODE_4BIT_1LINE&0xF0) ); 
	 
}

void lcd_init_8bit_mode(void){
	
	 EN=0;
	 
	 MS_DELAY(15); // Wait for >15ms after VDD>4.5Volts
	 lcd_cmd_8bit_mode( LCD_MODE_8BIT_1LINE ); // Function Set
	 MS_DELAY(5);  // Wait for >4.1ms
	 lcd_cmd_8bit_mode( LCD_MODE_8BIT_1LINE ); // Function Set
	 MS_DELAY(1);  // Wait for >100us
	 lcd_cmd_8bit_mode( LCD_MODE_8BIT_1LINE ); // Function Set
	
}

void lcd_cmd_4bit_mode(unsigned char lcd_cmd){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RS=0;
	RW=0;
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(lcd_cmd&0xF0); // Send Higher nibble
	en_strobe();
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((lcd_cmd<<4)&0xF0); // Send Lower nibble
	en_strobe();
}

void lcd_cmd_8bit_mode(unsigned char lcd_cmd){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RW=0;
	LCD_DATA_PORT=lcd_cmd;
	en_strobe();
}

void lcd_data_4bit_mode(unsigned char lcd_data){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RS=1;
	RW=0;
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(lcd_data&0xF0); // Send Higher nibble 
	en_strobe();
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((lcd_data<<4)&0xF0); // Send Lower nibble 
	en_strobe();
}

void lcd_data_8bit_mode(unsigned char lcd_data){
	
	MS_DELAY(2); //Wait for busy flag to be stable
	RS=1;
	RW=0;
	LCD_DATA_PORT=lcd_data;
	en_strobe();
}

void MS_DELAY(unsigned int delay){
	
	uint16_t i,j;
	for(i=0;i<delay;i++){
		for(j=0;j<1275;j++){}
	}
}

/*------------------------------------------------------------------------------------------------------
                                              END OF FILE
--------------------------------------------------------------------------------------------------------*/