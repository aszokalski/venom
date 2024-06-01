add_library(VenomModule
        STATIC
        PyAudioProcessor.cpp
        PyAudioProcessorEditor.cpp)
set_property(TARGET VenomModule PROPERTY POSITION_INDEPENDENT_CODE TRUE)

target_link_libraries(VenomModule
        PRIVATE
        pybind11::embed
        juce_shared
        spdlog::spdlog
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
target_include_directories(VenomModule
        PUBLIC
        "/home/mszawerd/venom/venom/cmake-build-debug/juce_shared_artefacts/JuceLibraryCode"
)