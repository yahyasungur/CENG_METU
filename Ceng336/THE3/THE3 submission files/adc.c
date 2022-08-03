#include "adc.h"

void init_adcon(void)
{
	INTCONbits.PEIE = 1;

	ADCON0 = 0b00110001; // select channel 12
	ADCON1 = 0b00000011;
	ADCON2 = 0b00000010; // 12 TAD, 32 TOSC, if results are not accurate increase tad
	ADRESH = 0;

	// configure interrupts
	PIR1bits.ADIF = 0;
	PIE1bits.ADIE = 1;
	IPR1bits.ADIP = 1;

	// start adcon conversion
	GODONE = 1;
}

// high priority
void adcon_isr()
{
	// clear interrupt flag
	PIR1bits.ADIF = 0;

	// read adcon result
	CURSOR_POS = ADRESH / 16;
	
	GODONE = 1;
}