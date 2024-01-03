cmake_minimum_required(VERSION 3.5...3.26)
project(venom VERSION 0.1.0)
set(FORMATS AU VST3 Standalone)

add_subdirectory(extern/juce)
add_subdirectory(extern/pybind11)

# Juce python bindings
pybind11_add_module(juce
        src/cpp/juce_audio_processors/AudioProcessor/AudioProcessor.cpp
        src/cpp/juce_audio_processors/AudioProcessor/AudioProcessor.h
        src/cpp/juce_audio_processors/AudioProcessorEditor/AudioProcessorEditor.cpp
        src/cpp/juce_audio_processors/AudioProcessorEditor/AudioProcessorEditor.h
        src/cpp/juce.cpp
        src/cpp/juce_audio_processors/juce_audio_processors.cpp
        src/cpp/juce_audio_processors/juce_audio_processors.h
)

target_compile_definitions(juce
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO}
                           PUBLIC
                           JUCE_WEB_BROWSER=0 
                           JUCE_USE_CURL=0 
                           JUCE_VST3_CAN_REPLACE_VST2=0
                           )

target_link_libraries(juce
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
                           ${Python_LIBRARIES}
                           PUBLIC
                           juce::juce_recommended_config_flags
                           juce::juce_recommended_lto_flags
                           juce::juce_recommended_warning_flags
                           )

# build juce bindings .so to src/python
set_target_properties(juce PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/python
        )


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
         ${Python_LIBRARIES}
         PUBLIC
         juce::juce_recommended_config_flags
         juce::juce_recommended_lto_flags
         juce::juce_recommended_warning_flags
         )


 target_sources(VenomPlugin
         PRIVATE
         src/cpp/create_plugin.cpp
         src/cpp/juce_audio_processors/AudioProcessor/PyAudioProcessor.h
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

foreach(FORMAT ${FORMATS})
    if(${FORMAT} STREQUAL "Standalone")
        set(PACKAGE_NAME ${PROJECT_NAME}.app)
    elseif (${FORMAT} STREQUAL "VST3")
        set(PACKAGE_NAME ${PROJECT_NAME}.vst3)
    elseif (${FORMAT} STREQUAL "AU")
        set(PACKAGE_NAME ${PROJECT_NAME}.component)

    add_custom_command(TARGET VenomPlugin POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/src/python/juce.cpython-311-darwin.so
            ${CMAKE_CURRENT_SOURCE_DIR}/src/python/PyAudioProcessor.py
            $<TARGET_FILE_DIR:VenomPlugin>/${FORMAT}/${PACKAGE_NAME}/Contents/MacOS/
    )
    endif()
endforeach()
