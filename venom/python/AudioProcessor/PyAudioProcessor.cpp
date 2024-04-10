#include <utility>

#include "include/PyAudioProcessor.h"

PyAudioProcessor::PyAudioProcessor(std::unique_ptr<py::object> clsInstance) : juce::AudioProcessor(), instance(std::move(clsInstance)){
}

void PyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  instance->attr("prepareToPlay")(sampleRate, samplesPerBlock);
}

void PyAudioProcessor::releaseResources()
{
  instance->attr("releaseResources")();
}

bool PyAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
  return true;
}

void PyAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
  py::gil_scoped_release nogil;
  {
    py::gil_scoped_acquire acquire;
    instance->attr("processBlock")(&buffer, &midiMessages);
  }
}

juce::AudioProcessorEditor* PyAudioProcessor::createEditor()
{
  JUCE_ASSERT_MESSAGE_MANAGER_IS_LOCKED
  auto editor = std::make_unique<py::object>(instance->attr("createEditor")());
//  if(editor->is_none()){
//    return nullptr;
//  }
  return new PyAudioProcessorEditor(this, std::move(editor));
}

bool PyAudioProcessor::hasEditor() const
{
  return true;
}

const juce::String PyAudioProcessor::getName() const
{
  return instance->attr("getName")().cast<juce::String>();
}

bool PyAudioProcessor::acceptsMidi() const
{
  return false;
}

bool PyAudioProcessor::producesMidi() const
{
  return false;
}

bool PyAudioProcessor::isMidiEffect() const
{
  return false;
}

double PyAudioProcessor::getTailLengthSeconds() const
{
  return instance->attr("getTailLengthSeconds")().cast<double>();
}

int PyAudioProcessor::getNumPrograms()
{
  return instance->attr("getNumPrograms")().cast<int>();
}

int PyAudioProcessor::getCurrentProgram()
{
  return instance->attr("getCurrentProgram")().cast<int>();
}

void PyAudioProcessor::setCurrentProgram(int index)
{
  instance->attr("setCurrentProgram")(index);
}

const juce::String PyAudioProcessor::getProgramName(int index)
{
  return instance->attr("getProgramName")(index).cast<juce::String>();
}

void PyAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
  instance->attr("changeProgramName")(index, newName);
}

void PyAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
//  instance->attr("getStateInformation")(destData);
}

void PyAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
//  instance->attr("setStateInformation")(data, sizeInBytes);
}

