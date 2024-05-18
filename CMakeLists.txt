cmake_minimum_required(VERSION 3.5...3.26)
project(.. VERSION 0.1.0)
set(Python_EXECUTABLE "C:/msys64/mingw64/bin/python.exe")
set(Python3_EXECUTABLE "C:/msys64/mingw64/bin/python.exe")

find_package(Python COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
message(STATUS "Python_INCLUDE_DIR: ${Python_INCLUDE_DIR}")
message(STATUS "Python_LIBRARY: ${Python_LIBRARY}")
message(STATUS "Python_LIBRARY: ${Python_LINK_OPTIONS}")
add_subdirectory(extern/juce)
add_subdirectory(extern/pybind11)

set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")
file(MAKE_DIRECTORY ${MODULES_DIR})

# juce python bindings
add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)
add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)