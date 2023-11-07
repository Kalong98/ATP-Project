#include "sht35.hpp"

SHT35::SHT35(GreenhouseSimulator &simulator):
	greenhouse(simulator) {}

uint16_t SHT35::readTemperature() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> noise(-0.25, 0.25); // Adjust the range as needed

	// Add noise to the temperature within the specified deviation
	double noisyTemperature = greenhouse.getTemperature() + noise(gen);

	uint16_t rawData = 0x0000;

	rawData = int((noisyTemperature + 45) * (65535 / 175));

	return rawData;
}

uint16_t SHT35::readHumidity() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> noise(-1.5, 1.5); // Adjust the range as needed

    // Add noise to the humidity within the specified deviation
    double noisyHumidity = greenhouse.getHumidity() + noise(gen);

    uint16_t rawData = 0x0000;

    rawData = int((65535 / 100) * noisyHumidity);
    return rawData;
}

// formula SHT35 temp C = -45 + 175 * (rawdata / 65535)
// formula SHT35 humid C = 100 * (rawdata / 65535)