#ifndef _BUFFER_H__
#define _BUFFER_H__

#define BUF_SIZE 40

void buf_enqueue(uint8_t);
void buf_dequeue();
void buf_process();

void terminal_line(); 

#endif //#ifndef _BUFFER_H__
