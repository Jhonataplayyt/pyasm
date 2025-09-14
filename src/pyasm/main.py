import utils
import subprocess
import platform
import os

def _raise(ex):
   raise ex 

def main():
    _os = platform.system()

    VAR_NAME = "PYASM_UTILS_k83bC67"
    VAR_VALUE = f"""[
        "{utils.find_abs_path("pyasm/rasm/keystone/build/llvm/lib/")}",
        "{os.path.join(
            utils.find_abs_path("pyasm/rasm/keystone/build/llvm/lib/"),
            'libkeystone.so.0'
        ) if _os == "Linux" else os.path.join(
            utils.find_abs_path("pyasm/rasm/keystone/winbuild/llvm/lib/"),
            'libkeystone.dll.a'
        ) if _os == "Windows" else _raise(OSError(f"System {_os} not automatically supported. Configure manually."))}",
        "{os.path.join(
            utils.find_abs_path("/pyasm/lib/"),
            'libpyasm.so'
        ) if _os == "Linux" else os.path.join(
            utils.find_abs_path("/pyasm/lib/"),
            'pyasm.dll'
        ) if _os == "Windows" else _raise(OSError(f"System {_os} not automatically supported. Configure manually."))}",
    ]"""

    if _os == "Windows":
        subprocess.run(["setx", VAR_NAME, VAR_VALUE], shell=True)
    elif _os == "Linux" or _os == "Darwin":
        shell_config = os.path.expanduser("~/.bashrc")

        if os.environ.get("SHELL", "").endswith("zsh"):
            shell_config = os.path.expanduser("~/.zshrc")

        with open(shell_config, "a") as f:
            f.write(f"\nexport {VAR_NAME}='{VAR_VALUE}'\n")
    else:
        raise OSError(f"System {_os} not automatically supported. Configure manually.")