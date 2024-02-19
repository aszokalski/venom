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
        auto executable_path = py::module::import("sys").attr("executable").cast<std::string>();
        // get parent directory
        std::string parent_directory = executable_path.substr(0, executable_path.find_last_of("/\\"));
        // add ../Resources/site-packages to parent directory
        std::string site_packages_path = parent_directory + "/../Resources/site-packages";
        // add to python path
        py::module::import("sys").attr("path").attr("append")(site_packages_path);
//        print python path
        py::print(py::module::import("sys").attr("path"));
        // print executable path
        py::print(py::module::import("sys").attr("executable"));

        try{
            this->altered_module = py::module_::import("PyAudioProcessor");

            this->altered_class_instance = this->altered_module.attr("PyAudioProcessor")();
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    }

    ~PyAudioProcessor() override = default;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        try{
            this->altered_class_instance.attr("prepareToPlay")(sampleRate, samplesPerBlock);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void releaseResources() override
    {
        try {
            this->altered_class_instance.attr("releaseResources")();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override
    {
        try{
            return this->altered_class_instance.attr("isBusesLayoutSupported")(layouts).cast<bool>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override
    {
        try{
            this->altered_class_instance.attr("processBlock")(buffer, midiMessages);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    juce::AudioProcessorEditor *createEditor() override
    {
        try{
            return this->altered_class_instance.attr("createEditor")().cast<juce::AudioProcessorEditor *>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return nullptr;
        }
    }

    bool hasEditor() const override
    {
        try{
            return this->altered_class_instance.attr("hasEditor")().cast<bool>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    const juce::String getName() const override
    {
        try{
            return this->altered_class_instance.attr("getName")().cast<juce::String>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return juce::String();
        }
    }

    bool acceptsMidi() const override
    {
        try{
            return this->altered_class_instance.attr("acceptsMidi")().cast<bool>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    bool producesMidi() const override
    {
        try{
            return this->altered_class_instance.attr("producesMidi")().cast<bool>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    bool isMidiEffect() const override
    {
        try{
            return this->altered_class_instance.attr("isMidiEffect")().cast<bool>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    double getTailLengthSeconds() const override
    {
        try{
            return this->altered_class_instance.attr("getTailLengthSeconds")().cast<double>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return 0.0;
        }
    }

    int getNumPrograms() override
    {
        try{
            return this->altered_class_instance.attr("getNumPrograms")().cast<int>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }

    int getCurrentProgram() override
    {
        try{
            return this->altered_class_instance.attr("getCurrentProgram")().cast<int>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }

    void setCurrentProgram(int index) override
    {
        try{
            this->altered_class_instance.attr("setCurrentProgram")(index);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    const juce::String getProgramName(int index) override
    {
        try{
            return this->altered_class_instance.attr("getProgramName")(index).cast<juce::String>();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return juce::String();
        }
    }

    void changeProgramName(int index, const juce::String &newName) override
    {
        try{
            this->altered_class_instance.attr("changeProgramName")(index, newName);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void getStateInformation(juce::MemoryBlock &destData) override {
        try{
            this->altered_class_instance.attr("getStateInformation")(destData);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void setStateInformation(const void *data, int sizeInBytes) override {
        try{
            this->altered_class_instance.attr("setStateInformation")(data, sizeInBytes);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
};
