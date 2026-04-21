# Steps for Building EvilHack WASM (Big Split Build)

## Overview
- Native and WASM builds are fully separated.
- All source code is copied from EvilHack-0.9.2 into dedicated build directories.
- WASM build skips dungeon file compilation and uses files from the native build.
- No unnecessary install/permission logic is present in the WASM build.
- All build outputs (evilhack.wasm, evilhack.js) are copied to the public/ directory for deployment.
- Dungeon and related files are protected from deletion or rebuild in WASM.

## Manual Build & Deployment Steps

1. **Prepare Build Directories**
   - Copy EvilHack-0.9.2 to build/EvilHack-0.9.2_native and build/EvilHack-0.9.2_wasm.
   - Never modify the original EvilHack-0.9.2 after copying.

2. **Native Build**
   - Build native version in build/EvilHack-0.9.2_native.
   - Dungeon and related files are generated here.

3. **WASM Build**
   - Build WASM version in build/EvilHack-0.9.2_wasm.
   - Makefile is patched to:
     - Use absolute paths for all src/*.c rules.
     - Skip dungeon file compilation.
     - Reference dungeon files from the native build.
     - Remove install/permission logic.
   - Outputs: evilhack.wasm and evilhack.js.

4. **Deployment**
   - Copy evilhack.wasm and evilhack.js from the WASM build output to public/.
   - Verify both files are present and uncorrupted in public/.

5. **File Safety**
   - Dungeon and related files are never deleted or rebuilt in the WASM build.
   - All .o files for WASM are built with emcc and correct include paths.

## Troubleshooting: WASM JS Glue Not Functional

- If you see errors like:
  - `Module default export is not a function (got undefined)`
- This means evilhack.js is not structured as an ES module with a default export.

### Solution
- Ensure Emscripten is invoked with:
  - `-s MODULARIZE=1`
  - `-s EXPORT_ES6=1`
  - `-o evilhack.js`
- evilhack.js should start with `export default function(...) { ... }` or similar.
- Rebuild and redeploy evilhack.js and evilhack.wasm.

## Notes
- All automation and scripting must follow the “don’t ask, do” policy.
- All changes are made only in the build directories, never in the original source.
- Persistent agent behavior guidelines are codified in /memories/greeting.md.
