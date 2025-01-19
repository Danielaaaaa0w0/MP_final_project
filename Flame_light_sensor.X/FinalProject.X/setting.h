#ifndef SETTING_H
#define	SETTING_H

#include <xc.h>
#include <pic18f4520.h>
#include "adc.h"
#include "ccp1.h"
#include "interrupt.h"
#include "pin_manager.h"
#include "tmr0.h"
#include "tmr1.h"
#include "tmr2.h"
#include "uart.h"

void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);

#endif