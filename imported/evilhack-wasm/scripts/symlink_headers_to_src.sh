#!/bin/bash
# Symlink all generated/copied headers from include/ and util/ into src/,
# because some EvilHack source files do `#include "config.h"` etc. directly
# (relative to src/) instead of using the Makefile's -I../include path.
set -e
EVILHACK_VERSION="${EVILHACK_VERSION:-0.9.3}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BASE="$ROOT/build/EvilHack-${EVILHACK_VERSION}_wasm/EvilHack-${EVILHACK_VERSION}"
SRC_DIR="$BASE/src"
INCLUDE_DIR="$BASE/include"
UTIL_DIR="$BASE/util"

if [ ! -d "$SRC_DIR" ]; then
    echo "Error: src dir not found: $SRC_DIR"
    exit 1
fi

cd "$SRC_DIR"
shopt -s nullglob
for h in "$INCLUDE_DIR"/*.h; do
    fname=$(basename "$h")
    if [ ! -e "$fname" ]; then
        ln -s "../include/$fname" "$fname"
        echo "Symlinked $fname from include/"
    fi
done
for h in "$UTIL_DIR"/*.h; do
    fname=$(basename "$h")
    if [ ! -e "$fname" ]; then
        ln -s "../util/$fname" "$fname"
        echo "Symlinked $fname from util/"
    fi
done
shopt -u nullglob

# Explicitly ensure config1.h and config.h symlinks exist
for ch in config1.h config.h; do
    if [ ! -e "$ch" ]; then
        if [ -f "../include/$ch" ]; then
            ln -s "../include/$ch" "$ch"
            echo "Symlinked $ch from include/"
        elif [ -f "../util/$ch" ]; then
            ln -s "../util/$ch" "$ch"
            echo "Symlinked $ch from util/"
        else
            echo "WARNING: $ch not found in include/ or util/!"
        fi
    fi
done

echo "All headers symlinked into $SRC_DIR for EvilHack ${EVILHACK_VERSION} WASM build."
