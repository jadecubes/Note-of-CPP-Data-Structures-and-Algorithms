#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"

# 🛠️ Run the script to generate CMakeLists.txt for each module
echo "🔄 Generating CMakeLists.txt files..."
"$ROOT_DIR/generateCMakeLists.sh"

# Find the newest source file and its modification time
read -r NEWEST_SRC_FILE_TIME NEWEST_SRC_FILE_NAME < <(
    find "$ROOT_DIR" -type f ! -path "$BUILD_DIR/*" -print0 |
        xargs -0 stat -f "%m %N" |
        sort -n |
        tail -1
)

# Find the newest build file and its modification time
if [ -d "$BUILD_DIR" ]; then
    read -r NEWEST_BUILD_FILE_TIME < <(
        find "$BUILD_DIR" -type f -print0 |
            xargs -0 stat -f "%m" |
            sort -n |
            tail -1
    )
else
    NEWEST_BUILD_FILE_TIME=0
fi

# Display the newest modified source file
echo "📄 Newest source file: $NEWEST_SRC_FILE_NAME (modified at $NEWEST_SRC_FILE_TIME)"

# Compare times and rebuild if needed
if [ "$NEWEST_SRC_FILE_TIME" -gt "$NEWEST_BUILD_FILE_TIME" ]; then
    echo "🗑️ Source files updated. Removing and rebuilding build directory..."
    rm -rf "$BUILD_DIR"
    cmake -S "$ROOT_DIR" -B "$BUILD_DIR"
    cmake --build "$BUILD_DIR"
    echo "🏗️ Build completed successfully."
else
    echo "✅ Build is up-to-date. No action needed."
fi
