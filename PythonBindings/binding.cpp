#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include "../CppSource/I2C/i2c.hpp"  // Include your C++ class headers
#include "../CppSource/LM75/lm75.hpp"
#include "../CppSource/SHT35/sht35.hpp"
#include "../CppSource/simulator/simulator.hpp"

namespace py = pybind11;

PYBIND11_MODULE(greenhouse, m) {
    m.doc() = "Your Python bindings for the C++ library";
    
    py::class_<I2CSimulation>(m, "I2CSimulation")
        .def(py::init<LM75, SHT35>())
        .def("write", &I2CSimulation::write)
        .def("request", &I2CSimulation::request)
        .def("read", &I2CSimulation::read)
        .def("selectDevice", &I2CSimulation::selectDevice);

    py::class_<LM75>(m, "LM75")
        .def(py::init<GreenhouseSimulator>())
        .def("readTemperature", &LM75::readTemperature);

    py::class_<SHT35>(m, "SHT35")
        .def(py::init<GreenhouseSimulator>())
        .def("readTemperature", &SHT35::readTemperature)
        .def("readHumidity", &SHT35::readHumidity);

    py::class_<GreenhouseSimulator>(m, "GreenhouseSimulator")
        .def(py::init<double, double, double, double>())
        .def("generateControls", &GreenhouseSimulator::generateControls)
        .def("getTemperature", &GreenhouseSimulator::getTemperature)
        .def("getHumidity", &GreenhouseSimulator::getHumidity)
        .def("adjustTemp", &GreenhouseSimulator::adjustTemp)
        .def("adjustHumid", &GreenhouseSimulator::adjustHumid);

    m.def("basic_temperature_control", &basic_temperature_control);
    m.def("basic_humidity_control", &basic_humidity_control);
}