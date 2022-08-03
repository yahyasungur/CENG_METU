#pragma config OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

#include <xc.h>
#include "breakpoints.h"


void init(){
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    TRISC = 0xFF;
    TRISD = 0xFF;
    TRISE = 0x00;
    TRISA = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    
    TRISB = 0x20;
    
    ADCON1 = 0xFF;
    
}

void init_interrupt(){
    INTCONbits.GIE = 0;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    INTCONbits.GIE = 1;
}

void handler(){
    PORTE = PORTC + PORTD;
    if(STATUSbits.C == 1){
        PORTAbits.RA0 = 1;
    }
    interrupt_checkpoint();
    
}

void __interrupt(high_priority) highPriorityISR(void) {
    if(INTCONbits.RBIF == 1){
        INTCONbits.RBIE = 0;
        handler();
        job_done();
        INTCONbits.RBIE = 1;
    }
}


void main(void) {
    init();
    init_interrupt();
    init_complete();
    while(1){
        // do nothing here
    }
}
