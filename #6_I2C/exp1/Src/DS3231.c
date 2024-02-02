#include "stm32f1xx_hal.h"
#include "DS3231.h"


extern I2C_HandleTypeDef hi2c1;


void DS3231_SetTime( DS3231_time time)
{
	uint8_t data[2];
	
	
	data[0]=Seconds_ADDRESS;
	data[1]=0x7f;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);
	
	
  data[0]=Seconds_ADDRESS;
	data[1]=hex2bcd(time.Second);
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);

	
	data[0]=Minutes_ADDRESS;
	data[1]=hex2bcd(time.Minute);
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);
	
	data[0]=Hours_ADDRESS;
	data[1]=hex2bcd(time.Hour);
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);
	
	data[0]=Day_ADDRESS;
	data[1]=hex2bcd(time.DAY);
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);
	
	data[0]=Date_ADDRESS;
	data[1]=hex2bcd(time.Date);
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);
	
	
	data[0]=Month_ADDRESS;
	data[1]=hex2bcd(time.Month);
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);
	
	data[0]=Year_ADDRESS;
	data[1]=hex2bcd(time.Year);
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,2,50);
		
}

void DS3231_GetTime(uint8_t *Get_Sec , uint8_t *Get_min ,uint8_t *Get_hour,uint8_t *Get_day ,uint8_t *Get_date,uint8_t *Get_month ,uint8_t *Get_year)
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t mount;
	uint8_t year;
	uint8_t data[1];

	data[0]=Seconds_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(&hi2c1,DS3231_ADDRESS,&sec,1,1);
	*Get_Sec=bcd2bin(sec);
	
	data[0]=Minutes_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(&hi2c1,DS3231_ADDRESS,&min,1,1);
	*Get_min=bcd2bin(min);

	
	data[0]=Hours_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(&hi2c1,DS3231_ADDRESS,&hour,1,1);
	*Get_hour=bcd2bin(hour);



	data[0]=Day_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(&hi2c1,DS3231_ADDRESS,&day,1,1);
	*Get_day=bcd2bin(day);


	data[0]=Date_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(&hi2c1,DS3231_ADDRESS,&date,1,1);
	*Get_date=bcd2bin(date);


	data[0]=Month_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(&hi2c1,DS3231_ADDRESS,&mount,1,1);
	*Get_month=bcd2bin(mount);


	data[0]=Year_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1,DS3231_ADDRESS,data,1,1);
	HAL_I2C_Master_Receive(&hi2c1,DS3231_ADDRESS,&year,1,1);
	*Get_year=bcd2bin(year);


}
unsigned char bcd2bin(unsigned char x)
{
  uint8_t bin;
	bin=((x & 0xf0)>>4)*10 +(x & 0x0f);
  return (bin);
}

unsigned char hex2bcd (unsigned char x)
{
	uint8_t y;
	y = (x/10) <<4;
	y = y | (x % 10);
	return (y);	
}