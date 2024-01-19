#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyGroupComponent : public juce::GroupComponent
{
public:
    /* Inherit the constructors */
    using juce::GroupComponent::GroupComponent;
};


void init_GroupComponent(py::module& m) {
        py::class_<juce::GroupComponent, PyGroupComponent>(m, "GroupComponent", py::dynamic_attr())
        .def(py::init<>());
}