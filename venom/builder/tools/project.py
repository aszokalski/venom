import os
import shutil
import site

from tqdm import tqdm
from pathlib import Path

from venom.builder.tools import cmake
from venom.builder.tools.template import is_present, new_project
from venom.builder.tools.utils.Config import Config


def build_project(source_path: str, p_bar: tqdm, cmake_args: list = []) -> None:
    cmake_args = cmake_args or []
    _source_path = Path(source_path)
    p_bar.refresh()

    if not is_present(source_path):
        p_bar.set_description("Copying boilerplate project")
        p_bar.refresh()
        new_project(source_path, "VenomPlugin", "VenomAuthor", ["Standalone", "VST3"])

    with (_source_path / "venom.yaml").open() as file_handle:
        config = Config.from_yaml(file_handle)

    if (_source_path / "build").exists():
        p_bar.set_description("Cleaning previous build directory")
        shutil.rmtree(_source_path / "build")
        shutil.rmtree(_source_path / "dist")
    p_bar.set_description("Creating build directory")
    (_source_path / "dist").symlink_to(
        _source_path / "build" / f"{config.name}_artefacts",
    )

    p_bar.update(2)
    p_bar.set_description("Initializing CMake")
    p_bar.refresh()

    # Initialize CMake with the given arguments
    cmake_args = [
        f"-DPLUGIN_NAME={config.name}",
        f"-DPLUGIN_VERSION={config.version}",
        f"-DPLUGIN_AUTHOR={config.author}",
        f"-DENTRYPOINT={config.entrypoint}",
        f"-DPROJECT_SOURCE_DIR={_source_path.resolve()}",
        "-DFORMATS=VST3", #TODO: Add support for other formats
        "-DDEFAULT_LOG_LEVEL=0", #TODO: Add other log levels
        *cmake_args,
    ]

    if "CMAKE_ARGS" in os.environ:
        cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]

    venom_source = site.getsitepackages()[0] + "/venom_source"
    cmake.init(venom_source, p_bar, cmake_args)

    p_bar.update(1)
    p_bar.set_description("Building CMake")
    p_bar.refresh()

    # Build the target
    build_args = [
        "--target",
        f"{config.name}",
    ]

    cmake.build_target(venom_source, p_bar, build_args)
    p_bar.update(4)
    p_bar.set_description("Done")
    p_bar.refresh()
