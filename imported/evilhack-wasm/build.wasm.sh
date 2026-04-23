patch_makefile_for_emcc() {
    # Patch Makefile for emcc if needed (placeholder, no-op for now)
    :
}

copy_bootstrap_sources() {
    cp "$EVILHACK_DIR/sys/share/lev_yacc.c" "$EVILHACK_DIR/util/lev_yacc.c"
    cp "$EVILHACK_DIR/sys/share/lev_lex.c" "$EVILHACK_DIR/util/lev_lex.c"
    cp "$EVILHACK_DIR/sys/share/dgn_yacc.c" "$EVILHACK_DIR/util/dgn_yacc.c"
    cp "$EVILHACK_DIR/sys/share/dgn_lex.c" "$EVILHACK_DIR/util/dgn_lex.c"
    cp "$EVILHACK_DIR/sys/share/lev_comp.h" "$EVILHACK_DIR/include/lev_comp.h"
    cp "$EVILHACK_DIR/sys/share/dgn_comp.h" "$EVILHACK_DIR/include/dgn_comp.h"
}

# 7. Remove makedefs.o to prevent Makefile linker error
rm -f "$EVILHACK_DIR/util/makedefs.o"
export PATH="$HOME/repos/emsdk/upstream/emscripten:$(cd "$SCRIPT_DIR/../../.." && pwd):$PATH"
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
EVILHACK_DIR="$SCRIPT_DIR/EvilHack-0.9.2"
BUILD_DIR="$SCRIPT_DIR/build"
WASM_DATA_DIR="$SCRIPT_DIR/wasm_data"
EM_CACHE_DIR="$SCRIPT_DIR/.emcache"
WASM_HINTS="$EVILHACK_DIR/sys/unix/hints/linux-wasm"
WASM_SRC_NOOP="$EVILHACK_DIR/sys/unix/hints/linux-wasm-src-noop"
TOOL_OVERRIDES=(
    CC=emcc
    LINK=emcc
    AR=emar
    "LFLAGS=-O3 -s WASM=1 -s ENVIRONMENT=node -s NODERAWFS=1 -s EXIT_RUNTIME=1"
)

# Extra CFLAGS for WASM game build (not for makedefs/tools phase)
WASM_GAME_CFLAGS="-I$EVILHACK_DIR/include -DDEFAULT_WINDOW_SYS=\\\"shim\\\" -DSHIM_GRAPHICS=1"
mkdir -p "$EM_CACHE_DIR"
export EM_CACHE="$EM_CACHE_DIR"

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
echo "=== EvilHack WASM Build ==="
echo "Source: $EVILHACK_DIR"
echo

echo "--- Setup: generating Unix Makefiles ---"
(
    cd "$EVILHACK_DIR"
    sh sys/unix/setup.sh
)
echo "  done."


# Skipping native tool build/clean steps; using existing makedefs, lev_comp, dgn_comp, dlb, tilemap.
echo "  Skipped native tool build steps; using existing makedefs, lev_comp, dgn_comp, dlb, tilemap."

# Only build the WASM binary (Wasmunix) with emcc and correct overrides


echo
echo "--- Phase 1: building wasm32 generator tools and data sources ---"
# Ensure config.h-t symlink exists for EvilHack Makefile compatibility
if [ -d "$EVILHACK_DIR/src" ] && [ -f "$EVILHACK_DIR/include/config.h" ]; then
    ln -sf ../include/config.h "$EVILHACK_DIR/src/config.h-t"
fi
copy_bootstrap_sources

# Clean all native object files before WASM tool build to force emcc rebuild
echo
echo "==================== CLEANING ALL .o FILES BEFORE WASM TOOL BUILD ===================="
rm -fv "$EVILHACK_DIR/src/"*.o
rm -fv "$EVILHACK_DIR/util/"*.o
echo "==================== DONE CLEANING .o FILES ===================="
rm -f "$EVILHACK_DIR/util/"*.wasm


bash copy-evilhack-wasm_js.sh



