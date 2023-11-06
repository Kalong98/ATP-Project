#include "i2c.hpp"
#include <iostream>
#include <thread>
#include <chrono>

I2CSimulation::I2CSimulation(LM75 lm75, SHT35 sht35):
lm75 (lm75),
sht35 (sht35),
dataRegister(0),
currentDevice(0),
tempRaw(0),
lm75Data(3, 0),
sht35Data(7, 0)
{}

void I2CSimulation::write(uint8_t registerAddress, uint8_t value) {
    if (currentDevice == LM75_ADRESS) {
        if (registerAddress == LM75_TEMP_REGISTER) {
            tempRaw = lm75.readTemperature();
        }
        // Add more conditionals for other device registers as needed
    }
    else if (currentDevice == SHT35_ADRESS){}
    {
        /* code */
    }
    
}

void I2CSimulation::request(uint8_t numBytes) {
    if (currentDevice == LM75_ADRESS) {
        if (numBytes == 2) {
            uint8_t tempMSB = (tempRaw >> 8) & 0xFF;
            uint8_t tempLSB = tempRaw & 0xFF;
            std::cout << "Request: " << static_cast<int>(tempMSB) << "," << static_cast<int>(tempLSB) << "\n";
            lm75Data[0] = tempMSB;
            lm75VectorSize += 1;
            lm75Data[1] = tempLSB;
            lm75VectorSize += 1;
        }
    }
}

uint8_t I2CSimulation::read() {
    if (currentDevice == LM75_ADRESS) {
        if (lm75VectorSize == 1){
            lm75VectorSize -= 1;
            return lm75Data[0];
        }
        else {
            uint8_t res = 0x00;
            for (unsigned int i = 0; i < lm75VectorSize - 1; i++){
                res = lm75Data[i];
                lm75Data[i] = lm75Data[lm75VectorSize - 1];
            }
            lm75VectorSize -= 1;
            return res;
        }
    }
    return 0;
}

void I2CSimulation::selectDevice(uint8_t deviceAddress) {
    currentDevice = deviceAddress;
}

int main()
{   
    double initial_inside_temperature = 25.0;
    double initial_inside_humidity = 50.0;
    double initial_outside_temperature = 15.0;
    double initial_outside_humidity = 60.0;
    int simulation_duration = 2;

    GreenhouseSimulator simulator(
        initial_inside_temperature,
        initial_inside_humidity,
        initial_outside_temperature,
        initial_outside_humidity
    );
    LM75 lm75(simulator);
    SHT35 sht35(simulator);
    I2CSimulation i2c(lm75, sht35);
    auto [s1, s2] = simulator.generateControls(basic_temperature_control, basic_humidity_control);

    for (int i = 0; i < simulation_duration; i++) {
        std::cout << "loop:" << i << "\n";
        i2c.selectDevice(0x48);
        i2c.write(0x00, 0);
        i2c.request(2);
        uint8_t tempMSB = i2c.read();
        uint8_t tempLSB = i2c.read();
        // int temperature = (i2c.read() << 8) | i2c.read();
        std::cout << "Loop: " << static_cast<int>(tempMSB) << "," << static_cast<int>(tempLSB) << "\n";
        std::cout << s1() << "\n";
        std::cout << s2() << "\n";
        std::cout << "\n";
    }

    return 0;
}
