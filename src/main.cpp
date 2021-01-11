//TODO different map function (possibly without using FPU)

#include <Arduino.h>
#include "LCD.h"
#include "Components.h"

volatile int temp = 0;
volatile float pot = 0;

float map(float value, float start1, float stop1, float start2, float stop2)
{
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1)); 
}

void setup() 
{
    InitLCD();
    InitADC();
    InitFan();
    InitServo();    
}

void loop() 
{  
    OCR0A = map(pot, 0, 1023, 0, 255);
    OCR2B = map(pot, 0, 1023, 4, 19);
    LCDPrintMenu(pot, temp);
}

//ADC Interrupt handler
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