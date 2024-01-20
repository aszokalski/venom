#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyComponent : public juce::Component
{
public:
    /* Inherit the constructors */
    using juce::Component::Component;
    explicit PyComponent (const juce::String& componentName) noexcept : juce::Component(componentName) {}


    juce::String getName() const noexcept {
        PYBIND11_OVERRIDE_PURE(
            juce::String,                       /* Return type */
            juce::Component,       /* Parent class */
            getName,              /* Name of function in C++ (must match Python name) */
        );
    }

    void addAndMakeVisible (juce::Component* child, int zOrder = -1) {
        PYBIND11_OVERRIDE_PURE(
            void,                       /* Return type */
            juce::Component,       /* Parent class */
            addAndMakeVisible,              /* Name of function in C++ (must match Python name) */
            child, zOrder /* Argument(s) */
        );
    }

    void paint(juce::Graphics& g) override
    {
         PYBIND11_OVERRIDE_PURE(
            void,                       /* Return type */
            juce::Component,       /* Parent class */
            paint,              /* Name of function in C++ (must match Python name) */
            g /* Argument(s) */
        );
    }

    void resized() override
    {
         PYBIND11_OVERRIDE_PURE(
            void,                       /* Return type */
            juce::Component,       /* Parent class */
            resized,              /* Name of function in C++ (must match Python name) */
        );
    }
};


void init_Component(py::module& m) {
        py::class_<juce::Component, PyComponent>(m, "Component", py::dynamic_attr())
        .def(py::init<>())
        .def("paint", [](juce::Component &self, juce::Graphics& g)
            { self.paint(g); })
        .def("resized", [](juce::Component &self)
            { self.resized(); })
        .def("getName", [](juce::Component &self)
            { return self.getName(); })
        .def("addAndMakeVisible", [](juce::Component &self, juce::Component* child, int zOrder = -1)
            { return self.addAndMakeVisible(child, zOrder); });
}