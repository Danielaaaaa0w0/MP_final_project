#include <xc.h>

void PIN_MANAGER_Initialize(void) {
    // LED
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    
    // Flame Senser
    TRISDbits.TRISD2 = 1;
    
    // Water Mator
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD6 = 0;
}
