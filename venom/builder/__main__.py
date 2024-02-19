import tempfile
from venom.builder.tools import package, project
import click
import os


@click.group()
def cli():
    pass


@click.command()
@click.option('--source-path', default='.', help='Path to the source directory')
def build(source_path):
    verify_source_path(source_path)
    print("Building venom project")
    with tempfile.TemporaryDirectory() as tmp_dir:
        print("Created temporary directory: ", tmp_dir)
        tmp_src_dir = os.path.join(tmp_dir, "src")
        package.create(source_path, "PyAudioProcessor", tmp_src_dir)
        package.install(tmp_src_dir)
    project.build(source_path)


cli.add_command(build)


def verify_source_path(source_path):
    if not os.path.exists(source_path):
        raise Exception("Source path does not exist: " + source_path)
    if not os.path.isdir(source_path):
        raise Exception("Source path is not a directory: " + source_path)
    if not os.path.exists(os.path.join(source_path, "venom.yaml")):
        raise Exception("venom.yaml file does not exist in source path: " + source_path)


if __name__ == "__main__":
    cli()
