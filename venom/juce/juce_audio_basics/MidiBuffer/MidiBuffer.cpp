#include "MidiBuffer.h"

void init_MidiBuffer(py::module &m) {
    py::class_<juce::MidiBufferIterator>(m, "MidiBufferIterator")
        .def(py::init<>())
        .def(py::init([](py::bytes data) {
            std::string str = data;
            return juce::MidiBufferIterator(reinterpret_cast<const uint8_t *>(str.data()));
        }))
        .def("__iter__", [](juce::MidiBufferIterator &it) -> juce::MidiBufferIterator & { return it; })
        .def("__next__",
             [](juce::MidiBufferIterator &it) {
                 auto current = *it;
                 ++it;
                 return current;
             })
        .def("__eq__", &juce::MidiBufferIterator::operator==)
        .def("__ne__", &juce::MidiBufferIterator::operator!=);

    py::class_<juce::MidiBuffer>(m, "MidiBuffer")
        .def(py::init<>())
        .def(py::init<const juce::MidiMessage &>())
        .def("clear", py::overload_cast<>(&juce::MidiBuffer::clear))
        .def("clear", py::overload_cast<int, int>(&juce::MidiBuffer::clear))
        .def("isEmpty", &juce::MidiBuffer::isEmpty)
        .def("getNumEvents", &juce::MidiBuffer::getNumEvents)
        .def("addEvent", py::overload_cast<const juce::MidiMessage &, int>(&juce::MidiBuffer::addEvent))
        .def("addEvent",
             [](juce::MidiBuffer &self, py::bytes rawData, int sampleNumber) {
                 std::string data = rawData;
                 return self.addEvent(data.data(), static_cast<int>(data.size()), sampleNumber);
             })
        .def("addEvents", &juce::MidiBuffer::addEvents)
        .def("getFirstEventTime", &juce::MidiBuffer::getFirstEventTime)
        .def("getLastEventTime", &juce::MidiBuffer::getLastEventTime)
        .def("swapWith", &juce::MidiBuffer::swapWith)
        .def("ensureSize", &juce::MidiBuffer::ensureSize)
        .def("begin", &juce::MidiBuffer::begin)
        .def("end", &juce::MidiBuffer::end)
        .def("cbegin", &juce::MidiBuffer::cbegin)
        .def("cend", &juce::MidiBuffer::cend)
        .def("findNextSamplePosition", &juce::MidiBuffer::findNextSamplePosition);
}