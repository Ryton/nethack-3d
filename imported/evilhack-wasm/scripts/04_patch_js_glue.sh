# Always replace initRuntime, preMain, and postRun with the correct definitions
RUNTIME_HOOKS_CODE='
function preRun() {
    if (Module["preRun"]) {
        if (typeof Module["preRun"] == "function") Module["preRun"] = [Module["preRun"]];
        while (Module["preRun"].length) { addOnPreRun(Module["preRun"].shift()); }
    }
    callRuntimeCallbacks(onPreRuns);
}
if (typeof Module !== "undefined") Module["preRun"] = preRun;
function initRuntime() { runtimeInitialized = true; if (!Module["noFSInit"] && !FS.initialized) FS.init(); TTY.init(); if (typeof wasmExports !== "undefined" && wasmExports["I"]) wasmExports["I"](); FS.ignorePermissions = false; }
function preMain() {}
function postRun() { if (Module["postRun"]) { if (typeof Module["postRun"] == "function") Module["postRun"] = [Module["postRun"]]; while (Module["postRun"].length) { addOnPostRun(Module["postRun"].shift()); } } callRuntimeCallbacks(onPostRuns); }
'

if [ -f "$EVILHACK_JS" ]; then
    # Remove any existing definitions
        awk '!/^function preRun\(\)/ && !/^function initRuntime\(\)/ && !/^function preMain\(\)/ && !/^function postRun\(\)/' "$EVILHACK_JS" > "$EVILHACK_JS.nohooks" && mv "$EVILHACK_JS.nohooks" "$EVILHACK_JS"
        # Inject runtime hooks immediately after the opening of the Module function
        awk -v code="$RUNTIME_HOOKS_CODE" 'BEGIN{injected=0} /async function Module\(/ && !injected {print; getline; print; print code; injected=1; next} 1' "$EVILHACK_JS" > "$EVILHACK_JS.patched" && mv "$EVILHACK_JS.patched" "$EVILHACK_JS"
        echo "[PATCH] Replaced preRun, initRuntime, preMain, postRun definitions inside Module() in $EVILHACK_JS."
fi
#!/bin/bash
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"
PUBLIC_DIR="$SCRIPT_DIR/../../../public"
PATCH_CODE="function updateMemoryViews() { var b = wasmMemory.buffer; HEAP8 = new Int8Array(b); HEAP16 = new Int16Array(b); HEAPU8 = new Uint8Array(b); HEAPU16 = new Uint16Array(b); HEAP32 = new Int32Array(b); HEAPU32 = new Uint32Array(b); HEAPF32 = new Float32Array(b); HEAPF64 = new Float64Array(b); HEAP64 = new BigInt64Array(b); HEAPU64 = new BigUint64Array(b); }"

## patch for updateMemoryViews
## updateMemoryViews is required for dynamic memory growth in Emscripten builds, but the generated evilhack.js may not include it if the build configuration doesn't trigger its inclusion. This patch ensures that updateMemoryViews is defined and injected into evilhack.js if it's missing, matching the style used in slashem.js.
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

# Patch code for preRun, matching slashem.js
PRE_RUN_CODE='function preRun() {
if (Module["preRun"]) {
    if (typeof Module["preRun"] == "function") Module["preRun"] = [Module["preRun"]];
    while (Module["preRun"].length) { addOnPreRun(Module["preRun"].shift()); }
}
callRuntimeCallbacks(onPreRuns);
}
// Ensure preRun is accessible as a Module property (Emscripten compatibility)
if (typeof Module !== "undefined") Module["preRun"] = preRun;'

# Always replace preRun with the correct definition
EVILHACK_JS="$BUILD_DIR/evilhack.js"
if [ -f "$EVILHACK_JS" ]; then
    # Remove any existing preRun definition
    awk '!/^function preRun\(\)/' "$EVILHACK_JS" > "$EVILHACK_JS.noprerun" && mv "$EVILHACK_JS.noprerun" "$EVILHACK_JS"
    # Inject preRun definition immediately after updateMemoryViews
    awk -v code="$PRE_RUN_CODE" '
        /function updateMemoryViews/ { print; found=1; next }
        found && !printed { print code; printed=1; found=0 }
        { print }
    ' "$EVILHACK_JS" > "$EVILHACK_JS.patched" && mv "$EVILHACK_JS.patched" "$EVILHACK_JS"
    echo "[PATCH] Replaced preRun() definition in $EVILHACK_JS."
fi
