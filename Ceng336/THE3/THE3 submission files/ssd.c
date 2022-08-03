#include "ssd.h"
#include "lcd.h"

void init_tmr1()
{
	T1CON = 0b11000001;
	TMR1H = (TIMER1_PRELOAD >> 8) & 0xff;
	TMR1L = TIMER1_PRELOAD & 0xff;
}

void tmr1_isr()
{
	PIR1bits.TMR1IF = 0;
	
	switch(curr_led) {
	case 1:
		LATH0 = 1;
		LATH1 = 0;
		LATH2 = 0;
		LATH3 = 0;
		
		LATJ = SSEGMENT_NUMBERS_GLYPHS[cc_num];
		break;
	case 2:
		LATH0 = 0;
		LATH1 = 0;
		LATH2 = 1;
		LATH3 = 0;
		
		LATJ = SSEGMENT_NUMBERS_GLYPHS[curr_x];
		break;
	case 4:
		LATH0 = 0;
		LATH1 = 0;
		LATH2 = 0;
		LATH3 = 1;
		
		LATJ = SSEGMENT_NUMBERS_GLYPHS[curr_y];
		break;
	};

	curr_led = ((curr_led << 1) | (curr_led >> 2)) & 7;
	TMR1H = (TIMER1_PRELOAD >> 8) & 0xff;
	TMR1L = TIMER1_PRELOAD & 0xff;
}