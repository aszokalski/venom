#include "SynthesiserVoice.h"

class PySynthesiserVoice : public juce::SynthesiserVoice {
   public:
    using juce::SynthesiserVoice::SynthesiserVoice;

    bool canPlaySound(juce::SynthesiserSound *sound) override {
        PYBIND11_OVERLOAD_PURE(bool, juce::SynthesiserVoice, canPlaySound, sound);
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                   int currentPitchWheelPosition) override {
        PYBIND11_OVERLOAD_PURE(void, juce::SynthesiserVoice, startNote, midiNoteNumber, velocity, sound,
                               currentPitchWheelPosition);
    }

    void stopNote(float velocity, bool allowTailOff) override {
        PYBIND11_OVERLOAD_PURE(void, juce::SynthesiserVoice, stopNote, velocity, allowTailOff);
    }

    void pitchWheelMoved(int newPitchWheelValue) override {
        PYBIND11_OVERLOAD_PURE(void, juce::SynthesiserVoice, pitchWheelMoved, newPitchWheelValue);
    }

    void controllerMoved(int controllerNumber, int newControllerValue) override {
        PYBIND11_OVERLOAD_PURE(void, juce::SynthesiserVoice, controllerMoved, controllerNumber, newControllerValue);
    }

    void renderNextBlock(juce::AudioSampleBuffer &outputBuffer, int startSample, int numSamples) override {
        PYBIND11_OVERLOAD_PURE(void, juce::SynthesiserVoice, renderNextBlock, outputBuffer, startSample, numSamples);
    }
};

void init_SynthesiserVoice(py::module &m) {
    py::class_<juce::SynthesiserVoice, PySynthesiserVoice>(m, "SynthesiserVoice")
        .def(py::init<>(
            []() { return new PySynthesiserVoice(); }
        ))
        .def("canPlaySound", &juce::SynthesiserVoice::canPlaySound)
        .def("isVoiceActive", &juce::SynthesiserVoice::isVoiceActive)
        .def("startNote", &juce::SynthesiserVoice::startNote)
        .def("stopNote", &juce::SynthesiserVoice::stopNote)
        .def("pitchWheelMoved", &juce::SynthesiserVoice::pitchWheelMoved)
        .def("controllerMoved", &juce::SynthesiserVoice::controllerMoved)
        .def("renderNextBlock",
             [](juce::SynthesiserVoice &self, juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
                 self.renderNextBlock(outputBuffer, startSample, numSamples);
             });
}
