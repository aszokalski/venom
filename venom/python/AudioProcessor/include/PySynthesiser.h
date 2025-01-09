#include <pybind11/embed.h>  // everything needed for embedding

#include "juce_audio_basics/juce_audio_basics.h"  // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"

#define PYBIND11_DETAILED_ERROR_MESSAGES

namespace py = pybind11;

class PySynthesiser : public juce::Synthesiser {
   private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PySynthesiser)
    std::unique_ptr<py::object> instance;

   public:
    explicit PySynthesiser(std::unique_ptr<py::object> clsInstance);

    ~PySynthesiser() override;

    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;

    void noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override;

    void renderNextBlock(juce::AudioBuffer<float> &outputAudio, const juce::MidiBuffer &inputMidi, int startSample,
                         int numSamples);
};
