#include "includes.h"
#include "lcd.h"

// Pulse the E pin of the LCD.
// This function is not in the header as it will not be used by any other function other than lcd functions.
void pulse_lcd(void)
{
	LCD_EN = 1;
	__delay_us(LCD_PULSE);
	LCD_EN = 0;
	__delay_us(LCD_PULSE);
}

void send_lcd_command(uint8_t cmd, uint8_t attr) // TODO: Check if there is a need for delay.
{
	LCD_RS = 0;
	PORTD = cmd | attr;
	pulse_lcd();
	PORTD = (cmd | attr) << 4;
	pulse_lcd();
	__delay_ms(COMMAND_DELAY);
	LATD = 0;
}

void send_lcd_data(uint8_t data)
{
	LCD_RS = 1;
	PORTD = data;
	pulse_lcd();
	PORTD = data << 4;
	pulse_lcd();
	__delay_ms(COMMAND_DELAY);
	LATD = 0;
}

void init_lcd(void)
{
	__delay_ms(20);
	PORTD = 0x30;
	pulse_lcd();

	__delay_ms(6);
	PORTD = 0x30;
	pulse_lcd();

	__delay_us(300);
	PORTD = 0x30;
	pulse_lcd();

	__delay_ms(2);
	PORTD = 0x20;
	pulse_lcd();

	send_lcd_command(FUNCTION_SET, 0x0C);
	send_lcd_command(DISPLAY_CONTROL, 0x06);
	send_lcd_command(CLEAR_DISPLAY, 0);
	send_lcd_command(ENTRY_MODE_SET, 0x02);
	LATD = 0;
}

void write_cc_char(uint8_t cc_idx, uint8_t charmap[])
{
	send_lcd_command(SET_CGRAM_ADDRESS, cc_idx << 3); // Set the address for custom char.
	for (int i = 0; i < 8; i++)
		send_lcd_data(charmap[i]); // Write char data, the address is incremented automatically.
	cc_num++;
}

void write_lcd_string(uint8_t address, char* str, uint8_t reset_to_address)
{
	send_lcd_command(SET_DDRAM_ADDRESS, address);
	for (int i = 0; i < 16; i++)
		send_lcd_data(str[i]);

	if (reset_to_address)
		send_lcd_command(SET_DDRAM_ADDRESS, address);
}