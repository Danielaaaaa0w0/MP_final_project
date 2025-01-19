#include "mcc_generated_files/mcc.h"
#include "ff.h"
#include <xc.h>
#include <pic18f4520.h>
#include <string.h>
#include <stdio.h>

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
    char buffer[64]; // store formatted string
    UINT length = 0;
	// Initialize the device
	SYSTEM_Initialize();
    LATDbits.LATD6 = 0;
    TRISDbits.TRISD7 = 0; 
    LATDbits.LATD7 = 0;
    
    FRESULT res = f_mount(&FatFs, "", 1);

    while (res == FR_OK) {
        LATDbits.LATD7 = 1;
        // adc_value is smoke sensor output value
        // RE0 is the the fan
        unsigned int adc_value = ADC_Read();
        
        // if the smoke sensor detects smoke
        if (adc_value >= 450 && f_open(&Fil, "hello.txt", 
            FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
            
            TRISDbits.TRISD6 = 0; 
            LATDbits.LATD6 = 1; // start the fan
            
            // Move pointer to the end before writing
            if (Fil.fsize != 0) f_lseek(&Fil, Fil.fsize);
            // use sprintf to get formatted string
            sprintf(buffer, "ADC_value: %d\r\n", adc_value);
            length = strlen(buffer); // get string length
            f_write(&Fil, buffer, length, &bw);	
            f_close(&Fil);
            
        } else { // < 600
            LATDbits.LATD6 = 0; 
        }
        
        __delay_ms(1000);
    }
}
//#include "mcc_generated_files/mcc.h"
//#include "ff.h"
//
//
//FATFS FatFs;	/* FatFs work area needed for each volume */
//FIL Fil;		/* File object needed for each open file */
//
//
///*
//						 Main application
// */
//void main(void) {
//	UINT bw;
//
//	// Initialize the device
//	SYSTEM_Initialize();
//    
//    FRESULT res = f_mount(&FatFs, "", 1);
//
//    
//	if (res == FR_OK) {	/* Mount SD */
//		if (f_open(&Fil, "hello.txt", FA_OPEN_EXISTING | FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {	/* Open or create a file */
//			if ((Fil.fsize != 1) && (f_lseek(&Fil, Fil.fsize) != FR_OK)) goto endSD;	/* Jump to the end of the file */
//			f_write(&Fil, "Hello world!...\r\n", 17, &bw);	/* Write data to the file */
//			endSD: f_close(&Fil);								/* Close the file */   
//		}
//	}
//
//
//	while (1) {
//
//	}
//}
