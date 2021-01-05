#include <Arduino.h>
#include "LCD.h"
#include "HAL.h"

volatile int temp = 0;
volatile int pot = 0;
char x[4];

void setup() 
{
    LCDSetup();
    InitADC();
   
    Serial.begin(9600);
}

void loop() 
{  
    LCDPrintMenu(temp, pot);
    delay(100);   
}

ISR(ADC_vect)
{
    if((ADMUX & 0x0F) == THERMISTOR_PIN) 
    {
        ADMUX--;
        temp = ADC;
    }
    else 
    {
        ADMUX++;
        pot = ADC;
    }

    
    ADCSRA |= (1 << ADSC);
}