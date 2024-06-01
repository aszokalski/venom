pybind11_add_module(ui_basics
        SHARED
        Component/Component.cpp
        ImageButton/ImageButton.cpp
        Viewport/Viewport.cpp
        ToggleButton/ToggleButton.cpp
        ProgressBar/ProgressBar.cpp
        ComboBox/ComboBox.cpp
        TextEditor/TextEditor.cpp
        GroupComponent/GroupComponent.cpp
        Label/Label.cpp
        Slider/Slider.cpp
        juce_gui_basics.cpp)

set_property(TARGET ui_basics PROPERTY POSITION_INDEPENDENT_CODE TRUE)

target_link_libraries(ui_basics
        PRIVATE
        ${Python_LIBRARIES}
        Python::Module
        pybind11::embed
        juce_shared
        creation_manager
)

set_target_properties(ui_basics
        PROPERTIES
        PREFIX "${PYTHON_MODULE_PREFIX}"
        SUFFIX "${PYTHON_MODULE_EXTENSION}"
        LIBRARY_OUTPUT_DIRECTORY "${MODULES_DIR}"
)

target_compile_definitions(ui_basics
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        MODULES_DIR="${MODULES_DIR}"
)
target_include_directories(ui_basics
        PUBLIC
        "/home/mszawerd/venom/venom/cmake-build-debug/juce_shared_artefacts/JuceLibraryCode"
)