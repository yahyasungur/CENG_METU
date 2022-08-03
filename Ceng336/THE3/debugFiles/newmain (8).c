/*
 * File:   main.c
 * Author: Okan (e2380723) ,Furkan (e2380665) ,Yahya (e2375723)
 *
 * Created on April 30, 2022, 9:02 AM
 */
// CONFIG1H
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

#define SEGMENT_L 0x38
#define SEGMENT_O 0x3F
#define SEGMENT_S 0x6D
#define SEGMENT_E 0x79
#define SEGMENT_n 0x54
#define SEGMENT_d 0x5E







uint8_t f2Pressed;
uint8_t f2Released;

uint8_t count= 0;

uint8_t segmentBool = 0;
uint8_t endDelay = 0;


void segment_function(){
   

          
            switch(endDelay)
            {
                case 0:
                    LATJ = 0x00;
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
                     LATJ = 0x00;
                    LATH = 0x04;
                    LATJ = SEGMENT_ZERO;
                    endDelay = 2;
                    break;
                case 2:
                     LATJ = 0x00;
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
    
    f2Pressed = 0;
    
    
    PORTG = 0x00;
}

void init_io(){
    ADCON1 = 0x0F;
    
   
    
    TRISG = 0x00;
    LATG = 0x00;
    TRISG = 0x1F; // Make g all input
    

    
    // set all pins off
    
    
}








void poll_f2(){
    if(PORTFbits.RF2 == 1 && !f2Pressed){
        f2Pressed = 1;
    }else if(PORTFbits.RF2 == 0 && f2Pressed){
        f2Pressed = 0;
        if(count < 8){
            count++; 
        }
       
     
    }
    
    
    
}





void main(void)
{
    init_segment();
    default_init();
    init_io();
   
       
    while(1){
        segment_function();
        poll_f2();
      
    }  
}
