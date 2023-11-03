#include "sht35.hpp"

SHT35::SHT35(uint8_t address, GreenhouseSimulator &simulator)
    : address(address), greenhouse(simulator) {}

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

    rawData = 

    return rawData; // Simulate humidity reading
}

main(){

	u8 data[6]={0};
	u16 temp_hex=0,hum_hex=0;
	CHECK_RESULT(ret,send_command(cfg_cmd));
	CHECK_RESULT(ret,read_bytes(data,sizeof(data),CLK_STRCH_STAT));

	temp_hex=(data[0] << 8) | data[1];
	hum_hex =(data[3] << 8) | data[4];

	*temp =get_temp(temp_hex);
	*hum=get_hum(hum_hex);


}
