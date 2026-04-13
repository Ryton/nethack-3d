# EvilHack WASM Integration Status

## Current Status: ⚠️ INCOMPLETE

The `evilhack.wasm` file in `public/` exists but **is missing required NetHack 3D graphics functions**.

## Problem

When the EvilHack WASM module is loaded, the runtime tries to call:

```typescript
const setCallback = this.nethackInstance.cwrap(
  "shim_graphics_set_callback",
  null,
  ["string"],
);
```

But this function is **not exported** from the current `evilhack.wasm`.

### Missing Exports

The current `evilhack.wasm` is missing these critical functions:

- `shim_graphics_set_callback` — Register UI callback
- `mapglyph` — Map glyph data
- `glyph_to_tile` — Convert glyphs to tile indices
- `nh3d_glyph_at` — Get glyph at position
- `nh_top_item_glyph_under_player` — Get item under player
- `recover_savefile` — Save recovery
- `resume_checkpoint_save` — Checkpoint resume

## Root Cause

Standard EvilHack source code does **not include graphics shim implementations**. These are custom additions made in the NetHack 3D forked builds (3.6.7 and 3.7).

To build a working EvilHack WASM for NetHack 3D, you would need:

1. **Patched EvilHack source** with graphics shim code integrated
2. **Proper emcc compilation** with all shims exported as WASM functions
3. **Full system function support** for all EvilHack-specific functions

## Current Workaround

For now, use the existing fully-integrated variants:
- NetHack 3.6.7 ✅ (complete, tested)
- NetHack 3.7 ✅ (complete, tested)
- SLASH'EM ✅ (complete, tested)

## Future Implementation

To enable EvilHack WASM support:

1. Obtain or create a patched EvilHack source with graphics shims (similar to the forked neth4ck-monorepo)
2. Use the build script at `scripts/wasm/build-evilhack.mjs` to compile it
3. Test with the existing runtime integration (already in place in TypeScript)

The TypeScript/runtime side is **already prepared** for EvilHack (see `EVILHACK_INCLUSION_PROGRESS.md`). Only the WASM build is missing.

## Related Files

- `scripts/wasm/build-evilhack.mjs` — Build script (requires proper source)
- `src/runtime/LocalNetHackRuntime.ts` — Runtime integration (✅ ready)
- `src/game/Nethack3DEngine.ts` — Engine integration (✅ ready)
- `public/evilhack.wasm` — Incomplete WASM module ⚠️
- `public/evilhack.js` — Glue code (expects missing functions)
