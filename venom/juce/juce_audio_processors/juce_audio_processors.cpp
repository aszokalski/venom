//
// Created by Adam Szokalski on 03/01/2024.
//
#include "juce_audio_processors.h"

#include "AudioProcessor/AudioProcessor.h"
#include "AudioProcessorEditor/AudioProcessorEditor.h"
#include "../helpers/include/initializer/Initializer.h"

//const static juce::ScopedJuceInitialiser_GUI libraryInitialiser;


void init_juce_audio_processors(py::module &super) {
    auto m = super.def_submodule("juce_audio_processors");
    init_AudioProcessor(m);
    init_AudioProcessorEditor(m);
}

PYBIND11_MODULE(audio_processor, m) {
//    initializeJuce();
    init_juce_audio_processors(m);
}