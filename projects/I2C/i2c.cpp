#include "i2c.hpp"
#include <iostream>
#include <thread>
#include <chrono>

I2CSimulation::I2CSimulation(uint8_t address):
address(address),
dataRegister(0),
data(0),
currentDevice(0)
{}

void I2CSimulation::write(uint8_t registerAddress, uint8_t value) {
    if (currentDevice == address) {
        if (registerAddress == LM75_TEMP_REGISTER) {
        // Wire.beginTransmission(address);
        // Wire.write(LM75_TEMP_REGISTER);
        // Wire.endTransmission();

        // Wire.requestFrom(address, 2);
        // if (Wire.available() >= 2) {
        // int raw_temperature = Wire.read() << 8 | Wire.read();
        // return (double(raw_temperature >> 7) * 0.5);
        // }
        // return -1.0; // Error reading temperature
            dataRegister = value;
        }
        // Add more conditionals for other device registers as needed
    }

    // SHT35 data:
    // 	u8 data[6]={0};
	// u16 temp_hex=0,hum_hex=0;
	// CHECK_RESULT(ret,send_command(cfg_cmd));
	// CHECK_RESULT(ret,read_bytes(data,sizeof(data),CLK_STRCH_STAT));

	// temp_hex=(data[0] << 8) | data[1];
	// hum_hex =(data[3] << 8) | data[4];

	// *temp =get_temp(temp_hex);
	// *hum=get_hum(hum_hex);

}

void I2CSimulation::request(uint8_t numBytes) {
    if (currentDevice == address) {
        if (numBytes == 2) {
            data = 0x1234; // Example temperature value (in this case, 25°C)
            // Add more conditionals for other device data as needed
        }
    }
}

uint16_t I2CSimulation::read() {
    if (currentDevice == address) {
        return data;
    }
    return 0;
}

void I2CSimulation::selectDevice(uint8_t deviceAddress) {
    currentDevice = deviceAddress;
}
