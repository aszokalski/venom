import subprocess
import sys

cmake_args = [
    f"-DPYTHON_EXECUTABLE={sys.executable}",
]

subprocess.run(
    ["cmake", "..", *cmake_args], cwd="./build", check=True
)
subprocess.run(
    ["cmake", "--build", ".", "--target VenomPlugin_Standalone"],  cwd="./build", check=True
)