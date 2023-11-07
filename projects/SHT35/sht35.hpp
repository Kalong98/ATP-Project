#ifndef SHT35_HPP
#define SHT35_HPP

#include <cstdint>
#include <random>
#include "../simulator/simulator.hpp"

class SHT35 { // 0x44
private:
    GreenhouseSimulator & greenhouse;

public:
    SHT35(GreenhouseSimulator &simulator);
    uint16_t readTemperature();
    uint16_t readHumidity();
};

#endif // SHT35_HPP
