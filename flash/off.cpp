#include <wiringPi.h>
#include "flash.h"

int main() {
    setupGpio();

    // pinMode(k_POSITIVE, OUTPUT);
    // pinMode(k_NEGATIVE, OUTPUT);

    // digitalWrite(k_POSITIVE, LOW);
    // digitalWrite(k_NEGATIVE, LOW);
    
    pinMode(k_POSITIVE, INPUT);
    pinMode(k_NEGATIVE, INPUT);
}