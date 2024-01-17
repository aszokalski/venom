pybind11_add_module(juce
        juce_audio_processors/AudioProcessor/AudioProcessor.cpp
        juce_audio_processors/AudioProcessor/AudioProcessor.h
        juce_audio_processors/AudioProcessorEditor/AudioProcessorEditor.cpp
        juce_audio_processors/AudioProcessorEditor/AudioProcessorEditor.h
        juce_audio_processors/juce_audio_processors.cpp
        juce_audio_processors/juce_audio_processors.h

        utils/utils.cpp
        utils/utils.h

        juce.cpp
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
                            pybind11::embed
                           PUBLIC
                           juce::juce_recommended_config_flags
                           juce::juce_recommended_lto_flags
                           juce::juce_recommended_warning_flags
                           )

## build juce bindings .so to src/python
#set_target_properties(juce PROPERTIES
#        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/python
#        )