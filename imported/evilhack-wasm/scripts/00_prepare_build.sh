# Ensure onames.h is present in include/ for both native and wasm builds
for INC_DIR in "$SRC_NATIVE_INCLUDE" "$SRC_WASM_INCLUDE"; do
  if [ ! -e "$INC_DIR/onames.h" ]; then
    # Try to symlink from util or src if available
    if [ -e "$SRC_NATIVE_UTIL/onames.h" ]; then
      ln -sf "$SRC_NATIVE_UTIL/onames.h" "$INC_DIR/onames.h"
    elif [ -e "$SRC_WASM_UTIL/onames.h" ]; then
      ln -sf "$SRC_WASM_UTIL/onames.h" "$INC_DIR/onames.h"
    elif [ -e "$SRC_NATIVE_SRC/onames.h" ]; then
      ln -sf "$SRC_NATIVE_SRC/onames.h" "$INC_DIR/onames.h"
    elif [ -e "$SRC_WASM_SRC/onames.h" ]; then
      ln -sf "$SRC_WASM_SRC/onames.h" "$INC_DIR/onames.h"
    fi
  fi
done
# Ensure LINK is set for all build scripts (workaround for Makefile default)
export LINK=cc
 # Brute-force: symlink sys/include -> ../include for both native and wasm
SYS_NATIVE_SYS="$SRC_NATIVE/EvilHack-0.9.2/sys"
SYS_WASM_SYS="$SRC_WASM/EvilHack-0.9.2/sys"
mkdir -p "$SYS_NATIVE_SYS" "$SYS_WASM_SYS"
ln -sf ../include "$SYS_NATIVE_SYS/include"
ln -sf ../include "$SYS_WASM_SYS/include"
#!/bin/bash
set -e
# 00_prepare_build.sh: Prepare build directories and symlink all headers for EvilHack WASM/Native
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../build"
SRC_NATIVE="$BUILD_DIR/EvilHack-0.9.2_native"
SRC_WASM="$BUILD_DIR/EvilHack-0.9.2_wasm"
SRC_NATIVE_SRC="$SRC_NATIVE/EvilHack-0.9.2/src"
SRC_NATIVE_INCLUDE="$SRC_NATIVE/EvilHack-0.9.2/include"
SRC_NATIVE_UTIL="$SRC_NATIVE/EvilHack-0.9.2/util"
SRC_WASM_SRC="$SRC_WASM/EvilHack-0.9.2/src"
SRC_WASM_INCLUDE="$SRC_WASM/EvilHack-0.9.2/include"
SRC_WASM_UTIL="$SRC_WASM/EvilHack-0.9.2/util"

# Ensure build directories exist
mkdir -p "$SRC_NATIVE_SRC" "$SRC_NATIVE_INCLUDE" "$SRC_NATIVE_UTIL"
mkdir -p "$SRC_WASM_SRC" "$SRC_WASM_INCLUDE" "$SRC_WASM_UTIL"

# Symlink all .h headers from include/ and util/ into src/ for both native and wasm
symlink_headers() {
  local SRC_DIR="$1"
  local INCLUDE_DIR="$2"
  local UTIL_DIR="$3"
  cd "$SRC_DIR"
  shopt -s nullglob
  for h in "$INCLUDE_DIR"/*.h "$UTIL_DIR"/*.h; do
    fname=$(basename "$h")
    if [ ! -e "$fname" ]; then
      if [[ "$h" == "$INCLUDE_DIR"* ]]; then
        ln -sf "../include/$fname" "$fname"
        echo "Symlinked $fname from include/ to $SRC_DIR"
      else
        ln -sf "../util/$fname" "$fname"
        echo "Symlinked $fname from util/ to $SRC_DIR"
      fi
    fi
  done
  shopt -u nullglob
}

symlink_headers "$SRC_NATIVE_SRC" "$SRC_NATIVE_INCLUDE" "$SRC_NATIVE_UTIL"
symlink_headers "$SRC_WASM_SRC" "$SRC_WASM_INCLUDE" "$SRC_WASM_UTIL"
symlink_headers "$SRC_NATIVE_UTIL" "$SRC_NATIVE_INCLUDE" "$SRC_NATIVE_UTIL"
symlink_headers "$SRC_WASM_UTIL" "$SRC_WASM_INCLUDE" "$SRC_WASM_UTIL"


# Symlink all .h headers from include/ into sys/share for both native and wasm (avoid chained symlinks)
symlink_headers_sys_share() {
  local SYS_SHARE_DIR="$1"
  local INCLUDE_DIR="$2"
  cd "$SYS_SHARE_DIR"
  shopt -s nullglob
  for h in "$INCLUDE_DIR"/*.h; do
    fname=$(basename "$h")
    ln -sf "../include/$fname" "$fname"
    echo "Symlinked $fname from include/ to $SYS_SHARE_DIR"
  done
  shopt -u nullglob
}

SYS_SHARE_NATIVE="$SRC_NATIVE/EvilHack-0.9.2/sys/share"
SYS_SHARE_WASM="$SRC_WASM/EvilHack-0.9.2/sys/share"
mkdir -p "$SYS_SHARE_NATIVE" "$SYS_SHARE_WASM"
symlink_headers_sys_share "$SYS_SHARE_NATIVE" "$SRC_NATIVE_INCLUDE"
symlink_headers_sys_share "$SYS_SHARE_WASM" "$SRC_WASM_INCLUDE"