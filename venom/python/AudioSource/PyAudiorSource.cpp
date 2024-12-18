#include <thread>
#include <utility>

#include "include/PyAudioProcessor.h"
#include "spdlog/spdlog.h"

PyAudioSource::PyAudioSource(std::unique_ptr<py::object> clsInstance)
    : juce::AudioSource(/*tu trzeba coś dać*/), instance(std::move(clsInstance)) {}

void PyAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    spdlog::debug("[Get Next Audio Block]");

    py::gil_scoped_acquire acquire;
    instance->attr("getNextAudioBlock")(bufferToFill);
}

void PyAudioProcessor::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    spdlog::debug("[Prepare To Play]");

    py::gil_scoped_acquire acquire;
    instance->attr("prepareToPlay")(samplesPerBlockExpected, sampleRate);
}

void PyAudioProcessor::releaseResources() {
    spdlog::debug("[Release Resources]");

    py::gil_scoped_acquire acquire;
    instance->attr("releaseResources")();
}

PyAudioProcessor::~PyAudioProcessor() {
    spdlog::debug("[DESCTRUCTOR]");
    py::gil_scoped_acquire acquire;
    instance.reset();
}
