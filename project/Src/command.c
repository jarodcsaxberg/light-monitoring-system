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

#include "command.h"
#include "rtc.h"
#include "sensor.h"
#include "log.h"

//Command list needs to be placed here. Moving it to command.h will cause 
//compilation error.
command_t commands[] = {
  {"help", help_command},
  {"lof", lof_command},
  {"lon", lon_command},
  {"test", test_command},
  {"ds", ds_command},
  {"ts", ts_command},
  {"temp", temp_command},
  {"tsl237", tsl237_command},
  {"battery", battery_command},
  {"sample", sample_command},
  {"log", log_command},
  {"data", data_command},
  {"ef", erase_command},
  {0,0}
};

/***********************************Retargeted Handlers***********************/
extern ADC_HandleTypeDef hadc1;

/************************************Command Execution************************/
//INPUT: line from ringbuffer
//returns 0 if command is successful, returns -1 of error

int execute_command(uint8_t * line) {
  uint8_t *cmd;
  uint8_t *arg;
  command_t *p = commands;
  int success = 0;

  if (!line) {
    printf("NOK (execute_command: line)\t\n");
    return (-1); // Passed a bad pointer 
  }
  if (parse_command(line,&cmd,&arg) == -1) {
    printf("NOK (execute_command: parse_command)\n\r");
    return (-1);
  }

  //loop through the list of all available commands
  //if there's a matching name, call it
  while (p->cmd_string) {
    if (!strcmp(p->cmd_string,(char *) cmd)) {
      if (!p->cmd_function) {
        printf("NOK (execute_command: p->cmd_function)\r\n");
        return (-1);
      }
      (*p->cmd_function)((char *)arg);            // Run the command with the passed arguments
      success = 1;
      break;
    }
    p++;
  }
  if (success) {
    return (0);
  } else {
    return (-2);
  }
}

//INPUT: line from ringbuffer, double pointer to command and double pointer to args
//The function will parse the line, store the name of the command into **command,
//and store the string of remaining arguments into **args
//returns 0 if parsing successful, -1 if there is error
int parse_command (uint8_t *line, uint8_t **command, uint8_t **args)
{
  char* token = strtok((char*) line, ",");

  if(token == NULL)
    return -1;

  if(token != NULL){
    *command = (uint8_t*) token;
  }

  return 0;
}

/*****************************Command functions*******************************/
//Displays the available commands in the commands[] array
void help_command(char *arguments) {
  command_t *p = commands;

  printf("Available commands:\r\n");
  while(p->cmd_string)
  {
    printf("%s\r\n", p->cmd_string);
    p++;
  }
  printf("OK\r\n");
}

//Turns LED3 on. Perhaps could take an argument to specify which GPIO port
void lof_command(char *arguments) {
  printf("LED OFF\r\n");
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}

//Turns LED3 on. Perhaps could take an argument to specify which GPIO port
void lon_command(char *arguments) {
  printf("LED ON\r\n");
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
}

//Prints the individual arguments passed to the function, each on a newline
//Arguments string is assumed to be in format "arg0,arg1,arg2,...argn".
void test_command(char *arguments) {
  char * arg;
  
  //strtok() takes a string to be split and a delimiter. All subsequent calls
  //to strtok() returns a ptr to the next "token" in the input string.
  arg = strtok(arguments, ",");

  if(arg == NULL)
    printf("NOK (test_command: no arguments)\r\n");

  while(arg != NULL)
  {
    printf("%s\r\n", arg);
    arg = strtok(NULL, ",");
  }
}

/************************************Set date/time***************************/

void ds_command(char* arguments) {
  int m, d, y;
  char *m_s, *d_s, *y_s; 
  char* args;

  args = strtok(arguments, ",");

  if(args == NULL){
    printf("NOK (ds_command: no arguments)\r\n");
    return;
  }
  
  m_s = args;
  if(!args){
    printf("NOK (ds_command: not enough arguments)\r\n");
    return;
  }

  args = strtok(NULL, ",");
  d_s = args;
  if(!args){
    printf("NOK (ds_command: not enough arguments)\r\n");
    return;
  }

  args = strtok(NULL, ",");
  y_s = args;
  if(!args){
    printf("NOK (ds_command: not enough arguments)\r\n");
    return;
  }

  m = atoi(m_s);
  d = atoi(d_s);
  y = atoi(y_s);

  set_date(m, d, y);
}

void ts_command(char* arguments) {
  int h, m, s;
  char *h_s, *m_s, *s_s;
  char* args;

  args = strtok(arguments, ",");

  if(args == NULL){
    printf("NOK (ds_command: no arguments)\r\n");
    return;
  }

  h_s = args;
  if(!args){
    printf("NOK (ds_command: not enough arguments)\r\n");
    return;
  }

  args = strtok(NULL, ",");
  m_s = args;
  if(!args){
    printf("NOK (ds_command: not enough arguments)\r\n");
    return;
  }

  args = strtok(NULL, ",");
  s_s = args;
  if(!args){
    printf("NOK (ds_command: not enough arguments)\r\n");
    return;
  }

  h = atoi(h_s);
  m = atoi(m_s);
  s = atoi(s_s);

  set_time(h, m, s);
}

/********************************Sensor Data**********************************/

void tsl237_command( char *arguments ) {
  float freq = calculate_freq();
  printf("Freq: %d.%d kHz\r\n", (int)freq/1000, (int)freq%1000);
}

void temp_command(char *arguments) {
  uint32_t temp;
  temp = read_temp();

  printf("%d C\r\n",(int)temp);
  printf("OK\r\n");
}

void battery_command(char *arguments) {
  uint32_t battery_voltage;
  battery_voltage = read_vrefint();

  printf("%d.%03d V\r\n",(int)battery_voltage/1000,(int)battery_voltage%1000);
  printf("OK\r\n");
}

/*************************************Logging Data****************************/
void sample_command(char *arguments) {
  uint8_t write_err;
  write_err = store_entry();

  if(write_err)
    printf("NOK (sample_command:bad store_entry)\r\n");
  else
    printf("OK\r\n");
}

void log_command(char *arguments) { // log command prints all logs
  char* args = strtok(arguments, ",");

  if(args == NULL){
    print_logs(-1);
    printf("OK\r\n");
  }else{
    if(atoi(args)){
      print_logs(atoi(args));
      printf("OK\r\n");
    }else{
      printf("NOK: (log_command: argument should be an int)\r\n");
    }
  }
}

void data_command(char *arguments){ // data command prints all data
  char* args = strtok(arguments, ",");

  if(args == NULL){
    print_data(-1);
    printf("OK\r\n");
  }else{
    if(atoi(args)){
      print_data(atoi(args));
      printf("OK\r\n");
    }else{
      printf("NOK: (data_command: argument should be an int)\r\n");
    }
  }
}

void erase_command(char *arguments){
  char* args = strtok(arguments, ",");

  if(strcmp(args, "all") == 0){
    printf("Erasing all flash...\r\n");

    if(flash_erase()) {
      printf("NOK: (erase_command: flash_erase)\r\n");
      return;
    }
    
    flash_write_init();
    printf("OK\r\n");
  } else {
    printf("NOK: (Use 'ef,all')\r\n");
  }
}
