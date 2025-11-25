cmake_minimum_required(VERSION 3.5...3.26)
project(ExternLibraries VERSION 0.1.0)
set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JUCE_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
# Add external libraries
add_subdirectory(juce)
add_subdirectory(pybind11)
add_subdirectory(spdlog)

set_target_properties(spdlog PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

function(juce_add_shared_library)
        add_library(temp_target OBJECT)
        set_target_properties(temp_target PROPERTIES POSITION_INDEPENDENT_CODE ON)
        _juce_initialise_target(temp_target)
        target_link_libraries(temp_target
                PRIVATE
                juce::juce_analytics
                juce::juce_audio_basics
                juce::juce_audio_devices
                juce::juce_audio_formats
                juce::juce_audio_processors
                juce::juce_audio_utils
                juce::juce_core
                juce::juce_cryptography
                juce::juce_data_structures
                juce::juce_dsp
                juce::juce_events
                juce::juce_graphics
                juce::juce_gui_basics
                juce::juce_gui_extra
                juce::juce_opengl
                juce::juce_osc
                juce::juce_video
                PUBLIC
                juce::juce_recommended_config_flags
                juce::juce_recommended_warning_flags)

        target_compile_definitions(temp_target
                INTERFACE $<TARGET_PROPERTY:temp_target,COMPILE_DEFINITIONS>
                PRIVATE
                JUCE_WEB_BROWSER=0
                JUCE_USE_CURL=0
        )

        target_include_directories(temp_target
                INTERFACE
                $<TARGET_PROPERTY:temp_target,INCLUDE_DIRECTORIES>)


        add_library(juce_shared SHARED)

        target_link_libraries(juce_shared PUBLIC temp_target)
        _juce_initialise_target(juce_shared)
        target_compile_definitions(juce_shared
                PRIVATE
                JUCE_WEB_BROWSER=0
                JUCE_USE_CURL=0
        )
        set_target_properties(juce_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MODULES_DIR})
endfunction()

juce_add_shared_library()
