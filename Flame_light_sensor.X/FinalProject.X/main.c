#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pic18f4520.h>
#include "setting.h"

#define _XTAL_FREQ 125000

#define BUFFER_SIZE 20

#define WATER_MOTOR LATDbits.LATD6
#define FIRE_SENSOR PORTDbits.RD2

int mode = 0;
int number = 0;
int degree = 0;

int adc_value = 0;
int pre_adc_value = 0;

int tmr2_cnt = 0;
int tmr2_target = 50;

char str[BUFFER_SIZE];
char buffer[BUFFER_SIZE];

void main(void) {

    SYSTEM_Initialize();

    while (1) {

        adc_value = ADC_Read(0);

        if (adc_value < 250) {
            LATDbits.LATD0 = 1;
            LATDbits.LATD1 = 1;
        } else {
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 0;
        }
        
        if (FIRE_SENSOR == 0) {
            WATER_MOTOR = 1;
        } else {
            WATER_MOTOR = 0;
        }

        __delay_ms(1000);
    }
    
    return;
}