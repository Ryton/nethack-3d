# Changes to build.split.wasm.sh

## Summary
This file documents all changes made to `build.split.wasm.sh` as a result of the discussions and debugging in this thread (April 2026).

---

## 1. Syntax and Robustness Fixes
- Fixed here-document and function closure issues in the script.
- Improved robustness of the script for directory and environment variable handling.

## 2. Post-Build JS Patching (REMOVED)
- The script previously included logic to patch `evilhack.js` after build, inserting assignments to expose Emscripten runtime methods (e.g., `cwrap`, `ccall`, `addFunction`, etc.) on the `Module` object.
- This patching was done using `awk` to inject code before the last `return moduleRtn;` statement in the generated JS glue.
- Additional patching with `sed` disabled strict aborting property guards for missing runtime exports.
- These post-build patching steps have now been **completely removed**.

## 3. Emscripten Build Flags (NEW)
- The script now injects the following Emscripten build flag before building the WASM target:

  ```sh
  export EMCC_CFLAGS="-sEXPORTED_RUNTIME_METHODS='[\"cwrap\",\"ccall\",\"addFunction\",\"removeFunction\",\"UTF8ToString\",\"stringToUTF8\",\"getValue\",\"setValue\",\"ENV\",\"FS\",\"IDBFS\",\"updateMemoryViews\"]' $EMCC_CFLAGS"
  ```
- This ensures all required runtime methods are exported directly by Emscripten, making the JS glue robust and eliminating the need for manual patching.

## 4. Copy and Verification Logic (UNCHANGED)
- The logic to copy `evilhack.js` and `evilhack.wasm` to the public directory and verify their integrity remains unchanged.

---

## Rationale
- The changes ensure that all required Emscripten runtime methods are available in the JS glue, fixing persistent runtime errors (e.g., `updateMemoryViews is not defined`).
- The build process is now more robust, maintainable, and less error-prone.

---

**Date:** April 22, 2026
**Author:** GitHub Copilot
