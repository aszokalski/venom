#include "MidiMessage.h"

void init_MidiMessage(py::module &m) {
    py::class_<juce::MidiMessage>(m, "MidiMessage")
        .def(py::init<>())
        .def(py::init<int, int, int, double>())
        .def(py::init<int, int, double>())
        .def(py::init<int, double>())
        
        .def("getRawData", &juce::MidiMessage::getRawData)
        .def("getRawDataSize", &juce::MidiMessage::getRawDataSize)
        .def("getTimeStamp", &juce::MidiMessage::getTimeStamp)
        .def("setTimeStamp", &juce::MidiMessage::setTimeStamp)
        
        .def("getChannel", &juce::MidiMessage::getChannel)
        .def("isForChannel", &juce::MidiMessage::isForChannel)
        .def("setChannel", &juce::MidiMessage::setChannel)
        
        .def("isNoteOn", &juce::MidiMessage::isNoteOn)
        .def("isNoteOff", &juce::MidiMessage::isNoteOff)
        .def("isNoteOnOrOff", &juce::MidiMessage::isNoteOnOrOff)
        .def("getNoteNumber", &juce::MidiMessage::getNoteNumber)
        .def("setNoteNumber", &juce::MidiMessage::setNoteNumber)
        .def("getVelocity", &juce::MidiMessage::getVelocity)
        .def("getFloatVelocity", &juce::MidiMessage::getFloatVelocity)
        .def("setVelocity", &juce::MidiMessage::setVelocity)
        
        .def_static("noteOn", py::overload_cast<int, int, float>(&juce::MidiMessage::noteOn))
        .def_static("noteOff", py::overload_cast<int, int, float>(&juce::MidiMessage::noteOff))
        .def_static("controllerEvent", &juce::MidiMessage::controllerEvent)
        .def_static("programChange", &juce::MidiMessage::programChange)
        .def_static("pitchWheel", &juce::MidiMessage::pitchWheel);
}