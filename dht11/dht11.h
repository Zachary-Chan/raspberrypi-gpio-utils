#ifndef DHT11_H
#define DHT11_H

#include <wiringPi.h>

// dht11 GPIO pin
inline const int k_GPIO_PIN { 23 };
inline void initializeGpio() { wiringPiSetupGpio(); }

void readDht11Data();

#endif