#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"

# Check if build directory is missing or empty
if [ ! -d "$BUILD_DIR" ] || [ -z "$(ls -A "$BUILD_DIR")" ]; then
    echo "📦 Build directory missing or empty. Regenerating..."
    rm -rf "$BUILD_DIR"
    cmake -S "$ROOT_DIR" -B "$BUILD_DIR"
    cmake --build "$BUILD_DIR"
else
    echo "✅ Build directory found. Skipping CMake generation..."
fi

echo "🏗️ Build completed successfully."
