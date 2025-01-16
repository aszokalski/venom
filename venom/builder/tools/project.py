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
    p_bar.set_description("Creating build directory")

    p_bar.update(2)
    p_bar.set_description("Initializing CMake")
    p_bar.refresh()

    # Initialize CMake with the given arguments
    cmake_args = [
        f"-DPLUGIN_NAME={config.name}",
        f"-DPLUGIN_VERSION={config.version}",
        f"-DPLUGIN_AUTHOR={config.author}",
        f"-DPLUGIN_FILE={(_source_path / config.entrypoint).resolve()}",
        f"-DPROJECT_SOURCE_DIR={_source_path.resolve()}",
        "-DFORMATS=VST3", #TODO: Add support for other formats
        "-DDEFAULT_LOG_LEVEL=0", #TODO: Add other log levels
        *cmake_args,
    ]

    if "CMAKE_ARGS" in os.environ:
        cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]

    venom_source = Path(site.getsitepackages()[0]) / "venom_source"
    cmake.init(venom_source.as_posix(), p_bar, cmake_args)

    p_bar.update(1)
    p_bar.set_description("Building CMake")
    p_bar.refresh()

    # Build the target
    build_args = [
        "--target",
        "BoilerplatePlugin",
    ]

    # Set CMAKE_BUILD_PARALLEL_LEVEL to control the parallel build level
    # across all generators.
    if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
        # self.parallel is a Python 3 only way to set parallel jobs by hand
        # using -j in the build_ext call, not supported by pip or PyPA-build.
        # CMake 3.12+ only.
        build_args += [f"-j{os.cpu_count()//2}"]

    cmake.build_target(venom_source.as_posix(), p_bar, build_args)
    p_bar.update(4)
    p_bar.set_description("Done")
    p_bar.refresh()
