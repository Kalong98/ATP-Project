#include <iostream>
#include <random>
#include <bitset>

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> noise(-0.25, 0.25); // Adjust the range as needed

    // Add noise to the temperature within the specified deviation
    double noisyTemperature = 25 + noise(gen);
    
    uint16_t rawData = 0x0000;
    uint8_t tempValue = 0;

int main()
{   
    std::cout << noisyTemperature << "\n";
    if (noisyTemperature == 0.0) {
        tempValue = 0;
    } 
    else if (noisyTemperature > 0.0) {
        if (noisyTemperature >= 125.0) {
            rawData = 250 << 7;
        } else {
            tempValue = noisyTemperature / 0.5;
            rawData = tempValue << 7;
        }
    } 
    else {
        if (noisyTemperature <= -55.0) {
            rawData = 1 << 15;
            rawData = rawData | 146 << 7;;
        } else {
            tempValue = 256 + (noisyTemperature / 0.5);
            rawData = 1 << 15;
            rawData = rawData | tempValue << 7;;

        }
    }

    std::cout << rawData << "\n";
}



