import greenhouse
import time
from PySource.DR966_Heater import DR966
from PySource.TPI_CE30B_Fan import TPI_CE30B

# initiation of values and objects
initial_inside_temperature = 25.0
initial_inside_humidity = 20.0
initial_outside_temperature = 15.0
initial_outside_humidity = 60.0
heater_threshold = 22.0
fan_threshold = 50.0
simulation_duration = 5
simulator = greenhouse.GreenhouseSimulator(
    initial_inside_temperature,
    initial_inside_humidity,
    initial_outside_temperature,
    initial_outside_humidity
)
lm75 = greenhouse.LM75(simulator)
sht35 = greenhouse.SHT35(simulator)
i2c = greenhouse.I2CSimulation(lm75, sht35)
s1, s2 = simulator.generateControls(greenhouse.basic_temperature_control, greenhouse.basic_humidity_control)
heater = DR966()
fan = TPI_CE30B()

def calculateTempCel_SHT35 (rawData):
    return (-45 + 175 * (rawData / 65535))

def calculateHumid_SHT35 (rawData):
    return (100 * (rawData / 65535))

for i in range(simulation_duration):
    print(f'loop: {i}')
    
    i2c.selectDevice(0x48)
    i2c.write(0x00, 0x00)
    i2c.request(2)
    tempMSB = i2c.read()
    tempLSB = i2c.read()
    i2c.selectDevice(0x44)
    i2c.write(0x44, 0x24)
    i2c.write(0x44, 0x26)
    i2c.request(6)
    data = [0] * 6
    for i in range(6):
        value = 0x00
        value = i2c.read()
        data[i] = value
    tempRaw = (data[0] << 8) | data[1]
    HumidRaw = (data[3] << 8) | data[4]
    temperature = calculateTempCel_SHT35(tempRaw)
    humidity = calculateHumid_SHT35(HumidRaw)
    print(f"SHT35 temp: {temperature}")
    print(f"SHT35 Humid: {humidity}")
    if temperature < heater_threshold:
        heater.turnOn()
    else:
        heater.turnOff()
    if humidity > fan_threshold:
        fan.turnOn()
    else:
        fan.turnOff()
    if heater.getStatus:
        simulator.adjustTemp(0.7)
    if fan.getStatus:
        simulator.adjustHumid(0.7)
    print(s1()) #update and print env temp
    print(s2()) #update and print env humid
    print()

