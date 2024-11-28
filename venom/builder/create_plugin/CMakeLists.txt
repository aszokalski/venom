cmake_minimum_required(VERSION 3.5...3.26)
project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})

set(VENV_PATH "${PROJECT_SOURCE_DIR}/venv")
set(REQUIREMENTS_FILE "${PROJECT_SOURCE_DIR}/requirements.txt")
option(DEFAULT_LOG_LEVEL "Set default log level for spdlog (0: trace, 1: debug, 2: info, etc.)" 1)

# DEPENDENCIES
add_subdirectory(extern)

# Set properties for external libraries
set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")
file(MAKE_DIRECTORY ${MODULES_DIR})

# Add subdirectories for other parts of the project
add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)

add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)


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
        juce_shared
        juceinit
        VenomModule
        audio_processor
        ui_basics
        spdlog::spdlog
        creation_manager
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
        PLUGIN_FILE_PATH="${PROJECT_SOURCE_DIR}/${ENTRYPOINT}"
        PLUGIN_CLASS_NAME="${PLUGIN_NAME}"
        PYTHON_SHARED_LIB="${PYTHON_SHARED_LIB}"
        PYTHON_SIDE_PACKAGES="${VENV_PATH}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/"
        LOG_LEVEL=${DEFAULT_LOG_LEVEL}
)


add_custom_target(copy_audio_processor ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:audio_processor> ${VENV_PATH}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ui_basics> ${VENV_PATH}/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/
        DEPENDS audio_processor
        DEPENDS ui_basics
        COMMENT "Copying audio_processor library to virtual environment site-packages..."
)

