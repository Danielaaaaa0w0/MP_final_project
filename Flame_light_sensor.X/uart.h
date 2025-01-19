#ifndef _UART_H
#define _UART_H

extern volatile int string_ready;
extern char mystring[];

void UART_Initialize(void);
void UART_Write(unsigned char data);
void UART_Write_Text(char* text);
void ClearBuffer();
void UART_Read();
char *GetString();
int GetLen();

#endif