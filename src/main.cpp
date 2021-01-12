#include <Arduino.h>
#include <Adafruit_Fingerprint.h> 
#include <EEPROM.h>
#include "LCD.h"
#include "Components.h"
#include "Constants.h"

volatile int thermistor = 0;
volatile float potentiometer = 0;

volatile boolean scan = false;
volatile unsigned long scanStartTime = 0;

boolean locked = true;

SoftwareSerial serial(FP_RX, FP_TX);
Adafruit_Fingerprint fpSensor = Adafruit_Fingerprint(&serial);

void setup() 
{
    sei();  // Enable global interrupts
    InitLCD();
    InitADC();
    InitFan();
    InitServo(); 
    InitButton();
    InitLEDS();
    fpSensor.begin(57600);   
}

void loop() 
{  
    // ADC reads 10 bit value from pot, scale this down to an 8-bit value for fan PWM timer
    FanPWMWrite(255.0f * (potentiometer / 1023.0f));

    LCDPrintMenu(GetTemp(thermistor), (potentiometer / 1023.0f) * 100);
    
    // Scan fingerprint only when button is pressed and for a duration of scanTime
    if(scan)
    {
        if(millis() - scanStartTime <= SCAN_TIME)
        {
            WriteLED(SCAN_LED_PIN, true);
            if(ScanFingerprint(fpSensor))
            {
                locked = EEPROM.read(EEPROM_ADR);
                ServoWrite(locked ? SERVO_UNLOCK_POS : SERVO_LOCK_POS);
                EEPROM.write(EEPROM_ADR, !locked);
                
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
    // Alternate between which channel is being read by ADC
    if((ADMUX & 0x0F) == THERMISTOR_PIN) 
    {
        ADMUX--;
        thermistor = ADC;
    }
    else 
    {
        ADMUX++;
        potentiometer = ADC;
    }

    
    ADCSRA |= (1 << ADSC);
}

// Interrupt handler for button
ISR(INT0_vect)
{
    if(!scan)
    {
        scanStartTime = millis();
        scan = true;
    }
}

