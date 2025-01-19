#include <xc.h>

void TMR0_Initialize(void) {
    T0CONbits.T0CS = 0;     // Internal clock
    T0CONbits.T08BIT = 0;   // TMR0 is 16-bit timer
    T0CONbits.PSA = 0;      // TMR0 prescaler is assigned
    
    /* Prescale bits
     * T0PS = 0b000 (1:2)
     * T0PS = 0b001 (1:4)
     * T0PS = 0b010 (1:8)
     * T0PS = 0b011 (1:16)
     * T0PS = 0b100 (1:32)
     * T0PS = 0b101 (1:64)
     * T0PS = 0b110 (1:128)
     * T0PS = 0b111 (1:256)
     */
    T0CONbits.T0PS = 0b110;
    
    /* Delay time
     * = (0xFFFF - (TMR0H:TMR0L) + 1) * 4 * Tosc * (TMR0 prescaler)
     * = (0xFFFF - 0xFA7F + 1) * 4 * 8 us * 128
     * = (244 + 1) * 4 * 8 us * 128
     * = 1.00352 ~= 1 s
     */
    TMR0H = 0xFF;
    TMR0L = 0x0B;

    T0CONbits.TMR0ON = 0;
}
