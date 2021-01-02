/*
 * RTC.h
 *
 * Created: 2/26/2017 2:02:17 PM
 *  Author: elbehairy
 */ 


#ifndef RTC_H_
#define RTC_H_

#define F_CPU 16000000UL

#include "TWI.h"
#include <stdbool.h>

#define RTC_WriteMode	0xD0 // write the device address
#define RTC_ReadMode	0xD1 // read the device address
#define RTC_SEC			0x00
#define RTC_MIN			0x01
#define RTC_HOUR		0x02
#define RTC_DAY			0x03
#define RTC_DATA		0x04
#define RTC_MONTH		0x05
#define RTC_YEAR		0x06
#define Mode12Hour		40
#define RTC_ControlReg	0x07

typedef struct{
  bool AmPm;
  bool Mode12_24;
  int sec;
  int min;
  int hour;
  int weekDay;
  int date;
  int month;
  int year;
}RTC;

void RTC_Init();
void RTC_WriteDataTime(RTC * data);
void RTC_ReadDataTime(RTC * data);
int BCD_to_Decimal(int temp);//BCD to decimal
int Decimal_to_BCD(int temp);//Decimal converted to BCD code



#endif /* RTC_H_ */