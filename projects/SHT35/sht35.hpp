#ifndef SHT35_HPP
#define SHT35_HPP

#include <cstdint>
#include <random>
#include "../simulator/simulator.hpp"

class SHT35 { // 0x44
private:
    GreenhouseSimulator & greenhouse;
    std::vector<uint8_t> data;

public:
    SHT35(GreenhouseSimulator &simulator);
    uint16_t readTemperature();
    uint16_t readHumidity();
    void updateData();
    std::vector<uint8_t>* getData();
};

#endif // SHT35_HPP
