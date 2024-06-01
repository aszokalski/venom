//
// Created by Adam Szokalski on 03/01/2024.
//

#include "AudioProcessorEditor.h"

class PyAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    using juce::AudioProcessorEditor::AudioProcessorEditor;

    explicit PyAudioProcessorEditor(juce::AudioProcessor &p) : juce::AudioProcessorEditor(p) {
        // In juce objects that are associated with UI need to be called on main Message thread
        JUCE_ASSERT_MESSAGE_MANAGER_IS_LOCKED
    }

    explicit PyAudioProcessorEditor(juce::AudioProcessor *p) : juce::AudioProcessorEditor(p) {
        // In juce objects that are associated with UI need to be called on main Message thread
        JUCE_ASSERT_MESSAGE_MANAGER_IS_LOCKED
    }


    void paint(juce::Graphics &g) override {
        PYBIND11_OVERLOAD(
                void,
                juce::AudioProcessorEditor, /* Parent class */
                paint,                      /* Name of function in C++ (must match Python name) */
                g                           /* Argument(s) */
        );
    }

    void resized() override {
        PYBIND11_OVERLOAD(
                void,                       /* Return type */
                juce::AudioProcessorEditor, /* Parent class */
                resized,                    /* Name of function in C++ (must match Python name) */
        );
    }
};

void init_AudioProcessorEditor(py::module &m) {
    py::class_<juce::AudioProcessorEditor, std::shared_ptr<juce::AudioProcessorEditor>, PyAudioProcessorEditor>(m,
                                                                                                                "AudioProcessorEditor",
                                                                                                                py::dynamic_attr())
            .def(py::init([](juce::AudioProcessor &p) -> std::unique_ptr<juce::AudioProcessorEditor> {

//                juce::ScopedJuceInitialiser_GUI libraryInitialiser;
                return createOnMessageThread<juce::AudioProcessorEditor>([&p] {
                    return new PyAudioProcessorEditor(p);
                });
            }))
            .def(py::init([](juce::AudioProcessor *p) { return new PyAudioProcessorEditor(p); }))
            .def("resized", [](juce::AudioProcessorEditor &self) { return self.resized(); })
            .def("paint", [](juce::AudioProcessorEditor &self, juce::Graphics &g) {
                return self.paint(g);
            })
            .def("getAudioProcessor", [](juce::AudioProcessorEditor &self) { return self.getAudioProcessor(); })
            .def("introduce", [](juce::AudioProcessorEditor &self, juce::AudioProcessorEditor &parent) {
                std::cout << "DUPAAA" << std::endl;
                parent.addAndMakeVisible(self);
            })
            .def("addAndMakeVisible", [](juce::AudioProcessorEditor &self, juce::Component &child, int zOrder = -1) {
                self.addAndMakeVisible(child, zOrder);
            })
            .def("setSize", [](juce::AudioProcessorEditor &self, int newWidth, int newHeight) {
                self.setSize(newWidth, newHeight);
            })
            .def("print", [](juce::AudioProcessorEditor &self) {
                auto img = self.createComponentSnapshot(self.getLocalBounds());
                juce::File file("/home/mszawerd/venom/venom/cmake-build-debug/dupae.png");
                std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream());
                juce::PNGImageFormat().writeImageToStream(img, *fileStream);
            });
    py::class_<juce::Graphics>(m, "Graphics")
            .def(py::init<const juce::Image &>())
            .def(py::init<juce::LowLevelGraphicsContext &>())
            .def("fillAll", py::overload_cast<>(&juce::Graphics::fillAll, py::const_))
            .def("fillAll", py::overload_cast<juce::Colour>(&juce::Graphics::fillAll, py::const_));
    py::class_<juce::Colour>(m, "Colour")
            .def(py::init<uint8_t, uint8_t, uint8_t, uint8_t>());
}
