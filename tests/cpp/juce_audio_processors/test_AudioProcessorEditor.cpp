#include <gtest/gtest.h>
#include <pybind11/embed.h>

#include "PyAudioProcessor.h"
#include "juce_audio_devices/juce_audio_devices.h"

namespace py = pybind11;

TEST(AUDIO_PROCESSOR, AudioProcessorProcessBlock) {
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(MODULES_DIR);
    path.attr("append")(STUBS_DIR);
    py::eval_file(PYTHON_STUBS_FILE);
    auto obj = py::eval("PyAudioProcessor()");
    juce::AudioBuffer<float> b(2, 64);
    juce::MidiBuffer b2;
    obj.attr("processBlock")(&b, &b2);
    auto reader = b.getReadPointer(0);
    std::cout << reader[10] << std::endl;
}

TEST(AUDIO_PROCESSOR, AudioProcessorMultiThreadRun) {
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    std::unique_ptr<py::object> pyProcessor;
    py::gil_scoped_release nogil;
    {
        py::gil_scoped_acquire acq;
        auto path = py::module_::import("sys").attr("path");
        path.attr("append")(MODULES_DIR);
        path.attr("append")(STUBS_DIR);
        py::eval_file(PYTHON_STUBS_FILE);
        pyProcessor = std::make_unique<py::object>(py::eval("PyAudioProcessor()"));
    }

    PyAudioProcessor processor(std::move(pyProcessor));

    std::thread t{[&processor] {
        py::gil_scoped_acquire acq;
        juce::AudioBuffer<float> b(2, 64);
        juce::MidiBuffer b2;
        processor.processBlock(b, b2);
        auto reader = b.getReadPointer(0);
        std::cout << reader[10] << std::endl;
    }};
    t.join();
}

TEST(AUDIO_PROCESSOR_EDITOR, AudioProcessorEditorPainting) {
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
    //
    //    juce::File file("PUT_ABSOLUTE_PATH");
    //    std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream());
    //    juce::PNGImageFormat().writeImageToStream(image, *fileStream);
}

TEST(AUDIO_PROCESSOR_EDITOR, AudioProcessorEditorCreation) {
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    std::unique_ptr<py::object> pyProcessor;
    py::gil_scoped_release nogil;
    {
        py::gil_scoped_acquire acq;
        auto path = py::module_::import("sys").attr("path");
        path.attr("append")(MODULES_DIR);
        path.attr("append")(STUBS_DIR);
        py::eval_file(PYTHON_STUBS_FILE);
        pyProcessor = std::make_unique<py::object>(py::eval("PyAudioProcessor()"));
    }

    PyAudioProcessor processor(std::move(pyProcessor));
    std::thread t{[&processor] {
        auto editor = std::unique_ptr<juce::AudioProcessorEditor>(processor.createEditor());
        juce::Image image(juce::Image::ARGB, 200, 400, true);
        juce::Graphics g(image);
        editor->paint(g);
    }};
    t.join();
}