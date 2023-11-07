#include "simulator.hpp"
#include <iostream>
#include <random>

GreenhouseSimulator::GreenhouseSimulator(float initial_temperature, float initial_humidity, float outside_temperature, float outside_humidity):
current_temperature(initial_temperature),
outside_temperature(outside_temperature),
current_humidity(initial_humidity),
outside_humidity(outside_humidity)
{}

std::tuple<std::function<std::string()>, std::function<std::string()>> GreenhouseSimulator::generateControls(
    std::function<float(float, float)> temperatureControlCallback,
    std::function<float(float, float)> humidityControlCallback){
    auto simulateTemperature = [this, temperatureControlCallback]() {
        float adjustment = temperatureControlCallback(current_temperature, outside_temperature);
        current_temperature += adjustment;
        std::string s1 = "Inside Temperature: " + std::to_string(current_temperature) + "°C (Outside: " + std::to_string(outside_temperature) + "°C)";
        return s1;
    };
    auto simulateHumidity = [this, humidityControlCallback]() {
        float adjustment = humidityControlCallback(current_humidity, outside_humidity);
        current_humidity += adjustment;
        std::string s2 = "Inside Humidity: " + std::to_string(current_humidity) + "% (Outside: " + std::to_string(outside_humidity) + "%)";
        return s2;
    };

    return std::make_tuple(simulateTemperature, simulateHumidity);
}

float GreenhouseSimulator::getTemperature(){
    return current_temperature;
}

float GreenhouseSimulator::getHumidity(){
    return current_humidity;
}

float basic_temperature_control(float inside_temperature, float outside_temperature) {
    float temperature_difference = outside_temperature - inside_temperature;
    float temperature_adjustment = temperature_difference * float(0.01);
    return temperature_adjustment;
}

float basic_humidity_control(float inside_humidity, float outside_humidity) {
    float humidity_difference = outside_humidity - inside_humidity;
    float humidity_adjustment = humidity_difference * float(0.01);
    return humidity_adjustment;
}
