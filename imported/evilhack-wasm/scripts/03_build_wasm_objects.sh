#!/bin/bash
set -e
EH_SRC_WASM="$(dirname "$0")/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"
cd "$EH_SRC_WASM"
echo "[WASM] Building WASM objects and game..."
make clean
export EMCC_CFLAGS="-sEXPORTED_RUNTIME_METHODS='[\"cwrap\",\"ccall\",\"addFunction\",\"removeFunction\",\"UTF8ToString\",\"stringToUTF8\",\"getValue\",\"setValue\",\"ENV\",\"FS\",\"IDBFS\",\"updateMemoryViews\"]' $EMCC_CFLAGS"
make evilhack || true
export PATH="${PATH#*:}"
unset EMCC_ORIG EMCC_TMPDIR
cd -
