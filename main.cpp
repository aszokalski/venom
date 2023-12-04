#include "MyClassAltered.h"
#include <iostream>
#include <pybind11/embed.h> // everything needed for embedding
namespace py = pybind11;

int main() {
    py::scoped_interpreter guard{}; // start the interpreter and keep it alive

    auto my_altered = MyClassAltered();
    std::cout << my_altered.add(1, 2) << std::endl;
    std::cout << my_altered.sub(1, 2) << std::endl;
}
