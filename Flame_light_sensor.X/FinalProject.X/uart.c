#include <xc.h>
#include "string.h"

#define BUFFER_SIZE 20

volatile int string_ready = 0;
int len = 0;
char mystring[BUFFER_SIZE];

void UART_Initialize() {
    // Setting TX & RX
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;

    // Setting baud rate, OSC = 125 kHz, baud rate = 300
    TXSTAbits.SYNC = 0;
    BAUDCONbits.BRG16 = 1;
    TXSTAbits.BRGH = 0;
    SPBRG = 25;

    // Serial enable
    PIR1bits.TXIF = 0;
    PIR1bits.RCIF = 0;

    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;

    IPR1bits.TXIP = 0;
    PIE1bits.TXIE = 0;
    IPR1bits.RCIP = 0;
    PIE1bits.RCIE = 1;
}

void UART_Write(unsigned char data) {
    while (!TXSTAbits.TRMT);
    TXREG = data; // write to TXREG will send data 
}

void UART_Write_Text(char* text) {
    for (int i = 0; text[i] != '\0'; i++)
        UART_Write(text[i]);
}

void ClearBuffer() {
    memset((void*)mystring, 0, BUFFER_SIZE);
    string_ready = 0;
    len = 0;
}

void UART_Read() {
    char receivedChar = RCREG;
    
    if ((receivedChar == '\b' || receivedChar == 127) && len > 0){
        mystring[--len] = '\0';
    } else {
        mystring[len++] = receivedChar;
    }
      
    if (receivedChar == '\r'){
        string_ready = 1;
    }

    UART_Write(receivedChar);
}

char *GetString() {
    return mystring;
}

int GetLen(){
    return len;
}

void __interrupt(low_priority) L_ISR(void) {
    if (RCIF) {
        if (RCSTAbits.OERR) {
            CREN = 0;
            Nop();
            CREN = 1;
        }

        if (len >= BUFFER_SIZE)
            ClearBuffer();

        UART_Read();
    }
    return;
}