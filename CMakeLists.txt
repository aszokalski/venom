cmake_minimum_required(VERSION 3.5...3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(venom VERSION 0.1.0)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
include_directories(${Python_INCLUDE_DIRS})
link_directories(${Python_LIBRARY_DIRS})
execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_path('purelib'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Python Site Packages: ${PYTHON_SITE_PACKAGES}")

set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")
# set(MODULES_DIR "${PYTHON_SITE_PACKAGES}/venom_modules" CACHE STRING "Directory for shared modules")
file(MAKE_DIRECTORY ${MODULES_DIR})

# DEPENDENCIES
add_subdirectory(extern)

# Set properties for external libraries
set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Add subdirectories for other parts of the project
add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)

add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)

# Logging configuration
option(ENABLE_DEBUG_LOGGING "Enable debug logging" OFF)

if(ENABLE_DEBUG_LOGGING)
    add_compile_definitions(ENABLE_DEBUG_LOGGING=1)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON PARENT_SCOPE)
endif()

if(Python_FOUND)
    add_compile_definitions(
        PYTHON_SHARED_LIB="${Python_LIBRARIES}"
        PYTHON_SIDE_PACKAGES="${Python_SITELIB}"
    )
endif()
