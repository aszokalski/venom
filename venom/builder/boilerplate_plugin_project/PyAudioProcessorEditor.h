#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_basics/juce_audio_basics.h" // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include <pybind11/embed.h> // everything needed for embedding
#define PYBIND11_DETAILED_ERROR_MESSAGES

namespace py = pybind11;

// This class links the python class back to the C++ class
class PyAudioProcessorEditor : public juce::AudioProcessorEditor{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PyAudioProcessorEditor)
    py::object altered_class_instance;

public:

    PyAudioProcessorEditor(juce::AudioProcessor *p, py::object editor) : juce::AudioProcessorEditor(p) {
        this->altered_class_instance = editor;
        setSize(400, 300);
    }

    PyAudioProcessorEditor(juce::AudioProcessor &p, py::object editor) : juce::AudioProcessorEditor(p) {
        this->altered_class_instance = editor;
    }

    ~PyAudioProcessorEditor() override = default;

    void resized() override
    {
        this->altered_class_instance.attr("resized")();
    }

    void paint(juce::Graphics &g) override
    {
//        TODO: Conversion error here
        this->altered_class_instance.attr("paint")(g);
    }
};
