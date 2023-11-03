#ifndef SHT35_HPP
#define SHT35_HPP

#include <cstdint>
#include <random>
#include "simulator\simulator.hpp"

class SHT35 {
private:
    uint8_t address; // 0x44
    GreenhouseSimulator & greenhouse;

public:
    SHT35(uint8_t address, GreenhouseSimulator &simulator);
    uint16_t readTemperature();
    uint16_t readHumidity();
};

#endif // SHT35_HPP
