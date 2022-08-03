/*
 * File:   main.c
 * Author: Okan (e2380723) ,Furkan (e2380665) ,Yahya (e2375723)
 *
 * Created on April 30, 2022, 9:02 AM
 */
// CONFIG1H
#pragma config OSC = HSPLL
//#pragma config WDT = ON // Watchdog Timer (WDT enabled) for debugging

#include <xc.h> 
#include <stdint.h>
#include "Includes.h"
#include "lcd.h"


#define SEGMENT_ZERO 0x3F
#define SEGMENT_ONE 0x06
#define SEGMENT_TWO 0x5B
#define SEGMENT_THREE 0x4F
#define SEGMENT_FOUR 0x66
#define SEGMENT_FIVE 0x6D
#define SEGMENT_SIX 0x7D
#define SEGMENT_SEVEN 0x07
#define SEGMENT_EIGHT 0x7F
#define SEGMENT_NINE 0x6F

#define SEGMENT_L 0x38
#define SEGMENT_O 0x3F
#define SEGMENT_S 0x6D
#define SEGMENT_E 0x79
#define SEGMENT_n 0x54
#define SEGMENT_d 0x5E


typedef enum{_TEM, _CDM, _TSM} program_state;
program_state programState;



uint8_t g0Pressed, e0Pressed, e1Pressed, e2Pressed, e3Pressed, e4Pressed, e5Pressed;
uint8_t g0Released, e0Released, e1Released, e2Released, e3Released, e4Released, e5Released;
int predefinedIndex;
int cursorIndex = 0;
uint8_t count= 0;

char text[] = "AAAAAAAAAAAAAAAA";

uint16_t adcResult = 0;
uint8_t adcFinished = 0;
uint8_t segmentBool = 0;
uint8_t endDelay = 0;
uint16_t tmr1Val;
uint16_t levelOverflow = 308;
uint16_t tmr0Counter;
int shift = 0;

void segment_function(){
    
            switch(endDelay)
            {
                case 0:
                    LATH = 0x01;
                    switch(count){
                        case 0:
                        LATJ = SEGMENT_ZERO;
                        break;
                        case 1:
                        LATJ = SEGMENT_ONE;
                        break;
                        case 2:
                        LATJ = SEGMENT_TWO;
                        break;
                        case 3:
                        LATJ = SEGMENT_THREE;
                        break;
                        case 4:
                        LATJ = SEGMENT_FOUR;
                        break;
                    }
                 
                    endDelay = 1;
                    break;
                case 1:
                    LATH = 0x04;
                    LATJ = SEGMENT_ZERO;
                    endDelay = 2;
                    break;
                case 2:
                    LATH = 0x08;
                    LATJ = SEGMENT_ZERO;
                    endDelay = 0;
                    break;
            }
            // End BAS
        }
   
        
void init_segment(){
    TRISJ = 0x00;
    TRISH = 0x00;
    LATH = 0x00;
    LATJ = 0x00;
    
    endDelay = 0;
   
}

void default_init(){
    tmr1Val = 0;
    tmr0Counter = 0;
    levelOverflow = 308;
    shift = 0;
    
    programState = _TEM;
    predefinedIndex = 0;
    
    e0Pressed = 0;
    e1Pressed = 0;
    e2Pressed = 0;
    e3Pressed = 0;
    e4Pressed = 0;
    e5Pressed = 0;
    
    e0Released = 0;
    e1Released = 0;
    e2Released = 0;
    e3Released = 0;
    e4Released = 0;
    e5Released = 0;
}

void init_io(){

    TRISE = 0x3F;
        
    // Set ADC Inputs
    TRISH = 0x10; // AN12 input RH4
    // Set LCD Outputs
    TRISB = 0x00; // LCD Control RB2/RB5
    LATB = 0x00;
    TRISD = 0x00; // LCD Data  RD[4-7]
    LATD = 0x00;
    // Configure ADC
    ADCON0 = 0x31; // Channel 12; Turn on AD Converter
    ADCON1 = 0x0F; // All analog pins
    ADCON2 = 0xAA; // Right Align | 12 Tad | Fosc/32
    ADRESH = 0x00;
    ADRESL = 0x00;
}

