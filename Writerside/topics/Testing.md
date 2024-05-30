# Testing

<!-- TOC -->

* [Introduction](#introduction)
* [Testing flow](#testing-flow)
* [Tests directory structure](#tests-directory-structure)

<!-- TOC -->

## Introduction

Testing project is divided into two parts: testing the C++ code and testing the Python code.
Main testing framework and `Gtest` for C++.

## Tests directory structure

```
tests
├── __init__.py
├── cpp
│   ├── CMakeLists.txt
│   ├── juce_audio_processors
│   │   ├── CMakeLists.txt
│   │   └── test_AudioProcessorEditor.cpp
│   └── stubs
│       ├── __init__.py
│       └── audio_processors_stubs.py
└── vst3                                            [see Test-plugin]
    ├── CMakeLists.txt
    ├── create_plugin.cpp
    ├── plugin.py
    └── requirements.txt
```

## Testing flow

1. Create tests in C++ using `Gtest` framework in `tests/cpp` directory. You can use
   `tests/cpp/juce_audio_processors/CMakeLists.txt` and `tests/cpp/juce_audio_processors/test_AudioProcessorEditor.cpp`
   as a template.
2. Create Python stubs for the C++ code in `tests/cpp/stubs` directory. You can
   use `tests/cpp/stubs/audio_processors_stubs.py` as a template.
   This code will be run in the tests.



