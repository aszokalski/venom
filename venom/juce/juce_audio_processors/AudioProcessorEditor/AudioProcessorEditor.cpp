//
// Created by Adam Szokalski on 03/01/2024.
//

#include "AudioProcessorEditor.h"
#include <juce_audio_processors/juce_audio_processors.h>

class PyAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PyAudioProcessorEditor(juce::AudioProcessor &p) : juce::AudioProcessorEditor(p) {}
    explicit PyAudioProcessorEditor(juce::AudioProcessor *p) : juce::AudioProcessorEditor(p) {}

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
    py::class_<juce::AudioProcessorEditor, PyAudioProcessorEditor>(m, "AudioProcessorEditor")
    .def(py::init([](juce::AudioProcessor &p)
                  { return new PyAudioProcessorEditor(p); }))
    .def(py::init([](juce::AudioProcessor *p)
                  { return new PyAudioProcessorEditor(p); }))
    .def("resized", [](juce::AudioProcessorEditor &self)
         { return self.resized(); })
    .def("paint", [](juce::AudioProcessorEditor &self, juce::Graphics &g)
         { return self.paint(g); });
}
