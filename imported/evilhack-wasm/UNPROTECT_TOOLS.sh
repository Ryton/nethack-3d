#!/usr/bin/env bash
# Remove immutable flag from all EvilHack native tools (makedefs, lev_comp, dgn_comp, dlb, tilemap)
# Usage: ./UNPROTECT_TOOLS.sh [path-to-evilhack-dir]

set -euo pipefail

EVILHACK_DIR="${1:-$(dirname "$0")/EvilHack-0.9.2}"
TOOLS=(makedefs lev_comp dgn_comp dlb tilemap)

for tool in "${TOOLS[@]}"; do
    if [ -f "$EVILHACK_DIR/util/$tool" ]; then
        sudo chattr -i "$EVILHACK_DIR/util/$tool" || true
    fi
    # Some tools may be in src or other dirs in future
    if [ -f "$EVILHACK_DIR/src/$tool" ]; then
        sudo chattr -i "$EVILHACK_DIR/src/$tool" || true
    fi
    if [ -f "$EVILHACK_DIR/$tool" ]; then
        sudo chattr -i "$EVILHACK_DIR/$tool" || true
    fi
    # Add more locations if needed
    done
