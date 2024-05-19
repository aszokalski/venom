cmake_minimum_required(VERSION 3.5...3.26)
#set(Python3_ROOT_DIR "/home/mszawerd/venom/venom/venv")
#find_package(Python3 REQUIRED COMPONENTS Interpreter Development  )
#set(Python_EXECUTABLE "/home/mszawerd/venom/venom/venv/bin/python3.11")

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
#        ${Python_LIBRARIES}
#        ${Python3_LIBRARIES}
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
        PLUGIN_FILE="${CMAKE_CURRENT_SOURCE_DIR}/plugin.py"
)

#set(PYTHON_VENV_PATH "/home/mszawerd/venom/venom/venv")
#set(PYTHON_EXECUTABLE "/home/mszawerd/venom/venom/venv/bin/python3.11")
#set(Python_EXECUTABLE "/home/mszawerd/venom/venom/venv/bin/python3.11")
#set(PYTHON_INCLUDE_DIR "/home/mszawerd/venom/venom/venv/include/python3.11")

## Add environment variables to the executable
#add_custom_command(TARGET ${PLUGIN_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E env
#        PYTHONHOME=${PYTHON_VENV_PATH}
#        PYTHONPATH=${PYTHON_VENV_PATH}/lib/python3.11/site-packages
#        LD_LIBRARY_PATH=${PYTHON_VENV_PATH}/lib
#        $<TARGET_FILE:${PLUGIN_NAME}>
#)
#
#set(PYTHON_VENV_PATH ${CMAKE_SOURCE_DIR}/myenv)

# Set environment variables for the build process
#add_custom_target(SetPythonEnv ALL
#        COMMAND ${CMAKE_COMMAND} -E env
#        PYTHONHOME=${PYTHON_VENV_PATH}
#        PYTHONPATH=${PYTHON_VENV_PATH}/lib/python3.11/site-packages
#        LD_LIBRARY_PATH=${PYTHON_VENV_PATH}/lib
#        ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#)
#
## Ensure the custom target is built before your plugin
#add_dependencies(TestPlugin_VST3 SetPythonEnv)

