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
        juce_shared
        ${Python_LIBRARIES}
        pybind11::embed
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

add_subdirectory(juce_audio_processors)
add_subdirectory(juce_gui_basics)
add_subdirectory(helpers)
