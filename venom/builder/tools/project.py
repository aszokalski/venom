import shutil
import os
import sys
from venom.builder.tools.utils.Config import Config
from venom.builder.tools import cmake
from tqdm import tqdm


def modify_cmake_lists(source_path: str, config: Config):
    with open(os.path.join(source_path, "build", "CMakeLists.txt"), "r") as file_handle:
        lines = file_handle.readlines()
        for index, line in enumerate(lines):
            if "set(PLUGIN_NAME" in line:
                lines[index] = "set(PLUGIN_NAME " + config.name + ")\n"
            if "set(PLUGIN_VERSION" in line:
                lines[index] = "set(PLUGIN_VERSION " + config.version + ")\n"
            if "set(PLUGIN_AUTHOR" in line:
                lines[index] = "set(PLUGIN_AUTHOR " + config.author + ")\n"
            if "set(FORMATS" in line:
                lines[index] = "set(FORMATS " + " ".join(config.targets) + ")\n"
            if "set(SITE_PACKAGES_DIRS" in line:
                site_packages_dirs = [f'"{path}"' for path in sys.path if "site-packages" in path]
                lines[index] = "set(SITE_PACKAGES_DIRS " + " ".join(site_packages_dirs) + ")\n"

    with open(os.path.join(source_path, "build", "CMakeLists.txt"), "w") as file_handle:
        file_handle.writelines(lines)


def build(source_path, p_bar: tqdm):
    # Clean previous build
    p_bar.update(1)
    if os.path.exists(os.path.join(source_path, "build")):
        p_bar.set_description("Cleaning old ./build")
    p_bar.refresh()

    try:
        os.remove(os.path.join(source_path, "dist"))
    except:
        pass
    finally:
        p_bar.set_description("Creating ./dist")
    p_bar.refresh()

    with open(os.path.join(source_path, "venom.yaml")) as file_handle:
        p_bar.set_description("Copying boilerplate project")
        p_bar.refresh()
        config = Config.from_yaml(file_handle)
        # Create dist directory as a symbolic link to source_pats/build/build/VenomPlugin_artefacts
        os.symlink(os.path.join(source_path, "build", "VenomPlugin_artefacts"),
                   os.path.join(source_path, "dist"))

        # copy boilerplate project from the same directory as this file
        shutil.copytree(os.path.join(os.path.dirname(__file__), "..", "boilerplate_plugin_project"),
                        os.path.join(source_path, "build"),
                        ignore=shutil.ignore_patterns('__pycache__', '*.pyc', 'build', 'tests', 'docs', 'examples'))

        source_dir = os.path.join(os.path.dirname(__file__), "..", "boilerplate_plugin_project")
        destination_dir = os.path.join(source_path, "build")
        files_to_copy = [
            'CMakeLists.txt',
            'create_plugin.cpp',
            'PyAudioProcessor.h',
            'PyAudioProcessorEditor.h',
            'PyAudioProcessor.py',
        ]

        if not os.path.exists(destination_dir):
            os.makedirs(destination_dir)

        # Copy each file from the source to the destination
        for file_name in files_to_copy:
            source_file = os.path.join(source_dir, file_name)
            destination_file = os.path.join(destination_dir, file_name)

            if os.path.exists(source_file):
                shutil.copy2(source_file, destination_file)
                print(f"Copied {file_name} to {destination_dir}")
            else:
                print(f"Warning: {file_name} not found in {source_dir}")


        # setup CMakeLists.txt with config
        modify_cmake_lists(source_path, config)
        p_bar.update(2)
        p_bar.set_description("Initializing CMake")
        p_bar.refresh()
        cmake.init(os.path.join(source_path, "build"), p_bar)

    p_bar.update(1)
    p_bar.set_description("Building CMake")
    p_bar.refresh()
    cmake.build_target(os.path.join(source_path, "build"), p_bar)
    p_bar.update(4)
    p_bar.set_description("Done")
    p_bar.refresh()
