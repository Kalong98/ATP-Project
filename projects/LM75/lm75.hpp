#ifndef LM75_HPP
#define LM75_HPP

#include <stdint.h>
#include <random>
#include "simulator\simulator.hpp"

class LM75 {
private:
    uint8_t address; // 0x48
    static const uint8_t LM75_TEMP_REGISTER = 0x00;
    GreenhouseSimulator & greenhouse;

public:
    LM75(uint8_t address, GreenhouseSimulator & simulator);
    uint16_t readTemperature();
};

#endif // LM75_HPP