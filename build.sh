#!/bin/bash
# Configure and build. CMake already rebuilds only what changed, so no
# freshness checks are needed here.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

cmake -S "$ROOT_DIR" -B "$ROOT_DIR/build"
cmake --build "$ROOT_DIR/build" --parallel
