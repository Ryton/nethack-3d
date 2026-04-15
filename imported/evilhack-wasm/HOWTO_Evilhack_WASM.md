# HOWTO: Building EvilHack for WASM

## Quick Steps


1. Clean and generate Makefiles:
   ```sh
   cd EvilHack-0.9.2
   make clean
   cd sys/unix && sh setup.sh hints/linux
   cd ../..
   ```
2. Build native tools:
   ```sh
   make -C util makedefs lev_comp dgn_comp dlb tilemap
   ```
3. (Optional) Verify native tools:
   ```sh
   ls -l util/makedefs util/lev_comp util/dgn_comp util/dlb util/tilemap
   file util/makedefs util/lev_comp util/dgn_comp util/dlb util/tilemap
   ```
   Ensure all are ELF executables and have +x permissions.
4. (Recommended) Protect native tools from deletion during build:
   ```sh
   sudo chattr +i util/makedefs util/lev_comp util/dgn_comp util/dlb util/tilemap
   ```
5. Build the WASM target:
   ```sh
   cd ..
   ./build.wasm.sh
   # or
   make -C src Wasmunix  # with the right overrides
   ```
6. Unprotect native tools after build (if needed):
   ```sh
   ./UNPROTECT.sh
   ```

## Summary
- Always build native tools (makedefs, lev_comp, dgn_comp, dlb, tilemap) natively before starting the WASM build.
- Do not let the WASM build system or Makefile rebuild or delete these tools.
- The WASM build should only use emcc for the main binary, not for utility tools.
- If you clean or rebuild, ensure your native tools are still present before running the WASM build.
