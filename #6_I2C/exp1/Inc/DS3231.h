#ifndef __DS3231_H
#define __DS3231_H

#include "stdint.h"


#define  DS3231_ADDRESS  	0xD0

/* Timekeeper Registers */
#define  Seconds_ADDRESS  	0x00
#define  Minutes_ADDRESS  	0x01
#define  Hours_ADDRESS   	0x02
#define  Day_ADDRESS     	0x03
#define  Date_ADDRESS    	0x04
#define  Month_ADDRESS  	0x05
#define  Year_ADDRESS    	0x06
#define  Control_ADDRESS 	0x07


 typedef struct {
              uint8_t Second;
              uint8_t Minute;
              uint8_t Hour;
	            uint8_t DAY;
              uint8_t Date;
              uint8_t Month;
              uint8_t Year;
}DS3231_time;




void DS3231_GetTime(uint8_t *Get_Sec , uint8_t *Get_min ,uint8_t *Get_hour,uint8_t *Get_day ,uint8_t *Get_date,uint8_t *Get_month ,uint8_t *Get_year);
void DS3231_SetTime( DS3231_time time);
unsigned char hex2bcd (unsigned char x);
unsigned char bcd2bin(unsigned char x);



#endif
