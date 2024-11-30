cmake_minimum_required(VERSION 3.5...3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(venom VERSION 0.1.0)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_path('purelib'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Python Site Packages: ${PYTHON_SITE_PACKAGES}")

include_directories(${Python_INCLUDE_DIRS})
link_directories(${Python_LIBRARY_DIRS})
set(MODULES_DIR "${PYTHON_SITE_PACKAGES}/venom_modules" CACHE STRING "Directory for shared modules")
file(MAKE_DIRECTORY ${MODULES_DIR})
message(STATUS "Modules Directory: ${MODULES_DIR}")

set(EXT_LIB_DIR "${PYTHON_SITE_PACKAGES}/venom_extern" CACHE STRING "Directory for external libraries")
file(MAKE_DIRECTORY ${EXT_LIB_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extern DESTINATION ${EXT_LIB_DIR})
message(STATUS "External Libraries Directory: ${EXT_LIB_DIR}")

# DEPENDENCIES
add_subdirectory(
  ${EXT_LIB_DIR}/extern
  ${MODULES_DIR}
)


# Set properties for external libraries
set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)


# Add subdirectories for other parts of the project
add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)

add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)
