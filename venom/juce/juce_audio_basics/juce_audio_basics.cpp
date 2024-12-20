#include "juce_audio_basics.h"

#include "../helpers/include/initializer/Initializer.h"
#include "MidiMessage/MidiMessage.h"
#include "Synthesizer/Synthesizer.h"
#include "SynthesizerVoice/SynthesizerVoice.h"

void init_juce_audio_basics(py::module &super) {
    auto m = super.def_submodule("juce_audio_basics");
    init_MidiMessage(m);
    init_Synthesizer(m);
    init_SynthesizerVoice(m);
}

PYBIND11_MODULE(audio_basics, m) {
    initializeJuce();
    init_juce_audio_basics(m);
}
