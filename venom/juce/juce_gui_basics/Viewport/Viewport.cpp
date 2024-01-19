#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyViewport : public juce::Viewport 
{
public:
    /* Inherit the constructors */
    using juce::Viewport::Viewport;

protected:
    juce::ScrollBar* createScrollBarComponent (bool isVertical) override {
        PYBIND11_OVERRIDE_PURE(
            juce::ScrollBar*,               /* Return type */
            juce::Viewport,                 /* Parent class */
            createScrollBarComponent,       /* Name of function in C++ (must match Python name) */
            isVertical                      /* Argument(s) */
        );
    }
};


void init_Viewport (py::module& m) {
        py::class_<juce::Viewport, PyViewport>(m, "Viewport", py::dynamic_attr())
        .def(py::init<>());
        // .def("createScrollBarComponent",[](juce::Viewport &self, bool isVertical) 
        //     { return self.createScrollBarComponent(isVertical) });
}