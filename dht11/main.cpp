#include "dht11.h"
#include <iostream>

int main() {
    std::cout << "DHT11 Humidity & Temperature module program\n";
    
    initializeGpio();

    while (true) {
        readDht11Data();
        delay (2000);
    }
    
}