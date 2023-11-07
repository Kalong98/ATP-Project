#ifndef GREENHOUSE_SIMULATOR_HPP
#define GREENHOUSE_SIMULATOR_HPP

#include <functional>
#include <string>
#include <tuple>

class GreenhouseSimulator {
private:
    float current_temperature;
    float outside_temperature;
    float current_humidity;
    float outside_humidity;

public:
    GreenhouseSimulator(float initial_temperature, float initial_humidity, float outside_temperature, float outside_humidity);

    std::tuple<std::function<std::string()>, std::function<std::string()>> generateControls(
        std::function<float(float, float)> temperatureControlCallback,
        std::function<float(float, float)> humidityControlCallback);
    float getTemperature();
    float getHumidity();
};

float basic_temperature_control(float inside_temperature, float outside_temperature);
float basic_humidity_control(float inside_humidity, float outside_humidity);
#endif //GREENHOUSE_SIMULATOR_HPP
