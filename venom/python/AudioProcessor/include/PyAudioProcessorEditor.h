#include <pybind11/embed.h>  // everything needed for embedding

#include <utility>

#include "juce_audio_basics/juce_audio_basics.h"  // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"

#define PYBIND11_DETAILED_ERROR_MESSAGES

namespace py = pybind11;

class PyAudioProcessorEditor : public juce::AudioProcessorEditor {
   private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PyAudioProcessorEditor)
    std::unique_ptr<py::object> instance;

   public:
    PyAudioProcessorEditor(juce::AudioProcessor *p, std::unique_ptr<py::object> instance);

    ~PyAudioProcessorEditor();

    void resized() override;

    void paint(juce::Graphics &g) override;
};