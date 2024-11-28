import tqdm

from venom.builder.tools.utils.run import run_with_progress


def init(project_path: str, progress_bar: tqdm, cmake_args: list = []):
    run_with_progress(
        ["cmake", ".", *cmake_args], progress_bar, cwd=project_path, max_val=30
    )


def build_target(project_path: str, progress_bar: tqdm, build_args: list = []):
    run_with_progress(
        ["cmake", "--build", ".", *build_args], progress_bar, cwd=project_path
    )
