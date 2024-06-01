cmake_minimum_required(VERSION 3.5...3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(venom VERSION 0.1.0)
find_package(Python REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
include_directories(${Python_INCLUDE_DIRS})
link_directories(${Python_LIBRARY_DIRS})
set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")


# DEPENDENCIES
add_subdirectory(extern)

# Set properties for external libraries
set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")
file(MAKE_DIRECTORY ${MODULES_DIR})

# Add subdirectories for other parts of the project
add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)

add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)
