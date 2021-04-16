#include <wiringPi.h>
#include "flash.h"
#include <iostream>

int main() {
    setupGpio();

    pinMode(k_SIGNAL, OUTPUT);

    
    while (true) {
        using namespace std;

        cout << "1. on \n2. off \n3. exit" << endl;

        int choice {};
        cin >> choice;

        switch(choice) {
            case 1:
                digitalWrite(k_SIGNAL, HIGH);
                break;

            case 2:
                digitalWrite(k_SIGNAL, LOW);
                break;
            
            default:
                exit(EXIT_SUCCESS);
        }

    }
}