#include "AudioProcessorValueTreeState.h"
#include <juce_audio_processors/juce_audio_processors.h>

class PyAudioProcessorValueTreeState : public juce::AudioProcessorValueTreeState
{
public:
    /* Inherit the constructors */
    using juce::AudioProcessorValueTreeState::AudioProcessorValueTreeState;

};

void init_AudioProcessorValueTreeState(py::module& m) {
        py::class_<juce::AudioProcessorValueTreeState, PyAudioProcessorValueTreeState>(m, "AudioProcessorValueTreeState", py::dynamic_attr())
        .def(py::init([](juce::AudioProcessor& processorToConnectTo, juce::UndoManager* undoManagerToUse)
                  { return new PyAudioProcessorValueTreeState(processorToConnectTo, undoManagerToUse); }));
}
