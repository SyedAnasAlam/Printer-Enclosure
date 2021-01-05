# pragma once

#define THERMISTOR_PIN 5
#define POTENTIOMETER_PIN 4
#define ADC_PRESCALER 0x07  // ADC cloc prescaler = 128 -> 125kHz

void InitADC();