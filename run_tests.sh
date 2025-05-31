#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"

# Check if build directory exists and is not empty
if [ ! -d "$BUILD_DIR" ] || [ -z "$(ls -A "$BUILD_DIR")" ]; then
  echo "📦 Build directory missing or empty. Building project..."
  rm -rf "$BUILD_DIR"
  cmake -S "$ROOT_DIR" -B "$BUILD_DIR"
  cmake --build "$BUILD_DIR"
else
  echo "✅ Build directory found. Skipping CMake generation..."
fi

# Go to build folder
cd "$BUILD_DIR" || exit 1

# Find all *_tests executables
echo "🔍 Searching for test executables..."
test_bins=$(find . -type f -name '*_tests' -perm +111)

if [[ -z "$test_bins" ]]; then
  echo "❌ No test executables found."
  exit 1
fi

# Run each test executable
all_passed=true
for test_bin in $test_bins; do
  echo "🚀 Running $test_bin"
  "./$test_bin"
  result=$?
  if [ $result -ne 0 ]; then
    echo "❌ Test failed: $test_bin"
    all_passed=false
  else
    echo "✅ Test passed: $test_bin"
  fi
  echo "----------------------------"
done

if $all_passed; then
  echo "🎉 All tests passed!"
  exit 0
else
  echo "❌ Some tests failed."
  exit 1
fi
