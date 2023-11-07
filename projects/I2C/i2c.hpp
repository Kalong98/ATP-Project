#ifndef I2C_SIMULATION_H
#define I2C_SIMULATION_H

#include <cstdint>
#include "../LM75/lm75.hpp"
#include "../SHT35/sht35.hpp"
#include "../simulator/simulator.hpp"

#define LM75_ADRESS 0x48
#define SHT35_ADRESS 0x44
#define LM75_TEMP_REGISTER 0x00
#define SHT35_MEASURE_TEMP_COMMANDO 0x24
#define SHT35_MEASURE_HUMID_COMMANDO 0x26

class I2CSimulation {
private:
    LM75 lm75;
    SHT35 sht35;
    uint8_t dataRegister;
    uint8_t currentDevice;
    uint16_t lm75TempRaw;
    uint16_t sht35TempRaw;
    uint16_t sht35HumidRaw;
    std::vector<uint8_t> lm75Data;
    std::vector<uint8_t> sht35Data;
    uint8_t lm75VectorSize;
    uint8_t sht35VectorSize;
public:
    I2CSimulation(LM75 lm75, SHT35 sht35);
    void write(uint8_t registerAddress, uint8_t value);
    void request(uint8_t numBytes);
    uint8_t read();
    void selectDevice(uint8_t deviceAddress);

};

#endif
