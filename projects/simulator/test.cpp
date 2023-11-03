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
    uint8_t data[6] = {0};
	uint16_t tempData = 6400;
	uint16_t humData = 26214;
	
	uint8_t tempMSB = (tempData >> 8) & 0xFF; // Shift right by 8 and then mask with 0xFF
    uint8_t tempLSB = tempData & 0xFF;        // Mask directly with 0xFF
    uint8_t humMSB = (humData >> 8) & 0xFF;   // Shift right by 8 and then mask with 0xFF
    uint8_t humLSB = humData & 0xFF;  

    std::cout << static_cast<int>(tempMSB) << "," << static_cast<int>(tempLSB) << "\n";
    std::cout << static_cast<int>(humMSB) << "," << static_cast<int>(humLSB) << "\n";

}



