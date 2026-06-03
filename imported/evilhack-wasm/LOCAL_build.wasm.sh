#!/usr/bin/env bash
# LOCAL_build.wasm.sh — full EvilHack WASM build entry point.
#
# Layout:
#   build/EvilHack-${V}_native/EvilHack-${V}/   <- native tree (gcc/clang)
#                                                  builds makedefs, lev_comp,
#                                                  dgn_comp, dlb, tilemap and
#                                                  generates onames.h, pm.h,
#                                                  vis_tab.h, date.h, tile.c,
#                                                  nhshare, nhushare, nhdat
#   build/EvilHack-${V}_wasm/EvilHack-${V}/     <- emcc tree (with SHIM_GRAPHICS
#                                                  patches). Receives generated
#                                                  headers + data from native
#                                                  tree, then links evilhack.{js,wasm}
#
# Both trees are rsync'd from the wasm tree on first use, so the wasm tree is
# treated as the source-of-truth (it carries the SHIM_GRAPHICS patches). The
# SHIM_GRAPHICS extern in windows.c is gated behind -DSHIM_GRAPHICS so it does
# not affect the native build.
#
# Default version is 0.9.3. Override with EVILHACK_VERSION=0.9.2 for rollback.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
EVILHACK_VERSION="${EVILHACK_VERSION:-0.9.3}"
BUILD_DIR="$SCRIPT_DIR/build"
WASM_ROOT="$BUILD_DIR/EvilHack-${EVILHACK_VERSION}_wasm"
NATIVE_ROOT="$BUILD_DIR/EvilHack-${EVILHACK_VERSION}_native"
EVILHACK_DIR="$WASM_ROOT/EvilHack-${EVILHACK_VERSION}"
NATIVE_DIR="$NATIVE_ROOT/EvilHack-${EVILHACK_VERSION}"
WASM_DATA_DIR="$EVILHACK_DIR/wasm-data"
EM_CACHE_DIR="$SCRIPT_DIR/.emcache"
WASM_HINTS="$EVILHACK_DIR/sys/unix/hints/linux-wasm"
WASM_SRC_NOOP="$EVILHACK_DIR/sys/unix/hints/linux-wasm-src-noop"
VALIDATION_SCRIPT="$SCRIPT_DIR/scripts/validate_wasm_artifacts.py"

echo "=== EvilHack ${EVILHACK_VERSION} WASM build ==="
echo "WASM tree:   $EVILHACK_DIR"
echo "Native tree: $NATIVE_DIR"

if [ ! -d "$EVILHACK_DIR" ]; then
    echo "Error: WASM source tree not found at $EVILHACK_DIR" >&2
    exit 1
fi

if ! command -v emcc >/dev/null 2>&1; then
    echo "Error: emcc not found. Install/activate the Emscripten SDK first." >&2
    exit 1
fi
if ! command -v node >/dev/null 2>&1; then
    echo "Error: node not found." >&2
    exit 1
fi
if ! command -v rsync >/dev/null 2>&1; then
    echo "Error: rsync not found." >&2
    exit 1
fi

mkdir -p "$EM_CACHE_DIR"
export EM_CACHE="$EM_CACHE_DIR"

# -----------------------------------------------------------------------------
# Helpers
# -----------------------------------------------------------------------------

run_setup_and_prepare() {
    # Generate Unix Makefiles + symlink headers into src/ etc.
    local TREE="$1"
    if [ -f "$TREE/sys/unix/setup.sh" ] && [ ! -f "$TREE/src/Makefile" ]; then
        echo "  [setup] $TREE/sys/unix/setup.sh"
        (cd "$TREE" && sh sys/unix/setup.sh)
    fi
    echo "  [prepare] header symlinks for $TREE"
    EVILHACK_VERSION="$EVILHACK_VERSION" bash "$SCRIPT_DIR/scripts/00_prepare_build.sh"
}

