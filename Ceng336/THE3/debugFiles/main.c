#include "Includes.h"
#include <stdio.h>


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


void main(void) {
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
  
  InitLCD();
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
  
  while(1){
    // Get ADC Sample
    GODONE = 1; // Start ADC conversion
    while(GODONE); // Poll and wait for conversion to finish.
    unsigned int result = (ADRESH << 8) + ADRESL; // Get the result;

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
  }
  return;
}