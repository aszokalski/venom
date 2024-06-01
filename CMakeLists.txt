cmake_minimum_required(VERSION 3.5...3.26)
project(.. VERSION 0.1.0)
find_package(Python REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
include_directories(${Python_INCLUDE_DIRS})
link_directories(${Python_LIBRARY_DIRS})
set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JUCE_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(MODULES_DIR "${CMAKE_BINARY_DIR}/bindings_modules" CACHE STRING "Directory for shared modules")

# DEPENDENCIES
add_subdirectory(extern/juce)
add_subdirectory(extern/pybind11)
add_subdirectory(extern/spdlog)

function(juce_add_shared_library target)
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
#    add_library(${target} SHARED)
#    target_link_libraries(${target}
#            PRIVATE
#            juce::juce_audio_processors
#            juce::juce_core
#            PUBLIC
#            juce::juce_recommended_config_flags
#            juce::juce_recommended_warning_flags
#            juce::juce_recommended_lto_flags
#    )
#    target_include_directories(juce_shared
#            INTERFACE $<TARGET_PROPERTY:juce_shared,INCLUDE_DIRECTORIES>)
    target_compile_definitions(juce_shared
            PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_CURL=0
    )
#    _juce_initialise_target(${target} ${ARGN})
##    _juce_set_output_name(${target} "$<TARGET_PROPERTY:${target},JUCE_PRODUCT_NAME>.so")
    set_target_properties(juce_shared PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${MODULES_DIR}
    )
endfunction()

juce_add_shared_library(juce_shared)




#juce_generate_juce_header(juce_shared)


set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)


file(MAKE_DIRECTORY ${MODULES_DIR})

add_subdirectory(venom/juce)
add_subdirectory(venom/python/AudioProcessor)

add_subdirectory(tests/cpp)
add_subdirectory(tests/vst3)