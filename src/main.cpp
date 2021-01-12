#include <Arduino.h>
#include <Adafruit_Fingerprint.h> 
#include <EEPROM.h>
#include "LCD.h"
#include "Components.h"

volatile int thermistor = 0;
volatile float pot = 0;

volatile boolean scan = false;
volatile unsigned long scanStartTime = 0;
const unsigned long scanTime = 10000;

const int eepromAdr = 0;
boolean locked = true;

const float A = 1.800146936e-03;
const float B = 1.230136967e-04;
const float C = 5.375031228e-07;
const int R1 = 10000;
int rt = 0;
int temp = 0;

SoftwareSerial mySerial(FP_RX, FP_TX);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() 
{
    SREG |= (1 << 7);    // Enable global interrupts 
    InitLCD();
    InitADC();
    InitFan();
    InitServo(); 
    InitButton();
    InitLEDS();
    finger.begin(57600);   
    Serial.begin(9600);
}

void loop() 
{  
    OCR0A = 255.0f * (pot / 1023.0f);

    rt = R1 * ((1023/float(thermistor)) - 1.0);
    temp = (1.0/(A + B*log(rt) + C*(pow(log(rt), 3)))) - 273.15;

    LCDPrintMenu((pot / 1023.0f) * 100, temp);
    
    if(scan)
    {
        if(millis() - scanStartTime <= scanTime)
        {
            WriteLED(SCAN_LED_PIN, true);
            if(ScanFingerprint(finger))
            {
                locked = EEPROM.read(eepromAdr);
                OCR2B = locked ? SERVO_UNLOCK_POS : SERVO_LOCK_POS;
                EEPROM.write(eepromAdr, !locked);
                
                WriteLED(SCAN_LED_PIN, false);
                scan = false;

                WriteLED(ACCESS_LED_PIN, true);
                delay(500);
                WriteLED(ACCESS_LED_PIN, false);
            }   
        }
        else
        {
            scan = false;
            WriteLED(SCAN_LED_PIN, false);
        }
        
    }
}

ISR(ADC_vect)
{
    if((ADMUX & 0x0F) == THERMISTOR_PIN) 
    {
        ADMUX--;
        thermistor = ADC;
    }
    else 
    {
        ADMUX++;
        pot = ADC;
    }

    
    ADCSRA |= (1 << ADSC);
}

ISR(INT0_vect)
{
    if(!scan)
    {
        scanStartTime = millis();
        scan = true;
    }
}

