import random
import time

class GreenhouseSimulator:
    def __init__(self, initial_temperature, initial_humidity, outside_temperature, outside_humidity):
        self.temperature = initial_temperature
        self.humidity = initial_humidity
        self.outside_temperature = outside_temperature
        self.outside_humidity = outside_humidity

    def simulate(self, control_callback, data):
        # Simulate time passing
        time.sleep(1)
        if data == "temp":
        # Adjust temperature and humidity based on control
            adjustment = control_callback(self.temperature)

        data[0] += adjustment

        # Print simulation status
        # s1 = (f"Inside Temperature: {self.temperature:.2f}°C (Outside: {self.outside_temperature:.2f}°C)")
        s1 = (f"Inside: {self.temperature:.2f} (Outside: {self.outside_temperature:.2f})")
        return s1
    
    def getTemperature(self):
        return (self.temperature, self.outside_temperature)

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

    for i in range(simulation_duration):
        print(simulator.getTemperature())
        s1 = simulator.simulate(basic_temperature_control, simulator.getTemperature())
        print (s1)
