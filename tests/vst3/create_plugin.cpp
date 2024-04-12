//
// Created by Adam Szokalski on 10/05/2023.
//
//#include <JuceHeader.h>
#include "PyAudioProcessor.h"
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/embed.h> // everything needed for embedding

namespace py = pybind11;
//
//// Global variable to hold the Python interpreter
std::unique_ptr<py::scoped_interpreter> python;
//
////==============================================================================
//// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    // Initialize the Python interpreter if it has not been initialized
    if(!python){
      python = std::make_unique<py::scoped_interpreter>();
    }
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(ABSOLUTE_BINDINGS_PATH);
    py::eval_file(std::string(ABSOLUTE_STUBS_PATH) + "/audio_processors_stubs.py");

    auto obj = std::make_unique<py::object>(py::eval("PyAudioProcessor()"));
    return new PyAudioProcessor(std::move(obj));
}