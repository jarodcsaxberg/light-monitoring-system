#include "main.h"

void set_alarm();
void reset_alarm();
void alarm_process();
char* get_td();
uint32_t get_td_bits();
void set_date(int, int, int);
void set_time(int, int, int);
void RetargetRTC(RTC_HandleTypeDef*);
int bcd2dec(uint8_t);
