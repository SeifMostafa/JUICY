/*
 * lcd.h
 *
 * Created: 11/2/2016 9:00:00 AM
 *  Author: elbehairy
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



// Pin lcd config
#define SER PORTD2
#define CLK PORTD3
#define RCLK PORTB0
#define LCDB PORTB
#define LCDD PORTD
#define LCD_DDR_PORTB DDRB
#define LCD_DDR_PORTD DDRD
#define LCD_PORTB_MASK 0x01
#define LCD_PORTD_MASK 0x0c

#define RS  0x00
#define EN  0x01
#define D4  0x02
#define D5  0x03
#define D6	0x04
#define D7	0x05



// LCD Instruction
#define LCD_CLEAR					0x01	// Clear LCD and set cursor to first location
#define LCD_HOME					0x02	// set cursor to first location	

// Entry Mode
#define DECREMENT_CURSOR			0x07	// Make cursor move to LEFT during writing
#define INCREMENT_CURSOR			0x05	// Make cursor move to RIGHT during writing

// Display Command
#define DISPLAY_OFF					0x08	// Display OFF
#define DISPLAY						0x0C	// Display ON Cursor OFF
#define DISPLAY_CURSOR				0x0E	// Display ON Cursor ON
#define DISPLAY_CURSOR_BLINKING		0x0F	// Display ON Cursor Blinking

//Cursor and Display
#define CURSOR_LEFT					0x10	// Make cursor move LEFT by one character		 
#define CURSOR_RIGHT				0x14	// Make cursor move RIGHT by one character
#define DISPLAY_LEFT				0x18	// Make display move LEFT by one character		
#define DISPLAY_RIGHT				0x1C	// Make cursor move RIGHT by one character

// LCD Lines
#define LINE_ONE	0x80
#define LINE_TWO	0xC0

// LCD Mode
#define _8_BIT 0x38					// it will use 8 pins for data or CMD and display in two line
#define _4_BIT 0x28					// it will use 4 pins for data or CMD and display in two line

// LCD Custom Character
uint8_t DownArrow[8];
uint8_t LeftArrow[8];
uint8_t UpArrow[8];
uint8_t _20Battery[8];
uint8_t _40Battery[8];
uint8_t _60Battery[8];
uint8_t _80Battery[8];
uint8_t _100Battery[8];
//??????????????????????????????????????????????????????????????????????????????

int data;
char Buffer[16];
void lcd4Bit_Init();
void Write4bit(int num);
void lcd4BitIns(int ins);
void lcd4Bitdata(char ch);
void lcd4BitStr(char*str);
void lcd4Bit_Init();
void LCD_build(unsigned char location, unsigned char *ptr);
void LCD_DisplayChar(unsigned char location, unsigned char pos);
void lcd4bitInt(int x);
void shiftRegisterLCD(int data);




#endif /* LCD_H_ */