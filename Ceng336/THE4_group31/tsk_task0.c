#include "common.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/


/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/


TASK(TASK0){
	SetRelAlarm(ALARM_TSK0, 50, 60);
	while (TRUE) {
		WaitEvent(TRIGGER_CMD);
		ClearEvent(TRIGGER_CMD);
		if (inner_command == END){
			break;
		}
		WaitEvent(DATA_RECEIVED_TRIGGER);
		ClearEvent(DATA_RECEIVED_TRIGGER);

		if (value_of_hungery < 20 && current_value_of_money >= 80) {
			current_value_of_money -= 80;
			value_of_hungery += 60;
			outer_command = FEED_CMD;
		} else if (value_of_happy < 20 && current_value_of_money >= 150) {
			current_value_of_money -= 150;
			value_of_happy += 80;
			outer_command = PLAY;
		} else if (value_of_thirsty < 20 && current_value_of_money >= 30) {
			current_value_of_money -= 30;
			value_of_thirsty += 30;
			outer_command = WATER_CMD;
		} else {
			if (hashing_complate) {
				hashing_complate = 0;
				outer_command = HASH_CMD;
			} 
			else {
				outer_command = CHECK;
			}
		}

		if (lcd_management) {
			lcd_management = 0;
			lcd_trigger();
			lcd_management = 0;
		}
		trigger_transmission(outer_command);
	}
	TerminateTask();
}


/* End of File : tsk_task0.c */