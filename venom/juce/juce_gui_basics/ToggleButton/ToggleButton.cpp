#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyToggleButton : public juce::ToggleButton 
{
public:
    /* Inherit the constructors */
    using juce::ToggleButton ::ToggleButton ;
};


void init_ToggleButton (py::module& m) {
        py::class_<juce::ToggleButton , PyToggleButton >(m, "ToggleButton ", py::dynamic_attr())
        .def(py::init<>());
}