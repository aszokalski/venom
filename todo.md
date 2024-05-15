example/build/CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.5...3.26)

# Set plugin details and formats
set(FORMATS AU VST3 Standalone)
set(PLUGIN_NAME "VenomPlugin")
set(PLUGIN_VERSION "0.1.0")
set(PLUGIN_AUTHOR "Veno")
set(SITE_PACKAGES_DIRS "../../../venv/lib/python3.11/site-packages")

project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})


# Include JUCE core CMake utilities (assuming path to the juce CMakeLists.txt that provides juce_add_plugin)
add_subdirectory(../../extern/juce juce)

# Include the pybind11 library
add_subdirectory(../../extern/pybind11 pybind11)

# Import the pre-built JUCE modules static library
add_library(JUCE_Modules STATIC IMPORTED)
set_target_properties(JUCE_Modules PROPERTIES
IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../../extern/lib/juce/libJUCE_Modules.a")

# Define the plugin with JUCE's CMake utility
juce_add_plugin(${PLUGIN_NAME}
PLUGIN_MANUFACTURER_CODE Veno
PLUGIN_CODE Veno
FORMATS ${FORMATS}
PRODUCT_NAME ${PROJECT_NAME}
)

# Generate the JUCE header
juce_generate_juce_header(${PLUGIN_NAME})

# Link the plugin with pybind11 and the imported JUCE modules library
target_link_libraries(${PLUGIN_NAME}
PRIVATE
pybind11::embed
PUBLIC
JUCE_Modules
)

# Set up source files
target_sources(${PLUGIN_NAME}
PRIVATE
create_plugin.cpp
PyAudioProcessor.h
PyAudioProcessorEditor.h
)

# Set up compile definitions
target_compile_definitions(${PLUGIN_NAME}
PUBLIC
JUCE_WEB_BROWSER=0
JUCE_USE_CURL=0
JUCE_VST3_CAN_REPLACE_VST2=0
)
```

venom/extern/juce/modules/juce_audio_plugin_client/juce_audio_plugin_client_Standalone.cpp:31:3: error: To compile AudioUnitv3 and/or Standalone plug-ins, you need to add the juce_audio_utils and juce_audio_devices modules!
#error To compile AudioUnitv3 and/or Standalone plug-ins, you need to add the juce_audio_utils and juce_audio_devices modules!