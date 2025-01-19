#include <xc.h>
#include "buzzer.h"
#include "melody.h"
#define _XTAL_FREQ 8000000     // Internal clock frequency: 8 MHz
// Multiple melody: [Frequency (PR2), Note duration (ms), Pause delay (ms)]

// for current song
int current_song = -1;   // Index of the current song(0 means stop playing)
const int (*current_melody)[3]; // Pointer to the current melody
int current_melody_length;      // Length of the current melody

// variables for playing a song
int current_note = 0;     // Index of the current note
int playing = 0;          // Flag to indicate whether music is playing
int is_pause = 0;         // Flag to indicate whether in pause phase

void Initialize_Buzzer(void)
{
    // Initialize PWM for CCP1
    TRISCbits.TRISC2 = 0;        // Set RC2 as output for PWM signal
    LATCbits.LATC2 = 0;
    CCP1CONbits.CCP1M = 0b1100; // Configure CCP1 module in PWM mode
    T2CONbits.T2CKPS = 0b11;    // Set Timer2 prescaler to 16 (11 = 1:16)
    T2CONbits.T2OUTPS = 0b0000; // Set Timer2 postscaler to 1:1
    PR2 = 0;    // set initial frequency to 0 (it decide note)
    CCPR1L = 0; // set volumn to 0
    T2CONbits.TMR2ON = 1;       // Turn on Timer2 to enable PWM

    
    // Initialize Timer0
    T0CON = 0b00000101;      // Configure Timer0:
                             // - Bit 7: TMR0ON: Enable Timer0 (1 = ON)
                             // - Bit 6: T08BIT: 16-bit mode (0 = 16-bit mode)
                             // - Bit 5: T0CS: Internal clock source (0 = Internal clock, Fosc/4)
                             // - Bit 4: T0SE: Increment on low-to-high transition (not used here)
                             // - Bit 3: PSA: Enable prescaler (0 = Prescaler is assigned)
                             // - Bits 2-0: Prescaler set to 1:64 (101)

    TMR0H = 0;               // Set Timer0 high byte to 0 (initialize counter)
    TMR0L = 0;               // Set Timer0 low byte to 0 (initialize counter)
    
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;   // Enable Timer0 interrupt
    INTCONbits.PEIE = 1;     // Enable peripheral interrupts
    INTCONbits.GIE = 1;      // Enable global interrupts
}

void Initialize_Songs(void) 
{
    current_melody = (const int(*)[3])melodies[current_song];
    current_melody_length = melody_lengths[current_song];
}



void __interrupt() ISR(void) 
{
    if (INTCONbits.TMR0IF) 
    { // Timer0 interrupt triggered
        INTCONbits.TMR0IF = 0; // Clear the interrupt flag

        if (playing) 
        {
            if (is_pause) 
            {
                // Pause phase ends, move to the next note
                is_pause = 0; // Exit pause phase
                current_note++;
                if (current_note >= current_melody_length) 
                { 
                    current_note = 0;
                    // Set the frequency for the next note
                    PR2 = current_melody[current_note][0]; // Set frequency
                    CCPR1L = PR2 >> 4;            // Set duty cycle (volumn 25%)

                    // Configure Timer0 for the duration of the next note
                    int duration = current_melody[current_note][1];
                    TMR0 = 65536 - (duration * (_XTAL_FREQ / 8) / 32 / 1000);
                } 
                else 
                {
                    // Set the frequency for the next note
                    PR2 = current_melody[current_note][0]; // Set frequency
                    CCPR1L = PR2 >> 4;            // Set duty cycle (volumn 25%)

                    // Configure Timer0 for the duration of the next note
                    int duration = current_melody[current_note][1];
                    TMR0 = 65536 - (duration * (_XTAL_FREQ / 8) / 32 / 1000);
                }
            } 
            else 
            {
                // Note phase ends, enter pause phase
                is_pause = 1;       // Enter pause phase
                CCPR1L = 0;         // Turn off the buzzer

                // Configure Timer0 for the pause duration
                int pause_time = current_melody[current_note][2];
                TMR0 = 65536 - (pause_time * (_XTAL_FREQ / 8) / 32 / 1000);
            }
        }
    }
}

void music_start(void) 
{
    if(current_song == (total_songs - 1))
    {
        playing = 0;
        current_song = -1;
        CCPR1L = 0;
        T0CONbits.TMR0ON = 0;
        return;
    }
    
    current_song++;
    Initialize_Songs();
    
    playing = 1;      // Start music playback
    current_note = 0; // Start from the first note
    is_pause = 0;     // Start with the note phase

    // Set the frequency and Timer0 for the first note
    PR2 = current_melody[current_note][0]; // Set frequency
    CCPR1L = PR2 >> 4;             // Set duty cycle (volumn 25%)

    // Configure Timer0 for the first note duration
    int duration = current_melody[current_note][1];
    TMR0 = 65536 - (duration * (_XTAL_FREQ / 8) / 32 / 1000);
    T0CONbits.TMR0ON = 1;
}
