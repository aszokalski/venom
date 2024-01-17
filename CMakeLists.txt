cmake_minimum_required(VERSION 3.5...3.26)
project(.. VERSION 0.1.0)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")

add_subdirectory(extern/juce)
add_subdirectory(extern/pybind11)

# juce python bindings
add_subdirectory(venom/juce)