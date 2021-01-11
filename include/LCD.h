#pragma once

#define ENABLE_PIN 4
#define RS_PIN 7

//LCD instructions
#define FUNCT_SET 0X38
#define HOME 0X02
#define CLEAR 0x01
#define SET_DISPLAY 0x0C
#define CURSOR 0x06

void InitLCD();
void WriteToBus(int data);
void PulseEnable();
void LCDPrintChar(char ch);
void LCDWriteInstruction(int instruction);
void LCDPrintString(const char * s);
void LCDGoto(int column, int row);
void LCDPrintMenu(int temperature, int fan);

