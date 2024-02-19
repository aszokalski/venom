#include "juce_gui_basics/juce_gui_basics.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


class PyTextEditor : public juce::TextEditor 
{
public:
    /* Inherit the constructors */
    using juce::TextEditor ::TextEditor ;
};


void init_TextEditor (py::module& m) {
        py::class_<juce::TextEditor, PyTextEditor >(m, "TextEditor ", py::dynamic_attr())
        .def(py::init<>())
        .def("addPopupMenuItems", [](juce::TextEditor &self, juce::PopupMenu& menuToAddTo, const juce::MouseEvent* mouseClickEvent)
            { self.addPopupMenuItems(menuToAddTo, mouseClickEvent); })
        .def("performPopupMenuAction", [](juce::TextEditor &self, int menuItemID)
            { self.performPopupMenuAction(menuItemID); });
}