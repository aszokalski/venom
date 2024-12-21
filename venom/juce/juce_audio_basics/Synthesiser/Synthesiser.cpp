#include "Synthesiser.h"

void init_Synthesiser(py::module &m) {
    py::class_<juce::Synthesiser>(m, "Synthesiser")
        .def(py::init<>())
        .def("noteOn", &juce::Synthesiser::noteOn)
        .def("noteOff", &juce::Synthesiser::noteOff)
        .def("addVoice", &juce::Synthesiser::addVoice, py::return_value_policy::reference)
        .def("addSound", &juce::Synthesiser::addSound, py::return_value_policy::reference)
        .def("clearVoices", &juce::Synthesiser::clearVoices)
        .def("clearSounds", &juce::Synthesiser::clearSounds)
        .def("renderNextBlock", [](juce::Synthesiser &self, juce::AudioBuffer<float> &outputAudio,
                                   const juce::MidiBuffer &inputMidi, int startSample, int numSamples) {
            self.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        });
}
