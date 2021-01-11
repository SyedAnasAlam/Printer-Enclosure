#include "Components.h"
#include <Arduino.h>

void InitADC()
{    
    SREG    |= (1 << 7);                                                                // Enable global interrupts              
    DIDR0   |= (1 << THERMISTOR_PIN);                                                   // Disable digital input buffer 
    DIDR0   |= (1 << POTENTIOMETER_PIN);                                                // Disable digital input buffer
    ADMUX   |= POTENTIOMETER_PIN | (1 << REFS0);                                        // Set initial input channel for ADC
    ADCSRA  |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Enable ADC and ADC interrupt and set prescaler to 128
    ADCSRA  |= (1 << ADSC);                                                             // Start conversion
}

void InitFan()
{
    DDRD    |= (1 << FAN_PIN);                              // Set as output
    TCCR0A  |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // Set to fast PWM mode on pin PD6
    TCCR0B  |= (1 << CS00);                                 // No prescaling
}

void InitServo()
{
    DDRD    |= (1 << SERVO_PIN);                // Set as output
    TCCR2A  |= (1 << COM2B1) | (1 << WGM20);    // Phase and frequency mode on pin PD3
    TCCR2B  |= (1 << CS21) | (1 << CS20);       // Prescaling to 32
}


