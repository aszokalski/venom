import os
import shutil
import sys

from tqdm import tqdm
from pathlib import Path

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


def build_project(source_path: str, p_bar: tqdm, cmake_args: list = []) -> None:
    cmake_args = cmake_args or []
    _source_path = Path(source_path)
    p_bar.refresh()

    with (_source_path / "venom.yaml").open() as file_handle:
        p_bar.set_description("Copying boilerplate project")
        p_bar.refresh()
        config = Config.from_yaml(file_handle)
        # Create dist directory as a symbolic link
        (_source_path / "dist").symlink_to(
            _source_path / "build" / f"{config.name}_artefacts",
        )

        # copy boilerplate project
        if not (_source_path / "build").exists():
            shutil.copytree(
                Path(__file__).parent.parent / "boilerplate_plugin_project",
                _source_path / "build",
                ignore=shutil.ignore_patterns(
                    "__pycache__", "*.pyc", "build", "tests", "docs", "examples"
                ),
            )

        source_dir = Path(__file__).parent.parent / "boilerplate_plugin_project"
        destination_dir = _source_path / "build"
        files_to_copy = [
            "CMakeLists.txt",
            "create_plugin.cpp",
            "plugin.py",
            "requirements.txt",
        ]

        destination_dir.mkdir(exist_ok=True)

        # Copy each file from the source to the destination
        for file_name in files_to_copy:
            source_file = source_dir / file_name
            destination_file = destination_dir / file_name

            if source_file.exists():
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
            f"-DPROJECT_SOURCE_DIR={source_path}",
            "-DFORMATS=VST3", #TODO: Add support for other formats
            "-DDEFAULT_LOG_LEVEL=0", #TODO: Add other log levels
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
    ]

    cmake.build_target(os.path.join(source_path, "build"), p_bar, build_args)
    p_bar.update(4)
    p_bar.set_description("Done")
    p_bar.refresh()
