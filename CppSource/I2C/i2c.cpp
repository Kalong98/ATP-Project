#include "i2c.hpp"
#include <iostream>
#include <thread>
#include <chrono>

I2CSimulation::I2CSimulation(LM75 lm75, SHT35 sht35):
lm75 (lm75),
sht35 (sht35),
dataRegister(0),
currentDevice(0),
lm75TempRaw(0),
sht35TempRaw(0),
sht35HumidRaw(0),
lm75Data(128, 0),
sht35Data(128, 0),
lm75VectorSize(0),
sht35VectorSize(0)
{}

void I2CSimulation::write(uint8_t registerAddress, uint8_t value) {
    if (currentDevice == LM75_ADRESS) {
        if (registerAddress == LM75_TEMP_REGISTER) {
            lm75TempRaw = lm75.readTemperature();
        }
    }
    else if (currentDevice == SHT35_ADRESS) {
        if (registerAddress == SHT35_ADRESS) {
            if (value == SHT35_MEASURE_TEMP_COMMANDO){
                sht35TempRaw = sht35.readTemperature();
            }
            if (value == SHT35_MEASURE_HUMID_COMMANDO){
                sht35HumidRaw = sht35.readHumidity();
            }
        }
    }
    else{
        // nothing
    }
}

void I2CSimulation::request(uint8_t numBytes) {
    if (currentDevice == LM75_ADRESS) {
        if (numBytes == 2) {
            uint8_t tempMSB = (lm75TempRaw >> 8) & 0xFF;
            uint8_t tempLSB = lm75TempRaw & 0xFF;
            lm75Data[lm75VectorSize] = tempMSB;
            lm75VectorSize += 1;
            lm75Data[lm75VectorSize] = tempLSB;
            lm75VectorSize += 1;
        }
    }
    else if (currentDevice == SHT35_ADRESS) {
        if (numBytes == 6) {
            uint8_t tempMSB = (sht35TempRaw >> 8) & 0xFF;
            uint8_t tempLSB = sht35TempRaw & 0xFF;
            uint8_t humidMSB = (sht35HumidRaw >> 8) & 0xFF;
            uint8_t humidLSB = sht35HumidRaw & 0xFF;
            uint8_t checksum = 0x12;
            sht35Data[sht35VectorSize] = tempMSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = tempLSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = checksum;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = humidMSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = humidMSB;
            sht35VectorSize += 1;
            sht35Data[sht35VectorSize] = checksum;
            sht35VectorSize += 1;
        }
    }
}

uint8_t I2CSimulation::read() {
    uint8_t res = 0x00;
    if (currentDevice == LM75_ADRESS) {
        if (lm75VectorSize == 1){
            lm75VectorSize -= 1;
            return lm75Data[0];
        }
        else {
            res = lm75Data[0];
            for (unsigned int i = 0; i < lm75VectorSize - 1; i++){
                lm75Data[i] = lm75Data[i + 1];
            }
            lm75VectorSize -= 1;
            return res;
        }
    }
    else if (currentDevice == SHT35_ADRESS) {
        if (sht35VectorSize == 1){
            sht35VectorSize -= 1;
            return sht35Data[0];
        }
        else {
            res = sht35Data[0];
            for (unsigned int i = 0; i < sht35VectorSize - 1; i++){
                sht35Data[i] = sht35Data[i + 1];
            }
            sht35VectorSize -= 1;
            return res;
        }
    }
    return 0;
}

void I2CSimulation::selectDevice(uint8_t deviceAddress) {
    currentDevice = deviceAddress;
}

// int main()
// {   
//     double initial_inside_temperature = 25.0;
//     double initial_inside_humidity = 20.0;
//     double initial_outside_temperature = 15.0;
//     double initial_outside_humidity = 60.0;
//     int simulation_duration = 5;

//     GreenhouseSimulator simulator(
//         initial_inside_temperature,
//         initial_inside_humidity,
//         initial_outside_temperature,
//         initial_outside_humidity
//     );
//     LM75 lm75(simulator);
//     SHT35 sht35(simulator);
//     I2CSimulation i2c(lm75, sht35);
//     auto [s1, s2] = simulator.generateControls(basic_temperature_control, basic_humidity_control);

//     for (int i = 0; i < simulation_duration; i++) {
//         std::cout << "loop:" << i << "\n";
//         i2c.selectDevice(0x48);
//         i2c.write(0x00, 0);
//         i2c.request(2);
//         uint8_t tempMSB = i2c.read();
//         uint8_t tempLSB = i2c.read();
//         i2c.selectDevice(0x44);
//         i2c.write(0x44, 0x24);
//         i2c.write(0x44, 0x26);
//         i2c.request(6);
//         uint8_t data[6] = {0};
//         for (unsigned int i = 0; i < 6; i++){
//             uint8_t value = 0x00;
//             value = i2c.read();
//             data[i] = value;
//         }
//         // int temperature = (i2c.read() << 8) | i2c.read();
//         std::cout << "LM75 temp: " << static_cast<int>(tempMSB) << "," << static_cast<int>(tempLSB) << "\n";
//         std::cout << "SHT35 temp: " << static_cast<int>(data[0]) << "," << static_cast<int>(data[1]) << "\n";
//         std::cout << "SHT35 Humid: " << static_cast<int>(data[3]) << "," << static_cast<int>(data[4]) << "\n";
//         std::cout << s1() << "\n";
//         std::cout << s2() << "\n";
//         std::cout << "\n";
//     }

//     return 0;
// }