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



uint8_t g0Pressed, e1Pressed, f0Pressed, f1Pressed, f2Pressed;
uint8_t g0Released, e1Released, f0Released, f1Released, f2Released;
uint8_t predefinedIndex = 0;
uint8_t count= 0;

uint8_t adcResult = 0;
uint8_t adcFinished = 0;
uint8_t segmentBool = 0;
uint8_t endDelay = 0;


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
    
    programState = _TEM;
    
    g0Pressed = 0;
    e1Pressed = 0;
    f0Pressed = 0;
    f1Pressed = 0;
    f2Pressed = 0;
    
    g0Released = 0;
    e1Released = 0;
    f0Released = 0;
    f1Released = 0;
    f2Released = 0;
}

void init_io(){

    TRISE = 0x02;
    TRISF = 0x07;
        
    // Set ADC Inputs
    TRISH = 0x10; // AN12 input RH4
    // Set LCD Outputs
    TRISB = 0x00; // LCD Control RB2/RB5
    TRISD = 0x00; // LCD Data  RD[4-7]
    // Configure ADC
    ADCON0 = 0x31; // Channel 12; Turn on AD Converter
    ADCON1 = 0x00; // All analog pins
    ADCON2 = 0xAA; // Right Align | 12 Tad | Fosc/32
    ADRESH = 0x00;
    ADRESL = 0x00;
    PIR1bits.ADIF == 0;
    
}

void poll_re(){
    if(PORTE & 0x01){
        e1Pressed = 1;
    }else if(g0Pressed){
        e1Pressed = 0;
        e1Released = 0x01;
     
    }
}

void poll_rf(){
    if(PORTF & 0x01){
        f0Pressed = 1;
    }else if(f0Pressed){
        f0Pressed = 0;
        f0Released = 0x01;
    }
    
    if(PORTF & 0x02){
        f1Pressed = 1;
    }else if(f1Pressed){
        f1Pressed = 0;
        f1Released = 0x01;
     
    }
    
    if(PORTF & 0x04){
        f2Pressed = 1;
    }else if(f2Pressed){
        f2Pressed = 0;
        f2Released = 0x01;
     
    }   
}

void checkPressedButtons(){
    switch(programState){
        case _TEM:
            if(e1Released){
                e1Released = 0;
                PREDEFINED[(predefinedIndex += 36) % 37];
            }
            if(f1Released){
                f1Released = 0;
                PREDEFINED[(predefinedIndex++) % 37];
            }
            if(f0Released){
                f0Released = 0;
                programState = _CDM;
            }
            if(f2Released){
                f2Released = 0;
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
  PIE1bits.ADIE = 1;
  INTCONbits.PEIE = 1;
  INTCONbits.GIE = 1;
  GODONE = 1;
}

void ad_interrupt_handle(){
    if(adcFinished){
        adcFinished = 0;
        adcResult = (ADRESH << 8) + ADRESL; // Get the result;
        LcdMove(0, adcResult/(1023/16));
        
        if(GODONE == 0){
          GODONE = 1;
        }
    }
}

void __interrupt(high_priority) highPriorityISR(void){
    
    if(PIR1bits.ADIF == 1)
    {
        PIE1bits.ADIE = 0;
        PIR1bits.ADIF = 0;
           
        adcFinished = 1;
        GODONE = 0;
        PIE1bits.ADIE = 1;
    }

    return;
}

void main(void)
{
    init_segment();
    default_init();
    init_io();
    InitLCD();
    
    init_AD_interrupt();
    while(1){
        switch(programState){
            case _TEM:
                poll_re();
                poll_rf();
                break;
            case _CDM:
                break;
            case _TSM:
                break;
        }
        ad_interrupt_handle();
        //segment_function();
        //checkPressedButtons();
    }  
}