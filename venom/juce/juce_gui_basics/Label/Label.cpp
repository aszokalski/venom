#include <pybind11/pybind11.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_events/juce_events.h>

namespace py = pybind11;


class PyLabel : public juce::Label
{
public:
    /* Inherit the constructors */
    using juce::Label::Label;
};


void init_Label(py::module& m) {
        py::class_<juce::Label, juce::Component>(m, "Label", py::dynamic_attr())
        .def(py::init([](const juce::String& componentName, const juce::String& labelText)
                { return new juce::Label(componentName, labelText); }))
        .def("setText", [](juce::Label &self, const juce::String& newText, juce::NotificationType notification)
            { self.setText(newText, notification); })
        .def("getText", [](juce::Label &self, bool returnActiveEditorContents=false)
            { return self.getText(returnActiveEditorContents); });
}