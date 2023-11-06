#ifndef I2C_SIMULATION_H
#define I2C_SIMULATION_H

#include <cstdint>
#include "projects\LM75\lm75.hpp"
#include "projects\SHT35\sht35.hpp"

#define LM75_ADRESS 0x48
#define SHT35_ADRESS 0x44

class I2CSimulation {
private:
    LM75 lm75;
    SHT35 sht35;
    uint8_t dataRegister;
    uint16_t data;
    uint8_t currentDevice;
public:
    I2CSimulation::I2CSimulation(LM75 lm75, SHT35 sht35);
    void write(uint8_t registerAddress, uint8_t value);
    void request(uint8_t numBytes);
    uint16_t read();
    void selectDevice(uint8_t deviceAddress);

};

#endif
