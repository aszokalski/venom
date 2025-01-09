#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H
#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "MessageManagerHelper.h"
#include <juce_audio_basics/juce_audio_basics.h>

namespace py = pybind11;

void init_MidiMessage(py::module &m);

#endif //MIDIMESSAGE_H