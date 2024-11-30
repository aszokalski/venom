cmake_minimum_required(VERSION 3.5...3.26)
project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})

find_package(Python REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")


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

execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import sys; print(sys.prefix)"
    OUTPUT_VARIABLE VENV_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_path('purelib'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Virtual Environment Path: ${VENV_PATH}")
message(STATUS "Python Site Packages: ${PYTHON_SITE_PACKAGES}")
message(STATUS "Python Shared Library: ${PYTHON_SHARED_LIB}")

set(REQUIREMENTS_FILE "${PROJECT_SOURCE_DIR}/requirements.txt")
set(EXT_LIB_DIR "${PYTHON_SITE_PACKAGES}/venom_extern/extern" CACHE STRING "Directory for external libraries")
set(MODULES_DIR "${PYTHON_SITE_PACKAGES}/venom_modules" CACHE STRING "Directory for shared modules")
option(DEFAULT_LOG_LEVEL "Set default log level for spdlog (0: trace, 1: debug, 2: info, etc.)" 1)


add_subdirectory(
  ${EXT_LIB_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/extern
)


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
        PYTHON_SIDE_PACKAGES="${PYTHON_SITE_PACKAGES}"
        LOG_LEVEL=${DEFAULT_LOG_LEVEL}
)


add_custom_target(copy_audio_processor ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:audio_processor> ${PYTHON_SITE_PACKAGES}/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ui_basics> ${PYTHON_SITE_PACKAGES}/
        DEPENDS audio_processor
        DEPENDS ui_basics
        COMMENT "Copying audio_processor library to virtual environment site-packages..."
)

add_dependencies(${PLUGIN_NAME} copy_audio_processor)

