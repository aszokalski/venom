#include "PyAudioProcessor.h"
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/embed.h>
namespace py = pybind11;
const py::scoped_interpreter python{};

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    auto path = py::module_::import("sys").attr("path");
    path.attr("append")(MODULES_DIR);
    py::eval_file(PYTHON_STUBS_FILE);
    auto obj = std::make_unique<py::object>(py::eval("PyAudioProcessor()"));
    return new PyAudioProcessor(std::move(obj));
}