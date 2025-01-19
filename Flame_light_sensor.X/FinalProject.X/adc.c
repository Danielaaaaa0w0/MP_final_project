#include <xc.h>

#define _XTAL_FREQ 125000

void ADC_Initialize(void) {
    TRISAbits.RA0 = 1;          // analog input port
    
    ADCON0bits.ADON = 1;
    
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.PCFG = 0b1110;   // AN0 is analog input, others are digital
    
    /* ADCS bits (Tad > 0.7 us)
     * ADCS = 0b000 (Fosc < 2.86 MHz, Tad = 2 * Tosc)
     * ADCS = 0b100 (Fosc < 5.71 MHz, Tad = 4 * Tosc)
     * ADCS = 0b001 (Fosc < 11.43 MHz, Tad = 8 * Tosc) 
     * ADCS = 0b101 (Fosc < 22.6 MHz, Tad = 16 * Tosc)
     * ADCS = 0b010 (Fosc < 40.0 MHz, Tad = 32 * Tosc)
     * ADCS = 0b110 (Fosc < 40.0 MHz, Tad = 64 * Tosc)
     */
    ADCON2bits.ADCS = 0b000;    // 000 (125 kHz < 2.86 Mhz)
    
    /* ACQT bits (acquisition time > 2.4 us)
     * ACQT = 0b000 (0 * Tad)
     * ACQT = 0b001 (2 * Tad)
     * ACQT = 0b010 (4 * Tad)
     * ACQT = 0b011 (6 * Tad)
     * ACQT = 0b100 (8 * Tad)
     * ACQT = 0b101 (12 * Tad)
     * ACQT = 0b110 (16 * Tad)
     * ACQT = 0b111 (20 * Tad)
     */
    ADCON2bits.ACQT = 0b001;    // Tad = 16 us, acquisition time = 2 * Tad = 32 us > 2.4 us
    
    ADCON2bits.ADFM = 1;        // right justified 

    ADRESH = 0;                 // Flush ADC output Register
    ADRESL = 0;
}

int ADC_Read(int channel) {
    ADCON0bits.CHS = channel & 0x0F;
    ADCON0bits.GO = 1;
    
    while (ADCON0bits.GO_nDONE == 1);   // ADC conversion in progress

    return (ADRESH << 8) | ADRESL;
}