#include "juce_audio_basics.h"

#include "../helpers/include/initializer/Initializer.h"
#include "MidiMessage/MidiMessage.h"
#include "MidiBuffer/MidiBuffer.h"
#include "Synthesiser/Synthesiser.h"
#include "SynthesiserSound/SynthesiserSound.h"
#include "SynthesiserVoice/SynthesiserVoice.h"

void init_juce_audio_basics(py::module &super) {
    auto m = super.def_submodule("juce_audio_basics");
    init_MidiMessage(m);
    init_MidiBuffer(m);
    init_Synthesiser(m);
    init_SynthesiserVoice(m);
    init_SynthesiserSound(m);
}

PYBIND11_MODULE(audio_basics, m) {
    initializeJuce();
    init_juce_audio_basics(m);
}
