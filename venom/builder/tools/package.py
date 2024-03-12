import os
import shutil
import subprocess
import sys
from venom.builder.tools.utils.Config import Config

def create(source_path: str, package_name: str, tmp_path: str):
    with open(os.path.join(source_path, "venom.yaml")) as file_handle:
        config = Config.from_yaml(file_handle)

    shutil.copytree(source_path, tmp_path, ignore=shutil.ignore_patterns("build", "dist", "venom.yaml"))

    try:
        os.rename(os.path.join(tmp_path, config.entrypoint), os.path.join(tmp_path, f"{package_name}.py"))
    except FileNotFoundError:
        raise FileNotFoundError(f"Entrypoint file not found: {config.entrypoint}")

    setup_content = f"""
from setuptools import setup

setup(
    name='PyAudioProcessor',
    version='1.0.0',
    py_modules=['PyAudioProcessor'],
    install_requires=['venom']
)
"""
    with open(os.path.join(tmp_path, "setup.py"), "w") as file_handle:
        file_handle.write(setup_content)



def install(tmp_path: str):
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", tmp_path], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except subprocess.CalledProcessError as e:
        print(f"PIP: Error installing package from {tmp_path}: {e}")
    finally:
        shutil.rmtree(tmp_path, ignore_errors=True)