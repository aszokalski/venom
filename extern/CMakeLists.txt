cmake_minimum_required(VERSION 3.5...3.26)
project(ExternLibraries)

# Add external libraries
add_subdirectory(juce)
add_subdirectory(pybind11)
add_subdirectory(spdlog)

set_target_properties(spdlog PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        )
