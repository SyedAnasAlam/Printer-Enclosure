#include <Arduino.h>
#include "LCD.h"
#include "Thermistor.h"

void setup() 
{
    LCDSetup();
    ThermistorInit();
    //Serial.begin(9600);
}

void loop() 
{  
    LCDPrintMenu(ADC, 69);   
}