/*
 * TWI.c
 *
 * Created: 2/26/2017 11:20:27 AM
 *  Author: elbehairy
 */ 

#include "TWI.h"

void twi_Init(){
	DDRC = 0x00; 
	TWSR = 0x00;
	TWBR = 0x48;
}

void twiStart(){
	TWCR = (1 << TWINT) |(1 << TWSTA)|(1 << TWEN); 
	while(!(TWCR & (1 << TWINT)));
}

void twiStop(){
	TWCR = (1 << TWINT) |(1 << TWSTO)|(1 << TWEN); 
}

void twiWrite(int data){
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
}
int twiRead(){
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}
int twiReadRegister(int address, int address2 ,int reg){
	int data;
	twiStart();
	twiWrite(address);
	twiWrite(reg);
	twiStart();
	twiWrite(address2);
	data = twiRead();
	twiStop();
	return data;
}


void twiWriteRegister(int address, int reg, int data){
	twiStart();
	twiWrite(address);
	twiWrite(reg);
	twiWrite(data);
	twiStop();
}
