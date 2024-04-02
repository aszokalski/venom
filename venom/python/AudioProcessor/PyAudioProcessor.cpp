#include <utility>

#include "include/PyAudioProcessor.h"

PyAudioProcessor::PyAudioProcessor(std::shared_ptr<py::object> clsInstance) : juce::AudioProcessor(), instance(std::move(clsInstance)){
}

void PyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  this->instance->attr("prepareToPlay")(sampleRate, samplesPerBlock);
}

void PyAudioProcessor::releaseResources()
{
  this->instance->attr("releaseResources")();
}

bool PyAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
  return this->instance->attr("isBusesLayoutSupported")(layouts).cast<bool>();
}

void PyAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
  this->instance->attr("processBlock")(buffer, midiMessages);
}

juce::AudioProcessorEditor* PyAudioProcessor::createEditor()
{
    return nullptr;
}

bool PyAudioProcessor::hasEditor() const
{
  return this->instance->attr("hasEditor")().cast<bool>();
}

const juce::String PyAudioProcessor::getName() const
{
  return this->instance->attr("getName")().cast<juce::String>();
}

bool PyAudioProcessor::acceptsMidi() const
{
  return this->instance->attr("acceptsMidi")().cast<bool>();
}

bool PyAudioProcessor::producesMidi() const
{
  return this->instance->attr("producesMidi")().cast<bool>();
}

bool PyAudioProcessor::isMidiEffect() const
{
  return this->instance->attr("isMidiEffect")().cast<bool>();
}

double PyAudioProcessor::getTailLengthSeconds() const
{
  return this->instance->attr("getTailLengthSeconds")().cast<double>();
}

int PyAudioProcessor::getNumPrograms()
{
  return this->instance->attr("getNumPrograms")().cast<int>();
}

int PyAudioProcessor::getCurrentProgram()
{
  return this->instance->attr("getCurrentProgram")().cast<int>();
}

void PyAudioProcessor::setCurrentProgram(int index)
{
  this->instance->attr("setCurrentProgram")(index);
}

const juce::String PyAudioProcessor::getProgramName(int index)
{
  return this->instance->attr("getProgramName")(index).cast<juce::String>();
}

void PyAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
  this->instance->attr("changeProgramName")(index, newName);
}

void PyAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
  this->instance->attr("getStateInformation")(destData);
}

void PyAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
  this->instance->attr("setStateInformation")(data, sizeInBytes);
}

