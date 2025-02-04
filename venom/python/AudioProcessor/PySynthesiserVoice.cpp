#include "include/PySynthesiserVoice.h"

#include <thread>
#include <utility>

#include "spdlog/spdlog.h"

PySynthesiserVoice::PySynthesiserVoice(std::unique_ptr<py::object> clsInstance)
    : juce::SynthesiserVoice(), instance(std::move(clsInstance)) {}

bool PySynthesiserVoice::canPlaySound(juce::SynthesiserSound *sound) {
    py::gil_scoped_acquire acquire;
    return instance->attr("canPlaySound")(sound).cast<bool>();
}

void PySynthesiserVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                                   int currentPitchWheelPosition) {
    py::gil_scoped_acquire acquire;
    instance->attr("startNote")(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
}

void PySynthesiserVoice::stopNote(float velocity, bool allowTailOff) {
    py::gil_scoped_acquire acquire;
    instance->attr("stopNote")(velocity, allowTailOff);
}

void PySynthesiserVoice::pitchWheelMoved(int newPitchWheelValue) {
    py::gil_scoped_acquire acquire;
    instance->attr("pitchWheelMoved")(newPitchWheelValue);
}

void PySynthesiserVoice::controllerMoved(int controllerNumber, int newControllerValue) {
    py::gil_scoped_acquire acquire;
    instance->attr("controllerMoved")(controllerNumber, newControllerValue);
}

void PySynthesiserVoice::renderNextBlock(juce::AudioBuffer<float> &outputAudio, int startSample, int numSamples) {
    py::gil_scoped_acquire acquire;
    instance->attr("renderNextBlock")(outputAudio, startSample, numSamples);
}
