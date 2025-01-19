#include <xc.h>
#include "ladder.h"

#define _XTAL_FREQ 8000000 // Define system clock frequency

// Step sequence for full-step mode
const unsigned char stepSequence[4] = {0b00110000, 0b01100000, 0b11000000, 0b10010000};

// Initialize ladder (stepper motor)
void Initialize_Ladder(void) 
{
    TRISDbits.TRISD4 = 0; // Set RD4 as output
    TRISDbits.TRISD5 = 0; // Set RD5 as output
    TRISDbits.TRISD6 = 0; // Set RD6 as output
    TRISDbits.TRISD7 = 0; // Set RD7 as output
    LATDbits.LATD4 = 0;   // Set initial value to low
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;
    LATDbits.LATD7 = 0;
}

// Update PORTD 4~7 only
void Update_StepperMotor(unsigned char stepValue) 
{
    LATD = (LATD & 0x0F) | (stepValue & 0xF0); // Keep D0~D3 unchanged, update D4~D7
}

// Rotate ladder forward
void Ladder_Forward(int turns) 
{
    int steps = turns * 2048;
    int stepIndex = 0;
    for (int i = 0; i < steps; i++) 
    {
        Update_StepperMotor(stepSequence[stepIndex]); // Update motor pins
        __delay_ms(2); // Adjust delay for speed control
        stepIndex = (stepIndex + 1) % 4; // Increment step index
    }
}

// Rotate ladder backward
void Ladder_Backward(int turns) 
{
    int steps = turns * 2048;
    int stepIndex = 3;
    for (int i = 0; i < steps; i++) 
    {
        Update_StepperMotor(stepSequence[stepIndex]); // Update motor pins
        __delay_ms(2); // Adjust delay for speed control
        stepIndex = (stepIndex - 1 + 4) % 4; // Decrement step index
    }
}

