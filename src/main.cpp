#include <Arduino.h>
#include "LCD.h"
#include "Thermistor.h"

volatile int temp = 0;
volatile int pot = 0;

void setup() 
{
    LCDSetup();
    ThermistorInit();
    Serial.begin(9600);
    DDRD |= (1 << 6);
   
    Serial.begin(9600);
}

void loop() 
{  
    LCDPrintMenu(temp, pot);   
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