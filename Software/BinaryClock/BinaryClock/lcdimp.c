/*
 * lcdimp.c
 *
 * Created: 11/2/2016 9:01:33 AM
 *  Author: elbehairy
 */ 


#include "lcd.h"

// LCD Custom Character
uint8_t DownArrow[8] = {0b00000,0b00000,0b00100,0b00100,0b00100,0b10101,0b01010,0b00100};
uint8_t LeftArrow[8] = {0b00000,0b00100,0b01000,0b11111,0b01000,0b00100,0b00000,0b00000};
uint8_t UpArrow[8] = {0b00100, 0b01010,0b10101,0b00100,0b00100,0b00100,0b00100,0b00000};
uint8_t _20Battery[8] = {0b01110,0b10001,0b10001,0b10001,0b10001,0b11111,0b11111,0b00000};
uint8_t _40Battery[8] = {0b01110,0b10001,0b10001,0b10001,0b11111,0b11111,0b11111,0b00000};
uint8_t _60Battery[8] = {0b01110,0b10001,0b10001,0b11111,0b11111,0b11111,0b11111,0b00000};
uint8_t _80Battery[8] = {0b01110,0b10001,0b11111,0b11111,0b11111,0b11111,0b11111,0b00000};
uint8_t _100Battery[8] = {0b01110,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b00000};
//??????????????????????????????????????????????????????????????????????????????
void Write4bit(int num){
	if(num & (1 << 7)){
		data |= (1 << D7);
	}else{
		data &= ~(1 << D7);	
	}
	
	if(num & (1 << 6)){
		data |= (1 << D6);
	}else{
		data &= ~(1 << D6);		
	}
	
	if(num & (1 << 5)){
		data |= (1 << D5);
	}else{
 		data &= ~(1 << D5);	
	}
	
	if(num & (1 << 4)){
		data |= (1 << D4);
	}else{
		data &= ~(1 << D4);
	}
	
	data |= (1 << EN);
	shiftRegisterLCD(data);
	_delay_us(1);
	data &= ~(1 << EN);
	shiftRegisterLCD(data);
	_delay_us(1);
}

void lcd4BitIns(int ins){
	data = 0;
	data &= ~(1 << RS);
	data &= ~(1 << EN);
	shiftRegisterLCD(data);
	Write4bit(ins);
	Write4bit(ins << 4);
}

void lcd4Bitdata(char ch){
	data = 0;	
	data |= (1 << RS);
	data &= ~(1 << EN);
	shiftRegisterLCD(data);	
	Write4bit(ch);
	Write4bit(ch << 4);
	_delay_us(80);
}
void lcd4BitStr(char*str){
	for(uint8_t i = 0; i < strlen(str); i ++){
		lcd4Bitdata(str[i]);
	}
}

void lcd4Bit_Init(){
	data = 0;
	LCD_DDR_PORTB |= LCD_PORTB_MASK;
	LCD_DDR_PORTD |= LCD_PORTD_MASK;
	_delay_ms(100);
	data &= ~(1 << RS);
	data &= ~(1 << EN);
	shiftRegisterLCD(data);
	Write4bit(_8_BIT);
	_delay_ms(10);

	Write4bit(_8_BIT);
	_delay_us(200);

	Write4bit(_8_BIT);
	_delay_us(200);
	
	Write4bit(_4_BIT);
	_delay_us(80);
	
	lcd4BitIns(_4_BIT);
	_delay_us(80);
	
	lcd4BitIns(LCD_CLEAR);
	_delay_ms(4);
		
	lcd4BitIns(LINE_ONE);
	_delay_us(80);

	lcd4BitIns(DISPLAY);
	_delay_us(80);
		
}

void LCD_build(unsigned char location, unsigned char *ptr){
      
      if(location<8){
          lcd4BitIns(0x40+(location*8));
		  _delay_us(80);
          for(int i=0;i<8;i++)
             lcd4Bitdata(ptr[ i ]);
     }
}
void LCD_DisplayChar(unsigned char location,unsigned char pos){
	 lcd4BitIns(pos);
	 _delay_us(80);
	 lcd4Bitdata(location);

}
void lcd4bitInt(int x){
	sprintf(Buffer,"%d",x);
	lcd4BitStr(Buffer);
}

void shiftRegisterLCD(int data){
LCDD &= ~(1 << CLK);
LCDB &= ~(1 << RCLK);
	for(int i = 7; i >= 0; i --){
		if((data & (1 << i)) && i <= 5){
			LCDD |= (1 << SER);
		}else{
			LCDD &= ~(1 << SER);	
		}
		LCDD |= (1 << CLK);	
		LCDD &= ~(1 << CLK);					
	}
	LCDB |= (1 << RCLK);
}
