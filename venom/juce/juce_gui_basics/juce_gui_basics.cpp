#include "juce_gui_basics.h"

#include "Component/Component.h"
#include "Slider/Slider.h"
#include "ComboBox/ComboBox.h"
#include "GroupComponent/GroupComponent.h"
#include "Label/Label.h"
#include "TextEditor/TextEditor.h"
#include "ToggleButton/ToggleButton.h"
#include "Viewport/Viewport.h"
#include "ImageButton/ImageButton.h"
#include "ProgressBar/ProgressBar.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;
//const static juce::ScopedJuceInitialiser_GUI libraryInitialiser;


void init_juce_gui_basics(py::module &super) {
    auto m = super.def_submodule("juce_gui_basics");
    init_Component(m);
    init_Slider(m);
    init_ComboBox(m);
    init_GroupComponent(m);
    init_Label(m);
    init_TextEditor(m);
    init_ToggleButton(m);
    init_Viewport(m);
    init_ImageButton(m);
    init_ProgressBar(m);
}

void init_ui_basics(py::module &super) {
    auto m = super.def_submodule("ui_basics");
    init_Component(m);
    init_Slider(m);
//    init_ComboBox(m);
//    init_GroupComponent(m);
//    init_Label(m);
//    init_TextEditor(m);
//    init_ToggleButton(m);
//    init_Viewport(m);
//    init_ImageButton(m);
//    init_ProgressBar(m);
}

PYBIND11_MODULE(ui_basics, m) {
    initializeJuce();
    init_ui_basics(m);
}