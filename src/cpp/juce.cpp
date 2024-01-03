//
// Created by Adam Szokalski on 03/01/2024.
//
#include "juce_audio_processors/juce_audio_processors.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;



PYBIND11_MODULE(juce, m)
{
    init_juce_audio_processors(m);
}
