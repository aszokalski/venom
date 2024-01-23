#include "AudioProcessorParameter.h"
#include <juce_audio_processors/juce_audio_processors.h>

class PyAudioProcessorParameter : public juce::AudioProcessorParameter
{
public:
    /* Inherit the constructors */
    using juce::AudioProcessorParameter::AudioProcessorParameter;

    float getValue() const override {
        PYBIND11_OVERRIDE_PURE(
            float,                       /* Return type */
            juce::AudioProcessorParameter,       /* Parent class */
            getValue,              /* Name of function in C++ (must match Python name) */
        );
    }

    void setValue(float newValue) override {
        PYBIND11_OVERRIDE_PURE(
            void,                       /* Return type */
            juce::AudioProcessorParameter,       /* Parent class */
            setValue,               /* Name of function in C++ (must match Python name) */
            newValue                /* Argument(s) */
        );
    }

    float getDefaultValue() const override {
        PYBIND11_OVERRIDE_PURE(
            float,                       /* Return type */
            juce::AudioProcessorParameter,       /* Parent class */
            getDefaultValue,              /* Name of function in C++ (must match Python name) */
        );
    }

    juce::String getName (int maximumStringLength) const override {
        PYBIND11_OVERRIDE(
            juce::String,               /* Return type */
            juce::AudioProcessorParameter, /* Parent class */
            getName,                      /* Name of function in C++ (must match Python name) */
            maximumStringLength                           /* Argument(s) */
        );
    }

    juce::String getLabel () const override {
        PYBIND11_OVERRIDE(
            juce::String,               /* Return type */
            juce::AudioProcessorParameter, /* Parent class */
            getLabel,                      /* Name of function in C++ (must match Python name) */
        );
    }

    float getValueForText (const juce::String& text) const override {
        PYBIND11_OVERRIDE(
            float,               /* Return type */
            juce::AudioProcessorParameter, /* Parent class */
            getValueForText,                      /* Name of function in C++ (must match Python name) */
            text                           /* Argument(s) */
        );
    }

};

void init_AudioProcessorParameter(py::module& m) {
        py::class_<juce::AudioProcessorParameter, PyAudioProcessorParameter>(m, "AudioProcessorParameter", py::dynamic_attr())
        .def(py::init<>())
        .def("getValue", [](juce::AudioProcessorParameter &self)
            { return self.getValue(); })
        .def("setValue", [](juce::AudioProcessorParameter &self, float newValue)
            { self.setValue(newValue); })
        .def("getDefaultValue", [](juce::AudioProcessorParameter &self)
            { return self.getDefaultValue(); })
        .def("getName", [](juce::AudioProcessorParameter &self, int maximumStringLength)
            { return self.getName(maximumStringLength); })
        .def("getLabel", [](juce::AudioProcessorParameter &self)
            { return self.getLabel(); })
        .def("getValueForText", [](juce::AudioProcessorParameter &self, const juce::String& text)
            { return self.getValueForText(text); });
}
