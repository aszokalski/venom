#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h> // for juce::AudioBuffer
#include <juce_audio_devices/juce_audio_devices.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class PyAudioProcessorEditor : protected juce::AudioProcessorEditor {
public:
    /* Inherit the constructors */
    explicit PyAudioProcessorEditor(juce::AudioProcessor& p) : juce::AudioProcessorEditor(p) {}
    explicit PyAudioProcessorEditor(juce::AudioProcessor* p) : juce::AudioProcessorEditor(p) {}

    void paint(juce::Graphics &g) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,               /* Return type */
            juce::AudioProcessorEditor, /* Parent class */
            paint,              /* Name of function in C++ (must match Python name) */
            g                   /* Argument(s) */
        );
    }

    void resized() override
    {
        PYBIND11_OVERRIDE_PURE(
            void,               /* Return type */
            juce::AudioProcessorEditor, /* Parent class */
            resized,            /* Name of function in C++ (must match Python name) */
        );
    }
};

class PyAudioProcessor : protected juce::AudioProcessor
{
public:
    /* Inherit the constructors */
    using juce::AudioProcessor::AudioProcessor;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,                       /* Return type */
            juce::AudioProcessor,       /* Parent class */
            prepareToPlay,              /* Name of function in C++ (must match Python name) */
            sampleRate, samplesPerBlock /* Argument(s) */
        );
    }

    void releaseResources() override
    {
        PYBIND11_OVERRIDE_PURE(
            void,                 /* Return type */
            juce::AudioProcessor, /* Parent class */
            releaseResources      /* Name of function in C++ (must match Python name) */
        );
    }

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override
    {
        PYBIND11_OVERRIDE_PURE(
            bool,                   /* Return type */
            juce::AudioProcessor,   /* Parent class */
            isBusesLayoutSupported, /* Name of function in C++ (must match Python name) */
            layouts                 /* Argument(s) */
        );
    }

    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,                 /* Return type */
            juce::AudioProcessor, /* Parent class */
            processBlock,         /* Name of function in C++ (must match Python name) */
            buffer, midiMessages  /* Argument(s) */
        );
    }

    using juce::AudioProcessor::processBlock;

    juce::AudioProcessorEditor* createEditor() override{
        PYBIND11_OVERLOAD_PURE(
                juce::AudioProcessorEditor*,
                juce::AudioProcessor,
                createEditor
        );
    }

    bool hasEditor() const override
    {
        PYBIND11_OVERRIDE_PURE(
            bool,
            juce::AudioProcessor,
            hasEditor);
    }

    const juce::String getName() const override
    {
        PYBIND11_OVERRIDE_PURE(
                juce::String,         /* Return type */
                juce::AudioProcessor, /* Parent class */
                getName               /* Name of function in C++ (must match Python name) */
        );
    }


    bool acceptsMidi() const override{
        PYBIND11_OVERRIDE_PURE(
                bool,
                juce::AudioProcessor,
                acceptsMidi
                );
    }

    bool producesMidi() const override{
        PYBIND11_OVERLOAD_PURE(
                bool,
                juce::AudioProcessor,
                producesMidi
                );
    }

    bool isMidiEffect() const override{
        PYBIND11_OVERLOAD_PURE(
                bool,
                juce::AudioProcessor,
                isMidiEffect
                );
    }

    double getTailLengthSeconds() const override{
        PYBIND11_OVERLOAD_PURE(
                double,
                juce::AudioProcessor,
                getTailLengthSeconds
                );
    }

    int getNumPrograms() override{
        PYBIND11_OVERLOAD_PURE(
                int,
                juce::AudioProcessor,
                getNumPrograms
                );
    }

    int getCurrentProgram() override{
        PYBIND11_OVERLOAD_PURE(
                int,
                juce::AudioProcessor,
                getCurrentProgram
                );
    }

    void setCurrentProgram (int index) override{
        PYBIND11_OVERLOAD_PURE(
                void,
                juce::AudioProcessor,
                setCurrentProgram,
                index
                );
    }

    const juce::String getProgramName (int index) override{
        PYBIND11_OVERLOAD_PURE(
                juce::String,
                juce::AudioProcessor,
                getProgramName,
                index
                );
    }

    void changeProgramName (int index, const juce::String& newName) override{
        PYBIND11_OVERLOAD_PURE(
                void,
                juce::AudioProcessor,
                changeProgramName,
                index,
                newName
                );
    }

    void getStateInformation (juce::MemoryBlock& destData) override{
        PYBIND11_OVERLOAD_PURE(
                void,
                juce::AudioProcessor,
                getStateInformation,
                destData
                );
    }

    void setStateInformation (const void* data, int sizeInBytes) override{
        PYBIND11_OVERLOAD_PURE(
                void,
                juce::AudioProcessor,
                setStateInformation,
                data,
                sizeInBytes
                );
    }

};

PYBIND11_MODULE(juce, m)
{
     py::class_<juce::AudioBuffer<float>>(m, "AudioBuffer")
         .def(py::init<>());

     py::class_<juce::MidiBuffer>(m, "MidiBuffer")
         .def(py::init<>());

     py::class_<juce::String>(m, "String")
         .def(py::init<>());

     py::class_<juce::MemoryBlock>(m, "MemoryBlock")
         .def(py::init<>());

    py::class_<juce::AudioProcessorEditor, PyAudioProcessorEditor>(m, "AudioProcessorEditor")
            .def(py::init([](juce::AudioProcessor& p) {
                return std::unique_ptr<PyAudioProcessorEditor>(new PyAudioProcessorEditor(p));
            }))
            .def(py::init([](juce::AudioProcessor* p) {
                return std::unique_ptr<PyAudioProcessorEditor>(new PyAudioProcessorEditor(p));
            }))
            .def("resized", &PyAudioProcessorEditor::resized)
            .def("paint", &PyAudioProcessorEditor::paint);

    py::class_<juce::AudioProcessor, PyAudioProcessor>(m, "AudioProcessor", py::dynamic_attr())
        .def(py::init<>())
        .def("getName", &PyAudioProcessor::getName)
        .def("prepareToPlay", &PyAudioProcessor::prepareToPlay)
        .def("releaseResources", &PyAudioProcessor::releaseResources)
        .def("isBusesLayoutSupported", &PyAudioProcessor::isBusesLayoutSupported)
        .def("processBlock", &PyAudioProcessor::processBlock)
        .def("createEditor", &PyAudioProcessor::createEditor)
        .def("hasEditor", &PyAudioProcessor::hasEditor)
        .def("acceptsMidi", &PyAudioProcessor::acceptsMidi)
        .def("producesMidi", &PyAudioProcessor::producesMidi)
        .def("isMidiEffect", &PyAudioProcessor::isMidiEffect)
        .def("getTailLengthSeconds", &PyAudioProcessor::getTailLengthSeconds)
        .def("getNumPrograms", &PyAudioProcessor::getNumPrograms)
        .def("getCurrentProgram", &PyAudioProcessor::getCurrentProgram)
        .def("setCurrentProgram", &PyAudioProcessor::setCurrentProgram)
        .def("getProgramName", &PyAudioProcessor::getProgramName)
        .def("changeProgramName", &PyAudioProcessor::changeProgramName)
        .def("getStateInformation", &PyAudioProcessor::getStateInformation)
        .def("setStateInformation", &PyAudioProcessor::setStateInformation);
}