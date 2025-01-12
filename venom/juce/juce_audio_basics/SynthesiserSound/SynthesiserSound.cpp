#include "SynthesiserSound.h"

class PySynthesiserSound : public juce::SynthesiserSound {
   public:
    using juce::SynthesiserSound::SynthesiserSound;

    bool appliesToNote(int midiNoteNumber) override {
        PYBIND11_OVERRIDE_PURE(bool, juce::SynthesiserSound, appliesToNote, midiNoteNumber);
    }

    bool appliesToChannel(int midiChannel) override {
        PYBIND11_OVERRIDE_PURE(bool, juce::SynthesiserSound, appliesToChannel, midiChannel);
    }
};

void init_SynthesiserSound(py::module &m) {
    py::class_<juce::SynthesiserSound, PySynthesiserSound>(m, "SynthesiserSound")
        .def(py::init<>(
            []() { return new PySynthesiserSound(); }
        ))
        .def("appliesToNote", &juce::SynthesiserSound::appliesToNote)
        .def("appliesToChannel", &juce::SynthesiserSound::appliesToChannel);
}
