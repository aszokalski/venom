//
// Created by Adam Szokalski on 03/01/2024.
//

#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_AudioProcessor(py::module &m);

#endif //AUDIOPROCESSOR_H
