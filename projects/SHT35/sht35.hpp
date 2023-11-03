#ifndef SHT35_HPP
#define SHT35_HPP

#include <cstdint>
#include <random>
#include "simulator\simulator.hpp"

class SHT35 {
private:
    uint8_t address; // 0x44
    GreenhouseSimulator & greenhouse;
    std::vector<uint8_t> data;
    uint8_t data[6] = {0};

public:
    SHT35(uint8_t address, GreenhouseSimulator &simulator);
    uint16_t readTemperature();
    uint16_t readHumidity();
    void updateData();
    const uint8_t* getData();
};

#endif // SHT35_HPP
