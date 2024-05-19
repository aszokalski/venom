#include "PyAudioProcessor.h"
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/embed.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <dlfcn.h>
namespace py = pybind11;
static std::unique_ptr<py::scoped_interpreter> interpreter;

void set_python_env() {
    const char* venv_path = "/home/mszawerd/venom/venom/venv";
    const char* python_bin_path = "/home/mszawerd/venom/venom/venv/bin";
    setenv("VIRTUAL_ENV", venv_path, 1);
    setenv("PATH", (std::string(python_bin_path) + ":" + getenv("PATH")).c_str(), 1);  // Ensure the virtual environment's bin directory is first in the PATH
//    setenv("PYTHONHOME", venv_path, 1);
//    setenv("PYTHONPATH", "/home/mszawerd/venom/venom/venv/lib/python3.11/site-packages", 1);
//    setenv("LD_LIBRARY_PATH", "/home/mszawerd/venom/venom/venv/lib:/usr/lib/x86_64-linux-gnu", 1);  // Include system library path
}

void activate_virtualenv(const std::string& venv_path) {
    // Set VIRTUAL_ENV environment variable
    setenv("VIRTUAL_ENV", venv_path.c_str(), 1);

    // Modify PATH environment variable to include virtual environment's bin directory
    std::string path = getenv("PATH");
    path = venv_path + "/bin:" + path;
    setenv("PATH", path.c_str(), 1);

    // Optionally, set PYTHONHOME to the virtual environment (needed in some cases)
    // setenv("PYTHONHOME", venv_path.c_str(), 1);
}

void preload_shared_libraries() {
    const char* py_core_lib = "/Users/marcinjarczewski/.pyenv/versions/3.11.3/lib/libpython3.11.dylib";
    void* handle = dlopen(py_core_lib, RTLD_LAZY | RTLD_GLOBAL);
    if (!handle) {
        std::cerr << "Error preloading shared library: " << dlerror() << std::endl;
    } else {
        std::cout << "Successfully preloaded shared library: " << py_core_lib << std::endl;
    }
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    preload_shared_libraries();
    activate_virtualenv("/Users/marcinjarczewski/Documents/studia/sem6/venom/venv");
    std::cout<<getenv("PATH")<<std::endl;
    std::cout << "ENTER12" << std::endl;

    if (!interpreter) {
        interpreter = std::make_unique<py::scoped_interpreter>();
    }

//    set_python_env();
//    chdir("/tmp");
    std::cout << "PY CREATED" << std::endl;

    auto path = py::module_::import("sys").attr("path");
    path.attr("append")("/Users/marcinjarczewski/Documents/studia/sem6/venom/venv/lib/python3.11/site-packages");
    py::module_::import("sys").attr("executable") = "/Users/marcinjarczewski/Documents/studia/sem6/venom/venv/bin/python";
    py::module os = py::module::import("os");
    py::module sys = py::module::import("sys");
    std::cout << "Current working directory: " << py::module_::import("os").attr("getcwd")().cast<std::string>() << std::endl;
    std::cout << "Python executable: " << py::module_::import("sys").attr("executable").cast<std::string>() << std::endl;
    std::cout << "Python version: " << sys.attr("version").cast<std::string>() << std::endl;
    std::cout << "LD_LIBRARY_PATH: " << (std::getenv("LD_LIBRARY_PATH") ? std::getenv("LD_LIBRARY_PATH") : "Not set") << std::endl;
    std::cout << "PYTHONPATH: " << (std::getenv("PYTHONPATH") ? std::getenv("PYTHONPATH") : "Not set") << std::endl;
//
//
//
//
    py::list sys_path = sys.attr("path");
    std::cout << "sys.path:" << std::endl;
    for (auto item : sys_path) {
        std::cout << "  " << item.cast<std::string>() << std::endl;
    }
//
//    py::print(os.attr("environ"));

    try {
        auto numpy = py::module_::import("numpy");
        py::eval_file(PLUGIN_FILE);
        std::cout << "PY PO NUMPY" << std::endl;

        auto obj = std::make_unique<py::object>(py::eval("PyAudioProcessor()"));
        std::cout << "PY PO AUDIOPROCESSOR" << std::endl;

        return new PyAudioProcessor(std::move(obj));
    } catch (const py::error_already_set &e) {
        std::cerr << "Python error: " << e.what() << std::endl;
        return nullptr;
    } catch (const std::exception &e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
        return nullptr;
    }
//    std::cout<<py::module_::import("os").attr("getcwd")().cast<std::string>()<<std::endl;
//    std::cout<<py::module_::import("sys").attr("executable").cast<std::string>()<<std::endl;
}