/*
 * File:   main.c
 * Author: Okan (e2380723) ,Furkan (e2380665) ,Yahya (e2375723)
 *
 * Created on April 30, 2022, 9:02 AM
 */
// CONFIG1H
#pragma config OSC = HSPLL
#pragma config WDT = ON // Watchdog Timer (WDT enabled) for debugging

// combine poll logics with state changing mechanisms like rf0 
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

uint8_t custRowOne = 0b00000;
uint8_t custRowTwo = 0b00000;
uint8_t custRowThree = 0b00000;
uint8_t custRowFour = 0b00000;
uint8_t custRowFive = 0b00000;
uint8_t custRowSix = 0b00000;
uint8_t custRowSeven = 0b00000;
uint8_t custRowEight= 0b00000;




uint8_t f2Pressed, f1Pressed,f0Pressed, e0Pressed, e1Pressed, e2Pressed;


uint8_t defCount= 0, col = 0, row = 0;

uint8_t segmentBool = 0;
uint8_t segmentDelay = 0;


void segment_function(){
   

          
            switch(segmentDelay)
            {
                case 0:
                    LATJ = 0x00;
                    LATH = 0x01;
                    switch(defCount){
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
                        case 5:
                        LATJ = SEGMENT_FIVE;
                        break;
                        case 6:
                        LATJ = SEGMENT_SIX;
                        break;
                        case 7:
                        LATJ = SEGMENT_SEVEN;
                        break;
                        case 8:
                        LATJ = SEGMENT_EIGHT;
                        break;
                    

                    }
                 
                    segmentDelay = 1;
                    break;
                case 1:
                     LATJ = 0x00;
                    LATH = 0x04;
                   
                     switch(col){
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
                        
                    

                    }
                    segmentDelay = 2;
                    break;
                case 2:
                     LATJ = 0x00;
                    LATH = 0x08;
                     switch(row){
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
                        case 5:
                        LATJ = SEGMENT_FIVE;
                        break;
                        case 6:
                        LATJ = SEGMENT_SIX;
                        break;
                        case 7:
                        LATJ = SEGMENT_SEVEN;
                        break;
                        
                    

                    }
                    segmentDelay = 0;
                    break;
            }
            // End BAS
            
          
         
        }
   
        
   


void init_segment(){
    TRISJ = 0x00;
    TRISH = 0x00;
    LATH = 0x00;
    LATJ = 0x00;
    
    segmentDelay = 0;
   
}

void default_init(){
    
    f2Pressed = 0;
    
    
    PORTG = 0x00;
}

void init_io(){
    ADCON1 = 0x0F;
    
   
    TRISA = 0XFF;
    TRISB = 0XFF;
    TRISC = 0XFF;
    TRISD = 0XFF;
    
    TRISE = 0X00;
    TRISF = 0x00;
    LATE = 0X00; // added later
    LATF = 0x00;
    TRISE = 0X07;
    TRISF = 0x07; // Make g all input
    

    
    // set all pins off
    
    
}








