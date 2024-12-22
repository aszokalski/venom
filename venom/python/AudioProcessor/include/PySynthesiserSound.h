#include <pybind11/embed.h>  // everything needed for embedding

#include "juce_audio_basics/juce_audio_basics.h"  // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"

#define PYBIND11_DETAILED_ERROR_MESSAGES

namespace py = pybind11;

class PySynthesiserSound : public juce::SynthesiserSound {
   private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PySynthesiserSound)
    std::unique_ptr<py::object> instance;

   public:
    explicit PySynthesiserSound(std::unique_ptr<py::object> clsInstance);

    ~PySynthesiserSound() override;

    bool appliesToNote(int midiNoteNumber) override;

    bool appliesToChannel(int midiChannel) override;
};
