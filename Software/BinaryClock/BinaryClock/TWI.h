/*
 * TWI.h
 *
 * Created: 2/26/2017 11:20:45 AM
 *  Author: elbehairy
 */ 

#ifndef TWI_H_
#define TWI_H_

#define F_CPU 16000000UL

#include <avr/io.h>

	
void twi_Init();
void twiStart();
void twiStop();
void twiWrite(int data);
void twiWriteRegister(int address, int reg, int data);
int twiRead();
int twiReadRegister(int address, int address2 ,int reg);




#endif /* TWI_H_ */