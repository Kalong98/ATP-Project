#ifndef GREENHOUSE_SIMULATOR_HPP
#define GREENHOUSE_SIMULATOR_HPP

#include <functional>
#include <string>
#include <tuple>

class GreenhouseSimulator {
private:
    double current_temperature;
    double outside_temperature;
    double current_humidity;
    double outside_humidity;

public:
    GreenhouseSimulator(double initial_temperature, double initial_humidity, double outside_temperature, double outside_humidity);

    std::tuple<std::string, std::string> generateControls(
        std::function<double(double, double)> temperatureControlCallback,
        std::function<double(double, double)> humidityControlCallback);

    double getTemperature();
};

double basic_temperature_control(double inside_temperature, double outside_temperature);

double basic_humidity_control(double inside_humidity, double outside_humidity);

#endif
