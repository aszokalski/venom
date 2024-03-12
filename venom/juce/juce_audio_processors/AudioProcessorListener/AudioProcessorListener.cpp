#include "AudioProcessorListener.h"
#include <juce_audio_processors/juce_audio_processors.h>

class PyAudioProcessorListener : public juce::AudioProcessorListener
{
public:
    /* Inherit the constructors */
    using juce::AudioProcessorListener::AudioProcessorListener;

    void audioProcessorParameterChanged (juce::AudioProcessor* processor,
                                                 int parameterIndex,
                                                 float newValue) override {
        PYBIND11_OVERRIDE_PURE(
            void,                                       /* Return type */
            juce::AudioProcessorListener,               /* Parent class */
            audioProcessorParameterChanged,             /* Name of function in C++ (must match Python name) */
            processor, parameterIndex, newValue         /* Argument(s) */
        );
    }

    void audioProcessorChanged (juce::AudioProcessor* processor, const juce::AudioProcessorListener::ChangeDetails& details) override {
        PYBIND11_OVERRIDE_PURE(
            void,                                       /* Return type */
            juce::AudioProcessorListener,               /* Parent class */
            audioProcessorChanged,             /* Name of function in C++ (must match Python name) */
            processor, details        /* Argument(s) */
        );
    }

};

void init_AudioProcessorListener(py::module& m) {
        py::class_<juce::AudioProcessorListener, PyAudioProcessorListener>(m, "AudioProcessorListener", py::dynamic_attr())
        .def(py::init<>())
        .def("audioProcessorParameterChanged", [](juce::AudioProcessorListener &self, juce::AudioProcessor* processor, int parameterIndex, float newValue)
             { self.audioProcessorParameterChanged(processor, parameterIndex, newValue); })
        .def("audioProcessorChanged", [](juce::AudioProcessorListener &self, juce::AudioProcessor* processor, const juce::AudioProcessorListener::ChangeDetails& details)
             { self.audioProcessorChanged(processor, details); });
}
