#include "AudioProcessor.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <pybind11/numpy.h>

class PyAudioProcessor : public juce::AudioProcessor
{
public:
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
            void,
            juce::AudioProcessor,
            releaseResources,
            
        );
    }

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override
    {
        PYBIND11_OVERRIDE(
            bool,
            juce::AudioProcessor,
            isBusesLayoutSupported,
            layouts
        );
    }

    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,
            juce::AudioProcessor,
            processBlock,
            buffer, midiMessages
        );
    }

    using juce::AudioProcessor::processBlock;

    juce::AudioProcessorEditor *createEditor() override
    {
        PYBIND11_OVERRIDE_PURE(
            juce::AudioProcessorEditor *,
            juce::AudioProcessor,
            createEditor,
            );
    }

    bool hasEditor() const override
    {
        PYBIND11_OVERRIDE_PURE(
            bool,
            juce::AudioProcessor,
            hasEditor,
            );
    }

    const juce::String getName() const override
    {
        PYBIND11_OVERRIDE_PURE(
            juce::String,
            juce::AudioProcessor,
            getName,
        );
    }

    bool acceptsMidi() const override
    {
        PYBIND11_OVERRIDE_PURE(
            bool,
            juce::AudioProcessor,
            acceptsMidi,
            );
    }

    bool producesMidi() const override
    {
        PYBIND11_OVERRIDE_PURE(
            bool,
            juce::AudioProcessor,
            producesMidi,
            );
    }


    bool isMidiEffect() const override
    {
        PYBIND11_OVERRIDE(
            bool,
            juce::AudioProcessor,
            isMidiEffect,
            );
    }

    double getTailLengthSeconds() const override
    {
        PYBIND11_OVERRIDE_PURE(
            double,
            juce::AudioProcessor,
            getTailLengthSeconds,
            );
    }

    int getNumPrograms() override
    {
        PYBIND11_OVERRIDE_PURE(
            int,
            juce::AudioProcessor,
            getNumPrograms,
            );
    }

    int getCurrentProgram() override
    {
        PYBIND11_OVERRIDE_PURE(
            int,
            juce::AudioProcessor,
            getCurrentProgram,
            );
    }

    void setCurrentProgram(int index) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,
            juce::AudioProcessor,
            setCurrentProgram,
            index);
    }

    const juce::String getProgramName(int index) override
    {
        PYBIND11_OVERRIDE_PURE(
            juce::String,
            juce::AudioProcessor,
            getProgramName,
            index);
    }

    void changeProgramName(int index, const juce::String &newName) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,
            juce::AudioProcessor,
            changeProgramName,
            index,
            newName);
    }

    void getStateInformation(juce::MemoryBlock &destData) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,
            juce::AudioProcessor,
            getStateInformation,
            destData);
    }

    void setStateInformation(const void *data, int sizeInBytes) override
    {
        PYBIND11_OVERRIDE_PURE(
            void,
            juce::AudioProcessor,
            setStateInformation,
            data,
            sizeInBytes);
    }
};

//template <class T> struct PyArrayView
//{
//    PyArrayView() = default;
//
//    PyArrayView (T* values, size_t numValues) noexcept
//        : values (values)
//          , numValues (numValues)
//    {
//    }
//
//    T* data() noexcept
//    {
//        return values;
//    }
//
//    template <class U = T>
//    auto data() const noexcept -> std::enable_if_t<! std::is_const_v<U>, const T*>
//    {
//        return values;
//    }
//
//    size_t size() const noexcept
//    {
//        return numValues;
//    }
//
//  private:
//    T* values = nullptr;
//    size_t numValues = 0;
//};

void init_AudioProcessor(py::module& m) {
        py::class_<juce::AudioProcessor, std::shared_ptr<juce::AudioProcessor>, PyAudioProcessor>(m, "AudioProcessor", py::dynamic_attr())
        .def(py::init([]() -> PyAudioProcessor* {

            juce::ScopedJuceInitialiser_GUI libraryInitialiser;
            auto createEditor = [](void* userData) -> void* {
              return new PyAudioProcessor();
            };
            if (juce::MessageManager::getInstanceWithoutCreating()->isThisTheMessageThread()) {
              return static_cast<PyAudioProcessor*>(createEditor(nullptr));
            } else {
              return static_cast<PyAudioProcessor*>(juce::MessageManager::getInstanceWithoutCreating()
                                                         ->callFunctionOnMessageThread(createEditor, nullptr));
            }
        }))
        .def("getName", [](juce::AudioProcessor &self)
             { return self.getName(); })
        .def("prepareToPlay", [](juce::AudioProcessor &self, double sampleRate, int samplesPerBlock)
             { self.prepareToPlay(sampleRate, samplesPerBlock); })
        .def("releaseResources", [](juce::AudioProcessor &self)
             { self.releaseResources(); })
        .def("isBusesLayoutSupported", [](juce::AudioProcessor &self, const juce::AudioProcessor::BusesLayout &layouts)
             { return dynamic_cast<PyAudioProcessor&>(self).isBusesLayoutSupported(layouts); })
        .def("processBlock", [](juce::AudioProcessor &self, juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
             { self.processBlock(buffer, midiMessages); })
        .def("createEditor", [](juce::AudioProcessor &self)
             {
               return self.createEditor(); })
        .def("hasEditor", [](juce::AudioProcessor &self)
             { return self.hasEditor(); })
        .def("acceptsMidi", [](juce::AudioProcessor &self)
             { return self.acceptsMidi(); })
        .def("producesMidi", [](juce::AudioProcessor &self)
             { return self.producesMidi(); })
        .def("isMidiEffect", [](juce::AudioProcessor &self)
             { return self.isMidiEffect(); })
        .def("getTailLengthSeconds", [](juce::AudioProcessor &self)
             { return self.getTailLengthSeconds(); })
        .def("getNumPrograms", [](juce::AudioProcessor &self)
             { return self.getNumPrograms(); })
        .def("getCurrentProgram", [](juce::AudioProcessor &self)
             { return self.getCurrentProgram(); })
        .def("setCurrentProgram", [](juce::AudioProcessor &self, int index)
             { self.setCurrentProgram(index); })
        .def("getProgramName", [](juce::AudioProcessor &self, int index)
             { return self.getProgramName(index); })
        .def("changeProgramName", [](juce::AudioProcessor &self, int index, const juce::String &newName)
             { self.changeProgramName(index, newName); })
        .def("getStateInformation", [](juce::AudioProcessor &self, juce::MemoryBlock &destData)
             { self.getStateInformation(destData); })
        .def("setStateInformation", [](juce::AudioProcessor &self, const void *data, int sizeInBytes)
             { self.setStateInformation(data, sizeInBytes); });

        using namespace py::literals;
        py::class_<juce::AudioBuffer<float>> (m, "AudioBuffer", py::buffer_protocol())
            .def (py::init<>())
            .def (py::init<int, int>(), "numChannels"_a, "numSamples"_a)
            .def ("getNumChannels", &juce::AudioBuffer<float>::getNumChannels)
            .def ("getNumSamples", &juce::AudioBuffer<float>::getNumSamples)
            .def("getWritePointer", [](juce::AudioBuffer<float>& self, int channelNumber) {
                return py::array_t<float>(
                        {self.getNumSamples()},
                        {sizeof(float)},
                        self.getWritePointer(channelNumber),
                        py::cast(&self)
                );
            }, py::arg("channelNumber"))
            .def("clear", py::overload_cast<>(&juce::AudioBuffer<float>::clear));
//
//        py::class_<PyArrayView<float>> classFloatArrayView (m, "FloatArrayView", py::buffer_protocol());
//
//        classFloatArrayView
//            .def ("__getitem__", [](PyArrayView<float>& self, size_t index)
//                 {
//                   if (self.data() == nullptr || index >= self.size())
//                     pybind11::pybind11_fail ("Out of bound access of array data");
//
//                   return *(self.data() + index);
//                 })
//            .def ("__setitem__", [](PyArrayView<float>& self, size_t index, float value)
//                 {
//                   if (index >= self.size())
//                     pybind11::pybind11_fail ("Out of bound access of channel data");
//
//                   *(self.data() + index) = value;
//                 })
//            .def ("__len__", &PyArrayView<float>::size)
//            .def ("__iter__", [](PyArrayView<float>& self)
//                 {
//                   if (self.data() == nullptr)
//                     pybind11::pybind11_fail ("Invalid empty array");
//
//                   return py::make_iterator (self.data(), self.data() + self.size());
//                 })
//            .def_buffer ([](PyArrayView<float>& self) -> py::buffer_info
//                        {
//                          return py::buffer_info (self.data(), static_cast<ssize_t> (self.size()), false);
//                        })
//            ;

        py::class_<juce::MidiBuffer>(m, "MidiBuffer")
            .def(py::init<>());

        py::class_<juce::String>(m, "String")
            .def(py::init<>())
            .def(py::init([](const char* text)
                          { return new juce::String(text); }));

        py::class_<juce::MemoryBlock>(m, "MemoryBlock")
            .def(py::init<>());
}
