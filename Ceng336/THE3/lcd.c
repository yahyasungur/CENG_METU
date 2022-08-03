#include <xc.h>
#include <p18cxxx.h>
#include <stdint.h>
#include <stdio.h>

#define _XTAL_FREQ   40000000

#pragma config  OSC = HSPLL, FCMEN = OFF, IESO = OFF
#pragma config  PWRT = OFF, BOREN = OFF, BORV = 3
#pragma config  WDT = OFF, WDTPS = 32768
#pragma config  MODE = MC, ADDRBW = ADDR20BIT, DATABW = DATA16BIT, WAIT = OFF
#pragma config  CCP2MX = PORTC, ECCPMX = PORTE, LPT1OSC = OFF, MCLRE = ON
#pragma config  STVREN = ON, LVP = OFF, BBSIZ = BB2K, XINST = OFF
#pragma config  CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CP4 = OFF, CP5 = OFF
#pragma config  CP6 = OFF, CP7 = OFF
#pragma config  CPB = OFF, CPD = OFF
#pragma config  WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRT4 = OFF
#pragma config  WRT5 = OFF, WRT6 = OFF, WRT7 = OFF
#pragma config  WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config  EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTR4 = OFF
#pragma config  EBTR5 = OFF, EBTR6 = OFF, EBTR7 = OFF
#pragma config  EBTRB = OFF
#pragma config DEBUG = ON

#define LCD_RS LATB2
#define LCD_EN LATB5
#define LCD_D4 LATD4
#define LCD_D5 LATD5
#define LCD_D6 LATD6
#define LCD_D7 LATD7

// Pulse time for the E pin.
#define LCD_PULSE 30

// Predefined set of characters.
volatile char PREDEFINED[] = " abcdefghijklmnopqrstuvwxyz0123456789";

// A custom character is defined as an array of 8 bytes.
// Each bytes' least significant 5 bits are used to draw
// custom characters to the LCD.
// Example custom character definition.
uint8_t fullHeart[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
};

// Implementation of below functions are provided in lcd.c

// Pulse the E pin of the LCD.
void Pulse(void);
// Properly initialize the LCD.
void InitLCD(void);
// Create a custom character and store it in the LCD's memory.
// First argument is the address to store the character. It can
// take values between 0 and 7 (for 8 custom characters). Second
// argument is the character data. See the fullHeart array above.
// When you send the address as 'data' to the LCD, the custom
// character stored at that address is displayed.
void CreateChar(uint8_t address, uint8_t* charmap);

// Takke a look at the functions below. They might give you
// some ideas on how to design your program. Again, you DON'T
// HAVE TO implement these functions. You can create your own
// functions if you want. You can also comment out or delete these
// functions.
//
void LcdCmd(uint8_t cmd);
void LcdData(uint8_t data);

// You can use this array to convert numbers in range [0x0-0xF] to seven segment
// glyphs by using the value at the index that you want to convert.
// E.g. SSEGMENT_NUMBERS_GLYPHS[3] -> will display 3 on seven segment display.
volatile uint8_t SSEGMENT_NUMBERS_GLYPHS[] = {
  0x3F, 0x06, 0x5B, 0x4F,
  0x66, 0x6D, 0x7D, 0x07,
  0x7F, 0x6F, 0x77, 0x7c,
  0x58, 0x5E, 0x79, 0x71,
};

void Pulse(void){
    PORTBbits.RB5 = 1;
    __delay_us(30);
    PORTBbits.RB5 = 0;
    __delay_us(30);
}

void SendBusContents(uint8_t data){
  PORTD = PORTD & 0x0F;           // Clear bus
  PORTD = PORTD | (data&0xF0);     // Put high 4 bits
  Pulse();                        
  PORTD = PORTD & 0x0F;           // Clear bus
  PORTD = PORTD | ((data<<4)&0xF0);// Put low 4 bits
  Pulse();
}

void InitLCD(void) {
    // Initializing by Instruction
    __delay_ms(20);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(6);
    PORTD = 0x30;
    Pulse();
    
    __delay_us(300);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(2);
    PORTD = 0x20;
    Pulse();
    PORTBbits.RB2 = 0;
    SendBusContents(0x2C);
    SendBusContents(0x0C);
    SendBusContents(0x01);
}

uint8_t charmap[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
};

void init_AD(){
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
  PIR1bits.ADIF = 0;
}

void init_AD_interrupt(){
  INTCONbits.GIE = 0;
  PIE1bits.ADIE = 1;
  INTCONbits.PEIE = 1;
  INTCONbits.GIE = 1;
}

