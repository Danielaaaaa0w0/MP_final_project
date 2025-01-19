#include <xc.h>

void CCP1_Initialize() {
    TRISCbits.TRISC2 = 0;           // RC2 pin is output.
    CCP1CONbits.CCP1M = 0b1100;     // PWM mode
    PIR1bits.CCP1IF = 0;
    IPR1bits.CCP1IP = 1;
    
    LATCbits.LATC2 = 0;

    /* Duty cycle
     * = (CCPR1L:CCP1CON<5:4>) * Tosc * (TMR2 prescaler)
     * = (CCPR1L * 4 + CCP1CON<5:4>) * Tosc * (TMR2 prescaler)
     * (0x02:0b11) 352 us ~= -90 degree
     * (0x07:0b00) 896 us ~= -45 degree
     * (0x0B:0b01) 1440 us ~= 0 degree
     * (0x0F:0b10) 1984 us ~= 45 degree
     * (0x13:0b11) 2528 us ~= 90 degree
     */
//    CCPR1L = 0x13;
//    CCP1CONbits.DC1B = 0b11;
}

