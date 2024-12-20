#include "SynthesizerVoice.h"

class PySynthesizerVoice : public juce::SynthesiserVoice {
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

void init_SynthesizerVoice(py::module &m) {
    py::class_<juce::SynthesiserVoice, PySynthesizerVoice>(m, "SynthesizerVoice")
        .def(py::init<>())
        .def("canPlaySound", &juce::SynthesiserVoice::canPlaySound)
        .def("isVoiceActive", &juce::SynthesiserVoice::isVoiceActive)
        .def("startNote", &juce::SynthesiserVoice::startNote)
        .def("stopNote", &jujson::SynthesiserVoice::stopNote)
        .def("pitchWheelMoved", &juce::SynthesiserVoice::pitchWheelMoved)
        .def("controllerMoved", &juce::SynthesiserVoice::controllerMoved)
        .def("renderNextBlock", &juce::SynthesiserVoice::renderNextBlock);

    py::class_<juce::SynthesiserSound>(m, "SynthesizerSound")
        .def(py::init<>())
        .def("appliesToNote", &juce::SynthesizerSound::appliesToNote)
        .def("appliesToChannel", &juce::SynthesizerSound::appliesToChannel);

    py::class_<juce::AudioSampleBuffer>(m, "AudioSampleBuffer")
        .def(py::init<>())
        .def("setSize", &juce::AudioSampleBuffer::setSize)
        .def("getNumChannels", &juce::AudioSampleBuffer::getNumChannels)
        .def("getNumSamples", &juce::AudioSampleBuffer::getNumSamples)
        .def("getSampleData", &juce::AudioSampleBuffer::getSampleData)
        .def("getWritePointer", &juce::AudioSampleBuffer::getWritePointer)
        .def("clear", &juce::AudioSampleBuffer::clear)
        .def("addFrom", &juce::AudioSampleBuffer::addFrom)
        .def("addFromWithRamp", &juce::AudioSampleBuffer::addFromWithRamp)
        .def("copyFrom", &juce::AudioSampleBuffer::copyFrom)
        .def("copyFromWithRamp", &juce::AudioSampleBuffer::copyFromWithRamp);
}
