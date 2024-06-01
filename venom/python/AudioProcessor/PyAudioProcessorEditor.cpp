#include "include/PyAudioProcessorEditor.h"

#include <utility>

PyAudioProcessorEditor::PyAudioProcessorEditor(juce::AudioProcessor *p, std::unique_ptr<py::object> instance)
        : juce::AudioProcessorEditor(p), instance(std::move(instance)) {
    setSize(400, 400);
    this->instance->attr("introduce")(this);
}

PyAudioProcessorEditor::~PyAudioProcessorEditor() {
    py::gil_scoped_acquire acquire;
    instance.reset();
};

void PyAudioProcessorEditor::resized() {
    py::gil_scoped_acquire acquire;
    instance->attr("resized")();
}

void PyAudioProcessorEditor::paint(juce::Graphics &g) {
    py::gil_scoped_acquire acquire;
    instance->attr("paint")(&g);
}