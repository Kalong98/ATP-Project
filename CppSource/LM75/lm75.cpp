#include <stdint.h>
#include <random>
#include "lm75.hpp"
#include <iostream>

LM75::LM75(GreenhouseSimulator & simulator):
greenhouse(simulator)
{}

uint16_t LM75::readTemperature() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> noise(-0.25, 0.25); // Adjust the range as needed

	// Add noise to the temperature within the specified deviation
	double noisyTemperature = greenhouse.getTemperature() + noise(gen);
	uint16_t rawData = 0x0000;
	uint8_t tempValue = 0x00;

	if (noisyTemperature == 0.0) {
		tempValue = 0;
	} else if (noisyTemperature > 0.0) { // Positive temperatures
		if (noisyTemperature >= 125.0) {
			rawData = 250 << 7;
		} else {
			tempValue = int(noisyTemperature / 0.5);
			rawData = tempValue << 7;
		}
	} else { // Negative temperatures
		if (noisyTemperature <= -55.0) {
			rawData = 1 << 15;
			rawData = rawData | 146 << 7;
		} else {
			tempValue = int(256 + (noisyTemperature / 0.5));
			rawData = 1 << 15;
			rawData = rawData | tempValue << 7;
		}
	}
	return rawData;
}