void ad_interrupt_handle(){
  PIR1bits.ADIF = 0;
  unsigned int result = (ADRESH << 8) + ADRESL; // Get the result;


/********************************************************************************/
  // 4bytes for ADC Res + 1 byte for custom char + 1 byte null;
  char buf[6];
  sprintf(buf, "%04u", result);
  buf[4]=0; // Address of custom char
  buf[5]=0; // Null terminator

  // Set DDRAM address to 0 (line 1 cell 1) -> 0x80
  PORTBbits.RB2 = 0;
  SendBusContents(0x80);
  // Write buf to LCD DDRAM
  PORTBbits.RB2 = 1;
  SendBusContents(buf[0]);
  SendBusContents(buf[1]);
  SendBusContents(buf[2]);
  SendBusContents(buf[3]);
  SendBusContents(0);
// Write custom char to lcd

/********************************************************************************/
}

void __interrupt(high_priority) highPriorityISR(void){
    
    if(PIR1bits.ADIF == 1)
    {
        PIE1bits.ADIE = 0;
        ad_interrupt_handle();
        ADCON0bits.GO_nDONE = 0;
        PIE1bits.ADIE = 1;
    }

    return;
}


void main(void) {

  init_AD();
  InitLCD();
  init_AD_interrupt();
  __delay_ms(30);
  
  PORTBbits.RB2 = 0;
  SendBusContents(0x0C); // Display on, cursor off, blink off.
  
  // Define custom char LCD
  // Set CGRAM address 0 -> 0x40
  PORTBbits.RB2 = 0;
  SendBusContents(0x40);

  // Start sending charmap
  for(int i=0; i<8; i++){
    PORTBbits.RB2 = 1; // Send Data
    SendBusContents(charmap[i]);
  }
  SendBusContents(0x02);

  ADCON0bits.GO_nDONE = 1;
  
  while(1){
      if(ADCON0bits.GO_nDONE == 0){
          ADCON0bits.GO_nDONE = 1;
      }
  }
  return;
}
/* 
#include "Includes.h"
#include "lcd.h"

void Pulse(void){
    LCD_EN = 1;
    __delay_us(LCD_PULSE);
    LCD_EN = 0;
    __delay_us(LCD_PULSE);
}

void InitLCD(void) {
    __delay_ms(20);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(6);
    PORTD = 0x30;
    Pulse();
    
    __delay_us(300);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(2);
    PORTD = 0x20;
    Pulse();
    
    
    //PORTBbits.RB2 = 0;

    LcdCmd(0x28);
    LcdCmd(0x0E);
    LcdClear();
}

void LcdClear(){
    LcdCmd(0x01);
}



void LcdStr(char* buf){
    int upper = 0x00;
    int lower = 0x00;
        
    if( 'a' <= (*buf) && (*buf) <= 'o'){
        upper = 0x60;
        lower = 1 + ((*buf) - 'a');
    }else if('p' <= (*buf) && (*buf) <= 'z'){
        upper = 0x70;
        lower = (*buf) - 'p';
    }else if('0' <= (*buf) && (*buf) <= '9'){
        upper = 0x30;
        lower = (*buf) - '0';
    }else{
        upper = 0x20;
        lower = 0;
    }
    LcdData(upper + lower);
}

void LcdMove(int row, int col){
    __delay_us(300);
    LCD_RS = 0;
    LATD = (row << 6) &  0xF0;
    LATD = LATD | 0x80;
    Pulse();
    __delay_us(300);
    LATD = (col << 4) & 0xF0;
    Pulse();
}

void LcdCmd(uint8_t cmd){
    // Send 'cmd' as a command to the LCD.
    __delay_us(300);
    LCD_RS = 0;
    LATD = LATD & 0x0F;
    LATD = LATD | (cmd & 0xF0);
    Pulse();
    __delay_us(300);
    LATD = LATD & 0x0F;
    LATD = LATD | ((cmd << 4) & 0xF0);
    Pulse();
}

void LcdData(uint8_t data){
    // Send 'data' as data to the LCD.
    __delay_us(300);
    LCD_RS = 1;
    LATD = LATD & 0x0F;
    LATD = LATD | (data & 0xF0);
    Pulse();
    __delay_us(300);
    LATD = LATD & 0x0F;
    LATD = LATD | ((data << 4) & 0xF0);
    Pulse();
}

void CreateChar(uint8_t addr, uint8_t charmap[]) {
  addr &= 0x7; // we only have 8 locations 0-7
  LcdCmd(0x40 | (addr << 3)); // Set the address for custom char.
  for (int i=0; i<8; i++) {
    LcdData(charmap[i]); // Write char data.
  }
}
 */