void poll_f2(){
    if(PORTFbits.RF2 == 1 && !f2Pressed){
        f2Pressed = 1;
    }else if(PORTFbits.RF2 == 0 && f2Pressed){
        f2Pressed = 0;
        //toggle led
        uint8_t temp = 0b00000001;
        uint8_t amount = 7-row;
        uint8_t mask = temp << amount;
        switch(col){
            case 0:
                
                LATA = LATA ^ mask;
                break;
            case 1:
               
                LATB = LATB ^ mask;
                break;
            case 2:
               
                LATC = LATC ^ mask;
                break;
            case 3:
               
                LATD = LATD ^ mask;
                break;
        }
       
     
    }
    
    
    
}
void poll_f1(){
    if(PORTFbits.RF1 == 1 && !f1Pressed){
        f1Pressed = 1;
    }else if(PORTFbits.RF1 == 0 && f1Pressed){
        f1Pressed = 0;
        if(row < 7){
            row++; 
        }
       
     
    }
    
    
    
}
void transposeForTransfer(){
    for(int i = 7; i<= 0; i--){
        uint8_t temp = 0b00000001;
        uint8_t trtemp = 0b00001;
        uint8_t amount = 7-i;
        uint8_t mask = temp << amount;
        
        switch(i){
            case 7:
                if(PORTA & mask){
                  custRowOne = custRowOne |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowOne = custRowOne |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowOne = custRowOne |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowOne = custRowOne |( trtemp << 1 );
                }
                break;
            case 6:
                 if(PORTA & mask){
                  custRowTwo = custRowTwo |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowTwo = custRowTwo |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowTwo = custRowTwo |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowTwo = custRowTwo |( trtemp << 1 );
                }
                 break;
            case 5:
                 if(PORTA & mask){
                  custRowThree = custRowThree |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowThree = custRowThree |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowThree = custRowThree |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowThree = custRowThree |( trtemp << 1 );
                }
                break;
            case 4:
                 if(PORTA & mask){
                  custRowFour = custRowFour |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowFour = custRowFour |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowFour = custRowFour |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowFour = custRowFour |( trtemp << 1 );
                }
                break;
            case 3:
                 if(PORTA & mask){
                  custRowFive = custRowFive |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowFive = custRowFive |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowFive = custRowFive |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowFive = custRowFive |( trtemp << 1 );
                }
                break;
            case 2: 
                if(PORTA & mask){
                  custRowSix = custRowSix |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowSix = custRowSix |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowSix = custRowSix |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowSix = custRowSix |( trtemp << 1 );
                }
                break;
            case 1:
                 if(PORTA & mask){
                  custRowSeven = custRowSeven |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowSeven = custRowSeven |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowSeven = custRowSeven |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowSeven = custRowSeven |( trtemp << 1 );
                }
                break;
            case 0:
                 if(PORTA & mask){
                  custRowEight = custRowEight |( trtemp << 4 );
                }
                if(PORTB & mask){
                   custRowEight = custRowEight |( trtemp << 3 );
                }
                if(PORTC & mask){
                   custRowEight = custRowEight |( trtemp << 2 );
                }
                if(PORTD & mask){
                   custRowEight = custRowEight |( trtemp << 1 );
                }
                break;
        }
        
      
        
    }
}
void poll_f0(){
    if(PORTFbits.RF0 == 1 && !f0Pressed){
        f0Pressed = 1;
    }else if(PORTFbits.RF0 == 0 && f0Pressed){
        f0Pressed = 0;
        if(defCount < 8){
            //add new letter
            //state change
            defCount++; 
        }
        col = 0;
        row = 0;
        transposeForTransfer();
        LATA = 0x00;
        LATB = 0X00;
        LATC = 0X00;
        LATD = 0x00;
     
    }
    
    
    
}
void poll_e0(){
    if(PORTEbits.RE0 == 1 && !e0Pressed){
        e0Pressed = 1;
    }else if(PORTEbits.RE0 == 0 && e0Pressed){
        e0Pressed = 0;
        if(col < 3){
            col++; 
        }
       
     
    }
    
    
    
}
void poll_e1(){
    if(PORTEbits.RE1 == 1 && !e1Pressed){
        e1Pressed = 1;
    }else if(PORTEbits.RE1 == 0 && e1Pressed){
        e1Pressed = 0;
        if(row > 0){
            row--; 
        }
       
     
    }
    
    
    
}
void poll_e2(){
    if(PORTEbits.RE2 == 1 && !e2Pressed){
        e2Pressed = 1;
    }else if(PORTEbits.RE2 == 0 && e2Pressed){
        e2Pressed = 0;
        if(col >0){
            col--; 
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
        poll_f0();
        poll_f1();
        poll_f2();
        poll_e0();
        poll_e1();
        poll_e2();
      
    }  
}
