import greenhouse
import ctypes

# Create instances of your C++ classes
initial_inside_temperature = 25.0
initial_inside_humidity = 20.0
initial_outside_temperature = 15.0
initial_outside_humidity = 60.0
simulation_duration = 60
simulator = greenhouse.GreenhouseSimulator(
    initial_inside_temperature,
    initial_inside_humidity,
    initial_outside_temperature,
    initial_outside_humidity
)
lm75 = greenhouse.LM75(simulator)
sht35 = greenhouse.SHT35(simulator)
i2c = greenhouse.I2CSimulation(lm75, sht35)
# s1, s2 = simulator.generateControls(simulator.basic_temperature_control, simulator.basic_humidity_control)

# s1, s2 = simulator.generateControls(simulator.basic_temperature_control, simulator.basic_humidity_control)
# s1, s2 = simulator.generateControls(simulator.basic_temperature_control, simulator.basic_humidity_control)


for i in range(1 , 60):
    print(f'loop: {i}')
    i2c.selectDevice(0x48)
    i2c.write(0x00, 0)
    i2c.request(2)
    tempMSB = i2c.read()
    tempLSB = i2c.read()
    i2c.selectDevice(0x44)
    i2c.write(0x44, 0x24)
    i2c.write(0x44, 0x26)
    i2c.request(6)
    data = [0] * 6
    for i in range(6):
        value = 0
        value = i2c.read()
        data[i] = value
    
    print(f"LM75 temp: {int(tempMSB)},{int(tempLSB)}")
    print(f"SHT35 temp: {int(data[0])},{int(data[1])}")
    print(f"SHT35 Humid: {int(data[3])},{int(data[4])}")
    # print(s1())
    # print(s2())
    print()