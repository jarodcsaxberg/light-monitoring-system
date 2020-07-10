#ifndef _COMMAND_H__
#define _COMMAND_H__

typedef struct command {
  char * cmd_string;
  void (*cmd_function)(char * arg);
} command_t;

/*************************************Command Parsing*************************/
int parse_command (uint8_t *line, uint8_t **command, uint8_t **args);
int execute_command(uint8_t * line);

/************************************Command Functions************************/
void help_command(char *arguments);
void lof_command(char *arguments);
void lon_command(char *arguments);
void test_command(char *arguments);
void ds_command(char* arguments);
void ts_command(char* arguments);
void temp_command(char *arguments);
void tsl237_command(char *arguments); 
void battery_command(char *arguments);
void sample_command(char *arguments);
void log_command(char *arguments);
void data_command(char* arguments);
void erase_command(char* arguments);

#endif //#ifndef _COMMAND_H__
