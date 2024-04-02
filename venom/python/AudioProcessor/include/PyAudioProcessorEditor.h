#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_basics/juce_audio_basics.h" // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include <pybind11/embed.h> // everything needed for embedding

#include <utility>
#define PYBIND11_DETAILED_ERROR_MESSAGES

namespace py = pybind11;

// This class links the python class back to the C++ class
class PyAudioProcessorEditor : public juce::AudioProcessorEditor{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PyAudioProcessorEditor)
    std::weak_ptr<py::object> instance;

public:

    PyAudioProcessorEditor(juce::AudioProcessor *p, std::weak_ptr<py::object> instance) : juce::AudioProcessorEditor(p), instance(std::move(instance)) {
    }
    ~PyAudioProcessorEditor() override{
    };

    void resized() override
    {
        this->instance.lock()->attr("resized")();
    }

    void paint(juce::Graphics &g) override
    {
        this->instance.lock()->attr("paint")(g);
    }
};
