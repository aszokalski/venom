import shutil

from pathlib import Path
from typing import List

from venom.builder.tools.utils.Config import Config

def new_project(source_path: str, plugin_name: str, author_name: str, targets: List[str]):
    targets_str = "\n".join([f"  - {target}" for target in targets])
    _source_path = Path(source_path)

    yaml = f"""
name: {plugin_name}
version: 1.0.0
author: {author_name}
entrypoint: plugin.py
targets:
{targets_str}
"""
    with open(_source_path / "venom.yaml", "w") as f:
        f.write(yaml)

    boilerplate_dir = Path(__file__).parent.parent / "boilerplate_plugin_project"
    files_to_copy = [
        "plugin.py",
        "requirements.txt",
    ]

    # Copy each file from the source to the destination
    for file_name in files_to_copy:
        source_file = boilerplate_dir / file_name
        destination_file = _source_path / file_name

        if source_file.exists():
            shutil.copy2(source_file, destination_file)
            print(f"Copied {file_name} to {source_path}")
        else:
            print(f"Warning: {file_name} not found in {boilerplate_dir}")


def is_present(source_path: str) -> bool:
    file_path = Path(source_path) / "venom.yaml"

    if not file_path.exists():
        return False

    with open(file_path) as file:
        config = Config.from_yaml(file)

    files = [
        config.entrypoint,
        "requirements.txt",
    ]

    for file in files:
        if not (Path(source_path) / file).exists():
            return False

    return True
