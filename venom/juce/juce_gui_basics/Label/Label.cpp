#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyLabel : public juce::Label
{
public:
    /* Inherit the constructors */
    using juce::Label::Label;
};


void init_Label(py::module& m) {
        py::class_<juce::Label, PyLabel>(m, "Label", py::dynamic_attr())
        .def(py::init<>());
}