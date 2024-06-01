//
// Created by Adam Szokalski on 03/01/2024.
//
#include <pybind11/pybind11.h>

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "utils/utils.h"
#include "Initializer.h"

#define PYBIND11_DETAILED_ERROR_MESSAGES


namespace py = pybind11;



PYBIND11_MODULE(juce, m)
{
    initializeJuce();
    init_juce_audio_processors(m);
    init_juce_gui_basics(m);
    init_utils(m);
}
