#include "i2c.hpp"
#include <iostream>

I2CSimulation::I2CSimulation(LM75 lm75, SHT35 sht35):
lm75 (lm75),
sht35 (sht35),
dataRegister(0),
currentDevice(0),
lm75TempRaw(0),
sht35TempRaw(0),
sht35HumidRaw(0),
lm75Data(128, 0),
sht35Data(128, 0),
lm75VectorSize(0),
sht35VectorSize(0)
{}

void I2CSimulation::write(uint8_t registerAddress, uint8_t value) {
    if (currentDevice == LM75_ADRESS) {
        if (registerAddress == LM75_TEMP_REGISTER) {
            lm75TempRaw = lm75.readTemperature();
        }
    }
    else if (currentDevice == SHT35_ADRESS) {
        if (registerAddress == SHT35_ADRESS) {
            if (value == SHT35_MEASURE_TEMP_COMMANDO){
                sht35TempRaw = sht35.readTemperature();
            }
            if (value == SHT35_MEASURE_HUMID_COMMANDO){
                sht35HumidRaw = sht35.readHumidity();
            }
        }
    }
    else{
        // nothing
    }
}

void I2CSimulation::request(uint8_t numBytes) {
    if (currentDevice == LM75_ADRESS) {
        if (numBytes == 2) {
            uint8_t tempMSB = (lm75TempRaw >> 8) & 0xFF;
            uint8_t tempLSB = lm75TempRaw & 0xFF;
            lm75Data[lm75VectorSize] = tempMSB;
            lm75VectorSize += 1;
            lm75Data[lm75VectorSize] = tempLSB;
            lm75VectorSize += 1;
        }
    }
    else if (currentDevice == SHT35_ADRESS) {
        if (numBytes == 6) {
            uint8_t tempMSB = (sht35TempRaw >> 8) & 0xFF;
            uint8_t tempLSB = sht35TempRaw & 0xFF;
            uint8_t humidMSB = (sht35HumidRaw >> 8) & 0xFF;
            uint8_t humidLSB = sht35HumidRaw & 0xFF;
            uint8_t checksum = 0x12;
            sht35Data[sht35VectorSize] = tempMSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = tempLSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = checksum;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = humidMSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = humidMSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = checksum;
            sht35VectorSize += 1;
        }
    }
}

uint8_t I2CSimulation::read() {
    uint8_t res = 0x00;
    if (currentDevice == LM75_ADRESS) {
        if (lm75VectorSize == 1){
            lm75VectorSize -= 1;
            return lm75Data[0];
        }
        else {
            res = lm75Data[0];
            for (unsigned int i = 0; i < lm75VectorSize - 1; i++){
                lm75Data[i] = lm75Data[i + 1];
            }
            lm75VectorSize -= 1;
            return res;
        }
    }
    else if (currentDevice == SHT35_ADRESS) {
        if (sht35VectorSize == 1){
            sht35VectorSize -= 1;
            return sht35Data[0];
        }
        else {
            res = sht35Data[0];
            for (unsigned int i = 0; i < sht35VectorSize - 1; i++){
                sht35Data[i] = sht35Data[i + 1];
            }
            sht35VectorSize -= 1;
            return res;
        }
    }
    return 0;
}

void I2CSimulation::selectDevice(uint8_t deviceAddress) {
    currentDevice = deviceAddress;
}

float calculateTempCel_SHT35 (uint16_t rawData){
    return (-45 + (175 * (static_cast<float>(rawData) / 65535)));
}
    
float calculateHumid_SHT35 (uint16_t rawData){
    return (100 * (static_cast<float>(rawData) / 65535));
}