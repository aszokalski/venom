cmake_minimum_required(VERSION 3.5...3.26)

set(FORMATS AU VST3 Standalone)
set(PLUGIN_NAME "VenomPlugin")
set(PLUGIN_VERSION "0.1.0")
set(PLUGIN_AUTHOR "Veno")

project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})

find_package(Python COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")

add_subdirectory(extern/juce)
add_subdirectory(extern/pybind11)

juce_add_plugin(VenomPlugin
        PLUGIN_MANUFACTURER_CODE Veno
        PLUGIN_CODE Veno
        FORMATS ${FORMATS}
        PRODUCT_NAME ${PROJECT_NAME})

juce_generate_juce_header(VenomPlugin)

target_link_libraries(VenomPlugin
        PRIVATE
        pybind11::embed
        juce::juce_audio_utils
        juce::juce_dsp
#        TODO: APPEND LIBRARIES THAT WE PORTED
        ${Python_LIBRARIES}
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)


target_sources(VenomPlugin
        PRIVATE
        create_plugin.cpp
        PyAudioProcessor.h
)

target_compile_definitions(VenomPlugin
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)


target_link_libraries(VenomPlugin
        PRIVATE
        pybind11::embed
        juce::juce_audio_utils
        juce::juce_dsp
        ${Python_LIBRARIES}
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
