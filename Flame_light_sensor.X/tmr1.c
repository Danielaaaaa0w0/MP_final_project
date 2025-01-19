#include <xc.h>

void TMR1_Initialize(void) {
    T1CONbits.TMR1CS = 0;       // Internal clock

    /* Prescale bits
     * T1CKPS = 0b00 (1:1)
     * T1CKPS = 0b01 (1:2)
     * T1CKPS = 0b10 (1:4)
     * T1CKPS = 0b11 (1:8)
     */
    T1CONbits.T1CKPS = 0b11;
    
    /* Delay time
     * = (0xFFFF - (TMR1H:TMR1L) + 1) * 4 * Tosc * (TMR1 prescaler)
     * = (0xFFFF - 0xF0BD + 1) * 4 * 8 us * 8
     * = (3906 + 1) * 4 * 8 us * 8
     * = 1.000192 ~= 1 s
     */
    TMR1H = 0xF0;
    TMR1L = 0xBD;

    T1CONbits.TMR1ON = 0;
}
