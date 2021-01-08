# pragma once

#define THERMISTOR_PIN 5
#define POTENTIOMETER_PIN 4
#define ADC_PRESCALER 0x07  // ADC cloc prescaler = 128 -> 125kHz

#define SERVO_PIN 3
#define FAN_PIN 6
#define FAN_OFF_PIN 5

void InitADC();
void InitPWM();