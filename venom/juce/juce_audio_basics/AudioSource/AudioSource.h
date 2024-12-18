#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "MessageManagerHelper.h"
#include "juce_audio_basics/juce_audio_basics.h"

namespace py = pybind11;

void init_AudioSource(py::module &m);

#endif  // AUDIOSOURCE_H
