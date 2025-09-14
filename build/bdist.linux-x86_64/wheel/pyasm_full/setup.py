import os
import sys
import shutil
import subprocess
from setuptools import setup
from setuptools.command.install import install

class CustomInstallCommand(install):
    def run(self):
        # Detecta se estamos dentro do processo de build do wheel
        if 'bdist_wheel' in self.distribution.get_command_list():
            print("Instalação dentro do bdist_wheel detectada, pulando cópia e execução do build_env.py")
            super().run()
            return

        # Instala normalmente
        super().run()

        # Só roda daqui pra baixo na instalação real
        origin = os.path.dirname(os.path.abspath(__file__))
        destination = os.path.join(self.install_lib, "pyasm_full")

        def ignore_unwanted(dir, files):
            unwanted = {'.git', '__pycache__', 'build', 'dist', '.venv', 'venv'}
            unwanted.update({f for f in files if f.endswith('.dist-info')})
            if os.path.abspath(dir) == os.path.abspath(destination):
                return files
            return [item for item in files if item in unwanted]

        shutil.copytree(origin, destination, dirs_exist_ok=True, ignore=ignore_unwanted)

        script_path = os.path.join(origin, "build_env.py")
        if os.path.exists(script_path):
            subprocess.run([sys.executable, script_path], check=True)

setup(
    cmdclass={
        'install': CustomInstallCommand,
    }
)
