#pragma once

#define E 4
#define RS 7

#define FUNCT_SET 0X38
#define HOME 0X02
#define CLEAR 0x01
#define SET_DISPLAY 0x0C
#define CURSOR 0x06

void LCDSetup();
void WriteToBus(int data);
void PulseEnable();
void LCDPrintChar(char ch);
void LCDWriteInstruction(int instruction);
void LCDPrintString(const char * s);
void LCDGoto(int column, int row);
void LCDPrintMenu(int tempString, int humString);

