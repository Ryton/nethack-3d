#!/usr/bin/env bash
# copy-evilhack-wasm_js.sh
# Copies evilhack.js and evilhack.wasm from the build directory to the public directory using relative paths.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"
PUBLIC_DIR="${SCRIPT_DIR}/../../public"

# Ensure destination exists
mkdir -p "$PUBLIC_DIR"

# Copy files
cp "$BUILD_DIR/evilhack.js" "$PUBLIC_DIR/"
cp "$BUILD_DIR/evilhack.wasm" "$PUBLIC_DIR/"

echo "Copied evilhack.js and evilhack.wasm to $PUBLIC_DIR"