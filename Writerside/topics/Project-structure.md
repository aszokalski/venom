# Package structure

The package structure is as follows:

```
venom/
├── bin/                                [executables shipped with the package]
│   ├── venom                           [venom builder CLI]
├── example/                            [example project]
│   ├── plugin.py
│   ├── venom.yaml
├── extern/                             [submodules]
│   ├── juce/
│   ├── pybind11/
├── venom/
*   ├── builder/                        [CLI tool]
*   │   ├── boilerplate_plugin_project/
│   │   │   ├── external/               [symlink to extern/]
│   │   │   ├── CmakeLists.txt          [boilerplate plugin build system]
│   │   │   ├── create_plugin.cpp       [boilerplate plugin source]
│   │   │   ├── [Python -> C++ bindings]
│   │   ├── [venom CLI tool source files]
│   │   ├── __init__.py
│   │   ├── __main__.py
│   │   ├── ...
*   ├── juce/                           [JUCE bindings]
│   │   ├── [JUCE bindings source files]
│   │   ├── CMakeLists.txt              [JUCE bindings build system pt. 2]
│   │   ├── __init__.py                 [exposes JUCE bindings as juce package]
*   ├── wrapper/                        [Pythonic API]
│   │   ├── [Pythonic API wrapping JUCE bindings]
│   │   ├── __init__.py
│   ├── __init__.py
├── CMakeLists.txt                      [JUCE bindings build system]
├── setup.py                            [Python package setup. Executes CMake]
├── MANIFEST.in                         [includes boilerplate plugin in the package]
├── requirements.txt
├── .gitmodules                         [git submodules]
├── ...

```

Main modules are marked with __*__. Each will be described in detail in its own chapter.
