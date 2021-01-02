/*
 * RTCimp.c
 *
 * Created: 2/26/2017 2:02:33 PM
 *  Author: elbehairy
 */ 

#include "RTC.h"


void RTC_Init(){
	twi_Init();
	twiStart();
	twiWrite(RTC_WriteMode);
	twiWrite(RTC_ControlReg);
	twiWrite(0x00);
	twiStop();
}
void RTC_WriteDataTime(RTC * data){
	if(data -> Mode12_24 ){
		data ->hour += (Mode12Hour | (data -> AmPm << 2) |(data -> AmPm << 4));
		twiWriteRegister(RTC_WriteMode,RTC_HOUR,Decimal_to_BCD(data -> hour));
	}else{
		twiWriteRegister(RTC_WriteMode,RTC_HOUR,Decimal_to_BCD(data -> hour));		
	}
	twiWriteRegister(RTC_WriteMode,RTC_SEC,Decimal_to_BCD(data -> sec));
	twiWriteRegister(RTC_WriteMode,RTC_MIN,Decimal_to_BCD(data -> min));
	twiWriteRegister(RTC_WriteMode,RTC_DAY,Decimal_to_BCD(data -> weekDay));
	twiWriteRegister(RTC_WriteMode,RTC_DATA,Decimal_to_BCD(data -> date));
	twiWriteRegister(RTC_WriteMode,RTC_MONTH,Decimal_to_BCD(data -> month));
	twiWriteRegister(RTC_WriteMode,RTC_YEAR,Decimal_to_BCD(data -> year));
	
}
void RTC_ReadDataTime(RTC * data){
	
	data -> sec = BCD_to_Decimal(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_SEC));
	data -> min = BCD_to_Decimal(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_MIN));
	if(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_HOUR) & 0x40){
		data->Mode12_24 = 1;
		data -> hour = twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_HOUR);
		if((data -> hour) & 0x20){
			data -> AmPm = 1;
		}else{
			data -> AmPm = 0;
		}
		data -> hour = BCD_to_Decimal((data -> hour)& 0x1f);
	}else{
		data->Mode12_24 = 0;
		data -> hour = BCD_to_Decimal(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_HOUR));		
	}
	data -> weekDay = BCD_to_Decimal(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_DAY));
	data -> date = BCD_to_Decimal(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_DATA));
	data -> month = BCD_to_Decimal(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_MONTH));
	data -> year = BCD_to_Decimal(twiReadRegister(RTC_WriteMode,RTC_ReadMode,RTC_YEAR));

}

int BCD_to_Decimal(int temp)//BCD to decimal
{
	int a,b,c;
	a=temp;
	b=0x00;
	if(a>=16)
	{
		while(a>=16)
		{
			a=a-16;
			b=b+10;
			c=a+b;
			temp=c;
		}
	}
	return temp;
}
int Decimal_to_BCD(int temp)//Decimal converted to BCD code
{
	int a,b,c;
	a=temp;
	b=0x00;
	if(a>=10)
	{
		while(a>=10)
		{
			a=a-10;
			b=b+16;
			c=a+b;
			temp=c;
		}
	}
	return temp;
}
