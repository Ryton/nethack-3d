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

echo
echo "--- Phase 1: building wasm32 generator tools and data sources ---"

# Workaround: copy config.h to src/ so Makefile can find it
cp -f "$EVILHACK_DIR/include/config.h" "$EVILHACK_DIR/src/config.h"

rm -f "$EVILHACK_DIR/src/"*.o
rm -f "$EVILHACK_DIR/util/"*.o

# Phase 1: build makedefs/tools (no window system defines)
make -C "$EVILHACK_DIR/util" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    "${TOOL_OVERRIDES[@]}" \
    makedefs lev_comp dgn_comp dlb tilemap \
    ../include/onames.h ../include/pm.h ../include/vis_tab.h \
    ../src/tile.c
make -C "$EVILHACK_DIR/src" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    "${TOOL_OVERRIDES[@]}" \
    ../include/date.h

# If you have a validation script, run it here (optional)
# python3 "$SCRIPT_DIR/scripts/validate_wasm_artifacts.py" "$EVILHACK_DIR/dat"

echo
echo "--- Phase 2: preparing embedded WASM data ---"
rm -rf "$WASM_DATA_DIR"
mkdir -p "$WASM_DATA_DIR"
# Add any data copy/touch steps here as needed

echo
echo "--- Phase 3: building evilhack.js + evilhack.wasm ---"
rm -f "$EVILHACK_DIR/src/"*.o
rm -f "$EVILHACK_DIR/src/Sysunix" "$EVILHACK_DIR/src/Wasmunix" "$EVILHACK_DIR/src/evilhack" \
    "$EVILHACK_DIR/src/evilhack.js" "$EVILHACK_DIR/src/evilhack.wasm"

make -C "$EVILHACK_DIR/src" \
    -f Makefile \
    -f ../sys/unix/hints/linux-wasm \
    -f ../sys/unix/hints/linux-wasm-src-noop \
    "${TOOL_OVERRIDES[@]}" \
    CFLAGS+="$WASM_GAME_CFLAGS -I../include" \
    Wasmunix
mkdir -p "$BUILD_DIR"
cp "$EVILHACK_DIR/src/evilhack.js" "$BUILD_DIR/evilhack.js"
cp "$EVILHACK_DIR/src/evilhack.wasm" "$BUILD_DIR/evilhack.wasm"

echo
echo "=== Build complete ==="
ls -lh "$BUILD_DIR/evilhack.js" "$BUILD_DIR/evilhack.wasm"
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
EVILHACK_DIR="$SCRIPT_DIR/EvilHack-0.9.2"
BUILD_DIR="$SCRIPT_DIR/build"
WASM_DATA_DIR="$SCRIPT_DIR/wasm_data"


# === WASM build uses shim window system, not tty ===

patch_makefile_for_emcc() {
  echo "==================== PATCHING util/Makefile FOR WASM OBJECTS ===================="
  sed -i.bak \
    # WASM build: use shim window system, not tty
    # (No need to patch for tty defines)
  echo \"==================== DONE PATCHING util/Makefile ====================\"
}

# === NATIVE TOOL/HEADER BUILD (makedefs, tilemap, etc.) ===
# ...existing code for native build...

# === ENSURE CLEAN STATE BEFORE WASM TOOL BUILD ===
echo "==================== make clean in src/ and util/ BEFORE WASM TOOL BUILD ===================="
make -C "$EVILHACK_DIR/src" clean
make -C "$EVILHACK_DIR/util" clean
echo "==================== DONE make clean ===================="

# === LOGGING AROUND LEV_COMP LINK STEP ===
echo "==================== ABOUT TO LINK lev_comp WITH EMCC ===================="
echo "===== DIAGNOSTIC: file types of .o files before WASM tool build (PRE-LINK) ====="
file "$EVILHACK_DIR/src/"*.o || true
file "$EVILHACK_DIR/util/"*.o || true
echo "===== END DIAGNOSTIC ====="

# Run make and always run diagnostic after, even if make fails
set +e
make -C "$EVILHACK_DIR/util" \
        -f Makefile -f ../sys/unix/hints/linux-wasm \
        lev_comp dgn_comp dlb tilemap \
        ../src/tile.c
MAKE_STATUS=$?
echo "===== POST-LINK DIAGNOSTIC: file types of .o files after failed link ====="
file "$EVILHACK_DIR/src/"*.o || true
ls -l "$EVILHACK_DIR/src/"*.o || true
echo "===== END POST-LINK DIAGNOSTIC ====="
set -e
# Optionally, exit if make failed
if [ $MAKE_STATUS -ne 0 ]; then
    exit $MAKE_STATUS
fi
echo "==================== FINISHED LINKING lev_comp ===================="
make -C "$EVILHACK_DIR/util" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    lev_comp dgn_comp dlb tilemap \
    ../src/tile.c
