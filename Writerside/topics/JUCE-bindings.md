# JUCE bindings

## Module structure
All bindings must be organized in a specific way. The structure is as follows:
```

juce/                          
├── [juce_module_name]/
│   ├── [juce_class_name]/
│   │   ├── [juce_class_name].h
│   │   ├── [juce_class_name].cpp
│   ├── [juce_module_name].h
│   ├── [juce_module_name].cpp
│   ├── ...
├── utils/                      [module for partial module bindings]
├── juce.cpp                    [pybind11 module] 
├── CMakeLists.txt              [Build system]
├── __init__.py                
...
```

## Developing bindings
JUCE is divided into modules. Each module contains classes and functions.

### Choosing the module
First, you need to choose the module you want to bind. Modules should be prioritized based on the needs of the project - if you only need a few helper classes from a module, you can bind them in `utils/` module.

If you need to bind the whole module, you should create a new module for it. You only need to bind classes that are crucial for the module to work.

Here is a [list of all JUCE modules](https://github.com/juce-framework/JUCE/tree/master/modules)
The ones that need to be bound first are mentioned in the [Roadmap](Roadmap.md).

### Creating a new module
1. Create a new directory in `juce/` with the name of the module.
2. Create the following files:
    - `juce_module_name.h` - the main header file for the module
    - `juce_module_name.cpp` - the main source file for the module

<tabs>
    <tab title="juce_module_name.h">
        <code-block lang="C++">
    <![CDATA[
#ifndef JUCE_MODULE_NAME_H
#define JUCE_MODULE_NAME_H

#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_juce_module_name(py::module &super);

#endif //JUCE_MODULE_NAME_H
]]>
</code-block>
    </tab>
    <tab title="juce_module_name.cpp">
        <code-block lang="C++">
    <![CDATA[
#include "juce_module_name.h"

// #include "juce_class_name/juce_class_name.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_juce_gui_basics(py::module &super) {
   auto m = super.def_submodule("juce_module_name");

   // for every class in the module:
   // init_Class_Name(m);
}

]]>
</code-block>
    </tab>
</tabs>

<note title="Suggestion">
This could be automated with a script.
</note>

3. Init the module in `juce.cpp`:
```C++
#include <pybind11/pybind11.h>

// ADD BEGIN
#include "juce_module_name/juce_module_name.h"
// ADD END
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "utils/utils.h"
#define PYBIND11_DETAILED_ERROR_MESSAGES


namespace py = pybind11;



PYBIND11_MODULE(juce, m)
{
    // ADD BEGIN
    init_juce_module_name(m);
    // ADD END
    init_juce_audio_processors(m);
    init_juce_gui_basics(m);
    init_utils(m);
}
```

4. Add the files to `CMakeLists.txt`

### Binding classes
1. Create a new directory in the module directory with the name of the class.
2. Create the following files:
    - `juce_class_name.h` - the header file for the class
    - `juce_class_name.cpp` - the source file for the class

<tabs>
    <tab title="juce_class_name.h">
        <code-block lang="C++">
    <![CDATA[
#ifndef CLASS_NAME_H
#define CLASS_NAME_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_ClassName(py::module &m);

#endif //CLASS_NAME_H
]]>
</code-block>
    </tab>
    <tab title="juce_class_name.cpp">
        <code-block lang="C++">
    <![CDATA[
#include "juce_class_name.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_ClassName(py::module &m) {
   // Your bindings here
    py::class_<ClassName>(m, "ClassName")
        .def(py::init<>())
        .def("method", &ClassName::method);
}

]]>
</code-block>
    </tab>
</tabs>

### Binding functions
There are not too many free functions in JUCE, but if you need to bind one, you can do it in the module file. If there are many functions, you can create a new directory for them.

```C++
#include "juce_module_name.h"

void init_juce_module_name(py::module &m) {
    m.def("function", &function);
}
```

## How to bind?
You can find the documentation for pybind11 [here](https://pybind11.readthedocs.io/en/stable/).
You can also explore the existing bindings in the `juce/` directory.

Most classes have virtual methods, so you need to bind them as well. There is a whole chapter dedicated to this kind of binding [here](https://pybind11.readthedocs.io/en/stable/advanced/classes.html)

You can see how it's done in `juce_audio_processors/juce_audio_processors.cpp`.

<note>
When binding classes closely examine their implementation (goto definition in your IDE works like a charm) and bind only the methods that are crucial for the class to work.
</note> 

## Testing
We do not test the bindings directly. We test them by using them in the Pythonic API. If the Pythonic API works, it means that the bindings work as well.
