# HOWTO_BUILD.md

## EvilHack WASM Build Instructions

Follow these steps to build EvilHack for WebAssembly (WASM):

### 1. Prerequisites
- Install all build dependencies:
  - Emscripten SDK (emcc, emar, etc.)
  - Node.js
  - Python 3
  - Standard build tools (make, gcc, etc.)
- Ensure all dependencies are available in your PATH.

### 2. Setup
- Run the EvilHack Unix setup script to generate Makefiles and config headers:
  ```sh
  cd EvilHack-0.9.2
  sh sys/unix/setup.sh
  ```

### 3. Generate Required Headers (Manual Step)
**Before running the build script, you must generate the following headers:**
- `include/pm.h`
- `include/onames.h`
- `include/vis_tab.h`
- `include/date.h`

From the EvilHack-0.9.2/util directory, run:
```sh
cd util
make ../include/pm.h ../include/onames.h ../include/vis_tab.h
make ../include/date.h
cd ..
```

If you skip this step, the build will fail with missing header errors.

### 4. Build WASM Artifacts
- Run the build script from the evilhack-wasm directory:
  ```sh
  ./build.wasm.sh
  ```

This will produce `evilhack.js` and `evilhack.wasm` in the `build/` directory.

### 5. Troubleshooting
- If you see errors about missing `config.h`, ensure setup.sh completed successfully.
- If you see errors about missing `pm.h`, `onames.h`, `vis_tab.h`, or `date.h`, repeat step 3.
- For other errors, check that all dependencies are installed and up to date.

---

**Summary of required manual step:**
> You must generate the makedefs headers (pm.h, onames.h, vis_tab.h, date.h) manually before running the build script. This is not automated in build.wasm.sh.
