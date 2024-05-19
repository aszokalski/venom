cmake_minimum_required(VERSION 3.5...3.26)
project(.. VERSION 0.1.0)
#set(Python3_ROOT_DIR "/home/mszawerd/venom/venom/venv")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development )
# Define the path to your virtual environment's activation script



message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})
add_subdirectory(extern/juce)
add_subdirectory(extern/pybind11)

set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")
file(MAKE_DIRECTORY ${MODULES_DIR})

# juce python bindings
add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)
add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)