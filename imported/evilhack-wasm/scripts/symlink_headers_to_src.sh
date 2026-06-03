#!/bin/bash
set -e
SRC_DIR="$(dirname "$0")/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/src"
INCLUDE_DIR="$(dirname "$0")/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/include"
UTIL_DIR="$(dirname "$0")/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/util"
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

# Explicitly ensure config1.h is symlinked if present
if [ ! -e "config1.h" ]; then
    if [ -f "../include/config1.h" ]; then
        ln -s "../include/config1.h" "config1.h"
        echo "Symlinked config1.h from include/"
    elif [ -f "../util/config1.h" ]; then
        ln -s "../util/config1.h" "config1.h"
        echo "Symlinked config1.h from util/"
    else
        echo "WARNING: config1.h not found in include/ or util/!"
    fi
else
    echo "config1.h already exists in src/"
fi

if [ ! -e "config.h" ]; then
    if [ -f "../include/config.h" ]; then
        ln -s "../include/config.h" "config.h"
        echo "Symlinked config.h from include/"
    else
        echo "WARNING: config.h not found in include/!"
    fi
else
    echo "config.h already exists in src/"
fi

#!/bin/bash
set -e
SRC_DIR="$(dirname "$0")/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/src"
INCLUDE_DIR="$(dirname "$0")/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/include"
UTIL_DIR="$(dirname "$0")/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/util"
cd "$SRC_DIR"
shopt -s nullglob
for h in "$INCLUDE_DIR"/*.h "$UTIL_DIR"/*.h; do
    fname=$(basename "$h")
    if [ ! -e "$fname" ]; then
        # Determine source dir for symlink
        if [[ "$h" == "$INCLUDE_DIR"* ]]; then
            ln -s "../include/$fname" "$fname"
            echo "Symlinked $fname from include/"
        else
            ln -s "../util/$fname" "$fname"
            echo "Symlinked $fname from util/"
        fi
    fi
done
shopt -u nullglob
echo "All headers symlinked from include/ and util/ to src/. for _wasm"


echo "All headers symlinked from include/ and util/ to src/. for _wasm"