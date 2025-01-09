#include "include/PySynthesiser.h"

#include <utility>

#include "spdlog/spdlog.h"

PySynthesiser::PySynthesiser(std::unique_ptr<py::object> clsInstance)
    : juce::Synthesiser(), instance(std::move(clsInstance)) {}

void PySynthesiser::noteOn(int midiChannel, int midiNoteNumber, float velocity) {
    py::gil_scoped_acquire acquire;
    instance->attr("noteOn")(midiChannel, midiNoteNumber, velocity);
}

void PySynthesiser::noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) {
    py::gil_scoped_acquire acquire;
    instance->attr("noteOff")(midiChannel, midiNoteNumber, velocity, allowTailOff);
}

void PySynthesiser::renderNextBlock(juce::AudioBuffer<float>& outputAudio, const juce::MidiBuffer& inputMidi,
                                    int startSample, int numSamples) {
    py::gil_scoped_acquire acquire;
    instance->attr("renderNextBlock")(outputAudio, inputMidi, startSample, numSamples);
}

PySynthesiser::~PySynthesiser() {
    spdlog::debug("[DESTRUCTOR]");
    py::gil_scoped_acquire acquire;
}

