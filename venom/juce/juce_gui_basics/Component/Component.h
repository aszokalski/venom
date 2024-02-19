#ifndef COMPONENT_H
#define COMPONENT_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_Component(py::module &m);

#endif //COMPONENT_H