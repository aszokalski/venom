#ifndef JUCE_GUI_BASICS_H
#define JUCE_GUI_BASICS_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include <juce_gui_basics/juce_gui_basics.h>

void init_juce_gui_basics(py::module &super);

#endif //JUCE_GUI_BASICS_H