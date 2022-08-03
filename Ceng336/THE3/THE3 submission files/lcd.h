#ifndef _LCD_H_
#define	_LCD_H_

#include "includes.h"

// This is the PIC to LCD pin mapping
#define LCD_RS LATB2
#define LCD_EN LATB5
#define LCD_D4 LATD4
#define LCD_D5 LATD5
#define LCD_D6 LATD6
#define LCD_D7 LATD7

// Pulse time for the E pin.
#define LCD_PULSE 30
#define COMMAND_DELAY 1

// Predefined set of characters.
volatile char PREDEFINED[] = " abcdefghijklmnopqrstuvwxyz0123456789";

// Number of custom characters.
// Use this to cycle through custom characters.
uint8_t cc_num = 0;

uint8_t curr_x = 0; // TODO: Where to put them
uint8_t curr_y = 0;

/*
Example custom character definition.
uint8_t fullHeart[8] = {
	0b00000,
	0b00000,
	0b01010,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b00000,
};
*/

// Properly initialize the LCD.
void init_lcd(void);

// Create a custom character and store it in the LCD's memory.
// First argument is the index to store the character. It can
// take values between 0 and 7 (for 8 custom characters). Second
// argument is the character data. See the fullHeart array above.
// When you send the address as 'data' to the LCD, the custom
// character stored at that address is displayed.
void write_cc_char(uint8_t cc_idx, uint8_t* charmap);

// Write string to lcd, string must be terminated with a null character.
// If reset_to_address is true, the cursor will be brought back to the address.
void write_lcd_string(uint8_t address, char* str, uint8_t reset_to_address);

// Enum of commands that can be sent to the LCD.
enum {
	CLEAR_DISPLAY = 0x01,
	RETURN_HOME = 0x02,
	ENTRY_MODE_SET = 0x04,
	DISPLAY_CONTROL = 0x08,
	CURSOR_DISPLAY_SHIFT = 0x10,
	FUNCTION_SET = 0x20,
	SET_CGRAM_ADDRESS = 0x40,
	SET_DDRAM_ADDRESS = 0x80,
};

// Send a command to the LCD, with given attributes like ddram address.
void send_lcd_command(uint8_t cmd, uint8_t attr);

// Send data to LCD.
// Data is sent to the address that was selected before with send_lcd_command(SET_**RAM_ADDRESS, address).
void send_lcd_data(uint8_t data);

#endif	/* _LCD_H_ */