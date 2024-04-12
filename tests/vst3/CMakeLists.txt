cmake_minimum_required(VERSION 3.5...3.26)

set(FORMATS VST3)
set(PLUGIN_NAME "TestPlugin")
set(PLUGIN_VERSION "2.1.38")
set(PLUGIN_AUTHOR "Test_test")

project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})


juce_add_plugin(${PLUGIN_NAME}
        PLUGIN_MANUFACTURER_CODE Veno
        COMPANY_NAME ${PLUGIN_AUTHOR}
        PLUGIN_CODE Veno
        FORMATS ${FORMATS}
        PRODUCT_NAME ${PROJECT_NAME})

target_link_libraries(${PLUGIN_NAME}
        PRIVATE
        pybind11::embed
        juce::juce_gui_basics
        VenomModule
        audio_processor
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)


target_sources(${PLUGIN_NAME}
        PRIVATE
        create_plugin.cpp
)

target_compile_definitions(${PLUGIN_NAME}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        MODULES_DIR="${MODULES_DIR}"
        PYTHON_STUBS_FILE="${CMAKE_CURRENT_SOURCE_DIR}/plugin.py"
)

foreach(format ${FORMATS})
    foreach (dir ${SITE_PACKAGES_DIRS})
        juce_add_bundle_resources_directory("VenomPlugin_${format}" ${dir})
    endforeach ()
endforeach()