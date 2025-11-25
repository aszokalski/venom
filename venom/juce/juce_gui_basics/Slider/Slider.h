#ifndef SLIDER_H
#define SLIDER_H

#include <pybind11/pybind11.h>
#include "../../helpers/include/initializer/Initializer.h"
#include "MessageManagerHelper.h"

namespace py = pybind11;

void init_Slider(py::module &m);

#endif //SLIDER_H

