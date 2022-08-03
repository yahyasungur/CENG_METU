#include "common.h"
#include "LCD.h"
/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/


/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/
const char starting_string[2][16] = {"    CENG 336    ", "   TAMAGOTCHI   "};

TASK(TASK2){
	WaitEvent(LCD_DONE);
	ClearEvent(LCD_DONE);
	LcdPrintString(starting_string[0], 0, 0);
	PIE1bits.RCIE = 1;
	while (1) {
		if (inner_command == GO) {
			lcd_update();
			ActivateTask(TASK0_ID);
			SetEvent(TASK0_ID, DATA_RECEIVED_TRIGGER);
		}
	}
	TerminateTask();
}

/* End of File : tsk_task2.c */
