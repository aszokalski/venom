add_library(VenomModule
        STATIC
        PyAudioProcessor.cpp)

target_link_libraries(VenomModule PRIVATE
        pybind11::embed
        juce::juce_audio_utils
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
)

target_include_directories(VenomModule
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>  # for install target
)



target_compile_definitions(VenomModule
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        MODULES_DIR="${MODULES_DIR}"
)