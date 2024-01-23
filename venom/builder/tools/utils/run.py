import subprocess
import re
from tqdm import tqdm


def execute(cmd, **kwargs):
    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, **kwargs)
    for stdout_line in iter(popen.stdout.readline, ""):
        yield stdout_line
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        raise subprocess.CalledProcessError(return_code, cmd)


def run_with_progress(command, progress_bar: tqdm, max_val=100, **kwargs):
    start_progress = progress_bar.n
    for line in execute(command, **kwargs):
        pattern = r"\s*(\d+)%"
        found = re.search(pattern, line)
        if found:
            progress = int(found.group(1))
            progress_after_max = int((progress / 100) * (max_val - start_progress / 2))
            if progress == 100:
                progress_bar.update(max_val - progress_bar.n)
            else:
                progress_bar.update(max(progress_after_max - progress_bar.n, 0))
        progress_bar.write(line, end="")
