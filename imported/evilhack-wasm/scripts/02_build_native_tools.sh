#!/bin/bash
set -e
EH_SRC_NATIVE="$(dirname "$0")/../build/EvilHack-0.9.2_native/EvilHack-0.9.2"
cd "$EH_SRC_NATIVE"
echo "[Native] Building native tools (makedefs, lev_comp, etc.)..."
make clean
make makedefs || true
cd -