echo "==================== FINISHED LINKING lev_comp ===================="
# Create a dummy makedefs.o for emcc to link (WASM phase)
echo 'int main() { return 0; }' | emcc -x c -c -o "$EVILHACK_DIR/util/makedefs.o" -
#!/usr/bin/env bash


# Ensure hints/linux-wasm exists, copy from slashem-wasm if missing
if [ ! -f "$EVILHACK_DIR/sys/unix/hints/linux-wasm" ]; then
    echo "Missing $EVILHACK_DIR/sys/unix/hints/linux-wasm, attempting to copy from slashem-wasm..."
    cp "$SCRIPT_DIR/../slashem-wasm/slashem-0.0.7E7F3/sys/unix/hints/linux-wasm" "$EVILHACK_DIR/sys/unix/hints/linux-wasm" \
    || { echo "Failed to copy linux-wasm hints file. Please copy manually."; exit 1; }
fi
# Ensure hints/linux-wasm exists, copy from slashem-wasm if missing






# === EvilHack Native Tool & Header Rebuild (only once, at the start) ===
echo "===== PHASE 1.4: Preserving native .o files before WASM phase ====="
for obj in alloc.o panic.o drawing.o decl.o monst.o objects.o; do
    OBJ_PATH="$EVILHACK_DIR/src/$obj"
    if [ -f "$OBJ_PATH" ]; then
        cp -f "$OBJ_PATH" "$OBJ_PATH.native"
        echo "  Preserved $obj as $obj.native"
    fi
done
echo "===== END PHASE 1.4 ====="
echo "--- Native EvilHack tool & header rebuild (makedefs, lev_comp, dgn_comp, dlb, tilemap, headers) ---"
cd "$EVILHACK_DIR"
# Always export CFLAGS with absolute include path so Makefile finds config.h
if [ -z "${CFLAGS+x}" ]; then
    export CFLAGS="-I$EVILHACK_DIR/include"
else
    export CFLAGS="$CFLAGS -I$EVILHACK_DIR/include"
fi
sudo chattr -i util/makedefs util/lev_comp util/dgn_comp util/dlb util/tilemap 2>/dev/null || true
make clean
cd sys/unix && sh setup.sh hints/linux
cd ../..
# Check for config.h after setup
if [ ! -f include/config.h ]; then
    echo "ERROR: include/config.h was not generated. Check sys/unix/setup.sh output and dependencies."
    exit 1
fi
sudo chattr -i util/makedefs util/lev_comp util/dgn_comp util/dlb util/tilemap 2>/dev/null || true
make -C util CC=gcc makedefs
make -C util CC=gcc lev_comp dgn_comp dlb tilemap

# --- Phase 1.5: Build tilemap natively and generate tile.c ---
echo
# Function to patch util/Makefile at runtime
patch_makefile_for_tilemap_native() {
  MAKEFILE="$EVILHACK_DIR/util/Makefile"
  if [ -f "$MAKEFILE" ]; then
    sed -i 's|^\(../src/tile\.c: tilemap\)$|../src/tile.c: tilemap.native|' "$MAKEFILE"
    sed -i 's|^[[:space:]]*\./tilemap$|\t./tilemap.native|' "$MAKEFILE"
    echo "Patched util/Makefile to use tilemap.native for tile.c generation."
  fi
}

make -C util CC=gcc tilemap
if [ -x util/tilemap ]; then
    (cd util && ./tilemap)
else
    echo "ERROR: util/tilemap not built or not executable!"
    exit 1
fi
ls -l src/tile.c || ls -l ../src/tile.c || echo "tile.c not found!"
# Save native tilemap binary for later restore
cp util/tilemap util/tilemap.native
patch_makefile_for_tilemap_native

echo "===== END OF PHASE 1.5 ====="

# --- PHASE 1.6: Backup all native .o files as .o.native after native build ---
echo "===== PHASE 1.6: Backing up native .o files after native build ====="
for obj in alloc.o panic.o drawing.o decl.o monst.o objects.o; do
    OBJ_PATH="$EVILHACK_DIR/src/$obj"
    if [ -f "$OBJ_PATH" ]; then
        cp -f "$OBJ_PATH" "$OBJ_PATH.native"
        echo "  Backed up $obj as $obj.native"
    fi
done

# ...after PHASE 1.6 (backups) and before any emcc build...
patch_makefile_for_emcc
echo "===== END PHASE 1.6 ====="

echo "===== PHASE 2.3: Restoring native .o files before native tool/header build ====="
for obj in alloc.o panic.o drawing.o decl.o monst.o objects.o; do
    OBJ_PATH="$EVILHACK_DIR/src/$obj"
    NATIVE_OBJ="$OBJ_PATH.native"
    if [ -f "$NATIVE_OBJ" ]; then
        cp -f "$NATIVE_OBJ" "$OBJ_PATH"
        echo "  Restored $obj from $obj.native for native tool build."
    else
        echo "  $obj.native not found, will be rebuilt if needed."
    fi
