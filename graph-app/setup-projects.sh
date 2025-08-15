#!/bin/bash

set -e  # Exit on error

BUILD_DIR="build"
CMAKE_CACHE="$BUILD_DIR/CMakeCache.txt"
ROOT_CMAKE="CMakeLists.txt"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Comprobar si conan está instalado
if ! command -v conan &> /dev/null
then
    echo "Conan not found. Installing Conan..."
    pip install --user conan
fi

# Configurar Conan e instalar dependencias
echo "Installing Conan dependencies..."
conan install .. -s compiler.cppstd=20 --build=missing

# Decidir si ejecutar cmake ..
if [ ! -f "$CMAKE_CACHE" ]; then
    echo "Running CMake configuration (first time)..."
    cmake .. --preset conan-default
else
    # Comprobar si el CMakeLists.txt raíz es más reciente que el cache
    if [ "../$ROOT_CMAKE" -nt "$CMAKE_CACHE" ]; then
        echo "Detected changes in CMakeLists.txt, reconfiguring..."
        cmake .. --preset conan-default
    else
        echo "CMake configuration is up-to-date."
    fi
fi

cd ..
echo "Building project..."
cmake --build --preset conan-release
echo "Done! Run with: ./build/bin/Debug/graph_api.exe"

