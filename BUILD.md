# Build Instructions

This document explains how to build the project from source using CMake with provided presets. The project depends on Qt6 and supports multiple build generators.

---

## Prerequisites

- CMake > 3.25  
- Qt6 (official installer)
- Compiler: MinGW, GCC

---

## Qt Environment

Before building, configure the environment so CMake can locate Qt:

1. Set `QT6_DIR` to the cmake directory of your Qt installation. This allows cmake to find Qt cmake when building.

    ```bash
    # Windows (PowerShell)
    $env:QT6_DIR="C:\Qt\6.7.2\mingw_64\lib\cmake"

    # Linux/macOS (bash/zsh)
    export QT6_DIR=/opt/Qt/6.10.1/gcc_64/lib/cmake
    ```

2. Add Qt’s bin directory to your PATH so tools like qmake are accessible.

    ```bash
    # Windows (PowerShell)
    $env:PATH="$env:C:\Qt\6.7.2\mingw_64\bin;$env:PATH"

    # Linux/macOS (bash/zsh)
    export PATH=/opt/Qt/6.10.1/gcc_64/bin:$PATH
    ```

3. Using the `MaintenanceTool` executable from Qt root folder, ensure the following modules are installed.
    - QtChart

---

## Building with CMake

The project includes CMake presets for convenience. These presets define build directories, generators, and jobs.

1. Configure the Project.

    ```bash
    # Example using MinGW preset
    cmake --preset MinGW_MakeFiles

    # Example using Ninja preset
    cmake --preset Ninja
    ```

2. Build the Project.

    ```bash
    # Using MinGW preset
    cmake --build --preset build-MinGW_MakeFiles

    # Using Ninja preset
    cmake --build --preset build-NINJA
    ```

3. Executables will stored in `build/bin`.