copy_bootstrap_sources() {
    # lev_yacc.c / lev_lex.c / dgn_*.c lex/yacc outputs are shipped in
    # sys/share and need to be copied into util/ so the native lev_comp /
    # dgn_comp builds work without bison/flex.
    local TREE="$1"
    cp "$TREE/sys/share/lev_yacc.c" "$TREE/util/lev_yacc.c"
    cp "$TREE/sys/share/lev_lex.c"  "$TREE/util/lev_lex.c"
    cp "$TREE/sys/share/dgn_yacc.c" "$TREE/util/dgn_yacc.c"
    cp "$TREE/sys/share/dgn_lex.c"  "$TREE/util/dgn_lex.c"
    for h in lev_comp.h dgn_comp.h; do
        local src="$TREE/sys/share/$h"
        local dst="$TREE/include/$h"
        if [ -f "$src" ] && [ ! "$src" -ef "$dst" ]; then
            cp "$src" "$dst"
        fi
    done
}

# -----------------------------------------------------------------------------
# Phase 0a — populate native tree (rsync from wasm tree if missing).
# -----------------------------------------------------------------------------
echo
echo "--- Phase 0a: ensuring native tree at $NATIVE_DIR ---"
if [ ! -d "$NATIVE_DIR" ]; then
    mkdir -p "$NATIVE_ROOT"
    echo "  rsync $EVILHACK_DIR -> $NATIVE_DIR (initial population)"
    rsync -a --delete \
        --exclude='/wasm-data/' \
        --exclude='*.o' --exclude='*.wasm' \
        --exclude='/src/evilhack' --exclude='/src/evilhack.js' --exclude='/src/evilhack.wasm' \
        --exclude='/src/Sysunix' --exclude='/src/Wasmunix' \
        "$EVILHACK_DIR/" "$NATIVE_DIR/"
fi

# -----------------------------------------------------------------------------
# Phase 0b — setup + header symlinks for both trees.
# -----------------------------------------------------------------------------
mkdir -p "$WASM_DATA_DIR"
run_setup_and_prepare "$NATIVE_DIR"
run_setup_and_prepare "$EVILHACK_DIR"

# -----------------------------------------------------------------------------
# Phase 1 — native tools + generated data files (in NATIVE_DIR with system cc).
# -----------------------------------------------------------------------------
echo
echo "--- Phase 1: native tools + generated headers/data in $NATIVE_DIR ---"

# Regenerate lex/yacc outputs from the .y/.l grammar files so that any new
# syntax added by upstream EvilHack (e.g. 0.9.3+ .des extensions) is supported.
# The sys/share/*.{c,h} files shipped in the tarball are pre-built with the
# 0.9.2-era grammar and would fail on newer .des files.
if command -v bison >/dev/null 2>&1 && command -v flex >/dev/null 2>&1 \
        && [ -f "$NATIVE_DIR/util/lev_comp.y" ]; then
    echo "  [native] regenerating lev/dgn lex+yacc with bison/flex"
    rm -f "$NATIVE_DIR/util/lev_yacc.c" "$NATIVE_DIR/util/lev_lex.c" \
          "$NATIVE_DIR/util/dgn_yacc.c" "$NATIVE_DIR/util/dgn_lex.c" \
          "$NATIVE_DIR/include/lev_comp.h" "$NATIVE_DIR/include/dgn_comp.h"
    NATIVE_YACC_LEX_OVERRIDES=( "YACC=bison -y" "LEX=flex" )
else
    echo "  [native] bison/flex not available, falling back to sys/share bootstraps"
    copy_bootstrap_sources "$NATIVE_DIR"
    NATIVE_YACC_LEX_OVERRIDES=()
fi

# Clean any stale objects (could be wasm-format from a prior failed attempt)
rm -f "$NATIVE_DIR/src/"*.o "$NATIVE_DIR/util/"*.o

NATIVE_CFLAGS="-I../include -DDLB"

# Pre-build lev_comp/dgn_comp from sys/share-derived sources
echo "  [native] util/{lev_comp,dgn_comp}"
(cd "$NATIVE_DIR/util" && make clean >/dev/null && make CC=cc CFLAGS="$NATIVE_CFLAGS" "${NATIVE_YACC_LEX_OVERRIDES[@]}" lev_comp dgn_comp)

# Build makedefs and the rest, generate headers + tile.c
echo "  [native] util/{makedefs,dlb,tilemap} + generated headers"
make -C "$NATIVE_DIR/util" \
    CC=cc CFLAGS="$NATIVE_CFLAGS" \
    "${NATIVE_YACC_LEX_OVERRIDES[@]}" \
    makedefs lev_comp dgn_comp dlb tilemap \
    ../include/onames.h ../include/pm.h ../include/vis_tab.h \
    ../src/tile.c

