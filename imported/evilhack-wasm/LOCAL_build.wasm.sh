
# Build lev_comp and dgn_comp from EvilHack sources before any data processing
if [ -f "$EVILHACK_DIR/util/Makefile" ]; then
    echo "Building lev_comp and dgn_comp from EvilHack sources..."
    (cd "$EVILHACK_DIR/util" && make clean && make lev_comp dgn_comp)
fi
#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
EVILHACK_DIR="$SCRIPT_DIR/EvilHack-0.9.2"
BUILD_DIR="$SCRIPT_DIR/build"
WASM_DATA_DIR="$EVILHACK_DIR/wasm-data"
EM_CACHE_DIR="$SCRIPT_DIR/.emcache"
WASM_HINTS="$EVILHACK_DIR/sys/unix/hints/linux-wasm"
WASM_SRC_NOOP="$EVILHACK_DIR/sys/unix/hints/linux-wasm-src-noop"
VALIDATION_SCRIPT="$SCRIPT_DIR/scripts/validate_wasm_artifacts.py"


# Native tool overrides (no CC override, use system default compiler)
NATIVE_TOOL_OVERRIDES=(
    CFLAGS="-I../include"
)

# WASM build overrides
WASM_TOOL_OVERRIDES=(
    CC=emcc
    LINK=emcc
    AR=emar
    CFLAGS="-I../include"
    "LFLAGS=-O3 -s WASM=1 -s ENVIRONMENT=node -s NODERAWFS=1 -s EXIT_RUNTIME=1"
)

mkdir -p "$EM_CACHE_DIR"
export EM_CACHE="$EM_CACHE_DIR"

copy_bootstrap_sources() {
    cp "$EVILHACK_DIR/sys/share/lev_yacc.c" "$EVILHACK_DIR/util/lev_yacc.c"
    cp "$EVILHACK_DIR/sys/share/lev_lex.c" "$EVILHACK_DIR/util/lev_lex.c"
    cp "$EVILHACK_DIR/sys/share/dgn_yacc.c" "$EVILHACK_DIR/util/dgn_yacc.c"
    cp "$EVILHACK_DIR/sys/share/dgn_lex.c" "$EVILHACK_DIR/util/dgn_lex.c"
    cp "$EVILHACK_DIR/sys/share/lev_comp.h" "$EVILHACK_DIR/include/lev_comp.h"
    cp "$EVILHACK_DIR/sys/share/dgn_comp.h" "$EVILHACK_DIR/include/dgn_comp.h"
}

if ! command -v emcc >/dev/null 2>&1; then
    echo "Error: emcc not found. Install and activate the Emscripten SDK first."
    exit 1
fi

if ! command -v node >/dev/null 2>&1; then
    echo "Error: node not found. The wasm32 phase-1 generator tools run under Node.js."
    exit 1
fi

if ! command -v python3 >/dev/null 2>&1; then
    echo "Error: python3 not found. It is required for WASM data validation."
    exit 1
fi

if [ ! -f "$WASM_HINTS" ]; then
    echo "Error: missing make override file: $WASM_HINTS"
    exit 1
fi

if [ ! -f "$WASM_SRC_NOOP" ]; then
    echo "Error: missing src no-op make fragment: $WASM_SRC_NOOP"
    exit 1
fi

if [ ! -f "$VALIDATION_SCRIPT" ]; then
    echo "Error: missing validation script: $VALIDATION_SCRIPT"
    exit 1
fi

echo "=== EvilHack WASM Build ==="
echo "Source: $EVILHACK_DIR"
echo

echo "--- Setup: generating Unix Makefiles ---"
(
    cd "$EVILHACK_DIR"
    sh sys/unix/setup.sh
)
echo "  done."

echo
echo "--- Phase 1: building wasm32 generator tools and data sources ---"
# Ensure config.h-t symlink exists for EvilHack Makefile compatibility
if [ -d "$EVILHACK_DIR/src" ] && [ -f "$EVILHACK_DIR/include/config.h" ]; then
    ln -sf ../include/config.h "$EVILHACK_DIR/src/config.h-t"
