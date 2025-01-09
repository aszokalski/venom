#include <pybind11/embed.h>  // everything needed for embedding

#include "juce_audio_basics/juce_audio_basics.h"  // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"

#define PYBIND11_DETAILED_ERROR_MESSAGES

namespace py = pybind11;

class PySynthesiserVoice : public juce::SynthesiserVoice {
   private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PySynthesiserVoice)
    std::unique_ptr<py::object> instance;

   public:
    explicit PySynthesiserVoice(std::unique_ptr<py::object> clsInstance);

    ~PySynthesiserVoice() override;

    bool canPlaySound(juce::SynthesiserSound *sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                   int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void renderNextBlock(juce::AudioBuffer<float> &outputAudio, int startSample, int numSamples) override;
};
