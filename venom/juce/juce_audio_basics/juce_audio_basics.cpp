#include "juce_audio_basics.h"

#include "../helpers/include/initializer/Initializer.h"
#include "MidiMessage/MidiMessage.h"

void init_juce_audio_basics(py::module &super) {
    auto m = super.def_submodule("juce_audio_basics");
    init_MidiMessage(m);
}

PYBIND11_MODULE(audio_basics, m) {
    initializeJuce();
    init_juce_audio_basics(m);
}
