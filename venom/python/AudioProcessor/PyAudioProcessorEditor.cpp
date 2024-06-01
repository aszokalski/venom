#include "include/PyAudioProcessorEditor.h"

#include <utility>
#include "spdlog/spdlog.h"

PyAudioProcessorEditor::PyAudioProcessorEditor(juce::AudioProcessor *p, std::unique_ptr<py::object> instance)
        : juce::AudioProcessorEditor(p), instance(std::move(instance)) {
    setSize(400, 400);
    this->instance->attr("introduce")(this);
//    addAndMakeVisible(slider);
//    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
}

PyAudioProcessorEditor::~PyAudioProcessorEditor() {
    spdlog::debug("[EDITOR DEL]");
    py::gil_scoped_acquire acquire;
    instance.reset();
};

void PyAudioProcessorEditor::resized() {
//    slider.setBounds(20, 20, getWidth() - 20, 20);
    spdlog::debug("[RESIZE]");
    py::gil_scoped_acquire acquire;
    instance->attr("resized")();
    auto img = createComponentSnapshot(getLocalBounds());
    juce::File file("/home/mszawerd/venom/venom/cmake-build-debug/dupaeh.png");
    std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream());
    juce::PNGImageFormat().writeImageToStream(img, *fileStream);
}

void PyAudioProcessorEditor::paint(juce::Graphics &g) {
//    py::gil_scoped_acquire acquire;
//    instance->attr("paint")(&g);
}

