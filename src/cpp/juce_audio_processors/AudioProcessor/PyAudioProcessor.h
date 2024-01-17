#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_basics/juce_audio_basics.h" // for juce::AudioBuffer
#include "juce_audio_devices/juce_audio_devices.h"
#include <pybind11/embed.h> // everything needed for embedding

namespace py = pybind11;

// This class links the python class back to the C++ class
class PyAudioProcessor : public juce::AudioProcessor{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PyAudioProcessor)
    py::module_ altered_module;
    py::object altered_class_instance;

public:

    PyAudioProcessor() : juce::AudioProcessor() {
//        print python path
        py::print(py::module::import("sys").attr("path"));
        // print executable path
        py::print(py::module::import("sys").attr("executable"));
        this->altered_module = py::module_::import("PyAudioProcessor");

        this->altered_class_instance = this->altered_module.attr("PyAudioProcessor")();
    }

    ~PyAudioProcessor() override = default;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        this->altered_class_instance.attr("prepareToPlay")(sampleRate, samplesPerBlock);
    }

    void releaseResources() override
    {
        this->altered_class_instance.attr("releaseResources")();
    }

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override
    {
        return this->altered_class_instance.attr("isBusesLayoutSupported")(layouts).cast<bool>();
    }

    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override
    {
        this->altered_class_instance.attr("processBlock")(buffer, midiMessages);
    }

    juce::AudioProcessorEditor *createEditor() override
    {
        return this->altered_class_instance.attr("createEditor")().cast<juce::AudioProcessorEditor *>();
    }

    bool hasEditor() const override
    {
        return this->altered_class_instance.attr("hasEditor")().cast<bool>();
    }

    const juce::String getName() const override
    {
        return this->altered_class_instance.attr("getName")().cast<juce::String>();
    }

    bool acceptsMidi() const override
    {
        return this->altered_class_instance.attr("acceptsMidi")().cast<bool>();
    }

    bool producesMidi() const override
    {
        return this->altered_class_instance.attr("producesMidi")().cast<bool>();
    }

    bool isMidiEffect() const override
    {
        return this->altered_class_instance.attr("isMidiEffect")().cast<bool>();
    }

    double getTailLengthSeconds() const override
    {
        return this->altered_class_instance.attr("getTailLengthSeconds")().cast<double>();
    }

    int getNumPrograms() override
    {
        return this->altered_class_instance.attr("getNumPrograms")().cast<int>();
    }

    int getCurrentProgram() override
    {
        return this->altered_class_instance.attr("getCurrentProgram")().cast<int>();
    }

    void setCurrentProgram(int index) override
    {
        this->altered_class_instance.attr("setCurrentProgram")(index);
    }

    const juce::String getProgramName(int index) override
    {
        return this->altered_class_instance.attr("getProgramName")(index).cast<juce::String>();
    }

    void changeProgramName(int index, const juce::String &newName) override
    {
        this->altered_class_instance.attr("changeProgramName")(index, newName);
    }

    void getStateInformation(juce::MemoryBlock &destData) override {
        this->altered_class_instance.attr("getStateInformation")(destData);
    }

    void setStateInformation(const void *data, int sizeInBytes) override {
        this->altered_class_instance.attr("setStateInformation")(data, sizeInBytes);
    }
};
