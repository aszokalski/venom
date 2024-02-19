# VENOM - Python JUCE

## Setup
```
git submodule update --init --recursive
```
## Installng
```shell
python3 -m venv venv
source venv/bin/activate
```

```shell
pip install .
```

## Usage
Example project in `example/` folder.

```shell
cd example
```
### Build the project
```shell
venom build
```

It will generate `build` and `dist` folders:

- `build` folder contains the build system files
- `dist` folder contains the built binaries

> Note: this may take a long time