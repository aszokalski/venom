#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include "juce_audio_devices/juce_audio_devices.h"
#include "PyAudioProcessor.h"

namespace py = pybind11;

TEST(AUDIO_PROCESSOR, AudioProcessorCreation){
  auto interpreter = std::make_unique<py::scoped_interpreter>();
  auto path = py::module_::import("sys").attr("path");
  path.attr("append")(MODULES_DIR);
  path.attr("append")(STUBS_DIR);
  py::eval_file(PYTHON_STUBS_FILE);
  auto obj = std::make_shared<py::object>(py::eval("PyAudioProcessor()"));

  obj->attr("prepareToPlay")(1.0, 2);
  {
    auto cppProcessor = obj->cast<std::shared_ptr<juce::AudioProcessor>>();
    cppProcessor->prepareToPlay(1.0, 2);
  }
  obj->attr("prepareToPlay")(1.0, 2);
  py::eval("gc.collect()");
}

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
