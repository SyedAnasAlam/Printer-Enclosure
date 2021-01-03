#include "Thermistor.h"
#include <Arduino.h>

void ThermistorInit()
{    
    DIDR0 |= (1 << THERMISTOR_PIN);                         // Disable digital input on PC5
    PRR &= ~(1 << PRADC);                                   // Make sure ADC is not shut down by power reduction
    ADMUX |= THERMISTOR_PIN;                 // Input channel selection   
    //ADCSRB &= ~(0x07);                                      // Set in free running mode
    ADCSRA |= (1 << ADSC) | (1 << ADEN) | (1 << ADATE) | 0x07;            // Enable ADC, start conversion and set auto trigger
}