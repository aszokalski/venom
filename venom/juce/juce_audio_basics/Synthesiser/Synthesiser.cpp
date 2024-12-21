#include "Synthesiser.h"

class PySynthesiser : public juce::Synthesiser {
   public:
    using juce::Synthesiser::Synthesiser;

    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override {
        PYBIND11_OVERRIDE_PURE(void, juce::Synthesiser, noteOn, midiChannel, midiNoteNumber, velocity);
    }

    void noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override {
        PYBIND11_OVERRIDE_PURE(void, juce::Synthesiser, noteOff, midiChannel, midiNoteNumber, velocity, allowTailOff);
    }

    void addVoice(std::unique_ptr<juce::SynthesiserVoice> voice) override {
        PYBIND11_OVERRIDE(void, juce::Synthesiser, addVoice, std::move(voice));
    }

    void clearVoices() override { PYBIND11_OVERRIDE(void, juce::Synthesiser, clearVoices); }

    void addSound(std::unique_ptr<juce::SynthesiserSound> sound) override {
        PYBIND11_OVERRIDE(void, juce::Synthesiser, addSound, std::move(sound));
    }

    void clearSounds() override { PYBIND11_OVERRIDE(void, juce::Synthesiser, clearSounds); }

    void renderNextBlock(juce::AudioBuffer<float> &outputAudio, const juce::MidiBuffer &inputMidi, int startSample,
                         int numSamples) override {
        PYBIND11_OVERRIDE_PURE(void, juce::Synthesiser, renderNextBlock, outputAudio, inputMidi, startSample,
                               numSamples);
    }
};

void init_Synthesiser(py::module &m) {
    py::class_<juce::Synthesiser, PySynthesiser>(m, "Synthesiser")
        .def(py::init<>())
        .def("noteOn", &juce::Synthesiser::noteOn)
        .def("noteOff", &juce::Synthesiser::noteOff)
        .def("addVoice", &juce::Synthesiser::addVoice)
        .def("addSound", &juce::Synthesiser::addSound)
        .def("clearVoices", &juce::Synthesiser::clearVoices)
        .def("clearSounds", &juce::Synthesiser::clearSounds)
        .def("renderNextBlock", &juce::Synthesiser::renderNextBlock);
}
