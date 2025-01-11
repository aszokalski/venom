#include "Synthesiser.h"

void init_Synthesiser(py::module &m) {
    py::implicitly_convertible<juce::SynthesiserVoice*, juce::ReferenceCountedObjectPtr<juce::SynthesiserVoice>>();
    py::implicitly_convertible<juce::SynthesiserSound*, juce::ReferenceCountedObjectPtr<juce::SynthesiserSound>>();

    py::class_<juce::Synthesiser>(m, "Synthesiser")
        .def(py::init<>(
            []() { return createOnMessageThread<juce::Synthesiser>([] { return new juce::Synthesiser(); }); }
        ))
        .def("noteOn", &juce::Synthesiser::noteOn)
        .def("noteOff", &juce::Synthesiser::noteOff)
        .def("addVoice", &juce::Synthesiser::addVoice)
        .def("addSound", &juce::Synthesiser::addSound)
        .def("clearVoices", &juce::Synthesiser::clearVoices)
        .def("clearSounds", &juce::Synthesiser::clearSounds)
        .def("renderNextBlock", [](juce::Synthesiser &self, juce::AudioBuffer<float> &outputAudio,
                                   const juce::MidiBuffer &inputMidi, int startSample, int numSamples) {
            self.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        });
}
