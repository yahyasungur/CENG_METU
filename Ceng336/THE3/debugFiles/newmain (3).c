/* 
 * File:   newmain.c
 * Author: kocak
 *
 * Created on June 2, 2022, 12:47 PM
 */

#include <stdio.h>
#include <stdlib.h>


#pragma config OSC = HSPLL
#pragma config WDT = ON // Watchdog Timer (WDT enabled) for debugging

#include <xc.h>
#include <stdint.h>

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
#define SEGMENT_E 0x79

uint8_t first = 0;
uint8_t defCharCount = 0;
uint8_t second = 0;
uint8_t third = 0;

uint8_t e0Pressed, e1Pressed, e2Pressed, f1Pressed;
uint8_t e0Released, e1Released, e2Released, f1Pressed;

uint8_t a0Pressed, a1Pressed, a2Pressed;
uint8_t a0Released, a1Released, a2Released;

uint8_t loseDelay = 0;


void segment_function(){
   
        switch(loseDelay){
                case 0:
                    LATH = 0x01;
                    switch(first){
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
                    
                    loseDelay = 1;
                    break;
             
                case 1:
                      LATH = 0x04;
                       switch(second){
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
                      loseDelay = 2;
                      break;
                             
                case 2:
                      LATH = 0x08;
                       switch(third){
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
                      loseDelay = 0;
                      break;
        
       
            
          
         
        
    }
    
}

void init_segment(){
    TRISJ = 0x00;
    TRISH = 0x00;
    LATH = 0x00;
    LATJ = 0x00;
  
    
}

void default_init(){

    first = 0;
    defCharCount= 0;
    
    second = 0;
    third = 0;
    a0Pressed = 0;
    a1Pressed = 0;
    a2Pressed = 0;

    a0Released = 0;
    a1Released = 0;
    a2Released = 0;
 
    
    
}

void init_io(){
 
    
    ADCON1 = 0x0F;
    TRISA = 0xFF;
 

    
    
    
}







void poll_ra0(){
    if(PORTAbits.RA0 == 1 && a0Pressed == 0)
    {
        a0Pressed = 1;
    }   
    else if(PORTAbits.RA0 == 0 && a0Pressed){
    // button release detected
       a0Pressed = 0;
       first++;
       defCharCount++;
    }
   
}
void poll_ra1(){
    if(PORTAbits.RA1 == 1 && a1Pressed == 0)
    {
        a1Pressed = 1;
    }   
    else if(PORTAbits.RA1 == 0 && a1Pressed){
    // button release detected
         a1Pressed = 0;
       second++;
    }
   
}
void poll_ra2(){
    if(PORTAbits.RA2 == 1 && a2Pressed == 0)
    {
        a2Pressed = 1;
    }   
    else if(PORTAbits.RA2 == 0 && a2Pressed){
    // button release detected
        a2Pressed = 0;
       third++;
    }
   
}



void main(void)
{
    init_segment();
    default_init();
    init_io();
  
       
    while(1){
        segment_function();
        poll_ra0();
        poll_ra1();
        poll_ra2();
    }  
}
