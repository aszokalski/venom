#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyProgressBar : public juce::ProgressBar
{
public:
    /* Inherit the constructors */
    explicit PyProgressBar (double& progress) : juce::ProgressBar(progress) {} ;
};


void init_ProgressBar(py::module& m) {
        py::class_<juce::ProgressBar, PyProgressBar>(m, "ProgressBar", py::dynamic_attr())
        .def(py::init([](double& progress)
            { return new PyProgressBar(progress); }));
}