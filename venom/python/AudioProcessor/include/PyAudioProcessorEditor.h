#include <pybind11/embed.h>  // everything needed for embedding

#include <utility>

#include "JuceHeader.h"


#define PYBIND11_DETAILED_ERROR_MESSAGES

namespace py = pybind11;

class PyAudioProcessorEditor : public juce::AudioProcessorEditor {
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PyAudioProcessorEditor)
    std::unique_ptr<py::object> instance;
//    juce::Slider slider;
public:
    PyAudioProcessorEditor(juce::AudioProcessor *p, std::unique_ptr<py::object> instance);

    ~PyAudioProcessorEditor();

    void resized() override;

    void paint(juce::Graphics &g) override;
};
