#include "Synthesizer.h"

class PySynthesizer : public juce::Synthesizer {
   public:
    using juce::Synthesizer::Synthesizer;

    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override {
        PYBIND11_OVERRIDE_PURE(void, juce::Synthesizer, noteOn, midiChannel, midiNoteNumber, velocity);
    }

    void noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override {
        PYBIND11_OVERRIDE_PURE(void, juce::Synthesizer, noteOff, midiChannel, midiNoteNumber, velocity, allowTailOff);
    }

    void addVoice(std::unique_ptr<juce::SynthesiserVoice> voice) override {
        PYBIND11_OVERRIDE(void, juce::Synthesizer, addVoice, std::move(voice));
    }

    void clearVoices() override { PYBIND11_OVERRIDE(void, juce::Synthesizer, clearVoices); }

    void addSound(std::unique_ptr<juce::SynthesiserSound> sound) override {
        PYBIND11_OVERRIDE(void, juce::Synthesizer, addSound, std::move(sound));
    }

    void clearSounds() override { PYBIND11_OVERRIDE(void, juce::Synthesizer, clearSounds); }

    void renderNextBlock(juce::AudioBuffer<float> &outputAudio, const juce::MidiBuffer &inputMidi, int startSample,
                         int numSamples) override {
        PYBIND11_OVERRIDE_PURE(void, juce::Synthesizer, renderNextBlock, outputAudio, inputMidi, startSample,
                               numSamples);
    }
};

void init_Synthesizer(py::module &m) {
    py::class_<juce::Synthesizer, PySynthesizer>(m, "Synthesizer")
        .def(py::init<>())
        .def("noteOn", &juce::Synthesizer::noteOn)
        .def("noteOff", &juce::Synthesizer::noteOff)
        .def("addVoice", &juce::Synthesizer::addVoice)
        .def("addSound", &juce::Synthesizer::addSound)
        .def("clearVoices", &juce::Synthesizer::clearVoices)
        .def("clearSounds", &juce::Synthesizer::clearSounds)
        .def("renderNextBlock", &juce::Synthesizer::renderNextBlock);
}
