#!/bin/bash
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"
PUBLIC_DIR="$SCRIPT_DIR/../../../public"
PATCH_CODE="function updateMemoryViews() { var b = wasmMemory.buffer; HEAP8 = new Int8Array(b); HEAP16 = new Int16Array(b); HEAPU8 = new Uint8Array(b); HEAPU16 = new Uint16Array(b); HEAP32 = new Int32Array(b); HEAPU32 = new Uint32Array(b); HEAPF32 = new Float32Array(b); HEAPF64 = new Float64Array(b); HEAP64 = new BigInt64Array(b); HEAPU64 = new BigUint64Array(b); }"


patch_file() {
    local jsfile="$1"
    if [ -f "$jsfile" ]; then
        # Remove any top-level updateMemoryViews definition
        awk '!/^function updateMemoryViews\(\)/' "$jsfile" > "$jsfile.noupdate" && mv "$jsfile.noupdate" "$jsfile"
        # Inject updateMemoryViews definition immediately before its first call
        if grep -q 'updateMemoryViews();' "$jsfile" && ! grep -q 'function updateMemoryViews' "$jsfile"; then
            awk -v code="$PATCH_CODE" '
                /updateMemoryViews\(\);/ && !x { print code; x=1 }
                { print }' "$jsfile" > "$jsfile.tmp" && mv "$jsfile.tmp" "$jsfile"
            echo "[PATCH] Moved updateMemoryViews() definition to just before its first call in $jsfile."
        fi
    fi
}
patch_file "$BUILD_DIR/evilhack.js"
