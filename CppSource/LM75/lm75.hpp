#ifndef LM75_HPP
#define LM75_HPP

#include <stdint.h>
#include <random>
#include "../simulator/simulator.hpp"

class LM75 { // 0x48
private:
    GreenhouseSimulator & greenhouse;

public:
    LM75(GreenhouseSimulator & simulator);
    uint16_t readTemperature();
};

#endif // LM75_HPP