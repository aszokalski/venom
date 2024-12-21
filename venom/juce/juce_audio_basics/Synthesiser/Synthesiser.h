#ifndef SYNTHESISER_H
#define SYNTHESISER_H
#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <juce_audio_basics/juce_audio_basics.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "MessageManagerHelper.h"

namespace py = pybind11;

void init_Synthesiser(py::module &m);

#endif  // SYNTHESISER_H
