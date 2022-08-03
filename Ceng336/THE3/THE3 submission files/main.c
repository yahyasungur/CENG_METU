/*
 * File:   main.c
 * Author: brk
 *
 * Created on June 2, 2022, 2:30 PM
 */

#include "lcd.h"
#include "adc.h"
#include "ssd.h"

uint8_t scroll_lcd = 0;

void __interrupt(high_priority) highPriorityISR(void)
{
	if (PIR1bits.ADIF)
		adcon_isr();
	if (PIR1bits.TMR1IF)
		tmr1_isr();
	if (INTCONbits.TMR0IF) {
		INTCONbits.TMR0IF = 0;
		scroll_lcd = 1;
	}
	return;
}

typedef enum {
	TEM, CDM, TSM
} STATE;

uint8_t charmap_display[4], charmap_lcd[8];
uint8_t rex_val = 0x00, rex_pressed = 0x00;
STATE lcd_state = TEM;

uint8_t text_buffer[16] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; //The extra last char is for NULL charachter.
uint8_t cust_ch_idx_buffer[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t pred_ch_idx_buffer[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void init_tsm_scroll()
{
	INTCONbits.TMR0IE = 1;
	T0CON = 0b10000110;
}

void init()
{
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0x3F;
	TRISH = 0x10;
	TRISJ = 0x00;

	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;

	init_lcd();

	INTCONbits.GIE = 0;
	init_tsm_scroll();
	init_adcon();
	init_tmr1();
	INTCONbits.GIE = 1;
}

void clear_charmap()
{
	for (int i = 0; i < 4; i++)
		charmap_display[i] = 0;

	for (int i = 0; i < 8; i++)
		charmap_lcd[i] = 0;
}

void shift_text_left()
{
	uint8_t prev_ch = text_buffer[0];

	for (int i = 15; i >= 0; i--) {
		uint8_t save_ch = text_buffer[i];
		text_buffer[i] = prev_ch;
		prev_ch = save_ch;
	}

	return;
}

void proceed_to_TSM()
{
	write_lcd_string(0x00, "   finished     ", 1);

	send_lcd_command(DISPLAY_CONTROL, 0x04);

	return;
}

void cursor_task(uint8_t change)
{
	uint8_t cust_ch_idx = cust_ch_idx_buffer[CURSOR_POS], pred_ch_idx = pred_ch_idx_buffer[CURSOR_POS];

	switch (lcd_state) {
	case CDM:

		if (curr_x != 0)
			curr_x = (curr_x - ((change & 0x08) >> 3));
		if (curr_x != 3)
			curr_x = (curr_x + (change & 0x01));
		if (curr_y != 0)
			curr_y = (curr_y - ((change & 0x04) >> 2));
		if (curr_y != 7)
			curr_y = (curr_y + ((change & 0x02) >> 1));

		break;

	case TEM:
		switch (change) {
		case 0x08:
			cust_ch_idx = (cust_ch_idx - 1 + (cc_num + 1)) % (cc_num + 1);

			//I have no idea whether these last 2 lines will work check this...
			//same goes for the last 2 lines for the other cases.
			if (cust_ch_idx == 0) {
				text_buffer[CURSOR_POS] = PREDEFINED[pred_ch_idx];
				send_lcd_data(PREDEFINED[pred_ch_idx]);
				send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);
			} else {
				text_buffer[CURSOR_POS] = cust_ch_idx - 1;
				send_lcd_data(cust_ch_idx - 1);
				send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);

			}

			break;

		case 0x04:
			pred_ch_idx = (pred_ch_idx - 1 + 37) % 37;
			cust_ch_idx = 0;

			text_buffer[CURSOR_POS] = PREDEFINED[pred_ch_idx];
			send_lcd_data(PREDEFINED[pred_ch_idx]);
			send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);
			break;

		case 0x02:
			pred_ch_idx = (pred_ch_idx + 1) % 37;
			cust_ch_idx = 0;

			text_buffer[CURSOR_POS] = PREDEFINED[pred_ch_idx];
			send_lcd_data(PREDEFINED[pred_ch_idx]);
			send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);
			break;

		case 0x01:
			cust_ch_idx = (cust_ch_idx + 1) % (cc_num + 1);

			if (cust_ch_idx == 0) {
				text_buffer[CURSOR_POS] = PREDEFINED[pred_ch_idx];
				send_lcd_data(PREDEFINED[pred_ch_idx]);
				send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);
			} else {
				text_buffer[CURSOR_POS] = cust_ch_idx - 1;
				send_lcd_data(cust_ch_idx - 1);
				send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);

			}

			break;
		}

		cust_ch_idx_buffer[CURSOR_POS] = cust_ch_idx;
		pred_ch_idx_buffer[CURSOR_POS] = pred_ch_idx;

		break;
	}

	return;
}

void toggle_led()
{
	charmap_display[curr_x] = charmap_display[curr_x] ^ (0x01 << curr_y);
	charmap_lcd[curr_y] = charmap_lcd[curr_y] ^ (0x01 << (4 - curr_x));

	LATA = charmap_display[0];
	LATB = charmap_display[1];
	LATC = charmap_display[2];
	LATD = charmap_display[3];

	return;
}

void RE4_task()
{
	switch (lcd_state) {
	case TEM:
		clear_charmap();
		lcd_state = CDM;
		break;

	case CDM:
		toggle_led();
		break;
	}

	return;
}

void RE5_task()
{
	switch (lcd_state) {
	case TEM:
		lcd_state = TSM;
		break;

	case CDM:
		lcd_state = TEM;
		write_cc_char(cc_num, charmap_lcd);
		send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);
		LATA = 0;
		LATB = 0;
		LATC = 0;
		LATD = 0;
		curr_x = 0;
		curr_y = 0;
		break;
	}

	return;
}

void RE_task(uint8_t change)
{
	switch (change) {
	case 0x01:
	case 0x02:
	case 0x04:
	case 0x08:
		cursor_task(change);
		break;

	case 0x10:
		RE4_task();
		break;

	case 0x20:
		RE5_task();
		break;
	}

	return;
}

void check_RE_button()
{
	rex_val = PORTE;
	rex_pressed = rex_pressed | rex_val;

	RE_task(rex_pressed ^ rex_val);

	rex_pressed = rex_pressed & rex_val;

	return;
}

void main(void)
{
	init();

	while (lcd_state != TSM) {
		if (lcd_state == TEM)
			send_lcd_command(SET_DDRAM_ADDRESS, CURSOR_POS);
		check_RE_button();
	}

	proceed_to_TSM();

	while (1) {
		if (scroll_lcd) {
			shift_text_left();
			write_lcd_string(0x40, text_buffer, 1);
			scroll_lcd = 0;
		}
	}
}