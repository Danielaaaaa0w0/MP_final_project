#include <xc.h>

void TMR2_Initialize(void) {
    /* Prescale bits
     * T2CKPS = 0b00 (1:1)
     * T2CKPS = 0b01 (1:4)
     * T2CKPS = 0b1X (1:16)
     */
    T2CONbits.T2CKPS = 0b01;

    /* Postscale bits
     * T2OUTPS = 0bXXXX (1:1~16)
     */
    T2CONbits.T2OUTPS = 0b0000;
    
    /* PWM period
     * = (PR2 + 1) * 4 * Tosc * (TMR2 prescaler)
     * = (0x9b + 1) * 4 * 8µs * 4
     * = 0.019968s ~= 20ms
     * 
     * Delay time
     * = (PR2 + 1) * 4 * Tosc * (TMR2 prescaler) * (TMR2 Postscale)
     * = (0x9b + 1) * 4 * 8µs * 4 * 1
     * = 0.019968s ~= 20ms
     */
    PR2 = 0x9b;

    T2CONbits.TMR2ON = 1;
}