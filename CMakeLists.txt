cmake_minimum_required(VERSION 3.5...3.26)
project(.. VERSION 0.1.0)
find_package(Python REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
include_directories(${Python_INCLUDE_DIRS})
link_directories(${Python_LIBRARY_DIRS})

# DEPENDENCIES
add_subdirectory(extern/juce)
add_subdirectory(extern/pybind11)
add_subdirectory(extern/spdlog)

set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)


set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")
file(MAKE_DIRECTORY ${MODULES_DIR})

add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)

add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)