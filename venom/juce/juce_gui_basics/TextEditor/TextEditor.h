#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_TextEditor(py::module &m);

#endif //TEXTEDITOR_H