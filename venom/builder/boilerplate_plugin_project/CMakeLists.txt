cmake_minimum_required(VERSION 3.5...3.26)

set(FORMATS AU VST3 Standalone)
set(PLUGIN_NAME "VenomPlugin")
set(PLUGIN_VERSION "0.1.0")
set(PLUGIN_AUTHOR "Veno")
set(SITE_PACKAGES_DIRS "../../../venv/lib/python3.11/site-packages" )

project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})

#find_package(Python COMPONENTS Interpreter Development REQUIRED)
#ex

add_subdirectory(external/juce)
add_subdirectory(external/pybind11)

juce_add_plugin(VenomPlugin
        PLUGIN_MANUFACTURER_CODE Veno
        PLUGIN_CODE Veno
        FORMATS ${FORMATS}
        PRODUCT_NAME ${PROJECT_NAME})

juce_generate_juce_header(VenomPlugin)

pybind11_find_import(PyAudioProcessor REQUIRED)
pybind11_find_import(venom REQUIRED)

target_link_libraries(VenomPlugin
        PRIVATE
        pybind11::embed
        juce::juce_audio_utils
        juce::juce_dsp
#        TODO: APPEND LIBRARIES THAT WE PORTED
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)


target_sources(VenomPlugin
        PRIVATE
        create_plugin.cpp
        PyAudioProcessor.h
        PyAudioProcessorEditor.h
)

target_compile_definitions(VenomPlugin
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

foreach(format ${FORMATS})
    foreach (dir ${SITE_PACKAGES_DIRS})
        juce_add_bundle_resources_directory("VenomPlugin_${format}" ${dir})
    endforeach ()
endforeach()