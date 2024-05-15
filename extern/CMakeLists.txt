cmake_minimum_required(VERSION 3.5...3.26)
project(JUCEModules)

# Include JUCE using the add_subdirectory, assuming JUCE source is located appropriately
add_subdirectory(juce)  # Adjust the path as necessary to the actual JUCE source location

# Define the JUCE modules library
add_library(JUCE_Modules STATIC)

# Link required JUCE modules to this library
target_link_libraries(JUCE_Modules
        PUBLIC
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        )

# Set the output directory for the static library
set_target_properties(JUCE_Modules PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/juce"
        )

message(STATUS "JUCE_Lib compiled successfully")
