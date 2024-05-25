#include "PyAudioProcessor.h"
#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <pybind11/embed.h>

#include <cstdlib>
#include <iostream>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace py = pybind11;

// Simulation of bin/activate
void activate_virtualenv(const std::string &venv_path) {
    setenv("VIRTUAL_ENV", venv_path.c_str(), 1);
    setenv("PATH", (venv_path + "/bin:" + getenv("PATH")).c_str(), 1);
    unsetenv("PYTHONHOME");
#if __APPLE__
    setenv("PYTHONPATH", PYTHON_SIDE_PACKAGES, 1);
#endif
    system("hash -r 2> /dev/null");

    spdlog::debug("[OS ENV] PATH: {}", std::getenv("PATH") ? std::getenv("PATH") : "Not set");
    spdlog::debug("[OS ENV] VIRTUAL_ENV: {}", std::getenv("VIRTUAL_ENV") ? std::getenv("VIRTUAL_ENV") : "Not set");
    spdlog::debug("[OS ENV] PYTHON_HOME: {}", std::getenv("PYTHONHOME") ? std::getenv("PYTHONHOME") : "Not set");
}

#ifdef __linux__

#include <dlfcn.h>

void preload_shared_libraries() {
    void *handle = dlopen(PYTHON_SHARED_LIB, RTLD_LAZY | RTLD_GLOBAL);
    if (!handle) {
        spdlog::error("Error preloading shared library: {}", dlerror());
    } else {
        spdlog::debug("Successfully preloaded shared library: {}", PYTHON_SHARED_LIB);
    }
}

#else
void preload_shared_libraries() {
    spdlog::debug("Preloading shared libraries is only supported on Linux.");
}
#endif

struct InitialSetupHelper {
    std::unique_ptr<py::scoped_interpreter> interpreter;

    std::unique_ptr<py::gil_scoped_release> release;

    std::unique_ptr<py::scoped_interpreter> createInterpreter() {
        spdlog::set_level(spdlog::level::debug);
        spdlog::flush_on(spdlog::level::debug);
        activate_virtualenv(VENV_PATH);
        preload_shared_libraries();
        spdlog::debug("[START PY]");
        return std::make_unique<py::scoped_interpreter>();
    }

    InitialSetupHelper() : interpreter(createInterpreter()), release(std::make_unique<py::gil_scoped_release>()) {}

    ~InitialSetupHelper() { spdlog::debug("[END]"); }
};

const static InitialSetupHelper setup_helper;

void log_python_environment() {
    py::module os = py::module::import("os");
    py::module sys = py::module::import("sys");
    spdlog::debug("[PY ENV] CWD: {}", os.attr("getcwd")().cast<std::string>());
    spdlog::debug("[PY ENV] PYEXEC: {}", sys.attr("executable").cast<std::string>());
    spdlog::debug("[PY ENV] PY_VER: {}", sys.attr("version").cast<std::string>());
    spdlog::debug("[PY ENV] SYS_PATH: {}", py::str(sys.attr("path")).cast<std::string>());
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    spdlog::debug("[LET THE BALL ROLLING]");

    try {
        py::gil_scoped_acquire acquire;
        log_python_environment();
        py::eval_file(PLUGIN_FILE);
        return new PyAudioProcessor(std::make_unique<py::object>(py::eval("PyAudioProcessor()")));
    } catch (const py::error_already_set &e) {
        spdlog::error("Error when evaluating provided python file: {}", e.what());
        return nullptr;
    } catch (const std::exception &e) {
        spdlog::error("Error when executing CPP code {}", e.what());
        return nullptr;
    }
}