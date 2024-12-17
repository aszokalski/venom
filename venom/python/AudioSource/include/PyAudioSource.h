#include "PyAudioProcessorEditor.h"
#include "juce_audio_basics/juce_audio_basics.h"  // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"

class PyAudioSource : public juce::AudioSource {
   private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PyAudioSource)
    std::unique_ptr<py::object> instance;

   public:
    explicit PyAudioProcessor(std::unique_ptr<py::object> clsInstance);

    ~PyAudioProcessor() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    void releaseResources() override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
};
