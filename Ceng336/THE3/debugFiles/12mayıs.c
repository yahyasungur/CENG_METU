/*
 * File:   main.c
 * Author: Okan (e2380723) ,Furkan () ,Yahya (e2375723)
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

typedef enum {_START,GAME,END} gameStateEnum;
gameStateEnum gameState;
typedef enum {LEVEL1,LEVEL2,LEVEL3} gameLevelEnum;
gameLevelEnum gameLevel;

uint8_t rc0_pressed;

uint8_t noteCount;

uint8_t shift;

uint16_t levelOverflow;
uint16_t tmr0Counter;
uint8_t health;

uint16_t tmr1Val;

uint8_t g0Pressed, g1Pressed, g2Pressed, g3Pressed, g4Pressed;
uint8_t g0Released, g1Released, g2Released, g3Released, g4Released;

uint8_t segmentBool = 0;
uint8_t loseDelay = 0;
uint8_t endDelay = 0;

void segment_function(){
   
    if(gameState == END){
        
        if(health <= 0){
            // LOSE BAS
            switch(loseDelay){
                case 0:
                    LATH = 0x01;
                    LATJ = SEGMENT_L;
                    loseDelay = 1;
                    break;
                case 1:
                      LATH = 0x02;
                      LATJ = SEGMENT_O;
                      loseDelay = 2;
                      break;
                case 2:
                      LATH = 0x04;
                      LATJ = SEGMENT_S;
                      loseDelay = 3;
                      break;
                             
                case 3:
                      LATH = 0x08;
                      LATJ = SEGMENT_E;
                      loseDelay = 0;
                      break;
            }
          
            
        }else{
            switch(endDelay)
            {
                case 0:
                    LATH = 0x01;
                    LATJ = SEGMENT_E;
                    endDelay = 1;
                    break;
                case 1:
                    LATH = 0x02;
                    LATJ = SEGMENT_n;
                    endDelay = 2;
                    break;
                case 2:
                    LATH = 0x04;
                    LATJ = SEGMENT_d;
                    endDelay = 0;
                    break;
            }
            // End BAS
            
          
         
        }
    }else if(gameState == GAME){
        
        switch(segmentBool){
            case 0:
                //LEVELi bas
                LATJ = 0x00;
                LATH = 0x08;
                switch(gameLevel){
                    case LEVEL1:
                        LATJ = SEGMENT_ONE;
                        break;
                    case LEVEL2:
                        LATJ = SEGMENT_TWO;
                        break;
                    case LEVEL3:
                        LATJ = SEGMENT_THREE;
                        break;
                }
                segmentBool = 1;
                break;
            case 1:
                segmentBool = 0;
                // Health bas
                LATJ = 0x00;
                LATH = 0x01;
                
                switch(health){
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
                    case 9:
                        LATJ = SEGMENT_NINE;
                        break;
                }
                break;
        }
        
        
    }
}

void init_segment(){
    TRISJ = 0x00;
    TRISH = 0x00;
    LATH = 0x00;
    LATJ = 0x00;
    gameState = _START;
    health = 9;
    loseDelay = 0;
    endDelay = 0;
}

void default_init(){
    noteCount = 0;
    shift = 0;
    tmr1Val = 0;
    tmr0Counter = 0;
    levelOverflow = 309;    
    
    g0Pressed = 0;
    g1Pressed = 0;
    g2Pressed = 0;
    g3Pressed = 0;
    g4Pressed = 0;
    g0Released = 0;
    g1Released = 0;
    g2Released = 0;
    g3Released = 0;
    g4Released = 0;
    
    PORTG = 0x00;
}

void init_io(){
    ADCON1 = 0x0F;
    
    // init io ports
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x01; // make c0 input as default
    TRISD = 0x00;
    TRISE = 0x00;
    TRISF = 0x00;
    
    TRISG = 0x00;
    LATG = 0x00;
    TRISG = 0x1F; // Make g all input
    

    
    // set all pins off
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    LATF = 0x00;

    
}

void init_timer0_interrupt(){
    T0CON = 0xC5;
}
void init_timer1_interrupt(){
    T1CON = 0xC1;
}


void change_timer0_speed(){
   /*
    Using prescalar 64 and setting the initial value of timer0 equal to 3, 
    we got 500, 400, 300ms as follows:

    0.0001(256-3)*64*308 = 499 ms
    0.0001(256-3)*64*247 = 399.9 ms
    0.0001(256-3)*64*185 = 299.6 ms
    
    */
    
    
   switch(gameLevel){
        case LEVEL1:
            TMR0L = 3;
            levelOverflow = 308;
            break;
        case LEVEL2:
            TMR0L = 3;
            levelOverflow = 247;
            break;
        case LEVEL3:
            TMR0L = 3;
            levelOverflow = 185;
            break;
                
    }
}

void init_interrupts(){
    init_timer0_interrupt();
    init_timer1_interrupt();
}


void interrupts_on(){
    INTCONbits.GIE = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1; 
    INTCONbits.GIE = 1;
}

