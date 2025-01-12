#ifndef SYNTHESISERSOUND_H
#define SYNTHESISERSOUND_H
#define PYBIND11_DETAILED_ERROR_MESSAGES

#include "MessageManagerHelper.h"
#include <juce_audio_basics/juce_audio_basics.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_SynthesiserSound(py::module &m);

#endif  // SYNTHESISERSOUND_H
