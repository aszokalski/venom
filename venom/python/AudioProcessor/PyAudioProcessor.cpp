#include <utility>

#include "include/PyAudioProcessor.h"

PyAudioProcessor::PyAudioProcessor(std::weak_ptr<py::object> clsInstance) : juce::AudioProcessor(), instance(std::move(clsInstance)){
}

void PyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  this->instance.lock()->attr("prepareToPlay")(sampleRate, samplesPerBlock);
}

void PyAudioProcessor::releaseResources()
{
  this->instance.lock()->attr("releaseResources")();
}

bool PyAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
  return this->instance.lock()->attr("isBusesLayoutSupported")(layouts).cast<bool>();
}

void PyAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
  this->instance.lock()->attr("processBlock")(buffer, midiMessages);
}

juce::AudioProcessorEditor* PyAudioProcessor::createEditor()
{
    return nullptr;
}

bool PyAudioProcessor::hasEditor() const
{
  return this->instance.lock()->attr("hasEditor")().cast<bool>();
}

const juce::String PyAudioProcessor::getName() const
{
  return this->instance.lock()->attr("getName")().cast<juce::String>();
}

bool PyAudioProcessor::acceptsMidi() const
{
  return this->instance.lock()->attr("acceptsMidi")().cast<bool>();
}

bool PyAudioProcessor::producesMidi() const
{
  return this->instance.lock()->attr("producesMidi")().cast<bool>();
}

bool PyAudioProcessor::isMidiEffect() const
{
  return this->instance.lock()->attr("isMidiEffect")().cast<bool>();
}

double PyAudioProcessor::getTailLengthSeconds() const
{
  return this->instance.lock()->attr("getTailLengthSeconds")().cast<double>();
}

int PyAudioProcessor::getNumPrograms()
{
  return this->instance.lock()->attr("getNumPrograms")().cast<int>();
}

int PyAudioProcessor::getCurrentProgram()
{
  return this->instance.lock()->attr("getCurrentProgram")().cast<int>();
}

void PyAudioProcessor::setCurrentProgram(int index)
{
  this->instance.lock()->attr("setCurrentProgram")(index);
}

const juce::String PyAudioProcessor::getProgramName(int index)
{
  return this->instance.lock()->attr("getProgramName")(index).cast<juce::String>();
}

void PyAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
  this->instance.lock()->attr("changeProgramName")(index, newName);
}

void PyAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
  this->instance.lock()->attr("getStateInformation")(destData);
}

void PyAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
  this->instance.lock()->attr("setStateInformation")(data, sizeInBytes);
}

