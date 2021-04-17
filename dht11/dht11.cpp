#include "dht11.h"
#include <wiringPi.h>
#include <iostream>
#include <vector>
#include <stdbool.h>

// timeout number of loop 
const int k_MAX_LOOP { 200 };

// check the checksum 
bool isValid(const std::vector<uint8_t>& data) {
	
	for (int counter {}; counter < 5; counter++ ) {
		if (data[counter] != 0) {
			break;
		}

		// all the data is 0
		if (counter == 4) {
			return false;
		}
	}
	
	unsigned sum { (static_cast<unsigned> (data[0] ) + static_cast<unsigned> (data[1] ) 
					+ static_cast<unsigned> (data[2] ) + static_cast<unsigned> (data[3] ) ) 
					& static_cast<unsigned> (0xFF) };
	if (sum != static_cast<unsigned> (data[4] ) ) {
		return false;
	}

	return true;
}

// return true if all works well, otherwise false 
bool workout(std::vector<uint8_t>& data, int last_state) {

	// if missed the first 50 us of LOW voltage input 
	if (digitalRead(k_GPIO_PIN) != last_state) {
		return false;
	}


	for (int index_data {}; index_data < 5; index_data++ ) {
		for (int index_bit {}; index_bit < 8; index_bit++ ) {

			if (last_state != digitalRead(k_GPIO_PIN) ) {
				return false;
			}
			
			// spec: 50 us of LOW voltage input 
			while (last_state == digitalRead(k_GPIO_PIN) ) {
				delayMicroseconds(1);
			}
			last_state = digitalRead(k_GPIO_PIN);

			// spec: 26-28us of HIGH voltage for bit-0, 70 us for bit-1
			int counter_high { };
			while (last_state == digitalRead(k_GPIO_PIN) ) {
				// if missed all the transaction process and the resistor has pulled the voltage high
				if (counter_high == 140) {
					return false;
				}

				counter_high++;
				delayMicroseconds(1);
			}
			last_state = digitalRead(k_GPIO_PIN);

			// is a bit-1
			if (counter_high > 50) {
				data[index_data] |= (1 << (7 - index_bit) );
			} /* is a bit-0 */ else {
				continue;
			}
		}
	}

	// if checksum does NOT match
	if ( !isValid(data) ) {
		return false;
	}

	return true;
}

/*
// BAD Method
// use 5*8 for loop to work on the data
// return true if all works well, otherwise false 
bool twoLayerLoopWorkout(int last_state) {
	// 5 8-bit dht data
	// std::vector<uint8_t> data {0, 0, 0, 0, 0};

	for (int data_index {}; data_index < 5; data_index++ ) {
		for (int bit_index {}; bit_index < 8; bit_index++ ) {
			
			if (last_state != digitalRead(k_GPIO_PIN) ) {
				return false;
			}
			
			// spec: 50 us of input LOW voltage 
			// Practical mic Counter: 23-55us, average 23us
			while (last_state == digitalRead(k_GPIO_PIN) ) {
				delayMicroseconds(1);
			}
			last_state = digitalRead(k_GPIO_PIN);

			// spec: 26-28us for bit-0, 70us for bit-1
			// practival mic Counter: 9-24us for bit-0, 
			int counter {};
			while (last_state == digitalRead(k_GPIO_PIN) ) {
				counter++;
				delayMicroseconds(1);
			}
			last_state = digitalRead(k_GPIO_PIN);
			// std::cout << counter << std::endl;
		}
	}

	return true;
}
*/

void printData(const std::vector<uint8_t>& data) {
	
	std::vector<unsigned> data_refined {};
	for (const auto& x : data) {
		data_refined.push_back(static_cast<unsigned> (x) );
	}

	std::cout << "Humidity: " << data_refined[0] << "." << data_refined[1] << " %"
		<< "	" << "Temperature: " << data_refined[2] << "." << data_refined[3] << " *C"
		<< std::endl;
}

void readDht11Data() {

	// create 5 8-bit vector to store the dht data
	std::vector<uint8_t> data {0, 0, 0, 0, 0};


	pinMode(k_GPIO_PIN, OUTPUT);
	
	// spec: at least 18 ms, pull down for 20 ms
	digitalWrite(k_GPIO_PIN, LOW);
	delay(20);

	// spec: 20-40us
	digitalWrite(k_GPIO_PIN, HIGH);
	delayMicroseconds(40);

	pinMode(k_GPIO_PIN, INPUT);
	// if missed the 80 us of LOW voltage input 
	if (digitalRead(k_GPIO_PIN) != LOW) {
		return;
	}

	// last pin input voltage state 
	int last_state { digitalRead(k_GPIO_PIN) };
	// std::cout << last_state << std::endl;
	
	// spec: 80us of input LOW voltage 
	// Practical mic Counter: 22-56us
	while (last_state == digitalRead(k_GPIO_PIN) ) {
		delayMicroseconds(1);
	}
	last_state = digitalRead(k_GPIO_PIN);

	// spec: 80 us of input HIGH voltage 
	// Practical mic Counter: 26-89us, average 38 us
	while (last_state == digitalRead(k_GPIO_PIN) ) {
		delayMicroseconds(1);
	}
	last_state = digitalRead(k_GPIO_PIN);

	// if data NOT correct 
	if ( !workout(data, last_state) ) {
		for (auto& x : data) {
			x = 0;
		}

		return;
	}

	printData(data);
}