from typing import List
import os
def new_project(source_path: str, plugin_name: str, author_name: str, targets: List[str]):
    targets_str = "\n".join([f"  - {target}" for target in targets])
    yaml = f"""
name: {plugin_name}
version: 1.0.0
author: {author_name}
entrypoint: plugin.py
targets:
{targets_str}
"""
    with open(os.path.join(source_path, "venom.yaml"), "w") as f:
        f.write(yaml)

    # copy utils/example_plugin.py to source_path/plugin.py
    example_plugin = open(os.path.join(os.path.dirname(__file__), "utils/example_plugin.py")).read()
    with open(os.path.join(source_path, "plugin.py"), "w") as f:
        f.write(example_plugin)