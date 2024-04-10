#include "include/PyAudioProcessorEditor.h"
#include <utility>
PyAudioProcessorEditor::PyAudioProcessorEditor(juce::AudioProcessor *p, std::unique_ptr<py::object> instance)
    : juce::AudioProcessorEditor(p), instance(std::move(instance)) {
}
PyAudioProcessorEditor::~PyAudioProcessorEditor() = default;
void PyAudioProcessorEditor::resized()
{
  instance->attr("resized")();
}

void PyAudioProcessorEditor::paint(juce::Graphics &g)
{
  instance->attr("paint")(&g);
}