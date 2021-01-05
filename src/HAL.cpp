#include "HAL.h"
#include <Arduino.h>

void InitADC()
{    
    SREG    |= (1 << 7);                                        // Enable global interrupts              
    DIDR0   |= (1 << THERMISTOR_PIN);                           // Disable digital input buffer 
    DIDR0   |= (1 << POTENTIOMETER_PIN);                        // Disable digital input buffer
    PRR     &= ~(1 << PRADC);                                   // Make sure ADC is not turned of by power reduction
    ADMUX   |= POTENTIOMETER_PIN | (1 << REFS0);                // Set initial input channel for ADC
    ADCSRA  |= (1 << ADEN) | (1 << ADIE) | ADC_PRESCALER;       // Enable ADC and ADC interrupt and set prescaler to 128
    ADCSRA  |= (1 << ADSC);                                     // Start conversion
}