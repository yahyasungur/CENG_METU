/* 
 * File:   ssd.h
 * Author: brk
 *
 * Created on June 3, 2022, 7:47 PM
 */

#ifndef SSD_H
#define	SSD_H

#include "lcd.h"

#define TIMER1_PRELOAD 33000

uint8_t curr_led = 1;

// Use timer 1 with seven segment display
void init_tmr1();

void tmr1_isr();

#endif	/* SSD_H */