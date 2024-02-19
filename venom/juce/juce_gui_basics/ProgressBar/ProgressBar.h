#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_ProgressBar(py::module &m);

#endif //PROGRESSBAR_H