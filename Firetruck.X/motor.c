#include <xc.h>
#include "motor.h"

void Initialize_Motor(void)
{
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;

    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 0;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
}

void Motor_Forward(void)
{
    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 1;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 1;
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 1;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 1;
}

void Motor_Stop(void)
{
    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 0;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
}

void Motor_Backward(void)
{   
    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 0;
    LATDbits.LATD0 = 1;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 1;
    LATDbits.LATD3 = 0;
    LATBbits.LATB4 = 1;
    LATBbits.LATB5 = 0;
}

void Motor_TurnLeft(void)
{
    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 1;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 1;
}

void Motor_TurnRight(void)
{
    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 1;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 1;
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 0;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
}