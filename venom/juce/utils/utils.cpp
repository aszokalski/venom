//
// Created by Adam Szokalski on 03/01/2024.
//
#include "utils.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

// this is a submodule for nescessary classes from unported modules
void init_utils(py::module &super) {
    auto m = super.def_submodule("utils");

}
