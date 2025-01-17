#include "LCD.h"
#include "Arduino.h"

void InitLCD()
{
    //D0 - D7 as outputs - Data pins are split between two GPIO banks
    DDRB |= 0x0F;   // PB0, PB1, PB2, PB3
    DDRC |= 0x0F;   // PC0, PC1, PC2, PC3

    //E + RS as outputs
    DDRB |= (1 << ENABLE_PIN);
    DDRD |= (1 << RS_PIN);

    delay(50);

    //Initialize E low
    PORTB &= ~(1 << ENABLE_PIN);

    //Initialization process
    LCDWriteInstruction(FUNCT_SET);
    delayMicroseconds(4500);
    LCDWriteInstruction(FUNCT_SET);
    delayMicroseconds(150);
    LCDWriteInstruction(FUNCT_SET);

    //LCD setup
    LCDWriteInstruction(HOME);
    LCDWriteInstruction(CURSOR);
    LCDWriteInstruction(SET_DISPLAY);
    LCDWriteInstruction(CLEAR);

    //Text that will always be displayed on LCD
    LCDPrintString("Fan Speed  :");
    LCDGoto(0, 1);
    LCDPrintString("Temperature:");
    
}

// This function writes to the databus of LCD screen
void WriteToBus(int data)
{
    PORTB &= ~B00001111;
    PORTC &= ~B00001111;

    // Get first and second half of the data
    char data03 = data & 0x0F;
    char data47 = (data & (0x0F << 4)) >> 4;
    
    // Output above
    PORTB |= data03;
    PORTC |= data47;
}

void PulseEnable()
{
    PORTB &= ~(1 << ENABLE_PIN);
    delayMicroseconds(1);
    PORTB |= (1 << ENABLE_PIN);
    delayMicroseconds(1);
    PORTB &= ~(1 << ENABLE_PIN);
    delayMicroseconds(100);
}

void LCDPrintChar(char ch)
{
    PORTD |= (1 << RS_PIN);
    WriteToBus(ch);
    PulseEnable();
}

void LCDWriteInstruction(int instruction)
{
    PORTD &= ~(1 << RS_PIN);
    WriteToBus(instruction);
    PulseEnable();
    delay(5);
}

void LCDPrintString(const char * s)
{
	while(*s != 0)
	{
	    LCDPrintChar(*s);
	    s++;
	}
}

void LCDGoto(int column, int row)
{
    LCDWriteInstruction((row == 0 ? 0x80  : 0xC0) + column);    		
}

void LCDPrintMenu(int temperature, int fan)
{
    char tempString[6];
    char fanString[6];

    sprintf(tempString, "%-3dC", temperature);
    sprintf(fanString, "%-3d%%", fan);

    LCDGoto(12, 0);
    LCDPrintString(fanString);
    LCDGoto(12, 1);
    LCDPrintString(tempString);
}
 
