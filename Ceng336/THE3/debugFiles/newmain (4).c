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

uint8_t b0Pressed, b1Pressed, b2Pressed;
uint8_t b0Released, b1Released, b2Released;

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
    b0Pressed = 0;
    b1Pressed = 0;
    b2Pressed = 0;

    b0Released = 0;
    b1Released = 0;
    b2Released = 0;
 
    
    
}

void init_io(){
 
    
    ADCON1 = 0x0F;
    TRISA = 0xFF;
    TRISB = 0xFF;
 

    
    
    
}







void poll_rb0(){
    if(PORTBbits.RB0 == 1 && b0Pressed == 0)
    {
        b0Pressed = 1;
    }   
    else if(PORTBbits.RB0 == 0 && b0Pressed){
    // button release detected
       b0Pressed = 0;
       first++;
       
    }
   
}



void main(void)
{
    init_segment();
    default_init();
    init_io();
  
       
    while(1){
        segment_function();
        poll_rb0();
      
    }  
}
