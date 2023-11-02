// #include <Wire.h>
#include <stdint.h>
#include "..\simulator/simulator.hpp"


class LM75 {
private:
    uint8_t address; //0x48
    static const uint8_t LM75_TEMP_REGISTER = 0x00;
    GreenhouseSimulator & greenhouse;

public:
    LM75(uint8_t address, GreenhouseSimulator & simulator):
    address(address),
    greenhouse(simulator)
    {}

    // void begin() {
    //     Wire.begin();
    // }

    double readTemperature() {
        Wire.beginTransmission(address);
        Wire.write(LM75_TEMP_REGISTER);
        Wire.endTransmission();

        Wire.requestFrom(address, 2);
        if (Wire.available() >= 2) {
        int raw_temperature = Wire.read() << 8 | Wire.read();
        return (double(raw_temperature >> 7) * 0.5);
        }
        return -1.0; // Error reading temperature
    }


};

LM75 lm75(0x48); // LM75 I2C address

void setup() {
  Serial.begin(9600);
  lm75.begin();
}

void loop() {
  double temperature = lm75.readTemperature();
  
  if (temperature >= 0.0) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  } else {
    Serial.println("Error reading temperature.");
  }

  delay(1000); // Adjust the sampling interval as needed
}
