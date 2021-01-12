# pragma once
#include <Adafruit_Fingerprint.h> 

#define THERMISTOR_PIN 7
#define POTENTIOMETER_PIN 6

#define SERVO_PIN 3
#define FAN_PIN 6

#define FP_RX 4
#define FP_TX 5
#define FP_BUTTON_PIN 2

#define ACCESS_LED_PIN 5
#define SCAN_LED_PIN 4

#define SERVO_LOCK_POS 4
#define SERVO_UNLOCK_POS 19

void InitADC();
void InitFan();
void InitServo();
void InitButton();
void InitLEDS();
void WriteLED(int ledPin, boolean onOff);

boolean ScanFingerprint(Adafruit_Fingerprint finger);
