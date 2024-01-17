//
// Created by Adam Szokalski on 03/01/2024.
//
#include "juce_audio_processors.h"

#include "AudioProcessor/AudioProcessor.h"
#include "AudioProcessorEditor/AudioProcessorEditor.h"



void init_juce_audio_processors(py::module &super) {
    auto m = super.def_submodule("juce_audio_processors");
    init_AudioProcessor(m);
    init_AudioProcessorEditor(m);
}
