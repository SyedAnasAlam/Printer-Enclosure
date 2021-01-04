#include "Thermistor.h"
#include <Arduino.h>

void ThermistorInit()
{    
    SREG |= (1 << 7);
    DIDR0 |= (1 << THERMISTOR_PIN);       
    DIDR0 |= (1 << POTENTIOMETER_PIN);                 
    PRR &= ~(1 << PRADC);                                   
    ADMUX |= POTENTIOMETER_PIN;                                                          
    ADCSRA |= (1 << ADSC) | (1 << ADEN) | (1 << ADIE) | 0x07;            
}