#include "include/PyAudioProcessor.h"

#include <thread>
#include <utility>

#include "spdlog/spdlog.h"

PyAudioProcessor::PyAudioProcessor(std::unique_ptr<py::object> clsInstance)
        : juce::AudioProcessor(),
          instance(std::move(clsInstance)) {
}

void PyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    spdlog::debug("[Prepare To Play]");

    py::gil_scoped_acquire acquire;
    instance->attr("prepareToPlay")(sampleRate, samplesPerBlock);
}

void PyAudioProcessor::releaseResources() {
    spdlog::debug("[Release Resources]");

    py::gil_scoped_acquire acquire;
    instance->attr("releaseResources")();
}

// TODO port BusesLayout
bool PyAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
    spdlog::debug("[BUS SUPPORT]");
    return false;
}

void PyAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    py::gil_scoped_acquire acquire;
    instance->attr("processBlock")(&buffer, &midiMessages);
}

juce::AudioProcessorEditor *PyAudioProcessor::createEditor() {
    JUCE_ASSERT_MESSAGE_MANAGER_IS_LOCKED

    py::gil_scoped_acquire acquire;
    auto editor = std::make_unique<py::object>(instance->attr("createEditor")());
    if (editor->is_none()) {
        return nullptr;
    }
    return new PyAudioProcessorEditor(this, std::move(editor));
}

bool PyAudioProcessor::hasEditor() const {
    py::gil_scoped_acquire acquire;
    return instance->attr("hasEditor")().cast<bool>();
}

const juce::String PyAudioProcessor::getName() const {
    py::gil_scoped_acquire acquire;
    return instance->attr("getName")().cast<juce::String>();
}

bool PyAudioProcessor::acceptsMidi() const {
    py::gil_scoped_acquire acquire;
    return instance->attr("acceptsMidi")().cast<bool>();
}

bool PyAudioProcessor::producesMidi() const {
    py::gil_scoped_acquire acquire;
    return instance->attr("producesMidi")().cast<bool>();
}

bool PyAudioProcessor::isMidiEffect() const {
    py::gil_scoped_acquire acquire;
    return instance->attr("isMidiEffect")().cast<bool>();
}

double PyAudioProcessor::getTailLengthSeconds() const {
    py::gil_scoped_acquire acquire;
    return instance->attr("getTailLengthSeconds")().cast<double>();
}

int PyAudioProcessor::getNumPrograms() {
    py::gil_scoped_acquire acquire;
    return instance->attr("getNumPrograms")().cast<int>();
}

int PyAudioProcessor::getCurrentProgram() {
    py::gil_scoped_acquire acquire;
    return instance->attr("getCurrentProgram")().cast<int>();
}

void PyAudioProcessor::setCurrentProgram(int index) {
    py::gil_scoped_acquire acquire;
    instance->attr("setCurrentProgram")(index);
}

const juce::String PyAudioProcessor::getProgramName(int index) {
    py::gil_scoped_acquire acquire;
    return instance->attr("getProgramName")(index).cast<juce::String>();
}

void PyAudioProcessor::changeProgramName(int index, const juce::String &newName) {
    py::gil_scoped_acquire acquire;
    instance->attr("changeProgramName")(index, newName);
}

void PyAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    py::gil_scoped_acquire acquire;
    instance->attr("getStateInformation")(&destData);
}

void PyAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    py::gil_scoped_acquire acquire;
    instance->attr("setStateInformation")(data, sizeInBytes);
}

PyAudioProcessor::~PyAudioProcessor() {
    spdlog::debug("[DESCTRUCTOR]");
    py::gil_scoped_acquire acquire;
    instance.reset();
}