// ** high pri interrupts for timer0 
void timer0interrupt(){
    INTCONbits.TMR0IF = 0;
    change_timer0_speed();
    tmr0Counter++;
    if(tmr0Counter == levelOverflow){
        tmr0Counter = 0;
        shift = 1;
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


void poll_rc0(){
    if(PORTCbits.RC0 == 1 && rc0_pressed == 0)
    {
        rc0_pressed = 1;
    }   
    else if(PORTCbits.RC0 == 0 && rc0_pressed){
    // button release detected
        gameState = GAME;
        //TMR0L = 61; // first timer0 set
        INTCONbits.TMR0IF = 0;
        rc0_pressed = 0;
        TRISC = 0x00;
        tmr1Val = TMR1;

        gameLevel = LEVEL1;
        health = 9;
        loseDelay = 0;
        endDelay = 0;
        // start interrupts
        interrupts_on();

    }
   
}

void createNote(){
    
    
    // Level shift configuration
    switch(gameLevel){
        
        case LEVEL1:
            tmr1Val = ((tmr1Val << 15) | ((tmr1Val >> 1) & 0x7FFF));
            break;
        case LEVEL2:
            tmr1Val = ((tmr1Val << 13) | ((tmr1Val >> 3) & 0x1FFF));
            break;
        case LEVEL3:
            tmr1Val = ((tmr1Val << 11) | ((tmr1Val >> 5) & 0x07FF));
            break;
    }
    
    uint16_t bits = tmr1Val & 0x0007;
    
    bits = bits % 5;
    
    // Led is generated
    switch(bits){
        case 0:
            LATA = 0x10;
            break;
        case 1:
            LATA = 0x01;
            break;
        case 2:
            LATA = 0x02;
            break;
        case 3:
            LATA = 0x04;
            break;
        case 4:
            LATA = 0x08;
            break;
    }
    
    noteCount++;
    
}

void poll_rg(){
    if(PORTG & 0x01){
        g0Pressed = 1;
    }else if(g0Pressed){
        g0Pressed = 0;
        g0Released = 0x01;
    }
    
    if(PORTG & 0x02){
        g1Pressed = 1;
    }else if(g1Pressed){
        g1Pressed = 0;
        g1Released = 0x02;
    }
    
    if(PORTG & 0x04){
        g2Pressed = 1;
    }else if(g2Pressed){
        g2Pressed = 0;
        g2Released = 0x04;
    }
    
    if(PORTG & 0x08){
        g3Pressed = 1;
    }else if(g3Pressed){
        g3Pressed = 0;
        g3Released = 0x08;
    }
    
    if(PORTG & 0x10){
        g4Pressed = 1;
    }else if(g4Pressed){
        g4Pressed = 0;
        g4Released = 0x10;
    }
}

void checkPressedButtons(){
    if(g0Released && ((LATF & 0x01) != g0Released)){
        health--;
        g0Released = 0;
    }else if (g0Released){
        LATF = LATF & 0xFE;
        g0Released = 0;
    }
    
    if(g1Released && ((LATF & 0x02) != g1Released)){
        health--;
        g1Released = 0;
    }else if (g1Released){
        LATF = LATF & 0xFD;
        g1Released = 0;
    }
    
    if(g2Released && ((LATF & 0x04) != g2Released)){
        health--;
        g2Released = 0;
    }else if (g2Released){
        LATF = LATF & 0xFB;
        g2Released = 0;
    }
    
    if(g3Released && ((LATF & 0x08) != g3Released)){
        health--;
        g3Released = 0;
    }else if (g3Released){
        LATF = LATF & 0xF7;
        g3Released = 0;
    }
    
    if(g4Released && ((LATF & 0x10) != g4Released)){
        health--;
        g4Released = 0;
    }else if (g4Released){
        LATF = LATF & 0xEF;
        g4Released = 0;
    }
    
    if(health <= 0){
        gameState = END;
        health = 0;
    }    
}

void updateLevel(){
    switch(noteCount){
        case 5:
            gameLevel = LEVEL2;
            break;
        case 15:
            gameLevel = LEVEL3;
            break; 
        case 30:
            gameState = END;
            break;
    }
}

void checkNotPressedButtons(){
    if(LATF != 0){
        health--;
    }
    
    if(health <= 0){
        gameState = END;
        health = 0;
    }    
    
}

void getShifted(){
    if(shift){
        checkNotPressedButtons();
        LATF = LATE;
        LATE = LATD;
        LATD = LATC;
        LATC = LATB;
        LATB = LATA;
        shift = 0;
        if(!LATA && !LATB && !LATC && !LATD && !LATE && !LATF && (noteCount == 5 || noteCount==15 || noteCount == 30)) updateLevel();
        if(gameState == GAME && ((gameLevel == LEVEL1 && noteCount != 5) || (gameLevel == LEVEL2 && noteCount != 15) || (gameLevel == LEVEL3 && noteCount != 30))) createNote();
        else{
            LATA = 0;
        }
    }   
}

void main(void)
{
    init_segment();
    default_init();
    init_io();
    init_interrupts();
       
    while(1){
        segment_function();
        switch(gameState){
        case _START:        
            poll_rc0();
            break;
        case GAME:
            poll_rg();
            checkPressedButtons();
            getShifted();
            break;
        case END:
            default_init();
            init_io();
            poll_rc0();
            break;
        }
    }  
}
