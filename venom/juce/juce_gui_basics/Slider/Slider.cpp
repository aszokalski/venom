#include "Slider.h"
#include <juce_gui_basics/juce_gui_basics.h>

class PySlider : public juce::Slider
{
public:
    /* Inherit the constructors */
    using juce::Slider::Slider;

    
};

void init_Slider(py::module& m) {
        py::class_<juce::Slider, PySlider>(m, "Slider", py::dynamic_attr())
        .def(py::init<>());
}
