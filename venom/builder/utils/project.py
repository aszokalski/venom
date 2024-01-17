import shutil
import os
from venom.builder.utils.Config import Config


def init(source_path):
    if not os.path.exists(source_path):
        raise Exception("Source path does not exist: " + source_path)
    if not os.path.isdir(source_path):
        raise Exception("Source path is not a directory: " + source_path)
    if not os.path.exists(os.path.join(source_path, "venom.yaml")):
        raise Exception("venom.yaml file does not exist in source path: " + source_path)

    # Clean previous build
    if os.path.exists(os.path.join(source_path, "build")):
        shutil.rmtree(os.path.join(source_path, "build"))
    if os.path.exists(os.path.join(source_path, "dist")):
        shutil.rmtree(os.path.join(source_path, "dist"))

    config = None
    with open(os.path.join(source_path, "venom.yaml")) as file_handle:
        config = Config.from_yaml(file_handle)
        print(config)

    # Create dist directory
    os.mkdir(os.path.join(source_path, "dist"))

    # copy boilerplate project from the same directory as this file
    shutil.copytree(os.path.join(os.path.dirname(__file__), "..", "boilerplate_plugin_project"),
                    os.path.join(source_path, "build"))

    # setup CMakeLists.txt with config
    modify_cmake_lists(source_path, config)




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
    with open(os.path.join(source_path, "build", "CMakeLists.txt"), "w") as file_handle:
        file_handle.writelines(lines)