void poll_re(){
    if(PORTE & 0x01){
        e0Pressed = 1;
    }else if(e0Pressed){
        e0Pressed = 0;
        e0Released = 1;
    }
    if(PORTE & 0x02){
        e1Pressed = 1;
    }else if(e1Pressed){
        e1Pressed = 0;
        e1Released = 1;
    }
    if(PORTE & 0x04){
        e2Pressed = 1;
    }else if(e2Pressed){
        e2Pressed = 0;
        e2Released = 1;
    }
    if(PORTE & 0x08){
        e3Pressed = 1;
    }else if(e3Pressed){
        e3Pressed = 0;
        e3Released = 1;
    }
    if(PORTE & 0x10){
        e4Pressed = 1;
    }else if(e4Pressed){
        e4Pressed = 0;
        e4Released = 1;
    }
    if(PORTE & 0x20){
        e5Pressed = 1;
    }else if(e5Pressed){
        e5Pressed = 0;
        e5Released = 1;
    }
}

void checkPressedButtons(){
    switch(programState){
        case _TEM:
            if(e1Released){
                e1Released = 0;
                predefinedIndex--; 
                if(predefinedIndex < 0){
                    predefinedIndex = 36;
                }
                text[adcResult] = PREDEFINED[predefinedIndex];
                LcdStr(&PREDEFINED[predefinedIndex]);
            }
            if(e2Released){
                e2Released = 0;
                predefinedIndex++; 
                if(predefinedIndex > 36){
                    predefinedIndex = 0;
                }
                text[adcResult] = PREDEFINED[predefinedIndex];
                LcdStr(&PREDEFINED[predefinedIndex]);
            }
            if(e4Released){
                e4Released = 0;
                programState = _CDM;
            }
            if(e5Released){
                e5Released = 0;
                programState = _TSM;
            }
            break;
        case _CDM:
            break;
        case _TSM:
            break;
    }
}

void init_AD_interrupt(){
  INTCONbits.GIE = 0;
  PIR1bits.ADIF == 0;
  PIE1bits.ADIE = 1;
  INTCONbits.PEIE = 1;
  INTCONbits.GIE = 1;
  GODONE = 1;
}

void init_timer0_interrupt(){
    INTCONbits.GIE = 0;
    PIE1bits.ADIE = 0;
    T0CON = 0xC5;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.GIE = 1;
}

void ad_interrupt_handle(){
    if(adcFinished){
        adcFinished = 0;
        adcResult = (ADRESH << 8) | ADRESL; // Get the result;
        adcResult = (adcResult/64)%16;
        cursorIndex = adcResult;
        LcdMove(0, adcResult);
        
        
        if(GODONE == 0){
          GODONE = 1;
        }
    }
}

void timer0interrupt(){
    tmr0Counter++;
    if(tmr0Counter == levelOverflow){
        tmr0Counter = 0;
        shift = 1;
    } 
}

void __interrupt(high_priority) highPriorityISR(void){
    
    if(PIR1bits.ADIF == 1)
    {
        PIE1bits.ADIE = 0;
        
        PIR1bits.ADIF = 0;
        adcFinished = 1;
        //GODONE = 0;
        
        PIE1bits.ADIE = 1;
    }
    
    if(INTCONbits.TMR0IF == 1){
        INTCONbits.TMR0IF = 0;
        timer0interrupt();
    }

    return;
}

void shiftLogic(){
    LcdCmd(0x0C); // Display off (on -- yahya), curser off
    
    char finished[16] = "   finished     ";

    for (int i = 0; i < 16; i++){
        LcdMove(0, i);
        LcdStr(&finished[i]);
    }
    
    __delay_ms(3000);

    for(int i = 0; i < 16; i++){
        LcdMove(1, i);
        if(text[i] == 'B'){
            /* print  custom char to here with special[index][index_iterator]*/
        }else{
            LcdStr(&text[i]);
        }
    }
    
    LcdCmd(0x0C); // Display on

    char firstChar = ' ';
    char emptyChar = ' ';
    
    while(1){
        if(shift == 0){
            continue;
        }
        shift = 0;
        
        firstChar = text[0];
        
        for(int i = 0; i < 15; i++){
            LcdMove(0, i);
            if(text[i] == 'B'){
                LcdStr(&emptyChar);
                /* print custom char */
            }else{
                LcdStr(&text[i+1]);
            }
            text[i] = text[i+1];
        }
        
        LcdMove(0, 15);
        if(text[15] == 'B'){
            LcdStr(&emptyChar);
            /* print custom char */
        }else{
            LcdStr(&firstChar);
        }
        text[15] = firstChar;
    }
    
}

void main(void)
{
    //init_segment();
    default_init();
    init_io();
    InitLCD();
    
    init_AD_interrupt();
    while(1){
        switch(programState){
            case _TEM:
                poll_re();
                break;
            case _CDM:
                poll_re();
                break;
            case _TSM:
                init_timer0_interrupt();
                shiftLogic();
                break;
        }
        ad_interrupt_handle();
        //segment_function();
        checkPressedButtons();
    }
}