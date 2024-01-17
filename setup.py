
from setuptools import setup, find_packages, find_namespace_packages
from build import CMakeExtension, CMakeBuild


# The information here can also be placed in setup.cfg - better separation of
# logic and declaration, and simpler if you include description/version in a file.
setup(
    name="venom",
    version="0.0.10",
    ext_modules=[CMakeExtension("juce")],
    packages=find_packages(exclude=["build", "build.*", "cmake", "cmake.*", "src", "src.*", "extern", "extern.*"]),
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False,
    python_requires=">=3.7",
)