echo "  [native] include/date.h"
make -C "$NATIVE_DIR/src" \
    CC=cc CFLAGS="$NATIVE_CFLAGS" \
    ../include/date.h

# -----------------------------------------------------------------------------
# Phase 1b — generate level data with native lev_comp (in NATIVE_DIR/dat).
# -----------------------------------------------------------------------------
echo
echo "--- Phase 1b: native dat/ build (level compilation) ---"

# Comment out problematic .des files (castle, gehennom) that broke the WASM-side
# lev_comp in 0.9.2. Keep the workaround until verified unneeded on 0.9.3+.
PROBLEM_DES_LIST=( castle gehennom )
MAKEFILE_PATH="$NATIVE_DIR/dat/Makefile"
if [ -f "$MAKEFILE_PATH" ]; then
    for des in "${PROBLEM_DES_LIST[@]}"; do
        sed -i.bak -E "/spec_levs: /s/(^.*)${des}\.des(.*\$)/\1#${des}.des\2/" "$MAKEFILE_PATH"
        sed -i.bak -E "/lev_comp ${des}\.des/s/^([ \t]*)/\1#/" "$MAKEFILE_PATH"
    done
fi

make -C "$NATIVE_DIR/dat" CC=cc CFLAGS="$NATIVE_CFLAGS"

# Note: we do NOT run `make dlb` here. Phase 4 (phase3-relink) rebuilds nhdat
# in the wasm tree using its own dlb_tool, with the correct .lev list (some
# .des files like castle/gehennom are intentionally skipped above which makes
# the upstream `make dlb` glob (castle-?.lev) fail).

# -----------------------------------------------------------------------------
# Phase 1c — propagate generated artifacts NATIVE_DIR -> EVILHACK_DIR (wasm tree).
# -----------------------------------------------------------------------------
echo
echo "--- Phase 1c: copying generated headers + data into wasm tree ---"
for h in onames.h pm.h vis_tab.h date.h; do
    if [ -f "$NATIVE_DIR/include/$h" ]; then
        # Skip if target is a symlink to the same file
        if [ -L "$EVILHACK_DIR/include/$h" ]; then
            rm -f "$EVILHACK_DIR/include/$h"
        fi
        cp "$NATIVE_DIR/include/$h" "$EVILHACK_DIR/include/$h"
        echo "  include/$h"
    fi
done
# Bump mtime so the wasm-tree make never re-runs makedefs (it would build
# emcc-makedefs and fail to execute it natively).
touch -d "+1 hour" "$EVILHACK_DIR/include/"{onames.h,pm.h,vis_tab.h,date.h} 2>/dev/null || true
if [ -f "$NATIVE_DIR/src/tile.c" ]; then
    cp "$NATIVE_DIR/src/tile.c" "$EVILHACK_DIR/src/tile.c"
    echo "  src/tile.c"
fi

# Copy native-built host tools so phase3-relink can run them directly without
# trying to execute the wasm-built versions natively.
for tool in makedefs lev_comp dgn_comp dlb tilemap; do
    if [ -x "$NATIVE_DIR/util/$tool" ]; then
        cp "$NATIVE_DIR/util/$tool" "$EVILHACK_DIR/util/$tool"
        echo "  util/$tool (native)"
    fi
done

