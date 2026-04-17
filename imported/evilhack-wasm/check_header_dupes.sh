#!/usr/bin/env bash
# Only report header files with differences between include/, src/, and util/

set -euo pipefail

EH_BASE="$(dirname "$0")/EvilHack-0.9.2"
INCLUDE="$EH_BASE/include"
SRC="$EH_BASE/src"
UTIL="$EH_BASE/util"

all_headers=$(find "$INCLUDE" "$SRC" "$UTIL" -maxdepth 1 -name '*.h' -exec basename {} \; | sort | uniq)

for base in $all_headers; do
    paths=("$INCLUDE/$base" "$SRC/$base" "$UTIL/$base")
    found=()
    hashes=()
    for p in "${paths[@]}"; do
        if [ -f "$p" ]; then
            found+=("$p")
            hashes+=("$(sha256sum "$p" | awk '{print $1}')")
        fi
    done
    if [ "${#found[@]}" -gt 1 ]; then
        unique_hashes=($(printf "%s\n" "${hashes[@]}" | sort -u))
        if [ "${#unique_hashes[@]}" -gt 1 ]; then
            echo -e "\n=== $base (DIFFERENCES FOUND) ==="
            for i in "${!found[@]}"; do
                size=$(stat -c %s "${found[$i]}")
                echo "${found[$i]}: size=$size sha256=${hashes[$i]}"
            done
        fi
    fi
done