#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyComboBox: public juce::ComboBox
{
public:
    /* Inherit the constructors */
    using juce::ComboBox::ComboBox;
};


void init_ComboBox(py::module& m) {
        py::class_<juce::ComboBox, PyComboBox>(m, "ComboBox", py::dynamic_attr())
        .def(py::init<>());
}