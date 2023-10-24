import random
import time

class GreenhouseSimulator:
    def __init__(self, initial_temperature, initial_humidity, outside_temperature, outside_humidity):
        self.current_temperature = initial_temperature
        self.outside_temperature = outside_temperature
        self.current_humidity = initial_humidity
        self.outside_humidity = outside_humidity

    def generateControls(self, temperatureControlCallback, humidityControlCallback):
        def simulateTemperature():
            # Simulate time passing
            time.sleep(1)
            # Adjust temperature and humidity based on control
            adjustment = temperatureControlCallback(self.current_temperature, self.outside_temperature)
            self.current_temperature += adjustment
            # Print simulation status
            s1 = (f"Inside Temperature: {self.current_temperature:.2f}°C (Outside: {self.outside_temperature:.2f}°C)")
            return s1
        def simulateHumidity():
            # Simulate time passing
            time.sleep(1)
            # Adjust temperature and humidity based on control
            adjustment = humidityControlCallback(self.current_humidity, self.outside_humidity)
            self.current_humidity += adjustment
            # Print simulation status
            s1 = (f"Inside Humidity: {self.current_humidity:.2f}% (Outside: {self.outside_humidity:.2f}%)")
            return s1
        return simulateTemperature, simulateHumidity

def basic_temperature_control(inside_temperature, outside_temperature):
    # Basic controls adjust temperature and humidity based on differences
    temperature_difference = outside_temperature - inside_temperature
    temperature_adjustment = temperature_difference * 0.01  # Adjust factor

    return temperature_adjustment

def basic_humidity_control(inside_humidity, outside_humidity):
    # Basic controls adjust humidity based on differences
    humidity_difference = outside_humidity - inside_humidity
    humidity_adjustment = humidity_difference * 0.01  # Adjust factor

    return humidity_adjustment

if __name__ == "__main__":
    initial_inside_temperature = 20.0
    initial_inside_humidity = 50.0
    initial_outside_temperature = 15.0
    initial_outside_humidity = 60.0
    simulation_duration = 60

    simulator = GreenhouseSimulator(
        initial_inside_temperature,
        initial_inside_humidity,
        initial_outside_temperature,
        initial_outside_humidity,
    )

    tempSim, humidSim = simulator.generateControls(basic_temperature_control, basic_humidity_control)
    for i in range(simulation_duration):
        s1 = tempSim()
        s2 = humidSim()
        print (s1)
        print (s2)
