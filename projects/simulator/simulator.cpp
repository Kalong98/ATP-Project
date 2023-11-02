#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <string>

class GreenhouseSimulator {
private:
    double current_temperature;
    double outside_temperature;
    double current_humidity;
    double outside_humidity;
public:
    GreenhouseSimulator(double initial_temperature, double initial_humidity, double outside_temperature, double outside_humidity): 
    current_temperature(initial_temperature), 
    outside_temperature(outside_temperature), 
    current_humidity(initial_humidity), 
    outside_humidity(outside_humidity)
    {}

    std::tuple<std::string, std::string> generateControls(
        std::function<double(double, double)> temperatureControlCallback,
        std::function<double(double, double)> humidityControlCallback) {
        auto simulateTemperature = [this, temperatureControlCallback]() {
            // Simulate time passing
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            // Adjust temperature based on control
            double adjustment = temperatureControlCallback(current_temperature, outside_temperature);
            current_temperature += adjustment;
            // Print simulation status
            std::string s1 = "Inside Temperature: " + std::to_string(current_temperature) + "°C (Outside: " + std::to_string(outside_temperature) + "°C)";
            return s1;
        };

        auto simulateHumidity = [this, humidityControlCallback]() {
            // Simulate time passing
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            // Adjust humidity based on control
            double adjustment = humidityControlCallback(current_humidity, outside_humidity);
            current_humidity += adjustment;
            // Print simulation status
            std::string s2 = "Inside Humidity: " + std::to_string(current_humidity) + "% (Outside: " + std::to_string(outside_humidity) + "%)";
            return s2;
        };

        return std::make_tuple(simulateTemperature(), simulateHumidity());
    }
};

double basic_temperature_control(double inside_temperature, double outside_temperature) {
    // Basic controls adjust temperature and humidity based on differences
    double temperature_difference = outside_temperature - inside_temperature;
    double temperature_adjustment = temperature_difference * 0.01;  // Adjust factor

    return temperature_adjustment;
}

double basic_humidity_control(double inside_humidity, double outside_humidity) {
    // Basic controls adjust humidity based on differences
    double humidity_difference = outside_humidity - inside_humidity;
    double humidity_adjustment = humidity_difference * 0.01;  // Adjust factor

    return humidity_adjustment;
}

int main() {
    double initial_inside_temperature = 20.0;
    double initial_inside_humidity = 50.0;
    double initial_outside_temperature = 15.0;
    double initial_outside_humidity = 60.0;
    int simulation_duration = 60;

    GreenhouseSimulator simulator(
        initial_inside_temperature,
        initial_inside_humidity,
        initial_outside_temperature,
        initial_outside_humidity
    );

    for (int i = 0; i < simulation_duration; ++i) {
        auto [s1, s2] = simulator.generateControls(basic_temperature_control, basic_humidity_control);
        std::cout << s1 << std::endl;
        std::cout << s2 << std::endl;
    }

    return 0;
}

