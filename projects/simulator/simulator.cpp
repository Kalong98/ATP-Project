#include "simulator.hpp"
#include <iostream>
#include <random>

GreenhouseSimulator::GreenhouseSimulator(double initial_temperature, double initial_humidity, double outside_temperature, double outside_humidity):
current_temperature(initial_temperature),
outside_temperature(outside_temperature),
current_humidity(initial_humidity),
outside_humidity(outside_humidity)
{}

std::tuple<std::string, std::string> GreenhouseSimulator::generateControls(
    std::function<double(double, double)> temperatureControlCallback,
    std::function<double(double, double)> humidityControlCallback){
    auto simulateTemperature = [this, temperatureControlCallback]() {
        double adjustment = temperatureControlCallback(current_temperature, outside_temperature);
        current_temperature += adjustment;
        std::string s1 = "Inside Temperature: " + std::to_string(current_temperature) + "°C (Outside: " + std::to_string(outside_temperature) + "°C)";
        return s1;
    };
    auto simulateHumidity = [this, humidityControlCallback]() {
        double adjustment = humidityControlCallback(current_humidity, outside_humidity);
        current_humidity += adjustment;
        std::string s2 = "Inside Humidity: " + std::to_string(current_humidity) + "% (Outside: " + std::to_string(outside_humidity) + "%)";
        return s2;
    };

    return std::make_tuple(simulateTemperature(), simulateHumidity());
}

double GreenhouseSimulator::getTemperature(){
    return current_temperature;
}

double GreenhouseSimulator::getHumidity(){
    return current_humidity;
}

double basic_temperature_control(double inside_temperature, double outside_temperature) {
    double temperature_difference = outside_temperature - inside_temperature;
    double temperature_adjustment = temperature_difference * 0.01;
    return temperature_adjustment;
}

double basic_humidity_control(double inside_humidity, double outside_humidity) {
    double humidity_difference = outside_humidity - inside_humidity;
    double humidity_adjustment = humidity_difference * 0.01;
    return humidity_adjustment;
}
