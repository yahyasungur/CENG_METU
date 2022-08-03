#ifndef __COMMON_H__
#define __COMMON_H__
#include <string.h>
#include "device.h"
#define _XTAL_FREQ   40000000

/* ------------------------ Timer settings -----------------------------*/
#define _10MHZ	63320
#define _16MHZ	61768
#define _20MHZ	60768
#define _32MHZ	57768
#define _40MHZ 	55768

/* ----------------------------- Events --------------------------------*/

#define ALARM_EVENT             0x80
#define TRIGGER_CMD             0x82
#define DATA_RECEIVED_TRIGGER   0x84
#define LCD_DONE                0x88
#define SOLVE_TRIGGER           0x81
#define LCD_TRIGGER             0x08

/*----------------------------- Task ID -------------------------------*/

#define TASK0_ID             1
#define TASK1_ID             2
#define TASK2_ID             4
#define LCD_ID               8

/* Priorities of the tasks */
#define ALARM_TSK0           0
#define LCD_ALARM_ID         2
#define TASK2_PRIO           4
#define TASK1_PRIO           6
#define TASK0_PRIO           6
#define LCD_PRIO             7

/*----------------------- GLOBAL DEFINITIONS -------------------------*/

extern int value_of_happy;
extern int value_of_thirsty;
extern char value_of_money;
extern int value_of_hungery;
extern int Current_LCD_Value;
extern int current_value_of_money;
extern char lcd_management;
extern char hashing_complate;
extern char str_alarm[8];
extern char hash[17];

typedef enum {
    GO, END, FEED_CMD, WATER_CMD, PLAY, CHECK, SENSOR_CMD, HASH_CMD, ALARM_CMD, MONEY
} cmd;

extern cmd outer_command;
extern cmd inner_command;

/*----------------------- FUNCTION PROTOTYPES ------------------------*/

/* transmits data using serial communication */
void transmitData();
/* Invoked when receive interrupt occurs; meaning that data is received */
void dataReceived();
void parser();
void lcd_update();
void lcd_trigger();
void trigger_transmission(cmd cmd);

#endif

/* End of File : common.h */
