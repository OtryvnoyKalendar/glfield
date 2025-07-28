#!/usr/bin/python
import os
import time
import argparse
import shutil
from pathlib import Path

RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[1;33m"
BLUE = "\033[0;34m"
PURPLE = "\033[0;35m"
CYAN = "\033[0;36m"
NO_COLOR = "\033[0m"

def print_message(color: str, mes: str) -> None:
    print(color, mes, NO_COLOR, sep="")

def print_dashes() -> None:
	print_message(GREEN, "----")

def print_exit_error(mes: str) -> None:
    print_message(RED, mes)
    exit(1)

def ensure_directory_exists(build_path: str) -> None:
    if not os.path.isdir(build_path):
        os.makedirs(build_path)
        print_message(RED, f"The {build_path} directory was not found, so a new {build_path} directory must be created")
        time.sleep(1)

def run_cmake(build_path: str, is_debug_mode: bool, is_mingw_mode: bool) -> None:
    print_message(BLUE, "Launching cmake")

    ensure_directory_exists(build_path)

    debug_mode="Release"
    if is_debug_mode:
        debug_mode="Debug"

    compiler_mode=""
    if is_mingw_mode:
        compiler_mode="-G 'MinGW Makefiles'"

    os.system(f"cmake {compiler_mode} -S . -B {build_path} -DCMAKE_BUILD_TYPE={debug_mode} --preset vcpkg")
    os.chdir(build_path)
    build_error = "Compilation or cmake build error"
    if is_mingw_mode:
        if os.system("mingw32-make") != 0:
            print_exit_error(build_error)
    else:
        if os.system("cmake --build . --parallel") != 0:
            print_exit_error(build_error)
    os.chdir("..")

def get_platform() -> str:
    filename = "cached_bin_dir.txt"
    try:
        with open(filename) as file:
            return file.readline().strip()
    except FileNotFoundError:
        print_exit_error(f"File '{filename}' not found")

def find_first_file_with_extension(directory: str, extension: str) -> str:
    """
    Searches for the first file with the specified extension in the directory and subdirectories.

    :param directory: Path to the directory to search
    :param extension: File extension, for example 'exe' or '.exe'
    :return: Full path to the found file as a string or an empty string if not found
    """

    if not extension.startswith('.'):
        extension = '.' + extension

    path = Path(directory)
    for file_path in path.rglob(f'*{extension}'):
        if file_path.is_file():
            return str(file_path)
    return ""
                
def run_program() -> int:
    platform_dir=get_platform()

    os.chdir(f"bin{os.sep}{platform_dir}")
    exe_file = find_first_file_with_extension(".", "exe")
    unix_file = find_first_file_with_extension(".", "unix")

    result = -1
    if exe_file != "":
        if os.name == "nt":
            result = os.system(rf".\{exe_file}")
        else:
            result = os.system(f"wine {exe_file}")
    elif unix_file != "":
        result = os.system(f"./{unix_file}")
    else:
        print_exit_error("The executable file was not found")

    return result

def configure_argparse(parser: argparse.ArgumentParser) -> None:
    parser.add_argument("-d", "--debug", action="store_true",
                        help="Enable debugging build")
    parser.add_argument("-r", "--remove", action="store_true",
                        help="Delete the project's build folder")
    parser.add_argument("-c", "--conly", action="store_true",
                        help="Just compile the program")
    parser.add_argument("-p", "--ronly", action="store_true",
                        help="Just run the program")
    parser.add_argument("-m", "--mingw", action="store_true",
                        help="Assembly using mingw32-make and 'MinGW Makefiles'")

def print_return_value(return_value) -> None:
    return_value_color = GREEN
    if return_value != 0:
        return_value_color = RED
    print_message(return_value_color, f"The program returns: {return_value}")

def main() -> None:
    script_version = "2.0"
    build_path = "build"

    parser = argparse.ArgumentParser(description="Project build script")
    configure_argparse(parser)
    args = parser.parse_args()

    print_message(GREEN, f"--- The project_start script.v.{script_version} ---")

    if args.remove:
        if os.path.isdir(build_path):
            shutil.rmtree(build_path)
        exit(0)

    if not args.ronly:
        run_cmake(build_path, args.debug, args.mingw)

    if not args.conly:
        print_dashes()
        return_value = run_program()
        print_dashes()
        print_return_value(return_value)

main()

