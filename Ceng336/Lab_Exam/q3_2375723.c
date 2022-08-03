#pragma config OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

#include <xc.h>
#include "breakpoints.h"

int levelOverflow = 0;
int tmr0Counter = 0;
int toogle = 0;

void default_init(){
    TMR0L = 3;
    levelOverflow = 308;
    tmr0Counter = 0;   
}

void init_timer0_interrupt(){
    T0CON = 0xC5;
}

void change_timer0_speed(){
    TMR0L = 3;
    levelOverflow = 308;
}

void init_interrupts(){
    init_timer0_interrupt();
}


void interrupts_on(){
    INTCONbits.GIE = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.GIE = 1;
}


void timer0interrupt(){
    INTCONbits.TMR0IF = 0;
    tmr0Counter++;
    if(tmr0Counter == levelOverflow){
        tmr0Counter = 0;
        toogle = 1;
    } 
}


void __interrupt(high_priority) highPriorityISR(void){
       
    if(INTCONbits.TMR0IF == 1)
    {
        INTCONbits.TMR0IE = 0;
        timer0interrupt();
        INTCONbits.TMR0IE = 1;
    }
   
    return;
}


void getToogle(){
    if(toogle){
        toggle_pin();
        toogle = 0;
    }   
}

void main(void){
    
    default_init();
    init_interrupts();
    change_timer0_speed();
    init_complete();
    //interrupts_on();
    while(1){
        getToogle();
    }  
}
