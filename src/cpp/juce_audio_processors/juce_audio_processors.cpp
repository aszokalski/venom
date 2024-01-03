//
// Created by Adam Szokalski on 03/01/2024.
//
#include "juce_audio_processors.h"

#include "AudioProcessor/AudioProcessor.h"
#include "AudioProcessorEditor/AudioProcessorEditor.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h> // for juce::AudioBuffer
#include <juce_audio_devices/juce_audio_devices.h>



void init_juce_audio_processors(py::module &super) {
    auto m = super.def_submodule("juce_audio_processors");
    init_AudioProcessor(m);
    init_AudioProcessorEditor(m);

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
