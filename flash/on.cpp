#include <wiringPi.h>
#include "flash.h"

int main() {
    setupGpio();

    pinMode(k_POSITIVE, OUTPUT);
    pinMode(k_NEGATIVE, OUTPUT);
    // pinMode(k_SIGNAL, OUTPUT);

    digitalWrite(k_POSITIVE, HIGH);
    digitalWrite(k_NEGATIVE, LOW);
    
}