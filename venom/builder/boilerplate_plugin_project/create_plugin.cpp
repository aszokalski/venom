//
// Created by Adam Szokalski on 10/05/2023.
//
#include <JuceHeader.h>
#include "PyAudioProcessor.h"
#include <pybind11/embed.h> // everything needed for embedding
#define PYBIND11_DETAILED_ERROR_MESSAGES
namespace py = pybind11;

// Global variable to hold the Python interpreter
std::unique_ptr<py::scoped_interpreter> guard;

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    // Initialize the Python interpreter if it has not been initialized
    if (!guard)
    {
        guard = std::make_unique<py::scoped_interpreter>();
    }
    return new PyAudioProcessor();
}