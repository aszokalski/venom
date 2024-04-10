//
// Created by Adam Szokalski on 03/01/2024.
//

#ifndef AUDIOPROCESSOREDITOR_H
#define AUDIOPROCESSOREDITOR_H

#include <pybind11/pybind11.h>
#include <pybind11/cast.h>

namespace py = pybind11;
void init_AudioProcessorEditor(py::module &m);
#endif //AUDIOPROCESSOREDITOR_H
