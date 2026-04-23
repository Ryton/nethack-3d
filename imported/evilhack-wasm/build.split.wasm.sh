#!/bin/bash
# build.split.wasm.sh - Split build for EvilHack WASM with native and WASM object separation
# This script builds native tools in a separate directory and WASM in another, avoiding object file contamination.
# Usage: ./build.split.wasm.sh

set -e

EH_SRC_NATIVE="$(dirname "$0")/build/EvilHack-0.9.2_native/EvilHack-0.9.2"
EH_SRC_WASM="$(dirname "$0")/build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"

main() {
	# 1. Build native tools (makedefs, etc.) in native dir
	# (shebang and set -e are only needed at top of file)
	EH_SRC_NATIVE="$(dirname "$0")/build/EvilHack-0.9.2_native/EvilHack-0.9.2"
	EH_SRC_WASM="$(dirname "$0")/build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"

	# === EMCC WRAPPER SETUP (top-level, before any build) ===
	EMCC_TMPDIR="$(mktemp -d)"
	echo "[DEBUG] EMCC_TMPDIR is $EMCC_TMPDIR"
	export PATH="$EMCC_TMPDIR:$PATH"
	export EMCC_ORIG=$(command -v emcc)
	cat > "$EMCC_TMPDIR/emcc" <<'EOF'
#!/bin/bash
# EMCC wrapper for EvilHack build
# This block must be closed with EOF at the left margin!
echo "=== EMCC WRAPPER USED ===" >&2
echo "[EMCC INVOCATION] $EMCC_ORIG $@" >&2
exec $EMCC_ORIG "$@"
EOF
	chmod +x "$EMCC_TMPDIR/emcc"
	ls -l "$EMCC_TMPDIR/emcc"
	echo "USING EMCC: $(which emcc)"

	# 1. Build native tools (makedefs, etc.) in native dir
	cd "$EH_SRC_NATIVE"
	echo "[Native] Building native tools (makedefs, lev_comp, etc.)..."
	make clean
	make makedefs || true
	cd -

	# 2. Build WASM objects and game in wasm dir
	cd "$EH_SRC_WASM"
	echo "[WASM] Building WASM objects and game..."
	make clean
	# Inject Emscripten EXPORTED_RUNTIME_METHODS for required runtime exports
	export EMCC_CFLAGS="-sEXPORTED_RUNTIME_METHODS='[\"cwrap\",\"ccall\",\"addFunction\",\"removeFunction\",\"UTF8ToString\",\"stringToUTF8\",\"getValue\",\"setValue\",\"ENV\",\"FS\",\"IDBFS\",\"updateMemoryViews\"]' $EMCC_CFLAGS"
	make evilhack || true
	export PATH="${PATH#*:}"
	unset EMCC_ORIG EMCC_TMPDIR
	cd -

	echo "Build complete. Native and WASM builds are isolated." | tee "$(dirname "$0")/build.split.log"


	       # Copy evilhack.js and evilhack.wasm to public/ after build
	       SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
	       if [ -f "$SCRIPT_DIR/copy-evilhack-wasm_js.sh" ]; then
		       bash "$SCRIPT_DIR/copy-evilhack-wasm_js.sh"
		       # Check that files were copied and are up to date
		       BUILD_DIR="$SCRIPT_DIR/build/EvilHack-0.9.2_wasm/EvilHack-0.9.2"
		       PUBLIC_DIR="$SCRIPT_DIR/../../public"
		       for f in evilhack.js evilhack.wasm; do
			       if [ ! -f "$PUBLIC_DIR/$f" ]; then
				       echo "[ERROR] $f was not copied to $PUBLIC_DIR!"
				       exit 1
			       fi
			       if ! cmp -s "$BUILD_DIR/$f" "$PUBLIC_DIR/$f"; then
				       echo "[ERROR] $f in $PUBLIC_DIR does not match build output!"
				       exit 1
			       fi
			       echo "[CHECK] $f successfully copied and matches build output."
		       done
	       else
		       echo "[WARN] copy-evilhack-wasm_js.sh not found; skipping copy to public/."
	       fi

	       # Patch evilhack.js to inject updateMemoryViews if missing (matches slashem.js style)
	       for jsfile in "$BUILD_DIR/evilhack.js" "$PUBLIC_DIR/evilhack.js"; do
		       if [ -f "$jsfile" ]; then
			       if ! grep -q 'function updateMemoryViews' "$jsfile"; then
				       awk 'NR==1{print "function updateMemoryViews() { var b = wasmMemory.buffer; HEAP8 = new Int8Array(b); HEAP16 = new Int16Array(b); HEAPU8 = new Uint8Array(b); HEAPU16 = new Uint16Array(b); HEAP32 = new Int32Array(b); HEAPU32 = new Uint32Array(b); HEAPF32 = new Float32Array(b); HEAPF64 = new Float64Array(b); HEAP64 = new BigInt64Array(b); HEAPU64 = new BigUint64Array(b); }\n"} 1' "$jsfile" > "$jsfile.tmp" && mv "$jsfile.tmp" "$jsfile"
				       echo "[PATCH] Injected updateMemoryViews() into $jsfile."
			       fi
		       fi
	       done

}

# Call main if this script is executed, not sourced
if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
	main 2>&1 | tee "$(dirname "$0")/build.split.log"
fi

