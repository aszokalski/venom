//
// Created by Adam Szokalski on 03/01/2024.
//
#include "utils.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>


// this is a submodule for nescessary classes from unported modules
void init_utils(py::module &super) {
    auto m = super.def_submodule("utils");

    py::class_<juce::AudioBuffer<float>>(m, "AudioBuffer")
    .def(py::init<>())
    .def("applyGain", [](juce::AudioBuffer<float> &self, float gain)
         { self.applyGain(gain); });

    py::class_<juce::MidiBuffer>(m, "MidiBuffer")
        .def(py::init<>());

    py::class_<juce::String>(m, "String")
        .def(py::init<>());

    py::class_<juce::MemoryBlock>(m, "MemoryBlock")
        .def(py::init<>());
}
