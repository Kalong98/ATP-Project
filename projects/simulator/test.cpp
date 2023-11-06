#include <iostream>
#include <random>
#include <bitset>
#include "../simulator/simulator.hpp"


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> noise(-0.25, 0.25); // Adjust the range as needed

    // Add noise to the temperature within the specified deviation
    double noisyTemperature = 25 + noise(gen);
    
    uint16_t rawData = 0x0000;
    uint8_t tempValue = 0;

int main()
{   
    
}



