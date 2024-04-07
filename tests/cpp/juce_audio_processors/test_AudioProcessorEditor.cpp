#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include "juce_audio_devices/juce_audio_devices.h"

namespace py = pybind11;

TEST(AUDIO_PROCESSOR, AudioProcessorEditorCreation){
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(MODULES_DIR);
    path.attr("append")(STUBS_DIR);
    py::eval_file(PYTHON_STUBS_FILE);
    auto obj = py::eval("PyAudioProcessorEditor(PyAudioProcessor())");

    juce::Image image(juce::Image::ARGB, 200, 400, true);
    juce::Graphics g(image);
    obj.attr("resized")();
}