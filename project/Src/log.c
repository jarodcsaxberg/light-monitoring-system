#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <limits.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include "retarget.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"
#include "sensor.h"
#include "rtc.h"

extern uint64_t __fini_array_end;
extern uint64_t _edata;
extern uint64_t _sdata;

flash_status_t fs;

/*
  uint8_t watermark;
  uint8_t status;
  uint16_t record_number;
  uint32_t timestamp;
  uint8_t msg[8]; 
*/
//Print log records from flash
void print_logs(int count){
  uint64_t* start = fs.data_start;
  uint64_t* end = fs.next_address;
  int i = 0;

  while(start > end){
    if(((*start & MASK_STATUS) >> 8) == 2){
      if(i == count) 
        break;

      uint16_t record_number = (*start & MASK_RECORD_NUMBER) >> 16;
      uint32_t timestamp = (*start & MASK_TIMESTAMP) >> 32;
      start--;
      uint8_t* msg = (uint8_t*) start;
      start--;      

      time_t rawtime = (time_t) timestamp;
      struct tm ts;
      char time[20];

      ts = *localtime(&rawtime);
      strftime(time, sizeof(time), "%m/%d/%Y,%H:%M:%S", &ts);

      printf("L,%d,%s,", record_number, time);

      for(int i = 0; msg[i] != '\0'; i++){
        printf("%c", msg[i]);
      }
      
      printf("\r\n");

      if(count > 0)
        i++;
    } else {
      start -= 2;
    }
  }
}

/*
  uint8_t watermark;               
  uint8_t status;
  uint16_t record_number;
  uint32_t timestamp;            
  uint16_t battery_voltage
  int16_t temperature;
  uint32_t sensor_period;
*/
//Print data records from flash
void print_data(int count){
  uint64_t* start = fs.data_start;
  uint64_t* end = fs.next_address;
  int i = 0;
  
  while(start > end){
    if(((*start & MASK_STATUS) >> 8) == 1){
      if(i == count)
        break;

      uint16_t record_number = (*start & MASK_RECORD_NUMBER) >> 16;
      uint32_t timestamp = (*start & MASK_TIMESTAMP) >> 32;
      start--;
      uint16_t voltage = *start & MASK_VOLTAGE;
      int16_t temperature = (*start & MASK_TEMPERATURE) >> 16;
      uint32_t period = (*start & MASK_SENSOR_PERIOD) >> 32;
      start--;

      time_t rawtime = (time_t) timestamp;
      struct tm ts;
      char time[20];

      ts = *localtime(&rawtime);
      strftime(time, sizeof(time), "%m/%d/%Y,%H:%M:%S", &ts);

      printf("D,%d,%s,%d.%d,%d,%d.%d\r\n", record_number, time, (int)voltage/1000, 
                                           (int)voltage%1000, (int)temperature, 
                                           (int)period/1000, (int)period%1000);
      if(count > 0)
        i++;
    } else {
      start -= 2;
    }
  }

}

//Writes current sensor readings to flash
uint8_t store_entry(void) {
  uint32_t period = calculate_period();
  uint32_t temp = read_temp();
  uint32_t voltage = read_vrefint();
  uint32_t t = get_td_bits();

  /*Error checking*/
  if(t < 0)
    return -1;

  sensordata_t data = {0};
  data.watermark = 0x01;
  data.status = SENSOR_DATA;
  data.record_number = fs.next_record_number;
  data.timestamp = t;
  data.battery_voltage = (uint16_t) voltage;
  data.temperature = (int16_t) temp;
  data.sensor_period = (uint32_t) period;

  /*Data structure debug*/
/*
  printf("-----------------\r\n");
  printf("Data Struct:\r\n");
  printf("watermark: %u\r\n", data.watermark);
  printf("status: %u\r\n", data.status);
  printf("record: %u\r\n", data.record_number);
  printf("timestamp: %ld\r\n", data.timestamp);
  printf("batt_volt: %u\r\n", data.battery_voltage);
  printf("temperature: %d\r\n", data.temperature);
  printf("sensor: %lu\r\n", data.sensor_period);
*/
  uint8_t write_err = write_record(&data);
  if(write_err) {
    printf("NOK (store_entry: write error)\r\n");
    return 1;
  }
  return 0;
}