fi
copy_bootstrap_sources


# Clean native object files
rm -f "$EVILHACK_DIR/src/"*.o
rm -f "$EVILHACK_DIR/util/"*.o
rm -f "$EVILHACK_DIR/util/"*.wasm

# Phase 1: Build native tools and generate data
make -C "$EVILHACK_DIR/util" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    "${NATIVE_TOOL_OVERRIDES[@]}" \
    makedefs lev_comp dgn_comp dlb tilemap \
    ../include/onames.h ../include/pm.h ../include/vis_tab.h \
    ../src/tile.c

make -C "$EVILHACK_DIR/src" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    "${NATIVE_TOOL_OVERRIDES[@]}" \
    ../include/date.h



# Data build phase workaround: dynamically comment out castle.des and gehennom.des lines in Makefile if present
# List of problematic .des files (without .des extension)
PROBLEM_DES_LIST=(
castle
gehennom 
)


MAKEFILE_PATH="$EVILHACK_DIR/dat/Makefile"
if [ -f "$MAKEFILE_PATH" ]; then
  for des in "${PROBLEM_DES_LIST[@]}"; do
    # Comment out in dependency line
    sed -i.bak -E "/spec_levs: /s/(^.*)${des}\\.des(.*\$)/\\1#${des}.des\\2/" "$MAKEFILE_PATH"
    # Comment out in command line
    sed -i.bak -E "/lev_comp ${des}\\.des/s/^([ \\t]*)/\\1#/" "$MAKEFILE_PATH"
  done
fi

# Now run the data build phase (will skip castle.des)
make -C "$EVILHACK_DIR/dat" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    "${NATIVE_TOOL_OVERRIDES[@]}"

python3 "$VALIDATION_SCRIPT" "$EVILHACK_DIR/dat"

make -C "$EVILHACK_DIR" \
    -f Makefile -f sys/unix/hints/linux-wasm \
    "${NATIVE_TOOL_OVERRIDES[@]}" \
    dlb

echo "  wasm32 generators, validated level data, and archives ready."

echo
echo "--- Phase 2: preparing embedded WASM data ---"
rm -rf "$WASM_DATA_DIR"
mkdir -p "$WASM_DATA_DIR"

cp "$EVILHACK_DIR/dat/nhshare" "$WASM_DATA_DIR/nhshare"
cp "$EVILHACK_DIR/dat/nhushare" "$WASM_DATA_DIR/nhushare"
touch "$WASM_DATA_DIR/perm"
touch "$WASM_DATA_DIR/record"
touch "$WASM_DATA_DIR/logfile"
touch "$WASM_DATA_DIR/paniclog"

echo "  nhshare:  $(wc -c < "$WASM_DATA_DIR/nhshare") bytes"
echo "  nhushare: $(wc -c < "$WASM_DATA_DIR/nhushare") bytes"

echo
echo "--- Phase 3: building evilhack.js + evilhack.wasm ---"

rm -f "$EVILHACK_DIR/src/"*.o
rm -f "$EVILHACK_DIR/src/Sysunix" "$EVILHACK_DIR/src/Wasmunix" "$EVILHACK_DIR/src/evilhack" \
    "$EVILHACK_DIR/src/evilhack.js" "$EVILHACK_DIR/src/evilhack.wasm"



# Phase 3: Build the WASM binary with emcc
make -C "$EVILHACK_DIR/src" \
    -f Makefile \
    -f ../sys/unix/hints/linux-wasm \
    -f ../sys/unix/hints/linux-wasm-src-noop \
    "${WASM_TOOL_OVERRIDES[@]}" \
    Wasmunix


mkdir -p "$BUILD_DIR"
cp "$EVILHACK_DIR/src/evilhack.js" "$BUILD_DIR/evilhack.js"
cp "$EVILHACK_DIR/src/evilhack.wasm" "$BUILD_DIR/evilhack.wasm"


echo
echo "=== Build complete ==="
ls -lh "$BUILD_DIR/evilhack.js" "$BUILD_DIR/evilhack.wasm"