# No further native tool rebuilds or unprotects needed during WASM build
chmod +x "$EVILHACK_DIR/util"/*




# --- Always use native makedefs for header generation before switching to emcc ---
echo "--- Generating headers with native makedefs (gcc) ---"
make -C "$EVILHACK_DIR/util" CC=gcc makedefs
make -C "$EVILHACK_DIR/src" CC=gcc ../include/onames.h ../include/pm.h ../include/vis_tab.h
make -C "$EVILHACK_DIR/src" CC=gcc ../include/date.h
# Touch headers so make sees them as up-to-date
touch "$EVILHACK_DIR/include/onames.h" "$EVILHACK_DIR/include/pm.h" "$EVILHACK_DIR/include/vis_tab.h" "$EVILHACK_DIR/include/date.h"
# Replace makedefs with a dummy script to prevent WASM execution
echo -e '#!/bin/sh\necho "(dummy makedefs: skipping run)"\nexit 0' > "$EVILHACK_DIR/util/makedefs"
chmod +x "$EVILHACK_DIR/util/makedefs"
# Touch makedefs and all generated headers with a future timestamp to prevent any rebuild or rerun
FUTURE_DATE=$(date -d "+2 years" +%Y%m%d%H%M.%S)
touch -t $FUTURE_DATE \
    "$EVILHACK_DIR/util/makedefs" \
    "$EVILHACK_DIR/include/onames.h" \
    "$EVILHACK_DIR/include/pm.h" \
    "$EVILHACK_DIR/include/vis_tab.h" \
    "$EVILHACK_DIR/include/date.h"

# Now, right before WASM build, create a dummy makedefs.o as a WASM object (emcc)
echo 'int main() { return 0; }' | emcc -x c -c -o "$EVILHACK_DIR/util/makedefs.o" -


# --- Now switch to emcc for WASM object and tool build ---
echo "--- Patching Makefile for emcc for WASM phase ---"
patch_makefile_for_emcc
echo "--- Forcing rebuild of all src/*.o with emcc for WASM phase ---"
echo "--- Pre-build mtimes ---"
ls -l --full-time "$EVILHACK_DIR/src/alloc.o" "$EVILHACK_DIR/src/decl.o" "$EVILHACK_DIR/src/drawing.o" "$EVILHACK_DIR/src/monst.o" "$EVILHACK_DIR/src/objects.o" || true
rm -f "$EVILHACK_DIR/src/alloc.o" "$EVILHACK_DIR/src/decl.o" "$EVILHACK_DIR/src/drawing.o" "$EVILHACK_DIR/src/monst.o" "$EVILHACK_DIR/src/objects.o"
for obj in alloc.o panic.o drawing.o decl.o monst.o objects.o; do
    make -C "$EVILHACK_DIR/src" -f Makefile -f ../sys/unix/hints/linux-wasm CC=emcc V=1 "$obj"
done
echo "--- Post-build mtimes ---"
ls -l --full-time "$EVILHACK_DIR/src/alloc.o" "$EVILHACK_DIR/src/decl.o" "$EVILHACK_DIR/src/drawing.o" "$EVILHACK_DIR/src/monst.o" "$EVILHACK_DIR/src/objects.o" || true

 # Now build WASM tools (lev_comp, etc.) with emcc and WASM objects

make -C "$EVILHACK_DIR/util" \
        -f Makefile -f ../sys/unix/hints/linux-wasm \
        lev_comp dgn_comp dlb tilemap \
        ../src/tile.c

# Restore native tilemap binary after WASM build overwrites it
if [ -f "$EVILHACK_DIR/util/tilemap.native" ]; then
    cp "$EVILHACK_DIR/util/tilemap.native" "$EVILHACK_DIR/util/tilemap"
    chmod +x "$EVILHACK_DIR/util/tilemap"
    echo "Restored native tilemap binary after WASM build."
fi

make -C "$EVILHACK_DIR/src" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    ../include/date.h

make -C "$EVILHACK_DIR/dat" \
    -f Makefile -f ../sys/unix/hints/linux-wasm

python3 "$VALIDATION_SCRIPT" "$EVILHACK_DIR/dat"


make -C "$EVILHACK_DIR" \
    -f Makefile -f sys/unix/hints/linux-wasm \
    CC= LINK= AR= "${NATIVE_TOOL_OVERRIDES[@]}" \
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




# Phase 3: Build the WASM binary with emcc (add EXPORTED_FUNCTIONS/EXPORTED_RUNTIME_METHODS only here)
EXPORTED_FLAGS=(
    -s EXPORTED_FUNCTIONS='["_main", "_malloc", "_free", "_shim_graphics_set_callback", "_nh3d_glyph_at", "_nh_top_item_glyph_under_player", "_recover_savefile", "_resume_checkpoint_save", "_hack_save", "_hack_restore", "_nh_wasm_init"]'
    -s EXPORTED_RUNTIME_METHODS='["cwrap", "ccall", "addFunction", "removeFunction", "UTF8ToString", "stringToUTF8", "getValue", "setValue", "ENV", "FS", "IDBFS"]'
)
make -C "$EVILHACK_DIR/src" \
    -f Makefile \
    -f ../sys/unix/hints/linux-wasm \
    -f ../sys/unix/hints/linux-wasm-src-noop \
    "${WASM_TOOL_OVERRIDES[@]}" \
    LFLAGS+=" ${EXPORTED_FLAGS[*]}" \
    Wasmunix

echo
echo "--- Phase 3: building slashem.js + slashem.wasm ---"
rm -f "$EVILHACK_DIR/src/"*.o
rm -f "$EVILHACK_DIR/src/Sysunix" "$EVILHACK_DIR/src/Wasmunix" "$EVILHACK_DIR/src/slashem" \
    "$EVILHACK_DIR/src/slashem.js" "$EVILHACK_DIR/src/slashem.wasm"

## copy to other dirs
mkdir -p "$BUILD_DIR"
cp "$EVILHACK_DIR/src/evilhack.js" "$BUILD_DIR/evilhack.js"
# Patch evilhack.js to assign FS to Module.FS after Module is created
sed -i '/async function Module(moduleArg = {}) {/a \\n  // Patch: Ensure Module.FS is assigned to prevent recursion error\n  if (typeof FS !== '\''undefined'\'') Module.FS = FS;\n' "$BUILD_DIR/evilhack.js"
cp "$EVILHACK_DIR/src/evilhack.wasm" "$BUILD_DIR/evilhack.wasm"


echo
echo "=== Build complete ==="
ls -lh "$BUILD_DIR/evilhack.js" "$BUILD_DIR/evilhack.wasm"

# Patch util/Makefile at runtime to use tilemap.native for tile.c generation (using sed) before WASM tool build
MAKEFILE="$EVILHACK_DIR/util/Makefile"
if [ -f "$MAKEFILE" ]; then
  sed -i 's|^\(../src/tile\.c: tilemap\)$|../src/tile.c: tilemap.native|' "$MAKEFILE"
  sed -i 's|^[[:space:]]*\./tilemap$|\t./tilemap.native|' "$MAKEFILE"
  echo "Patched util/Makefile to use tilemap.native for tile.c generation (pre-WASM build)."
fi
