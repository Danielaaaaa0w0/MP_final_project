#include <xc.h>
#include <pic18f4520.h>
#include "buzzer.h"
#include "motor.h"
#include "ladder.h"

// CONFIGURATION SETTINGS
#pragma config OSC = INTIO67    // Oscillator Selection bits: Internal oscillator block, port function on RA6 and RA7
#pragma config WDT = OFF        // Watchdog Timer Enable bit: Watchdog Timer disabled
#pragma config PWRT = OFF       // Power-up Timer Enable bit: Power-up timer disabled
#pragma config BOREN = ON       // Brown-out Reset Enable bit: Brown-out Reset enabled
#pragma config PBADEN = OFF     // PORTB A/D Enable bit: PORTB configured as digital I/O
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit: Disabled
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit: Disabled

#define _XTAL_FREQ 8000000     // Internal clock frequency: 8 MHz

// Function to initialize UART for Bluetooth communication
void Initialize_Bluetooth()
{
    // Configure the RX and TX pins
    TRISC6 = 1; // RC6 is output, but UART adjust automatically, so set it 1
    TRISC7 = 1; // RX Pin (RC7) as input
    
    // Set the baud rate (8 MHz crystal, 9600 bps)
    BRGH = 1;    // High-speed baud rate
    SPBRG = 51;  // Baud rate set to 9600 bps

    // Enable the asynchronous serial port
    SYNC = 0;    // Asynchronous mode
    SPEN = 1;    // Enable serial port (RC6/TX and RC7/RX)

    // Set 8-bit reception and transmission
    RX9 = 0;     // 8-bit reception mode
    TX9 = 0;     // 8-bit transmission mode
    
    // Enable transmission and reception
    TXEN = 1;    // Enable transmission
    CREN = 1;    // Enable continuous reception(for asynchronous mode)
                 // SREN is for synchronous mode(?)
    
    // Enable global and peripheral interrupts
    GIE = 0;     // Global Interrupt Enable
    PEIE = 1;    // Peripheral Interrupt Enable
    
    // Enable interrupts for transmission and reception
    RCIE = 0;    // UART Receive Unable, we use polling here
    TXIE = 0;    // UART Transmit Interrupt Unable, we use polling here
}

// Function to send a single character via UART
void BT_load_char(char byte)
{
    TXREG = byte; // Load the given character into the UART transmit register
    while (!TXIF); // Wait until the UART transmit buffer is ready (TXIF is 1 while empty)
    while (!TRMT); // Wait until the data has been completely transmitted (TRMT is 1 while empty)
}

// Function to send a string via UART
void BT_load_string(char* string)
{
    while (*string) // Loop through each character in the string(end with \0)
        BT_load_char(*string++); // Send the character and move to the next
}

// Function to send a carriage return as the end of the message
void broadcast_BT()
{
    TXREG = 13;   // Send the ASCII character 13 (Carriage Return)
    //__delay_ms(200); // Wait 500 ms for the receiver to process the message
    while (!TXSTAbits.TRMT);
}

char BT_get_char(void)
{
    // Check for UART overrun error
    if (OERR) // If an overrun error has occurred
    {
        CREN = 0;  // Disable reception to clear the error
        CREN = 1;  // Re-enable reception
    }

    // Check if new data is available in the receive buffer
    if (RCIF == 1) // If data is available
    {
        while (!RCIF);  // Wait until the data is fully received
        
        // Return the received character from the UART receive register
        // RCIF would be cleared after accessing RCREG
        return RCREG;  
    }
    else // If no data is available
        return 0;       // Return 0 to indicate no new data
}

void main(void) 
{
    OSCCONbits.IRCF = 0b111; // Set the internal oscillator frequency to 8 MHz
    
    // Initialize UART for Bluetooth communication
    Initialize_Bluetooth();
    Initialize_Motor();
    Initialize_Buzzer();
    Initialize_Ladder();
    int ladder_state = 0;
    
    // Send initial messages via Bluetooth
    BT_load_string("Bluetooth Initialized and Ready");
    broadcast_BT();
    
    // Main loop (not needed with interrupt handling)
    while (1) 
    {
        // Main loop is empty because UART is handled in the interrupt
        char get_value = BT_get_char(); // Read the character received via Bluetooth
        // If we receive a '0'
        if (get_value == 'w')
        {
           Motor_Forward();
           BT_load_string("Motor_Forward");
           broadcast_BT();
           __delay_ms(80);
        }

        // If we receive a '1'
        else if (get_value == 'a')
        {
           Motor_TurnLeft();
           BT_load_string("Motor_TurnLeft");
           broadcast_BT();
           __delay_ms(80);
        }
        else if (get_value == 's')
        {
            Motor_Backward();
            BT_load_string("Motor_Backward");
            broadcast_BT();
            __delay_ms(80);
        }
        else if (get_value == 'd')
        {
            Motor_TurnRight();
            BT_load_string("Motor_TurnRight");
            broadcast_BT();    
            __delay_ms(80);
        }
        else if (get_value == 'q')
        {
            Motor_Stop();
            BT_load_string("Motor_Stop");
            broadcast_BT();
        }
        else if (get_value == 'p')
        {
            BT_load_string("change_music");
            broadcast_BT();
            music_start();
        }
        
        else if (get_value == 'l')
        {
            if(ladder_state == 0)
            {
                BT_load_string("Ladder_Forward");
                broadcast_BT();
                Ladder_Forward(10);
                ladder_state = 1;
            }
            else
            {
                BT_load_string("Ladder_Backward");
                broadcast_BT();
                Ladder_Backward(10);
                ladder_state = 0;
            }
        }
        
        else if (get_value != 0)
        {
            BT_load_char(get_value);
            broadcast_BT();
        }
        else
        {
            Motor_Stop();
        }
    }
    return;
}