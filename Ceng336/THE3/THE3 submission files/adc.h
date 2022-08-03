#ifndef _ADC_H_
#define _ADC_H_

#include "includes.h"

// init adcon configuration
// enable adcon interrupt

uint8_t CURSOR_POS = 0;

void init_adcon(void);

void adcon_isr();

#endif