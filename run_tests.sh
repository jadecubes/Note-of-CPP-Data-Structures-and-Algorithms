#!/bin/bash
# Build (incremental) and run the whole test suite through ctest.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

"$ROOT_DIR/build.sh"
ctest --test-dir "$ROOT_DIR/build" --output-on-failure --no-tests=error
