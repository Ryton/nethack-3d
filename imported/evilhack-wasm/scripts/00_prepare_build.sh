#!/bin/bash
# 00_prepare_build.sh: Prepare build directories and symlink all headers for EvilHack WASM/Native.
# Versioned with EVILHACK_VERSION (default 0.9.3). Pass EVILHACK_VERSION=0.9.2 for the rollback build.
set -e
EVILHACK_VERSION="${EVILHACK_VERSION:-0.9.3}"
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../build"
SRC_NATIVE="$BUILD_DIR/EvilHack-${EVILHACK_VERSION}_native"
SRC_WASM="$BUILD_DIR/EvilHack-${EVILHACK_VERSION}_wasm"

prepare_one() {
    local FLAVOR_ROOT="$1"
    local TREE="$FLAVOR_ROOT/EvilHack-${EVILHACK_VERSION}"
    if [ ! -d "$TREE" ]; then
        echo "Skipping $FLAVOR_ROOT: tree not present"
        return 0
    fi
    local SRC_DIR="$TREE/src"
    local INCLUDE_DIR="$TREE/include"
    local UTIL_DIR="$TREE/util"
    local SYS_SHARE="$TREE/sys/share"
    local SYS_DIR="$TREE/sys"

    mkdir -p "$SRC_DIR" "$INCLUDE_DIR" "$UTIL_DIR" "$SYS_SHARE"

    symlink_headers() {
        local TARGET="$1"
        cd "$TARGET"
        shopt -s nullglob
        for h in "$INCLUDE_DIR"/*.h; do
            fname=$(basename "$h")
            [ -e "$fname" ] || [ -L "$fname" ] || ln -s "../include/$fname" "$fname"
        done
        for h in "$UTIL_DIR"/*.h; do
            fname=$(basename "$h")
            [ -e "$fname" ] || [ -L "$fname" ] || ln -s "../util/$fname" "$fname"
        done
        shopt -u nullglob
        cd - >/dev/null
    }

    symlink_headers "$SRC_DIR"
    symlink_headers "$UTIL_DIR"

    # sys/share gets include/*.h via relative symlinks
    cd "$SYS_SHARE"
    shopt -s nullglob
    for h in "$INCLUDE_DIR"/*.h; do
        fname=$(basename "$h")
        ln -sf "../../include/$fname" "$fname"
    done
    shopt -u nullglob
    cd - >/dev/null

    # sys/include -> ../include
    ln -sfn ../include "$SYS_DIR/include"

    echo "Prepared $TREE"
}

prepare_one "$SRC_NATIVE"
prepare_one "$SRC_WASM"

export LINK=cc
