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
        
    LcdCmd(0x2C);
    LcdCmd(0x0C);
    LcdClear();
}

void LcdClear(){
    LcdData(0x20);
}



void LcdStr(char* buf){
    int upper = 0x00;
    int lower = 0x00;
    if( "a" <= (*buf) && (*buf) <= "o"){
        upper = 0x60;
        lower = 1 + *buf - 'a';
    }else if("p" <= (*buf) && (*buf) <= "z"){
        upper = 0x70;
        lower = (*buf) - 'p';
    }else if("0" <= (*buf) && (*buf) <= "9"){
        upper = 0x30;
        lower = *buf - '0';
    }else{
        upper = 0x02;
        lower = 0;
    }
    LcdData(upper + lower);
}

void LcdMove(int row, int col){
    __delay_us(300);
    LCD_RS = 0;
    LATD = (row << 6) &  0xF0;
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