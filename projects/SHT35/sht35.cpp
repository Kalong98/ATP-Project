#include "sht35.hpp"

SHT35::SHT35(GreenhouseSimulator &simulator):
	greenhouse(simulator) {}

uint16_t SHT35::readTemperature() { // Might not be accurate with SHT35 datasheet, function copied from LM35
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
			tempValue = noisyTemperature / 0.5;
			rawData = tempValue << 7;
		}
	} else { // Negative temperatures
		if (noisyTemperature <= -55.0) {
			rawData = 1 << 15;
			rawData = rawData | 146 << 7;
		} else {
			tempValue = 256 + (noisyTemperature / 0.5);
			rawData = 1 << 15;
			rawData = rawData | tempValue << 7;
		}
	}
	return rawData;
}

uint16_t SHT35::readHumidity() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> noise(-1.5, 1.5); // Adjust the range as needed

    // Add noise to the humidity within the specified deviation
    double noisyHumidity = greenhouse.getHumidity() + noise(gen);

    uint16_t rawData = 0x0000;

    rawData = (65535 / 100) * noisyHumidity;
    return rawData;
}

void SHT35::updateData(){
	uint16_t tempData = readTemperature();
	uint16_t humData = readHumidity();
	uint8_t checksum = 0x12;
	
	uint8_t tempMSB = (tempData >> 8) & 0xFF;
    uint8_t tempLSB = tempData & 0xFF;
    uint8_t humMSB = (humData >> 8) & 0xFF;
    uint8_t humLSB = humData & 0xFF;

	data[0] = tempMSB;
    data[1] = tempLSB;
	data[2] = checksum;
    data[3] = humMSB;
	data[4] = humLSB;
    data[5] = checksum;
}

std::vector<uint8_t>* SHT35::getData() {
    return &data;
}