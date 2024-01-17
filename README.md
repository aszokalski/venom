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
### Setup the build system
```shell
python -m venom.builder init
```

It will generate `build` and `dist` folders:

- `build` folder contains the build system files
- `dist` folder contains the built binaries

### Build the project
```shell
python -m venom.builder build
```

The built binaries will be in `dist` folder.

