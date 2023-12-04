#include "MyClass.h"
#include <pybind11/embed.h> // everything needed for embedding

namespace py = pybind11;

class MyClassAltered : public MyClass {
    private:
        py::module_ altered_module;
        py::object altered_class_instance;

    public:
        MyClassAltered() {
            this->altered_module = py::module_::import("my_altered_class");
            this->altered_class_instance = this->altered_module.attr("MyClassAltered")();
        }

        int add(int a, int b) { return this->altered_class_instance.attr("add")(a, b).cast<int>(); };
};
