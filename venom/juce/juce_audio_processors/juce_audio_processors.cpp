//
// Created by Adam Szokalski on 03/01/2024.
//
#include "juce_audio_processors.h"

#include "AudioProcessor/AudioProcessor.h"
#include "AudioProcessorEditor/AudioProcessorEditor.h"
#include "AudioProcessorListener/AudioProcessorListener.h"
#include "AudioProcessorParameter/AudioProcessorParameter.h"
#include "AudioProcessorValueTreeState/AudioProcessorValueTreeState.h"

void init_juce_audio_processors(py::module &super) {
    auto m = super.def_submodule("juce_audio_processors");
    init_AudioProcessor(m);
    init_AudioProcessorEditor(m);
    init_AudioProcessorParameter(m);
    init_AudioProcessorListener(m);
    init_AudioProcessorValueTreeState(m);
}

PYBIND11_MODULE(audio_processor, m)
{
    init_juce_audio_processors(m);
}