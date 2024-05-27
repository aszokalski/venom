cmake_minimum_required(VERSION 3.5...3.26)
set(FORMATS VST3)
set(PLUGIN_NAME "TestPlugin")
set(PLUGIN_VERSION "2.1.38")
set(PLUGIN_AUTHOR "Test_test")
project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})

set(VENV_PATH "${CMAKE_BINARY_DIR}/tests/vst3/venv")
set(REQUIREMENTS_FILE "${PROJECT_SOURCE_DIR}/requirements.txt")

execute_process(
        COMMAND ${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_config_var('LIBDIR'))"
        OUTPUT_VARIABLE PYTHON_LIB_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND ${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_config_var('LDLIBRARY'))"
        OUTPUT_VARIABLE PYTHON_LIB_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(PYTHON_SHARED_LIB "${PYTHON_LIB_DIR}/${PYTHON_LIB_NAME}")

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
        spdlog::spdlog
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
        VENV_PATH="${VENV_PATH}"
        PLUGIN_FILE="${CMAKE_CURRENT_SOURCE_DIR}/plugin.py"
        PYTHON_SHARED_LIB="${PYTHON_SHARED_LIB}"
        PYTHON_SIDE_PACKAGES="${VENV_PATH}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/"
)

add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)


add_custom_target(copy_audio_processor ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:audio_processor> ${VENV_PATH}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/
        DEPENDS audio_processor
        COMMENT "Copying audio_processor library to virtual environment site-packages..."
)


if(NOT EXISTS "${VENV_PATH}/bin/activate")
    add_custom_target(create_venv ALL
            COMMAND ${Python_EXECUTABLE} -m venv ${VENV_PATH}
            COMMAND ${VENV_PATH}/bin/pip install -r ${REQUIREMENTS_FILE}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Creating virtual environment and installing dependencies..."
    )
    add_dependencies(${PLUGIN_NAME} create_venv copy_audio_processor)
else()
    message(STATUS "Virtual environment already exists at ${VENV_PATH}")
    add_dependencies(${PLUGIN_NAME}  copy_audio_processor)

endif()
