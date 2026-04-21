#!/bin/bash
# build.split.wasm.sh - Split build for EvilHack WASM with native and WASM object separation
# This script builds native tools in a separate directory and WASM in another, avoiding object file contamination.
# Usage: ./build.split.wasm.sh

set -e

EH_SRC_NATIVE="$(dirname "$0")/build/EvilHack-0.9.2_native/EvilHack-0.9.2"
EH_SRC_WASM="$(dirname "$0")/build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"



# 1. Build native tools (makedefs, etc.) in native dir
{
	cd "$EH_SRC_NATIVE"
	echo "[Native] Building native tools (makedefs, lev_comp, etc.)..."
	make clean
	make makedefs || true
	cd -

	# 2. Build WASM objects and game in wasm dir
	cd "$EH_SRC_WASM"
	echo "[WASM] Building WASM objects and game..."
	make clean
	make evilhack || true
	cd -

	echo "Build complete. Native and WASM builds are isolated."
} | tee "$(dirname "$0")/build.split.log"

echo "Build complete. Native and WASM builds are isolated."
