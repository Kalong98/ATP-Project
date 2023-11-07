from setuptools import setup, Extension

extension_mod = Extension(
    "greenhouse",  # Your module name
    sources = [
    "CppSource/I2C/i2c.cpp",
    "CppSource/LM75/lm75.cpp",
    "CppSource/SHT35/sht35.cpp",
    "CppSource/simulator/simulator.cpp",
    "PythonBindings/binding.cpp"
    ],  # List of source files
    include_dirs=["../CppSource", "pybind11/include"],  # Include directories for C++ headers
)

setup(
    name="greenhouse",  # Your package name
    ext_modules=[extension_mod],
)