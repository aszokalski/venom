#include "MyClass.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(example, m)
{
    py::class_<MyClass>(m, "MyClass")
        .def(py::init())
        .def("add", &MyClass::add)
        .def("sub", &MyClass::sub);
}
