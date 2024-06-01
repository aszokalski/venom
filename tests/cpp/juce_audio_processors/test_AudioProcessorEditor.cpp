#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include "JuceHeader.h"

#include "PyAudioProcessor.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "../../../venom/juce/helpers/include/initializer/Initializer.h"


namespace py = pybind11;

TEST(AUDIO_PROCESSOR, AudioProcessorProcessBlock) {
//    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    auto interpreter = std::make_unique<py::scoped_interpreter>();

    {
        initializeJuce();
        auto path = py::module_::import("sys").attr("path");
        path.attr("append")(MODULES_DIR);
        path.attr("append")(STUBS_DIR);
        try {
            py::eval_file(PYTHON_STUBS_FILE);
        } catch (const py::error_already_set &e) {
            spdlog::error("Error when evaluating provided python file: {}", e.what());
        } catch (const std::exception &e) {
            spdlog::error("Error when executing CPP code {}", e.what());
        }
        auto obj = py::eval("PyAudioProcessor()");
        juce::AudioBuffer<float> b(2, 64);
        juce::MidiBuffer b2;
        obj.attr("processBlock")(&b, &b2);
        shutdownJuce();

    }

//    {
//        py::gil_scoped_acquire acq;
//        interpreter.reset();
//    }
//    auto reader = b.getReadPointer(0);
    std::cout << "END" << std::endl;
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
    initializeJuce();
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(MODULES_DIR);
    path.attr("append")(STUBS_DIR);
    try {
        py::eval_file(PYTHON_STUBS_FILE);
        auto obj = py::eval("PyAudioProcessorEditor(PyAudioProcessor())");
        juce::Image image(juce::Image::ARGB, 200, 400, true);
        juce::Graphics g(image);
        obj.attr("paint")(&g);
    } catch (const py::error_already_set &e) {
        spdlog::error("Error when evaluating provided python file: {}", e.what());
    } catch (const std::exception &e) {
        spdlog::error("Error when executing CPP code {}", e.what());
    }
    shutdownJuce();

    //
    //    juce::File file("PUT_ABSOLUTE_PATH");
    //    std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream());
    //    juce::PNGImageFormat().writeImageToStream(image, *fileStream);
}

TEST(AUDIO_PROCESSOR_EDITOR, AudioProcessorEditor_WithSliderPainting) {
    initializeJuce();

    auto interpreter = std::make_unique<py::scoped_interpreter>();
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(MODULES_DIR);
    path.attr("append")(STUBS_DIR);
    juce::Image image(juce::Image::ARGB, 400, 400, true);
    try {
        py::eval_file(PYTHON_STUBS_FILE);
        auto obj = std::make_unique<py::object>(py::eval("SliderGUI(PyAudioProcessor())"));
        juce::Graphics g(image);
//        obj->attr("paint")(&g);
    } catch (const py::error_already_set &e) {
        spdlog::error("Error when evaluating provided python file: {}", e.what());
    } catch (const std::exception &e) {
        spdlog::error("Error when executing CPP code {}", e.what());
    }


    //
    juce::File file("/home/mszawerd/venom/venom/cmake-build-debug/dupa.png");
    std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream());
    juce::PNGImageFormat().writeImageToStream(image, *fileStream);
    shutdownJuce();
}

TEST(AUDIO_PROCESSOR_EDITOR, AudioProcessorEditorCreation) {
//    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    initializeJuce();
    auto interpreter = std::make_unique<py::scoped_interpreter>();
    std::unique_ptr<py::object> pyProcessor;
    py::gil_scoped_release nogil;
    {
        py::gil_scoped_acquire acq;
//        juce::MessageManagerLock lock;
        auto path = py::module_::import("sys").attr("path");
        path.attr("append")(MODULES_DIR);
        path.attr("append")(STUBS_DIR);
        try {
            py::eval_file(PYTHON_STUBS_FILE);
            pyProcessor = std::make_unique<py::object>(py::eval("PyAudioProcessor()"));
        } catch (const py::error_already_set &e) {
            spdlog::error("Error when evaluating provided python file: {}", e.what());
        } catch (const std::exception &e) {
            spdlog::error("Error when executing CPP code {}", e.what());
        }
    }
    spdlog::error("DONE");

    PyAudioProcessor processor(std::move(pyProcessor));
    std::thread t{[&processor] {
        std::promise<int> promise;
        std::future<int> future = promise.get_future();
        auto result = globalCall([&processor, &promise]() {
            spdlog::error("DONE");
            try {
                JUCE_ASSERT_MESSAGE_THREAD

                auto editor = std::unique_ptr<juce::AudioProcessorEditor>(processor.createEditor());
                juce::Image image(juce::Image::ARGB, 200, 400, true);
                juce::Graphics g(image);
                editor->paint(g);
                editor.reset();
                spdlog::error("DONE");
                promise.set_value(1);
            } catch (const py::error_already_set &e) {
                spdlog::error("Error when evaluating provided python file: {}", e.what());
                promise.set_value(1);

            } catch (const std::exception &e) {
                spdlog::error("Error when executing CPP code {}", e.what());
                promise.set_value(1);
            }
        });
        assert(result);
        auto res = future.get();
        std::cout << res << std::endl;


    }};
    t.join();
    shutdownJuce();
    spdlog::error("DONE");

}

TEST(SLIDER, PRINT_SLIDER) {
    juce::Slider slider;
    slider.setRange(0.0, 1.0);
    slider.setValue(0.5);
    slider.setBounds(10, 50, 200, 30);

    auto img = slider.createComponentSnapshot(slider.getLocalBounds());
    juce::File file("/home/mszawerd/venom/venom/cmake-build-debug/dupas.png");
    std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream());
    juce::PNGImageFormat().writeImageToStream(img, *fileStream);
}