# Copy generated dat files (post-makedefs/lev_comp processing) from native ->
# wasm tree so phase3-relink (which rebuilds nhdat in the wasm tree) finds
# bogusmon, data, oracles, rumors, quest.dat, *.lev, dungeon, vaults.dat, etc.
echo "  [native -> wasm] dat/ generated files"
shopt -s nullglob
for f in "$NATIVE_DIR"/dat/bogusmon "$NATIVE_DIR"/dat/data \
         "$NATIVE_DIR"/dat/engrave "$NATIVE_DIR"/dat/epitaph \
         "$NATIVE_DIR"/dat/oracles "$NATIVE_DIR"/dat/options \
         "$NATIVE_DIR"/dat/rumors "$NATIVE_DIR"/dat/tribute \
         "$NATIVE_DIR"/dat/quest.dat "$NATIVE_DIR"/dat/dungeon \
         "$NATIVE_DIR"/dat/vaults.dat "$NATIVE_DIR"/dat/nhdat \
         "$NATIVE_DIR"/dat/*.lev; do
    if [ -f "$f" ]; then
        cp "$f" "$EVILHACK_DIR/dat/$(basename "$f")"
    fi
done
shopt -u nullglob

# Re-run symlink prep on wasm tree so any newly-introduced header in include/
# (e.g. onames.h that was missing earlier) gets a src/ symlink.
EVILHACK_VERSION="$EVILHACK_VERSION" bash "$SCRIPT_DIR/scripts/00_prepare_build.sh" >/dev/null

# -----------------------------------------------------------------------------
# Phase 2 — wasm-data/ embed payload.
# -----------------------------------------------------------------------------
echo
echo "--- Phase 2: preparing wasm-data/ embed payload ---"
rm -rf "$WASM_DATA_DIR"
mkdir -p "$WASM_DATA_DIR"

# Prefer nhdat from native build; fall back to dat directory contents.
if [ -f "$NATIVE_DIR/dat/nhdat" ]; then
    cp "$NATIVE_DIR/dat/nhdat" "$WASM_DATA_DIR/nhdat"
    echo "  nhdat: $(wc -c < "$WASM_DATA_DIR/nhdat") bytes"
fi
for f in nhshare nhushare license sysconf data rumors oracles dungeon quest.dat; do
    if [ -f "$NATIVE_DIR/dat/$f" ]; then
        cp "$NATIVE_DIR/dat/$f" "$WASM_DATA_DIR/$f"
    fi
done
touch "$WASM_DATA_DIR/perm" "$WASM_DATA_DIR/record" \
      "$WASM_DATA_DIR/logfile" "$WASM_DATA_DIR/paniclog"

if [ -f "$VALIDATION_SCRIPT" ]; then
    python3 "$VALIDATION_SCRIPT" "$WASM_DATA_DIR"
fi

# -----------------------------------------------------------------------------
# Phase 3 — build evilhack.js + evilhack.wasm with emcc.
# -----------------------------------------------------------------------------
echo
echo "--- Phase 3: building evilhack.js + evilhack.wasm (emcc) ---"
copy_bootstrap_sources "$EVILHACK_DIR"

# Wipe any stale object files in the wasm tree.
rm -f "$EVILHACK_DIR/src/"*.o "$EVILHACK_DIR/util/"*.o
rm -f "$EVILHACK_DIR/src/Sysunix" "$EVILHACK_DIR/src/Wasmunix" \
      "$EVILHACK_DIR/src/evilhack" \
      "$EVILHACK_DIR/src/evilhack.js" "$EVILHACK_DIR/src/evilhack.wasm"

WASM_TOOL_OVERRIDES=(
    CC=emcc
    LINK=emcc
    AR=emar
    CFLAGS="-I../include"
)

make -C "$EVILHACK_DIR/src" \
    -f Makefile \
    -f ../sys/unix/hints/linux-wasm \
    -f ../sys/unix/hints/linux-wasm-src-noop \
    "${WASM_TOOL_OVERRIDES[@]}" \
    Wasmunix

mkdir -p "$BUILD_DIR"
cp "$EVILHACK_DIR/src/evilhack.js"   "$BUILD_DIR/evilhack.js"
cp "$EVILHACK_DIR/src/evilhack.wasm" "$BUILD_DIR/evilhack.wasm"

echo
echo "--- Phase 3 output ---"
ls -lh "$BUILD_DIR/evilhack.js" "$BUILD_DIR/evilhack.wasm"

# -----------------------------------------------------------------------------
# Phase 4 — relink with shim_procs + asyncify, embed wasm-data, install to public/.
# -----------------------------------------------------------------------------
echo
echo "--- Phase 4: phase3-relink.sh (asyncify + shim_procs + nhdat embed) ---"
# Re-install native host tools (phase 3's wasm make may have rebuilt util/* as
# wasm node scripts; phase3-relink invokes them on host so they must be native).
for tool in makedefs lev_comp dgn_comp dlb tilemap; do
    if [ -x "$NATIVE_DIR/util/$tool" ]; then
        cp "$NATIVE_DIR/util/$tool" "$EVILHACK_DIR/util/$tool"
    fi
done
EVILHACK_VERSION="$EVILHACK_VERSION" bash "$SCRIPT_DIR/phase3-relink.sh"

echo
echo "=== EvilHack ${EVILHACK_VERSION} build complete ==="
