#include <xc.h>

void INTERRUPT_Initialize(void) {
    RCONbits.IPEN = 1;      // enable Interrupt Priority mode
    INTCONbits.GIEH = 0;    // enable high priority interrupt
    INTCONbits.GIEL = 0;    // enable low priority interrupt
    
    // External interrupt
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 0;
    
    // ADC interrupt
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    
    // TMR0 interrupt
    INTCON2bits.TMR0IP = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 0;
    
    // TMR1 interrupt
    IPR1bits.TMR1IP = 1;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 0;
    
    // TMR2 interrupt
    IPR1bits.TMR2IP = 1;
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;
}