#include "include/PySynthesiserSound.h"

#include <thread>
#include <utility>

#include "spdlog/spdlog.h"

PySynthesiserSound::PySynthesiserSound(std::unique_ptr<py::object> clsInstance)
    : juce::SynthesiserSound(), instance(std::move(clsInstance)) {}

bool PySynthesiserSound::appliesToNote(int midiNoteNumber) {
    return true;
}

bool PySynthesiserSound::appliesToChannel(int midiChannel) {
    return true;
}

PySynthesiserSound::~PySynthesiserSound() {
    spdlog::debug("[DESCTRUCTOR]");
    py::gil_scoped_acquire acquire;
}
