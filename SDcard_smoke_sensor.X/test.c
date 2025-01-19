#include "mcc_generated_files/mcc.h"
#include "ff.h"
#include <xc.h>
#include <pic18f4520.h>

FATFS FatFs;	/* FatFs work area needed for each volume */
FIL Fil;		/* File object needed for each open file */

unsigned int ADC_Read(void) {
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);
    return ((ADRESH << 8) + ADRESL);
}

/*
						 Main application
 */
void main(void) {
	UINT bw;
	// Initialize the device
	SYSTEM_Initialize();

    FRESULT res = f_mount(&FatFs, "", 1);

    while (res == FR_OK) {
        // adc_value is smoke sensor output value
        // RD2 is the flame sensor (digital)
        // RE0 is the the fan
        // RE1 control the water
        unsigned int adc_value = ADC_Read();
        
        // if the smoke sensor detects smoke
        if (adc_value >= 550 && f_open(&Fil, "hello.txt", 
            FA_OPEN_EXISTING | FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
            LATEbits.LATE0 = 1; // start the fan
            f_write(&Fil, "Hello smoke!\r\n", 14, &bw);	
            f_close(&Fil);
            
        } else { // < 550
            LATEbits.LATE0 = 0; 
        }
        
        // if the flame sensor detects fire
        if (PORTDbits.RD2 == 0 && f_open(&Fil, "hello.txt",
            FA_OPEN_EXISTING | FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
            LATEbits.LATE1 = 1; // start to splash water
            f_write(&Fil, "Hello water?\r\n", 14, &bw);	
            f_close(&Fil);
            
        } else {
            LATEbits.LATE1 = 0; 
        }
        
        __delay_ms(100);
    }
}
