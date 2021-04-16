#include <wiringPi.h>

// 7-color-flashing module pinpoints connected by GPIO pinout
const int k_POSITIVE { 27 };
const int k_NEGATIVE { 22 };
const int k_SIGNAL { 17 };

void setupGpio() {
    wiringPiSetupGpio();
}