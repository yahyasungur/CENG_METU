#include "common.h"
#include "hash.h"
/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/


/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/

TASK(TASK1){
	while (1) {
		WaitEvent(SOLVE_TRIGGER);
		ClearEvent(SOLVE_TRIGGER);
		hash_handler(str_alarm, hash);
		value_of_money = 0;
		hashing_complate = 1;
	}
	TerminateTask();
}