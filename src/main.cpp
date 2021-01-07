//TODO different map function (possibly without using FPU)
//TODO cleanup

#include <Arduino.h>
#include "LCD.h"
#include "HAL.h"

volatile int temp = 0;
volatile float pot = 0;

float map(float value, float start1, float stop1, float start2, float stop2)
{
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1)); 
}

void setup() 
{
    LCDSetup();
    InitADC();
    InitPWM();
   
    Serial.begin(9600);
}

void loop() 
{  
    //OCR0A = map(pot, 0, 1023, 0, 255);
    OCR2B = 4;
    delay(2000);
    OCR2B = 19;
    delay(2000);
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