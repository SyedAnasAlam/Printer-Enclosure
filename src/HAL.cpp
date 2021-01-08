#include "HAL.h"
#include <Arduino.h>

void InitADC()
{    
    SREG    |= (1 << 7);                                        // Enable global interrupts              
    DIDR0   |= (1 << THERMISTOR_PIN);                           // Disable digital input buffer 
    DIDR0   |= (1 << POTENTIOMETER_PIN);                        // Disable digital input buffer
    ADMUX   |= POTENTIOMETER_PIN | (1 << REFS0);                // Set initial input channel for ADC
    ADCSRA  |= (1 << ADEN) | (1 << ADIE) | ADC_PRESCALER;       // Enable ADC and ADC interrupt and set prescaler to 128
    ADCSRA  |= (1 << ADSC);                                     // Start conversion
}

void InitPWM()
{
    DDRD |= (1 << FAN_PIN) | (1 << SERVO_PIN);

    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS01); 

    TCCR2A |= (1 << COM2B1) | (1 << WGM20);
    TCCR2B |= (1 << CS21) | (1 << CS20);
}


