project(venom_juce)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/out)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

add_subdirectory(../../extern/juce JUCE)

add_subdirectory(../../extern/pybind11 pybind11)
add_subdirectory(juce_audio_processors)

set(Python3_INCLUDE_DIR "/Users/marcinjarczewski/Documents/studia/sem6/venom/venv/lib/python3.11")
set(Python3_LIBRARY "/Users/marcinjarczewski/.pyenv/versions/3.11.3/lib/libpython3.11.dylib")

#set(SITE_PACKAGES_DIRS "../../venv/lib/python3.11/site-packages")

#find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

pybind11_add_module(juce
        juce_audio_processors/AudioProcessor/AudioProcessor.cpp
        juce_audio_processors/AudioProcessor/AudioProcessor.h
        juce_audio_processors/AudioProcessorEditor/AudioProcessorEditor.cpp
        juce_audio_processors/AudioProcessorEditor/AudioProcessorEditor.h
        juce_audio_processors/juce_audio_processors.cpp
        juce_audio_processors/juce_audio_processors.h


        juce_gui_basics/juce_gui_basics.cpp
        juce_gui_basics/juce_gui_basics.h
        juce_gui_basics/Component/Component.cpp
        juce_gui_basics/Component/Component.h
        juce_gui_basics/ImageButton/ImageButton.cpp
        juce_gui_basics/ImageButton/ImageButton.h
        juce_gui_basics/Viewport/Viewport.cpp
        juce_gui_basics/Viewport/Viewport.h
        juce_gui_basics/ToggleButton/ToggleButton.cpp
        juce_gui_basics/ToggleButton/ToggleButton.h
        juce_gui_basics/ProgressBar/ProgressBar.cpp
        juce_gui_basics/ProgressBar/ProgressBar.h

        juce_gui_basics/ComboBox/ComboBox.cpp
        juce_gui_basics/ComboBox/ComboBox.h
        juce_gui_basics/TextEditor/TextEditor.cpp
        juce_gui_basics/TextEditor/TextEditor.h
        juce_gui_basics/GroupComponent/GroupComponent.cpp
        juce_gui_basics/GroupComponent/GroupComponent.h
        juce_gui_basics/Label/Label.cpp
        juce_gui_basics/Label/Label.h
        juce_gui_basics/Slider/Slider.cpp
        juce_gui_basics/Slider/Slider.h


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

# Export targets
install(TARGETS juce
        EXPORT juceConfig
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

# Export JUCE's recommended config flags
install(TARGETS
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags
        EXPORT juceConfig
        )

# Install headers
install(FILES
        juce_gui_basics/juce_gui_basics.h
        juce_gui_basics/Component/Component.h
        juce_gui_basics/ImageButton/ImageButton.h
        juce_gui_basics/Viewport/Viewport.h
        juce_gui_basics/ToggleButton/ToggleButton.h
        juce_gui_basics/ProgressBar/ProgressBar.h
        juce_gui_basics/ComboBox/ComboBox.h
        juce_gui_basics/TextEditor/TextEditor.h
        juce_gui_basics/GroupComponent/GroupComponent.h
        juce_gui_basics/Label/Label.h
        juce_gui_basics/Slider/Slider.h
        utils/utils.h
        DESTINATION include/juce
        )

# Export the installation configuration
install(EXPORT juceConfig
        FILE juceConfig.cmake
        NAMESPACE juce::
        DESTINATION lib/cmake/juce
        )