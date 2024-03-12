import tqdm
from venom.builder.tools.utils.run import run_with_progress


def init(project_path: str, progress_bar: tqdm):
    run_with_progress(
        ["cmake", "."], progress_bar, cwd=project_path, max_val=30)


def build_target(project_path: str, progress_bar: tqdm):
    run_with_progress(["cmake", "--build", "."], progress_bar, cwd=project_path)
