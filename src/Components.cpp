#include <Arduino.h>
#include "Components.h"

void InitADC()
{                 
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

void InitButton()
{
    EICRA |= (1 << ISC01) | (1 << ISC00);       // INT0 interrupts on rising edges
    EIMSK |= (1 << INT0);                       // Enable INT0 interrupts
}

void InitLEDS()
{
    DDRC |= (1 << ACCESS_LED_PIN) | (1 << SCAN_LED_PIN);
}

void WriteLED(int ledPin, boolean val)
{
    if(ledPin != ACCESS_LED_PIN && ledPin != SCAN_LED_PIN) return;
    if(val) PORTC |= (1 << ledPin);
    else PORTC &= ~(1 << ledPin);
}

boolean ScanFingerprint(Adafruit_Fingerprint finger) 
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return false;
  

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return false;


  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return false;
  
  // found a match!
  return true;
}

