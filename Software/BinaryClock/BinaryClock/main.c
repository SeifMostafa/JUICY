/*
 * BinaryClock.c
 *
 * Created: 12/25/2020 10:26:14 PM
 * Author : mosta
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "RTC.h"
#include "lcd.h"


void row(int data){
	PORTD &= ~(1 << PORTD4);
	PORTD &= ~(1 << PORTD5);
	for(int i = 7; i >= 0; i --){
		if( data & (1 << i)){
			PORTD |= (1 << PORTD3);
			}else{
			PORTD &= ~(1 << PORTD3);
			 		
		}

		PORTD |= (1 << PORTD5);
		PORTD &= ~(1 << PORTD5);
	}
	PORTD |= (1 << PORTD4);
}

void column(int data){
	PORTD &= ~(1 << PORTD1);
	PORTD &= ~(1 << PORTD2);
	for(int i = 7; i >= 0; i --){
		if( data & (1 << i)){
			PORTD |= (1 << PORTD0);
			}else{
			PORTD &= ~(1 << PORTD0);
				
		}

		PORTD |= (1 << PORTD2);
		PORTD &= ~(1 << PORTD2);
	}
	PORTD |= (1 << PORTD1);

}

int Menna[5][16] = {
	{
		0B10000001,
		0B10000001,
		0B10000001,
		0B10000001,
		0B10011001,
		0B10100101,
		0B11000011,
		0B10000001
		},{
		0B01111100,
		0B01000000,
		0B01000000,
		0B01111100,
		0B01000000,
		0B01000000,
		0B01000000,
		0B01111100
		},{
		0B10000001,
		0B10000011,
		0B10000101,
		0B10001001,
		0B10010001,
		0B10100001,
		0B11000001,
		0B10000001
		},{
		0B01000000,
		0B01000001,
		0B01000010,
		0B01000100,
		0B01001000,
		0B01010000,
		0B01100000,
		0B01000000
		},{
		0B10100001,
		0B10100001,
		0B10111111,
		0B10111111,
		0B10100001,
		0B10100001,
		0B10100001,
		0B10011110
	}};
	

void displayMenna(){
	int x = 0;
	int time =1000;
	for(int an = 0; an < 4;){
					
		for (int y = 0; y < 25; y ++)
		{
			for(int i = 0; i < 8; i++){
				column(Menna[an][i] << x | Menna[1+an][i] >> (8 - x));
				row(1 << i);
				_delay_us(time);
			}
		}
		x++;
		if(x > 8){
			x = 0;
			an ++;
		}
	}
}


int main(void)
{ 
	RTC data;
	RTC_Init();
	lcd4Bit_Init();
	DDRD = 0xff;
	int counter = 1,start = 1;
/*
	data.hour = 3;
	data.min = 59;
	data.sec = 0;
	data.date = 31;
	data.month = 12;
	data.year = 2020;
	data.AmPm = 1;
	data.Mode12_24 = 1;
	RTC_WriteDataTime(&data);
*/
	while(1){



			RTC_ReadDataTime(&data);
			
			column(0x80);
			row(data.hour/10);
			_delay_ms(2);
			column(0x40);
			row(data.hour%10);
			_delay_ms(2);

			column(0);
			row(0);

			column(0x10);
			row(data.min/10);
			_delay_ms(2);
			column(0x08);
			row(data.min%10);
			_delay_ms(2);

			column(0);
			row(0);
			
			column(0x02);
			row(data.sec/10);
			_delay_ms(2);
			column(0x01);
			row(data.sec%10);
			_delay_ms(2);

			column(0);
			row(0);
			if((data.hour == 11 && data.min == 28 && counter != 0) || start){
				displayMenna();
				counter = 0;
				start = 0;
				}else if(data.hour == 11 && data.min != 28) {
				counter = 1;
			}
		
	}
}

