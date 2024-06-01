//
// Created by Adam Szokalski on 03/01/2024.
//

#ifndef JUCE_AUDIO_PROCESSORS_H
#define JUCE_AUDIO_PROCESSORS_H
#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <pybind11/pybind11.h>
#include "Initializer.h"

namespace py = pybind11;

void init_juce_audio_processors(py::module &super);

#endif //JUCE_AUDIO_PROCESSORS_H
