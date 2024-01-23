#ifndef AUDIOPROCESSORLISTENER_H
#define AUDIOPROCESSORLISTENER_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_AudioProcessorListener(py::module &m);

#endif //AUDIOPROCESSORLISTENER_H
