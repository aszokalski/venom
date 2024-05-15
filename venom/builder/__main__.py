import tempfile
from venom.builder.tools import package, project, template
from venom.builder.tools.utils.Config import Config
import click
import survey
from tqdm import tqdm
import os
import shutil

@click.group()
def cli():
    pass


@click.command()
@click.option('--source-path', default='.', help='Path to the source directory')
@click.option('--plugin-name', default=None, help='Name of the plugin')
@click.option('--author-name', default=None, help='Name of the author')
@click.option('--targets', default=[], help='Targets to build [Standalone, VST3, AU]', multiple=True)
def init(source_path, plugin_name, author_name, targets):
    verify_source_path(source_path, yaml=False)
    options = ["Standalone", "VST3", "AU"]
    if plugin_name is None:
        plugin_name = survey.routines.input("Name of the plugin: ")
    if author_name is None:
        author_name = survey.routines.input("Name of the author: ")
    if not targets:
        indexes = survey.routines.basket("Targets: ", options=options)
        targets = [options[i] for i in indexes]

    if any(target not in options for target in targets or not targets):
        print("Incorrect target. Allowed targets are Standalone, VST3 and AU")
    else:
        print("Creating venom project")
        template.new_project(source_path, plugin_name, author_name, targets)


@click.command()
@click.option('--source-path', default='.', help='Path to the source directory')
def build(source_path):
    verify_source_path(source_path)
    p_bar = tqdm(total=100, unit="%", dynamic_ncols=True)
    p_bar.update(1)
    p_bar.set_description("Creating plugin package")
    p_bar.refresh()
    # with tempfile.TemporaryDirectory() as tmp_dir:
    #     tmp_src_dir = os.path.join(tmp_dir, "src")
    #     package.create(source_path, "PyAudioProcessor", tmp_src_dir)
    #     p_bar.update(1)
    #     p_bar.set_description("Installing plugin package")
    #     p_bar.refresh()
    #     package.install(tmp_src_dir)

    project.build(source_path, p_bar)


@click.command(help="Allows faster building (for dev testing) on macOS. It only replaces the juce bindings.")
@click.option('--source-path', default='.', help='Path to the source directory')
@click.option('--juce-bindings-path', default='../venv/lib/python3.11/site-packages/juce.cpython-311-darwin.so', help='Path to the source directory')
@click.option('--mac-bundle-path', default='./dist/Standalone/VenomPlugin1.app', help='Path to a macOS bundle')
def test(source_path, juce_bindings_path, mac_bundle_path):
    verify_source_path(source_path)
    with open(os.path.join(source_path, "venom.yaml")) as file:
        config = Config.from_yaml(file)
        print("Fast building for " + config.name + " " + config.version)

        # copy all python files from source_path to mac_bundle_path and rename config.entrypoint to PyAudioProcessor.py
        shutil.copy(os.path.join(source_path, config.entrypoint), os.path.join(mac_bundle_path, "Contents", "Resources", "site-packages", "PyAudioProcessor.py"))
        for file in tqdm(os.listdir(source_path), desc="Copying python files"):
            if file.endswith(".py") and file != config.entrypoint:
                shutil.copy(os.path.join(source_path, file), os.path.join(mac_bundle_path, "Contents", "Resources", "site-packages", file))

        # copy juce bindings to mac_bundle_path
        shutil.copy(juce_bindings_path, os.path.join(mac_bundle_path, "Contents", "Resources", "site-packages", "juce.cpython-311-darwin.so"))


cli.add_command(test)
cli.add_command(build)
cli.add_command(init)


def verify_source_path(source_path, yaml=True):
    if not os.path.exists(source_path):
        raise Exception("Source path does not exist: " + source_path)
    if not os.path.isdir(source_path):
        raise Exception("Source path is not a directory: " + source_path)
    if yaml and not os.path.exists(os.path.join(source_path, "venom.yaml")):
        raise Exception("venom.yaml file does not exist in source path: " + source_path)


if __name__ == "__main__":
    cli()
