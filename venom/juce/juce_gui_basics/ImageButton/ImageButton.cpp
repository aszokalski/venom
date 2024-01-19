#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyImageButton : public juce::ImageButton
{
public:
    /* Inherit the constructors */
    using juce::ImageButton::ImageButton;
};


void init_ImageButton(py::module& m) {
        py::class_<juce::ImageButton, PyImageButton>(m, "ImageButton", py::dynamic_attr())
        .def(py::init<>());
}