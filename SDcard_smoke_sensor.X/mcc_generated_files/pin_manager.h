/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB� Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25
        Device            :  PIC18F25K20
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SD_CS aliases
#define SD_CS_TRIS               TRISC2
#define SD_CS_LAT                LATC2
#define SD_CS_PORT               PORTCbits.RC2
#define SD_CS_SetHigh()    do { LATC2 = 1; } while(0)
#define SD_CS_SetLow()   do { LATC2 = 0; } while(0)
#define SD_CS_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define SD_CS_GetValue()         PORTCbits.RC2
#define SD_CS_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define SD_CS_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

// get/set SCK aliases
#define SCK_TRIS               TRISC3
#define SCK_LAT                LATC3
#define SCK_PORT               PORTCbits.RC3
#define SCK_SetHigh()    do { LATC3 = 1; } while(0)
#define SCK_SetLow()   do { LATC3 = 0; } while(0)
#define SCK_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCK_GetValue()         PORTCbits.RC3
#define SCK_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

// get/set SDI aliases
#define SDI_TRIS               TRISC4
#define SDI_LAT                LATC4
#define SDI_PORT               PORTCbits.RC4
#define SDI_SetHigh()    do { LATC4 = 1; } while(0)
#define SDI_SetLow()   do { LATC4 = 0; } while(0)
#define SDI_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDI_GetValue()         PORTCbits.RC4
#define SDI_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDI_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

// get/set SDO aliases
#define SDO_TRIS               TRISC5
#define SDO_LAT                LATC5
#define SDO_PORT               PORTCbits.RC5
#define SDO_SetHigh()    do { LATC5 = 1; } while(0)
#define SDO_SetLow()   do { LATC5 = 0; } while(0)
#define SDO_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define SDO_GetValue()         PORTCbits.RC5
#define SDO_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define SDO_SetDigitalOutput()   do { TRISC5 = 0; } while(0)


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */