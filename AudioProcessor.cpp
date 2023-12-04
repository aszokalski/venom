#include <juce_audio_processors/juce_audio_processors.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(juce, m)
{
    py::class_<juce::AudioProcessor>(m, "AudioProcessor")
        .def(py::init());
    // .def("add", &MyClass::add)
    // .def("sub", &MyClass::sub);
}
