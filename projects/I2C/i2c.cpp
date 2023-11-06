#include "i2c.hpp"
#include <iostream>
#include <thread>
#include <chrono>



I2CSimulation::I2CSimulation(LM75 lm75, SHT35 sht35):
lm75 (lm75),
sht35 (sht35),
dataRegister(0),
data(0),
currentDevice(0)
{}

void I2CSimulation::write(uint8_t registerAddress, uint8_t value) {
    if (currentDevice == LM75_ADRESS) {
        if (registerAddress == LM75_TEMP_REGISTER) {
            dataRegister = value;
        }
        // Add more conditionals for other device registers as needed
    }
    else if (currentDevice == SHT35_ADRESS){}
    {
        /* code */
    }
    
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
