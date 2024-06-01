cmake_minimum_required(VERSION 3.5...3.26)

set(FORMATS AU VST3 Standalone)
set(PLUGIN_NAME "VenomPlugin")
set(PLUGIN_VERSION "0.1.0")
set(PLUGIN_AUTHOR "Veno")
set(SITE_PACKAGES_DIRS "../../venv/lib/python3.11/site-packages")

project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION})

# Include external libraries
if(NOT TARGET JUCE)
    message(STATUS "Building JUCE modules...")
    add_subdirectory(${CMAKE_SOURCE_DIR}/../../extern/juce JUCE_Lib)
else()
    message(STATUS "JUCE modules already built, using cached version.")
endif()
add_subdirectory(../../extern/pybind11 pybind11)

# Define the plugin target
juce_add_plugin(VenomPlugin
        PLUGIN_MANUFACTURER_CODE Veno
        PLUGIN_CODE Veno
        FORMATS ${FORMATS}
        PRODUCT_NAME ${PROJECT_NAME}
        )

# Generate JUCE headers for the plugin
juce_generate_juce_header(VenomPlugin)

# Link libraries to the plugin target
target_link_libraries(VenomPlugin
        PRIVATE
        pybind11::embed
        juce::juce_audio_utils
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        )

# Specify the source files for the plugin target
target_sources(VenomPlugin
        PRIVATE
        create_plugin.cpp
        PyAudioProcessor.h
        PyAudioProcessorEditor.h
        )

# Define compile definitions for the plugin target
target_compile_definitions(VenomPlugin
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        )

# Function to copy necessary files only if they don't already exist
function(copy_site_packages src_dir dest_dir)
    get_filename_component(abs_src_dir ${src_dir} ABSOLUTE)
    file(GLOB_RECURSE site_package_files
            "${abs_src_dir}/*.py"
            "${abs_src_dir}/*.so"
            "${abs_src_dir}/*.pyd"
            )
    foreach(file_path ${site_package_files})
        file(RELATIVE_PATH rel_path ${abs_src_dir} ${file_path})
        set(dest_path ${dest_dir}/${rel_path})
        if(NOT EXISTS ${dest_path})
            file(COPY ${file_path} DESTINATION ${dest_dir}/${rel_path})
            message(STATUS "Copied ${file_path} to ${dest_dir}/${rel_path}")
        else()
            message(STATUS "File ${dest_path} already exists, skipping copy")
        endif()
    endforeach()
endfunction()

foreach(format ${FORMATS})
    foreach(dir ${SITE_PACKAGES_DIRS})
        set(dest_dir ${CMAKE_BINARY_DIR}/site-packages/${format})
        copy_site_packages(${dir} ${dest_dir})
        juce_add_bundle_resources_directory("VenomPlugin_${format}" ${dest_dir})
    endforeach()
endforeach()
