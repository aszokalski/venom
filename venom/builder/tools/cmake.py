import os
import subprocess


def init(project_path: str):
    subprocess.run(
        ["cmake", "."], cwd=project_path)


def build_target(project_path: str):
    subprocess.run(["cmake", "--build", "."], cwd=project_path)
