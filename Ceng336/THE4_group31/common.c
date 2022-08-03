#include "common.h"
#include "LCD.h"
#include "stdlib.h"
#include <p18f8722.h>

/*----------------------- GLOBAL VARIABLES ---------------------------*/

int value_of_hungery = 100;
int value_of_happy = 100;
int value_of_thirsty = 100;
cmd outer_command = CHECK;
cmd inner_command = -1;
char lcd_management = 0;
char value_of_money = 0;
int Current_LCD_Value = 0;
char indices_of_transmit_data = 0;
char received_index = 0;
char receive = 0;
int current_value_of_money = 0;
char hashing_complate = 0;
char in_buffer[11];
char str_alarm[8];
char hash[17];
char money_string[17] = "MONEY:";
char money_amount[11];
char hungery_string[17] = "HUNGER";
char happy_string[17] = "HAPPY:";
char thirsty_string[17] = "THIRST";

char commands[10][20] = {"{GO##}", "{END}", "{F}", "{W}", "{P}", "{C}", "{S###}", "{H################}", "{A########}", "{M##}"};

void lcd_update(){
	switch (Current_LCD_Value) {
	case 1:
		Current_LCD_Value = 2;
		break;
	case 2:
		Current_LCD_Value = 3;
		break;
	case 0:
		Current_LCD_Value = 1;
		break;
	case 3:
		Current_LCD_Value = 1;
		break;
	}
	lcd_management = 1;
}

void lcd_trigger(){
	int i, length_of_money = 0, money_for_use = current_value_of_money;
	char number_of_full_cell = 0;

	memset(money_amount, 0, 11);
	itoa(money_for_use, money_amount);

	money_string[0] = 'M';
	money_string[1] = 'O';
	money_string[2] = 'N';
	money_string[3] = 'E';
	money_string[4] = 'Y';
	money_string[5] = ':';

	length_of_money = strlen(money_amount);

	for(i = 0; i < (10 - length_of_money); i++){
		money_string[i + 6] = ' ';
	}

	for(; i < 10; i++){
		money_string[i + 6] = money_amount[i - (10 - length_of_money)];
	}

	memset(money_amount, 0, 11);
	LcdPrintString(money_string, 0, 0);

	switch (Current_LCD_Value) {
	case 1:
		number_of_full_cell = value_of_hungery / 10;

		for (i = 0; i < number_of_full_cell; i++){
			hungery_string[6 + i] = 0xFF;
		}
		for (; i < 10; i++){
			hungery_string[6 + i] = ' ';
		}

		LcdPrintString(hungery_string, 0, 1);
		break;
	case 2:
		number_of_full_cell = value_of_happy / 10;

		for (i = 0; i < number_of_full_cell; i++){
			happy_string[6 + i] = 0xFF;
		}
		for (; i < 10; i++){
			happy_string[6 + i] = ' ';
		}
		LcdPrintString(happy_string, 0, 1);
		break;
	case 3:
		number_of_full_cell = value_of_thirsty / 10;

		for (i = 0; i < number_of_full_cell; i++){
			thirsty_string[6 + i] = 0xFF;
		}
		for (; i < 10; i++){
			thirsty_string[6 + i] = ' ';
		}
		LcdPrintString(thirsty_string, 0, 1);
		break;
	}
}

/* Invoked when receive interrupt occurs; meaning that data is received */
void dataReceived(){
	char charac = RCREG1;
	if (charac == '{') {
		received_index = 0;
		receive = 1;
		return;
	}
	else if (charac == '}') {
		received_index = 0;
		receive = 0;
		parser();
		return;
	}
	else if (!receive){
		return;
	}
	in_buffer[received_index++] = charac;
}

void trigger_transmission(cmd cmd){
	int i = 2;
	outer_command_ = cmd;
	if (cmd == HASH_CMD) {
		for (; i < 18; i++){
			commands[cmd][i] = hash[i - 2];
		}		
		memset(hash, 0, 16);
	}
	indices_of_transmit_data = 0;
	TXSTA1bits.TXEN = 1;
	TXREG1 = commands[cmd][indices_of_transmit_data++];
}

void parser(){
	char hungry_amo = 0, happy_amo = 0, thirsty_amo = 0;
	int index = 0, money = 0;

	switch (in_buffer[0]) {
	case 'S':
		hungry_amo = in_buffer[1];
		happy_amo = in_buffer[2];
		thirsty_amo = in_buffer[3];
		if (hungry_amo != value_of_hungery || happy_amo != value_of_happy || thirsty_amo != value_of_thirsty){
			lcd_management = 1;
		}
		value_of_hungery = hungry_amo;
		value_of_happy = happy_amo;
		value_of_thirsty = thirsty_amo;
		inner_command = SENSOR_CMD;
		break;
	case 'G':
		money = in_buffer[2];
		money <<= 8;
		money += in_buffer[3];
		current_value_of_money = money;
		inner_command = GO;
		break;
	case 'A':
		for (index = 1; index < 9; index++){
			str_alarm[index - 1] = in_buffer[index];
		}
		value_of_money = 1;
		inner_command = ALARM_CMD;
		SetEvent(TASK1_ID, SOLVE_TRIGGER);
		break;
	case 'M':
		money = in_buffer[1];
		money <<= 8;
		money += in_buffer[2];
		current_value_of_money += money;
		lcd_management = 1;
		inner_command = MONEY;
		break;
	case 'E':
		inner_command = END;
		break;
	}
}

void transmitData(){
	if (commands[outer_command_][indices_of_transmit_data] == '\0') {
		outer_command_ = CHECK;
		TXSTA1bits.TXEN = 0;
		SetEvent(TASK0_ID, DATA_RECEIVED_TRIGGER);
		return;
	}
	TXREG1 = commands[outer_command_][indices_of_transmit_data++];
}

/* End of File : common.c */
