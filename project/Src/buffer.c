#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "command.h"
#include "rtc.h"

uint8_t buf[BUF_SIZE];
uint8_t recv;
uint8_t pos = 0;

void buf_enqueue(uint8_t c){
  recv = c;
}

void buf_dequeue(){
  if(pos < 1){
    pos = 0;
    return;
  }
  printf("\b \b");
  pos -= 1;
}

void buf_process(){
  if(recv != 0){
    if(pos == BUF_SIZE-1 && recv != 0x7f){
      printf("\nReached end of buffer, overwriting.\r\n");
      pos = 0;
      terminal_line();
      recv = 0;
      return;
    }

    if(recv == 0x7f){
      buf_dequeue();
    }else if(recv == 0x0d){
      printf("\r\n");
      buf[pos] = '\0';
      if(execute_command(buf) == -2)
        printf("NOK (invalid command: %s)\r\n", buf);
      pos = 0;
      terminal_line();
    }else{
      buf[pos] = recv;
      pos++;
      printf("%c", recv);
    }
    
    recv = 0;
  }
}


void terminal_line() {
  char* td = get_td();
  printf("%s IULS> ", td);
  free(td);
}

