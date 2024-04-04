//
// Created by Adam Szokalski on 03/01/2024.
//

#include "AudioProcessorEditor.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class PyAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PyAudioProcessorEditor(juce::AudioProcessor &p) : juce::AudioProcessorEditor(p) {
      // In juce objects that are associated with UI need to be called on main Message thread
      JUCE_ASSERT_MESSAGE_MANAGER_IS_LOCKED
    }
    explicit PyAudioProcessorEditor(juce::AudioProcessor *p) : juce::AudioProcessorEditor(p) {
      // In juce objects that are associated with UI need to be called on main Message thread
      JUCE_ASSERT_MESSAGE_MANAGER_IS_LOCKED
    }

    void paint(juce::Graphics &g) override
    {
        PYBIND11_OVERRIDE(
            void,
            juce::AudioProcessorEditor, /* Parent class */
            paint,                      /* Name of function in C++ (must match Python name) */
            g                           /* Argument(s) */
        );
    }

    void resized() override
    {
        PYBIND11_OVERRIDE(
            void,                       /* Return type */
            juce::AudioProcessorEditor, /* Parent class */
            resized,                    /* Name of function in C++ (must match Python name) */
        );
    }
};

void init_AudioProcessorEditor(py::module& m) {
    py::class_<juce::AudioProcessorEditor, std::shared_ptr<juce::AudioProcessorEditor>, PyAudioProcessorEditor>(m, "AudioProcessorEditor")
        .def(py::init([](juce::AudioProcessor &p){
            juce::ScopedJuceInitialiser_GUI libraryInitialiser;
            auto createEditor = [](void* userData) -> void* {
              auto* processor = static_cast<juce::AudioProcessor*>(userData);
              return new PyAudioProcessorEditor(*processor);
            };
            if (juce::MessageManager::getInstance()->isThisTheMessageThread()) {
              return static_cast<PyAudioProcessorEditor*>(createEditor(&p));
            } else {
              return static_cast<PyAudioProcessorEditor*>(juce::MessageManager::getInstance()
                                                               ->callFunctionOnMessageThread(createEditor, &p));
            }
        }))
    .def(py::init([](juce::AudioProcessor *p)
                  { return new PyAudioProcessorEditor(p); }))
    .def("resized", [](juce::AudioProcessorEditor &self)
         { return self.resized(); })
    .def("paint", [](juce::AudioProcessorEditor &self, juce::Graphics &g)
         { return self.paint(g); })
    .def("getAudioProcessor", [](juce::AudioProcessorEditor &self)
         { return self.getAudioProcessor(); })
    .def("addAndMakeVisible", [](juce::AudioProcessorEditor &self, juce::Component& child, int zOrder = -1)
         { self.addAndMakeVisible(child, zOrder); })
    .def("setSize", [](juce::AudioProcessorEditor &self, int newWidth, int newHeight)
         { self.setSize(newWidth, newHeight); });
}
