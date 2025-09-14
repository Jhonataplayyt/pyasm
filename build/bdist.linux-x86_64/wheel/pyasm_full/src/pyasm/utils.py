import platform
import os

def find_abs_path(frac, rt="/" if platform.system() == "Linux" else "C:/"):
    norm_frac = os.path.normpath(frac)

    for root, dirs, files in os.walk(rt):
        for d in dirs:
            current = os.path.join(root, d)

            if current.endswith(norm_frac):
                return os.path.abspath(current)

        for f in files:
            current = os.path.join(root, f)

            if current.endswith(norm_frac):
                return os.path.abspath(current)

    return