//writes a short message to flash
uint8_t log_entry(char *message) {
  uint32_t t = get_td_bits();
  int i;

  /*Error checking*/
  if(t < 0)
    return -1;
  if(message == NULL)
    return -1;

  logdata_t data = {0};
  data.watermark = 0x01;
  data.status = LOG_DATA;
  data.record_number = fs.next_record_number;
  data.timestamp = t;
  //Copy the first seven characters of message
  for(i=0; message[i] && i < 7; i++) {
    data.msg[i] = (uint8_t)message[i];
  }
  data.msg[i] = '\0';

  /*Data structure debug*/
/*
  printf("-----------------\r\n");
  printf("Data Struct:\r\n");
  printf("watermark: %u\r\n", data.watermark);
  printf("status: %u\r\n", data.status);
  printf("record: %u\r\n", data.record_number);
  printf("timestamp: %ld\r\n", data.timestamp);
  printf("msg: %s\r\n", data.msg);
*/
  uint8_t write_err = write_record(&data);
  if(write_err) {
    printf("NOK (log_entry: write error)\r\n");
    return 1;
  }
  return 0;
}

/******************************************************************************/
/*****************************Flash Section************************************/
/******************************************************************************/

//function to initialize a sentinel to its position
uint8_t write_sentinel(uint64_t *address, raw_t *sentinel) {
  HAL_StatusTypeDef err_status;
  uint64_t *write_address;
  //error checking
  if(!sentinel || !address) {
    printf("Sentinel or address is not set\r\n");
    return 1;
  }

  write_address = address;

  HAL_FLASH_Unlock();
  err_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t) write_address, sentinel->data0);
  if (err_status) {
    HAL_FLASH_Lock();
    printf("NOK (write_sentinel: raw0)\r\n");
    return 1;
  }
  write_address--; //move to the next address before writing next 8 bytes
  err_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t) write_address, sentinel->data1);
  if (err_status) {
    HAL_FLASH_Lock();
    printf("NOK (write_sentinel: raw1)\r\n");
    return 1;
  }
  HAL_FLASH_Lock();

  return 0;
}

//function to write data to flash
uint8_t write_record(void *record) {
  raw_t *write_data;
  HAL_StatusTypeDef err_status=0;

  //error checking
  if(!record){
    return 1;
  }
  if(fs.total_records >= fs.max_possible_records) {
    printf("NOK (write_record: flash_full)\r\n");
    return 1;
  }

  write_data = (raw_t *) record;

  HAL_FLASH_Unlock();
  err_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t) fs.next_address, write_data->data0);
  if (err_status) {
    printf("NOK (write_record: first flash)\r\n");
    HAL_FLASH_Lock();
    return 1;
  }
  fs.next_address--; //move to the next address before writing next 8 bytes
  err_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t) fs.next_address, write_data->data1);
  if (err_status) {
    printf("NOK (write_record: second flash)\r\n");
    HAL_FLASH_Lock();
    return 1;
  }
  fs.next_address--; //move to the next address before writing next 8 bytes
  HAL_FLASH_Lock();
  //update fs
  fs.next_record_number++;
  fs.total_records++;

  return 0;
}

