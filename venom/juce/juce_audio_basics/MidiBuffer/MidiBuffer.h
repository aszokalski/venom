#ifndef MIDIBUFFER_H
#define MIDIBUFFER_H
#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "MessageManagerHelper.h"
#include <juce_audio_basics/juce_audio_basics.h>

namespace py = pybind11;

void init_MidiBuffer(py::module &m);

#endif //MIDIBUFFER_H