#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "main.h"
#include <time.h>

int alarm_flag = 0;
RTC_HandleTypeDef* gHrtc;
int led = 0;
uint32_t tick;

void set_alarm(){
  alarm_flag = 1;
}

void reset_alarm(){
  alarm_flag = 0;
}

//Checks if alarm flag is raised, respond and reset the flag
void alarm_process(){
  if(alarm_flag){
    /*
    char* td = get_td();
    printf("\nalarmed at %s\r\n", td);
    terminal_line();
    free(td);
    */
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    led = 1;
    tick = HAL_GetTick();
    reset_alarm();
  }
  if(led == 1 && HAL_GetTick() - tick >= 100){
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    led = 0;
  }
}

/*
 *INPUT: time and date struct pointers
 *Sets time and date pointers to the current time and date from RTC.
 *Generally, HAL_RTC_GetDate() must be called after calling HAL_RTC_GetTime()
 *due to how the RTC registers work (even if we don't need the date).
 */
char* get_td() {
  char *td_s = malloc(sizeof(char)*20);
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  if (HAL_RTC_GetTime(gHrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK){
    printf("NOK (get_time: HAL_RTC_GetTime)\r\n");
    return NULL;
  }

  if (HAL_RTC_GetDate(gHrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK){
    printf("NOK (get_date: HAL_RTC_GetDate)\r\n");
    return NULL;
  }

  int mo = sDate.Month;
  int d = sDate.Date;
  int y = sDate.Year;
  int h = sTime.Hours;
  int mi = sTime.Minutes;
  int s = sTime.Seconds;

  td_s[0] = '0' + (mo >> 4) % 16;
  td_s[1] = '0' + (mo >> 0) % 16;
  td_s[2] = '/';
  td_s[3] = '0' + (d >> 4) % 16;
  td_s[4] = '0' + (d >> 0) % 16;
  td_s[5] = '/';
  td_s[6] = '2';
  td_s[7] = '0';
  td_s[8] = '0' + (y >> 4) % 16;
  td_s[9] = '0' + (y >> 0) % 16;
  td_s[10] = ' ';
  td_s[11] = '0' + (h >> 4) % 16;
  td_s[12] = '0' + (h >> 0) % 16;
  td_s[13] = ':';
  td_s[14] = '0' + (mi >> 4) % 16;
  td_s[15] = '0' + (mi >> 0) % 16;
  td_s[16] = ':';
  td_s[17] = '0' + (s >> 4) % 16;
  td_s[18] = '0' + (s >> 0) % 16;
  td_s[19] = '\0';

  return td_s;
}

uint32_t get_td_bits(){
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  if (HAL_RTC_GetTime(gHrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK){
    printf("NOK (get_time: HAL_RTC_GetTime)\r\n");
    return -1;
  }

  if (HAL_RTC_GetDate(gHrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK){
    printf("NOK (get_date: HAL_RTC_GetDate)\r\n");
    return -1;
  }

  //obtain current time values
  int mo = bcd2dec(sDate.Month);     // 1-12
  int d = bcd2dec(sDate.Date);       // 1-31
  int y = bcd2dec(sDate.Year);       // 0-99
  int h = bcd2dec(sTime.Hours);      // 0-23
  int mi = bcd2dec(sTime.Minutes);   // 0-59
  int s = bcd2dec(sTime.Seconds);    // 0-59
  
  //store current time values into a struct tm
  struct tm current = {0};
  current.tm_sec = s;
  current.tm_min = mi;
  current.tm_hour = h;
  current.tm_mday = d;
  //this is stored as "month since January"
  //subtract 1 because we store 1-12 as month
  current.tm_mon = mo - 1;
  //this is stored as "years since 1900"
  //add 100 to current year because we store year since 2000
  current.tm_year = y + 100;
  //set Daylight Savings flag to -1, which forces mktime() to figure it out
  current.tm_isdst = -1;

  //convert struct tm to epoch time, which is of type time_t
  time_t epoch_seconds = mktime(&current);
  //debug
  /*printf("Input time is %s\r\n", asctime(&current));*/
  /*printf("Converted time is %s\r\n", ctime(&epoch_seconds));*/

  return (uint32_t)epoch_seconds;
}

unsigned int dec2bcd(unsigned int num){
  unsigned int ones = 0;
  unsigned int tens = 0;
  unsigned int temp = 0;

  ones = num%10;
  temp = num/10;
  tens = temp<<4;
  return (tens + ones);
}

int bcd2dec(uint8_t num) {
  return num - 6 * (num >> 4);
}

void set_date(int m, int d, int y){
  RTC_DateTypeDef sDate = {0};

  if(m > 12 || m < 1){
    printf("NOK (set_date: invalid date)\r\n");
    return;
  }
  if(d > 31 || d < 1){
    printf("NOK (set_date: invalid date)\r\n");
    return;
  }
  if(y > 99 || y < 0){
    printf("NOK (set_date: invalid date)\r\n");
    return;
  }

  sDate.Month = dec2bcd(m);
  sDate.Date = dec2bcd(d);
  sDate.Year = dec2bcd(y);

  if (HAL_RTC_SetDate(gHrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK){
    printf("NOK (set_date: HAL_RTC_SetDate)\r\n");
  }else{
    printf("OK (set_date)\r\n");
  }

}

void set_time(int h, int m, int s){
  RTC_TimeTypeDef sTime = {0};
 
  if(h > 23 || h < 0){
    printf("NOK (set_time: invalid time)\r\n");
    return;
  }
  if(m > 59 || m < 0){
    printf("NOK (set_time: invalid time)\r\n");
    return;
  }
  if(s > 59 || s < 0){
    printf("NOK (set_time: invalid time)\r\n");
    return;
  }

 
  sTime.Hours = dec2bcd(h);
  sTime.Minutes = dec2bcd(m);
  sTime.Seconds = dec2bcd(s);
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;

  if(HAL_RTC_SetTime(gHrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK){
    printf("NOK (set_time: HAL_RTC_SetTime)\r\n");
  }else{
    printf("OK (set_time)\r\n");
  }
}

void RetargetRTC(RTC_HandleTypeDef *hrtc){
  gHrtc = hrtc;
}
