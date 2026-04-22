#!/bin/bash
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"
PUBLIC_DIR="$SCRIPT_DIR/../../../public"
mkdir -p "$PUBLIC_DIR"
for f in evilhack.js evilhack.wasm; do
    src="$BUILD_DIR/$f"
    dest="$PUBLIC_DIR/$f"
    if [ ! -f "$src" ]; then
        echo "ERROR: $src not found. Build may have failed."
        exit 1
    fi
    if [ -f "$dest" ]; then
        mv "$dest" "$dest.OLD"
        echo "Moved existing $dest to $dest.OLD"
    fi
    cp "$src" "$dest"
    echo "Copied $src to $dest"
done
