#ifndef I2C_SIMULATION_H
#define I2C_SIMULATION_H

#include <cstdint>

class I2CSimulation {
private:
    uint8_t address;
    uint8_t dataRegister;
    uint16_t data;
    uint8_t currentDevice;
public:
    I2CSimulation(uint8_t address);

    void write(uint8_t registerAddress, uint8_t value);
    void request(uint8_t numBytes);
    uint16_t read();
    void selectDevice(uint8_t deviceAddress);

};

#endif
