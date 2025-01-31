# CLI tool

Before using the cli tool you need to install it to your virtual environment.
We recommend installing it outside of your main system environment because there may be write permission errors while building dependencies in site packages.


## Installing

1. Clone repository with submodules

``` bash
git clone https://github.com/aszokalski/venom.git
cd venom
git submodule update --init --recursive
```

2. Create virtual environment

```bash
python3 -m venv venv
source venv/bin/activate
```

3. Install package with pip by providing path to cloned repository
> Note: this may take a long time

``` bash
pip install /path/to/venom
```

## Usage

You can view possible commands by running `venom --help`.
There are two main commands you can use in venom cli tool.
`init` command creates nessessary files with correct arguments for your project.
`build` build the plugin defined in python file. 
It can be done only once per project, because it compiles nessessary C++ libraries to `site-packages`. The python plugin file is dynamically interpreted so after changes are saved, plugin should work without recompiling.
> Note: you can build only one plugin per virtual environment

### `init`

Project tree after using the command:
```
example                            [example project]
├── plugin.py
└── venom.yaml
```
Variables used for building the plugin can be found inside `venom.yml` file.
Inside `plugin.py` is defined logic for the plugin.

### `build`

After using the command project tree should look like this:
```
example                            [example project]
├── plugin.py
├── venom.yaml
├── dist/
│   ├── VST3
│   │   └── TestPlugin.vst3
│   │       └── Contents
│   │           ├── Info.plist
│   │           ├── MacOS
│   │           │   └── TestPlugin
│   │           ├── PkgInfo
│   │           ├── Resources
│   │           │   └── moduleinfo.json
│   │           └── CodeSignature
│   │               └── CodeResources
│   └── libTestPlugin_SharedCode.a
└── build/                        [other build artifacts]
```
Inside `dist` folder is plugin binary.
Inside `build` are all files built by using this command.