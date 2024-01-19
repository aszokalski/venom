import shutil
import os
import sys
from venom.builder.tools.utils.Config import Config
from venom.builder.tools import cmake


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


def build(source_path):
    # Clean previous build
    if os.path.exists(os.path.join(source_path, "build")):
        print("Cleaning old ./build")
        shutil.rmtree(os.path.join(source_path, "build"))

    try:
        os.remove(os.path.join(source_path, "dist"))
    except:
        pass
    finally:
        print("Cleaning old ./dist")

    with open(os.path.join(source_path, "venom.yaml")) as file_handle:
        config = Config.from_yaml(file_handle)
        # Create dist directory as a symbolic link to source_pats/build/build/VenomPlugin_artefacts
        os.symlink(os.path.join(source_path, "build", "VenomPlugin_artefacts"),
                   os.path.join(source_path, "dist"))

        # copy boilerplate project from the same directory as this file
        shutil.copytree(os.path.join(os.path.dirname(__file__), "..", "boilerplate_plugin_project"),
                        os.path.join(source_path, "build"))

        # setup CMakeLists.txt with config
        modify_cmake_lists(source_path, config)
        cmake.init(os.path.join(source_path, "build"))

    cmake.build_target(os.path.join(source_path, "build"))
