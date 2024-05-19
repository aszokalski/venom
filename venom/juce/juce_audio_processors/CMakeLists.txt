pybind11_add_module(audio_processor
        SHARED
        AudioProcessor/AudioProcessor.cpp
        AudioProcessorEditor/AudioProcessorEditor.cpp
        juce_audio_processors.cpp)

set_property(TARGET audio_processor PROPERTY POSITION_INDEPENDENT_CODE TRUE)

target_link_libraries(audio_processor
        PRIVATE
        ${Python_LIBRARIES}
        Python3::Module
        pybind11::embed
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