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
            for (unsigned int i = 0; i < lm75VectorSize - 1; i++){
            lm75Data[i] = lm75Data[lm75VectorSize - 1];
            }
            lm75VectorSize -= 1;
            return lm75Data[0];
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

    for (int i = 0; i < simulation_duration; ++i) {
        i2c.selectDevice(0x48);
        i2c.write(0x00, 0);
        i2c.request(2);
        int temperature = (i2c.read() << 8) | i2c.read();
        std::cout << temperature << std::endl;
        std::cout << s1 << std::endl;
        std::cout << s2 << std::endl;
    }

    return 0;
}
