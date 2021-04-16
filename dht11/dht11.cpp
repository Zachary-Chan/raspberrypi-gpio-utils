// The documentation of DHT11 specifies the exact interval time periods between each phase.
// But when implementing the module, they don't follow it at all!
// So it mess up all the code design, I have no choice but do it like this.
// Anyway it can run properly!

#include <wiringPi.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

const int k_GPIO_PIN { 23 };
const int k_MAX_TIMING { 255 };

void readDhtData();


int main() {
	std::cout << "Raspberry Pi wiringPi DHT11 Temperature and Humidity test Program" << std::endl
		<< "Calculating... It may take up to 20 seconds, please wait" << std::endl;

	wiringPiSetupGpio();

	while (true) {
		readDhtData();

		delay( 1000 );
	}
}

void readDhtData() {
	
	uint8_t checksum {};
	// restore the dht data-- 5 uint8_t vector
	std::vector<uint8_t> data { 0, 0, 0, 0, 0 };

	// pull pin down for 20 milliseconds 
	pinMode( k_GPIO_PIN, OUTPUT );
	digitalWrite( k_GPIO_PIN, LOW );
	delay( 20 );

	// then pull it up for 40 microseconds 
	digitalWrite( k_GPIO_PIN, HIGH );
	delayMicroseconds( 40 );

	//delayMicroseconds(5);
	// prepare to read the pin
	pinMode( k_GPIO_PIN, INPUT );
	

	/*
	// wait for the dht to be prepared for the transmission 
	delayMicroseconds( 80 );	// LOW voltage
	delayMicroseconds( 80 );	// HIGH voltage
	*/

	for (int counter {}; (LOW == digitalRead(k_GPIO_PIN) ); counter++) {
		/*
		int counter { };
		counter++;
		*/
		if(counter == k_MAX_TIMING) {
			goto skip;
			
		}
		delayMicroseconds(1);
	}

	// int last_state { HIGH };
	// go through the first 80 microseconds HIGH voltage period 
	for (int counter {}; HIGH == digitalRead(k_GPIO_PIN); counter++) {
		/*
		int counter { };
		counter++;
		*/
		if (counter == k_MAX_TIMING) {
			goto skip;
			
		}
		delayMicroseconds(1);
	}

	// 40 bits data flow 
	for (int i {}; i < 5; i++) {
		for (int j {}; j < 8; j++ ) {

			for (int counter {}; LOW == digitalRead(k_GPIO_PIN); counter++) {
				if (counter == k_MAX_TIMING) {
					goto skip;
					
				}

				delayMicroseconds(1);
			}

			// conut the time and judge if it is HIGH or LOW voltage 
			int counter {};
			for ( ; HIGH == digitalRead(k_GPIO_PIN); ) {
				if (counter == k_MAX_TIMING) {
					goto skip;
					
				}

				counter++;
				delayMicroseconds(1);
			}
			// the last period is more than 70 miscroseconds (50 for secure)
			// then it is the bit 1

			if (counter > 50) {
				data[i] |= ( 1 << (7 - j) );
			} /* the bit 0 */ else {
				continue;
			}
		}
	}

	if ( 0 == data[0] == data[1] == data[2] == data[3] == data[4] ){
		goto skip;
	}


	checksum = ( (data[0] + data[1] + data[2] + data[3] ) & 0xFF);
	if (checksum != data[4] ) {
		goto skip;
	}

	// for debuging
/*
	for (const auto& x : data) {
		std::cout << static_cast<unsigned int> (x) << std::endl;
	}
*/
	std::cout << "Humidity: " << static_cast<unsigned> (data[0] ) << "." << static_cast<unsigned> (data[1] ) << " %"
		<< "	Temperature: " << static_cast<unsigned> (data[2] ) << "." << static_cast<unsigned> (data[3] )<< " *C"
		<< std::endl;

skip:
	return;
}