#include "AudioSource.h"

class PyAudioSource : public juce::AudioSource {
   public:
    using juce::AudioSource::AudioSource;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override {
        PYBIND11_OVERLOAD_PURE(void, juce::AudioSource, getNextAudioBlock, bufferToFill);
    }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {
        PYBIND11_OVERLOAD_PURE(void, juce::AudioSource, prepareToPlay, samplesPerBlockExpected, sampleRate);
    }

    void releaseResources() override { PYBIND11_OVERLOAD_PURE(void, juce::AudioSource, releaseResources, ); }
};

void init_AudioSource(py::module &m) {
    py::class_<juce::AudioSource, PyAudioSource>(m, "AudioSource")
        .def(py::init<>())
        .def("getNextAudioBlock", &juce::AudioSource::getNextAudioBlock)
        .def("prepareToPlay", &juce::AudioSource::prepareToPlay)
        .def("releaseResources", &juce::AudioSource::releaseResources);

    using namespace py::literals;
    py::class_<juce::AudioSourceChannelInfo>(m, "AudioSourceChannelInfo")
        .def(py::init<>())
        .def(py::init<int, int>(), "numChannels"_a, "numSamples"_a)
        .def("getNumChannels", &juce::AudioBuffer<float>::getNumChannels)
        .def("getNumSamples", &juce::AudioBuffer<float>::getNumSamples)
        .def(
            "getWritePointer",
            [](juce::AudioBuffer<float> &self, int channelNumber) {
                return py::array_t<float>({self.getNumSamples()}, {sizeof(float)}, self.getWritePointer(channelNumber),
                                          py::cast(&self));
            },
            py::arg("channelNumber"))
        .def("clear", py::overload_cast<>(&juce::AudioBuffer<float>::clear));
}
