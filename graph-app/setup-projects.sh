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

# Decidir si ejecutar cmake ..
if [ ! -f "$CMAKE_CACHE" ]; then
    echo "Running CMake configuration (first time)..."
    cmake ..
else
    # Comprobar si el CMakeLists.txt raíz es más reciente que el cache
    if [ "../$ROOT_CMAKE" -nt "$CMAKE_CACHE" ]; then
        echo "Detected changes in CMakeLists.txt, reconfiguring..."
        cmake ..
    else
        echo "CMake configuration is up-to-date."
    fi
fi

echo "Building project..."
cmake --build .

echo "Done! Run with: ./build/bin/Debug/graph_api.exe"

