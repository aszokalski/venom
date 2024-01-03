//
// Created by Adam Szokalski on 03/01/2024.
//

#ifndef JUCE_AUDIO_PROCESSORS_H
#define JUCE_AUDIO_PROCESSORS_H

#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_juce_audio_processors(py::module &super);

#endif //JUCE_AUDIO_PROCESSORS_H
