add_library(audio_processor
        SHARED
        AudioProcessor/AudioProcessor.cpp
        AudioProcessorEditor/AudioProcessorEditor.cpp
        AudioProcessorListener/AudioProcessorListener.cpp
        AudioProcessorParameter/AudioProcessorParameter.cpp
        AudioProcessorValueTreeState/AudioProcessorValueTreeState.cpp
        juce_audio_processors.cpp)

target_link_libraries(audio_processor
        PRIVATE
        pybind11::module
        juce::juce_core
        juce::juce_audio_utils

)

set_target_properties(audio_processor
        PROPERTIES
        PREFIX "${PYTHON_MODULE_PREFIX}"
        SUFFIX "${PYTHON_MODULE_EXTENSION}"
        LIBRARY_OUTPUT_DIRECTORY "${MODULES_DIR}"
)

target_compile_definitions(audio_processor
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        MODULES_DIR="${MODULES_DIR}"
)