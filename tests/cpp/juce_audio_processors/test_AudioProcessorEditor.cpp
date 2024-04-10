#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include "juce_audio_devices/juce_audio_devices.h"
#include "PyAudioProcessor.h"

namespace py = pybind11;

TEST(AUDIO_PROCESSOR_EDITOR, AudioProcessorEditorPainting){
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(MODULES_DIR);
    path.attr("append")(STUBS_DIR);
    py::eval_file(PYTHON_STUBS_FILE);
    auto obj = py::eval("PyAudioProcessorEditor(PyAudioProcessor())");

    juce::Image image(juce::Image::ARGB, 200, 400, true);
    juce::Graphics g(image);
    obj.attr("paint")(&g);

//    juce::File file("PUT_ABSOLUTE_PATH_HERE_AND_ADMIRE_THAT_IT_WORKS");
//    std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream());
//    juce::PNGImageFormat().writeImageToStream(image, *fileStream);
}

TEST(AUDIO_PROCESSOR_EDITOR, AudioProcessorEditorCreation){
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(MODULES_DIR);
    path.attr("append")(STUBS_DIR);
    py::eval_file(PYTHON_STUBS_FILE);
    auto obj = std::make_unique<py::object>(py::eval("PyAudioProcessor()"));
    PyAudioProcessor processor(std::move(obj));
    std::thread t{[&processor]{
        auto editor = std::unique_ptr<juce::AudioProcessorEditor>(processor.createEditor());
        juce::Image image(juce::Image::ARGB, 200, 400, true);
        juce::Graphics g(image);
        editor->paint(g);
    }};
    t.join();

}