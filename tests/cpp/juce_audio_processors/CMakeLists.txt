add_executable(
        audio_processor_tests
        test_AudioProcessorEditor.cpp
)
target_link_libraries(audio_processor_tests
        PRIVATE
        GTest::gtest_main
        pybind11::embed
        juce::juce_gui_basics
#        audio_processor
#        VenomModule
)

target_compile_definitions(audio_processor_tests
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        MODULES_DIR="${MODULES_DIR}"
        STUBS_DIR="${STUBS_DIR}"
        PYTHON_STUBS_FILE="${STUBS_DIR}/audio_processors_stubs.py"
)
gtest_discover_tests(audio_processor_tests)