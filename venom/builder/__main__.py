import tempfile
from venom.builder.utils import package, project
import click

@click.group()
def cli():
    pass

@click.command()
@click.option('--source-path', default='.', help='Path to the source directory')
def init(source_path):
    project.init(source_path)


@click.command()
@click.option('--source-path', default='.', help='Path to the source directory')
def build(source_path):
    print("Building venom project")
    with tempfile.TemporaryDirectory() as tmp_dir:
        print("Created temporary directory: ", tmp_dir)
    package.create(source_path, "PyAudioProcessor", tmp_dir)
    package.install(tmp_dir)


cli.add_command(init)
cli.add_command(build)
if __name__ == "__main__":
    cli()