done
UTIL_MAKEDEFS_O="$EVILHACK_DIR/util/makedefs.o"
UTIL_MAKEDEFS_O_NATIVE="$UTIL_MAKEDEFS_O.native"
if [ -f "$UTIL_MAKEDEFS_O_NATIVE" ]; then
    cp -f "$UTIL_MAKEDEFS_O_NATIVE" "$UTIL_MAKEDEFS_O"
    echo "  Restored util/makedefs.o from util/makedefs.o.native for native tool build."
else
    echo "  util/makedefs.o.native not found, will be rebuilt if needed."
fi
echo "===== END PHASE 2.3 ====="
echo "===== PHASE 2.4: Ensuring WASM .o files for lev_comp/dgn_comp ====="
for obj in alloc.o panic.o drawing.o decl.o monst.o objects.o; do
    OBJ_PATH="$EVILHACK_DIR/src/$obj"
    if [ -f "$OBJ_PATH" ]; then
        FILE_TYPE=$(file -b "$OBJ_PATH")
        if [[ "$FILE_TYPE" != *"WebAssembly"* ]]; then
            echo "  Rebuilding $obj as WASM object..."
            rm -f "$OBJ_PATH"
            make -C "$EVILHACK_DIR/src" -f Makefile -f ../sys/unix/hints/linux-wasm CC=emcc $obj
        else
            echo "  $obj is already a WASM object."
        fi
    else
        echo "  $obj does not exist, will be built as needed."
    fi
done
echo "===== END PHASE 2.4 ====="
# --- PHASE 2.5: About to build WASM tools (lev_comp, etc.) ---
echo "===== PHASE 2.5: About to build WASM tools (lev_comp, dgn_comp, dlb, tilemap, ../src/tile.c) ====="
# Diagnostic: print file types of all .o files before WASM tool build
echo "===== DIAGNOSTIC: file types of .o files before WASM tool build ====="
file "$EVILHACK_DIR/src/"*.o || true
file "$EVILHACK_DIR/util/"*.o || true
echo "===== END DIAGNOSTIC ====="
# WASM tool build (lev_comp, dgn_comp, dlb, tilemap, ../src/tile.c)
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

# Replace tilemap with a dummy script to prevent WASM execution errors
echo -e '#!/bin/sh\necho "(dummy tilemap: skipping run)"\nexit 0' > "$EVILHACK_DIR/util/tilemap"
chmod +x "$EVILHACK_DIR/util/tilemap"
if [ -f include/Makefile ] || [ -f include/makefile ]; then
    make -C include
fi
make -C src CC=gcc ../include/onames.h ../include/pm.h ../include/vis_tab.h
make -C src CC=gcc ../include/date.h
ls -l util/makedefs util/lev_comp util/dgn_comp util/dlb util/tilemap
ls -l include/onames.h include/pm.h include/vis_tab.h include/date.h
echo
echo "===== END OF PHASE 1 ====="
echo
cd "$SCRIPT_DIR"
WASM_HINTS="$EVILHACK_DIR/sys/unix/hints/linux-wasm"
WASM_SRC_NOOP="$EVILHACK_DIR/sys/unix/hints/linux-wasm-src-noop"
VALIDATION_SCRIPT="$SCRIPT_DIR/scripts/validate_wasm_artifacts.py"



# Native tool overrides (force native compiler, never emcc)
NATIVE_TOOL_OVERRIDES=(
    CC= 
    LINK= 
    AR= 
    CFLAGS="-I../include"
)

# WASM build overrides (for main binary only)
WASM_TOOL_OVERRIDES=(
    CC=emcc
    LINK=emcc
    AR=emar
    CFLAGS="-I../include"
    "LFLAGS=-O3 -s WASM=1 -s ENVIRONMENT=node -s NODERAWFS=1 -s EXIT_RUNTIME=1"
    # Full export list for main WASM binary only
    "-s EXPORTED_FUNCTIONS='[\"_main\", \"_malloc\", \"_free\", \"_shim_graphics_set_callback\", \"_nh3d_glyph_at\", \"_nh_top_item_glyph_under_player\", \"_recover_savefile\", \"_resume_checkpoint_save\", \"_hack_save\", \"_hack_restore\", \"_nh_wasm_init\"]'"
    "-s EXPORTED_RUNTIME_METHODS='[\"cwrap\", \"ccall\", \"addFunction\", \"removeFunction\", \"UTF8ToString\", \"stringToUTF8\", \"getValue\", \"setValue\", \"ENV\", \"FS\", \"IDBFS\"]'"
)

EM_CACHE_DIR="$SCRIPT_DIR/.emcache"

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
 