uint8_t flash_write_init() {
  sensordata_t *sd = {0};
  uint16_t record_counter = 0;
  //raw_t sentinel_top = {SENTINEL_MARK_TOP, 0};
  raw_t sentinel_bottom = {SENTINEL_MARK_BOTTOM, 0};

  //address the end of the program
  uint64_t *program_end = (uint64_t *) ((uint32_t )&__fini_array_end
                                        + (uint32_t)&_edata
                                        - (uint32_t)&_sdata);
  //address the top  of flash, fixed based on MCU variant
  uint64_t *top = (uint64_t *) FLASH_END;
  //address of the bottom of flash available for records
  uint64_t *bottom = (uint64_t *) (((uint32_t)program_end & ~0x7FF) + 0x800);
  //top memory pointer: located at the very top of flash
  uint64_t *pt = top;//find_sentinel_top(top, bottom);
  //bottom memory pointer: located at the first open page after the software
  uint64_t *pb = find_sentinel_bottom(top, bottom);

  /*
  There are 4 cases for the top and bottom memory ptrs.
  1) pt = 0, pb =0: memory uninitialized
  Action: Erase memory if needed, add top and bottom sentinels
  2) pt > 0, pb =0: lower sentinel has been corrupted,
  Action: restore lower sentinel. Accept that dat may have been lost
  3) pt = 0, pb >0: upper sentinel has been corrupted
  Action: erase memory, add top and bottom sentinels
  4) pt > 0, pb >0: Memory is initialized
  Action: no memory changes are necessary
  */
  /*********************************************Sentinel Checking**************/
  if((!pt) && (!pb)) {
    /*Write top sentinel*/
    /*
    if(write_sentinel(top,&sentinal_top)) {
      printf("Failed to write top sentinel\r\n");
      return -1;
    }*/
    //*********************************end fix**************************

    //Erase flash
    if(flash_erase()) {
      printf("NOK (flash_write_init: erase flash)\r\n");
      return -1;
    }

    /*Write bottom sentinel*/
    if(write_sentinel(bottom,&sentinel_bottom)) {
      printf("NOK (flash_write_init: bottom sentinel)\r\n");
      return -1;
    }
  }
  else if(pt && !pb) {
    /*Write bottom sentinel*/
    if(write_sentinel(bottom, &sentinel_bottom)) {
      printf("NOK (flash_write_init: bottom sentinel)\r\n");
      return -1;
    }
  }
  else if(!pt && pb) {
    return -1;
  }
  else if(pt && pb) {
    if(pb!=bottom) {
      printf("NOK (flash_write_init: sentinel not at bottom)\r\n");
      return -1;
    }
  }
  else {
    printf("NOK (flash_write_init: undefined memory condition)\r\n");
    return -1;
  }

  /*********************************************Initialize Flash***************/
  fs.data_start = top - 2;
  fs.max_possible_records = (((uint32_t)top-(uint32_t)bottom)>>4)-1;
  sd = (sensordata_t *) top;
  sd--;
  while ((sd->watermark!=0xFF) && (sd->watermark!=0xa5)) {
    record_counter++;
    sd--;
  }
  fs.next_record_number = record_counter;
  fs.total_records = record_counter;
  fs.next_address = (uint64_t *) sd;

  return 0;
}

//No longer used
/*
uint64_t *find_sentinel_top(uint64_t *top, uint64_t *bottom) {
  return 0;
}
*/

uint64_t *find_sentinel_bottom(uint64_t *top, uint64_t *bottom) {
  //address the bottom of flash, fixed based on MCU variant
  uint64_t *current_addr = bottom;

  //start from the bottom of flash, and move up until bottom is found
  //or until the top of flash is reached
  while(*current_addr != SENTINEL_MARK_BOTTOM) {
    //printf("Curr: %x\r\n", current_addr);
    current_addr += 2;  //Each data entry has width 128 bits, so add 2
    if(current_addr > top) {
      printf("NOK (find_sentinel_bottom: sentinel not found)\r\n");
      return 0;
    }
  }
  return current_addr;
}
/******************************************************************************/
/****************************Flash Erase***************************************/
/******************************************************************************/
int flash_erase(void) {
  uint32_t FirstPage = 0, NbOfPages = 0, BankNumber = 0;
  uint32_t PAGEError = 0;
  /* __IO uint32_t data32 = 0 , MemoryProgramStatus = 0; */

  static FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t program_end = ((uint32_t )&__fini_array_end
                  + (uint32_t)&_edata
                  - (uint32_t)&_sdata);
  uint32_t bottom  = (((uint32_t)program_end & ~0x7FF) + 0x800);
  uint32_t top = FLASH_END;

  HAL_FLASH_Unlock();
  /* Clear OPTVERR bit set on virgin samples */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
  /* Get the 1st page to erase */
  FirstPage = GetPage(bottom);
  /* Get the number of pages to erase from 1st page */
  NbOfPages = GetPage(top) - FirstPage + 1;
  /* Get the bank */
  BankNumber = GetBank(bottom);
  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Banks       = BankNumber;
  EraseInitStruct.Page        = FirstPage;
  EraseInitStruct.NbPages     = NbOfPages;

  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) {
    HAL_FLASH_Lock();
    return (-1);
  }
  HAL_FLASH_Lock();
  return(0);
}

static uint32_t GetPage(uint32_t Addr) {
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }

  return page;
}

static uint32_t GetBank(uint32_t Addr) {
  return FLASH_BANK_1;
}
