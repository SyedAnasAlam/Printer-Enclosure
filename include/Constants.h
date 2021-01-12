# pragma once

//Constants for calculating temperature
const float A = 1.800146936e-03;
const float B = 1.230136967e-04;
const float C = 5.375031228e-07;
const int R1 = 10000;

const unsigned long SCAN_TIME = 10000;

//eeprom adress at which current position of lock can be read
const int EEPROM_ADR = 0;