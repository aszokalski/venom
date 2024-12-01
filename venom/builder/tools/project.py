import os
import shutil
import sys

from tqdm import tqdm

from venom.builder.tools import cmake
from venom.builder.tools.utils.Config import Config


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
                site_packages_dirs = [
                    f'"{path}"' for path in sys.path if "site-packages" in path
                ]
                lines[index] = (
                    "set(SITE_PACKAGES_DIRS " + " ".join(site_packages_dirs) + ")\n"
                )

    with open(os.path.join(source_path, "build", "CMakeLists.txt"), "w") as file_handle:
        file_handle.writelines(lines)


def build(source_path, p_bar: tqdm, cmake_args: list = [], build_args: list = []):
    # Clean previous build
    p_bar.update(1)
    if os.path.exists(os.path.join(source_path, "build")):
        p_bar.set_description("Cleaning old ./build")
    p_bar.refresh()

    try:
        os.remove(os.path.join(source_path, "dist"))
    except FileNotFoundError:
        p_bar.write("No old dist directory found")
        p_bar.set_description("Creating ./dist")
    finally:
        p_bar.set_description("Creating ./dist")
    p_bar.refresh()

    with open(os.path.join(source_path, "venom.yaml")) as file_handle:
        p_bar.set_description("Copying boilerplate project")
        p_bar.refresh()
        config = Config.from_yaml(file_handle)
        # Create dist directory as a symbolic link to source_pats/build/build/VenomPlugin_artefacts
        os.symlink(
            os.path.join(source_path, "build", f"{config.name}_artefacts"),
            os.path.join(source_path, "dist"),
        )

        # copy boilerplate project from the same directory as this file
        shutil.copytree(
            os.path.join(os.path.dirname(__file__), "..", "create_plugin"),
            os.path.join(source_path, "build"),
            ignore=shutil.ignore_patterns(
                "__pycache__", "*.pyc", "build", "tests", "docs", "examples"
            ),
        )

        source_dir = os.path.join(os.path.dirname(__file__), "..", "create_plugin")
        destination_dir = os.path.join(source_path, "build")
        files_to_copy = [
            "CMakeLists.txt",
            "create_plugin.cpp",
        ]

        os.makedirs(destination_dir, exist_ok=True)

        # Copy each file from the source to the destination
        for file_name in files_to_copy:
            source_file = os.path.join(source_dir, file_name)
            destination_file = os.path.join(destination_dir, file_name)

            if os.path.exists(source_file):
                shutil.copy2(source_file, destination_file)
                print(f"Copied {file_name} to {destination_dir}")
            else:
                print(f"Warning: {file_name} not found in {source_dir}")

        # Setup CMakeLists.txt with config
        modify_cmake_lists(source_path, config)
        p_bar.update(2)
        p_bar.set_description("Initializing CMake")
        p_bar.refresh()

        # Initialize CMake with the given arguments
        cmake_args = [
            f"-DPLUGIN_NAME={config.name}",
            f"-DPLUGIN_VERSION={config.version}",
            f"-DPLUGIN_AUTHOR={config.author}",
            f"-DENTRYPOINT={config.entrypoint}",
            f"-DFORMATS={' '.join(config.targets)}",
            f"-DPROJECT_SOURCE_DIR={source_path}",
            *cmake_args,
        ]

        if "CMAKE_ARGS" in os.environ:
            cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]

        cmake.init(os.path.join(source_path, "build"), p_bar, cmake_args)

    p_bar.update(1)
    p_bar.set_description("Building CMake")
    p_bar.refresh()

    # Build the target
    build_args = [
        "--target",
        f"{config.name}",
        *build_args,
    ]
    cmake.build_target(os.path.join(source_path, "build"), p_bar, build_args)
    p_bar.update(4)
    p_bar.set_description("Done")
    p_bar.refresh()
