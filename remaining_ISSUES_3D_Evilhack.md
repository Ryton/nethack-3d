# Remaining issues — EvilHack integration into nethack-3d (post upstream/1.3.5 merge)

State at write time: local `main` and `origin/main` at commit `3fc62da`.
Backup branch: `backup/pre-rebase-evilhack` at `0ce476c`.

## Priority issues

### 1. Tile edge seams (black bleed between floor tiles)
- Symptom: thin black/dark lines visible between adjacent floor tiles in the
  3D scene (screenshot in chat 2026-06-03).
- Likely cause introduced by the `upstream/1.3.5` merge: a change to
  floor-tile texture filtering, mipmap generation, or UV insets in
  `src/game/Nethack3DEngine.ts`.
- Suspected suspects:
  - `THREE.NearestFilter` set on tile texture without UV padding.
  - `generateMipmaps` flag change.
  - New code path for animated tiles / blood pooling altering tile UVs.
- Recommended diagnostic:
  `git diff backup/pre-rebase-evilhack..HEAD -- src/game/Nethack3DEngine.ts`
  filtered for `Filter|generateMipmaps|repeat|wrap|inset|floor`.

### 2. Fix vault generation (currently bypassed in EvilHack WASM)
- Commit `577c2b0` "fix(evilhack): 0.9.3 brought to 0.9.2 parity (vault
  bypass + extcmd validator)" disables vault generation as a workaround
  for the `mklev → makelevel → makerooms → load_special` busy-loop
  documented in user memory (CRITICAL: 64-bit→32-bit header patching).
- Root cause: EvilHack 0.9.2 native `lev_comp` / `dgn_comp` write
  `version_info` as 5×unsigned long = 40 bytes on 64-bit Linux, but
  wasm32 reads it as 5×uint32 = 20 bytes. `check_version()` silently
  fails → `load_special()` returns FALSE → `makerooms()` infinite loop.
- Proper fix: patch `version_info` headers on all `.lev`, `dungeon`,
  `vaults.dat` files at build time (post-process to 32-bit layout), OR
  cross-compile `lev_comp`/`dgn_comp` with wasm32 alignment, then
  re-enable vault generation in the EvilHack patch.
- Affected files: see `scripts/wasm/` and `imported/evilhack-wasm/`.

### 3. Flat (2D) shopkeeper / NPC billboards in EvilHack
- Symptom: shopkeeper (and likely other EvilHack-specific NPCs) renders
  as a flat upright billboard instead of the engine's standard
  monster representation. Screenshot 2026-06-03.
- Likely cause: glyph for the EvilHack shopkeeper monster is not
  classified into the same monster-billboard / 3D-sprite category as
  stock NetHack's shopkeeper, so it falls through to a fallback
  "flat" renderer.
- Suspects:
  - `src/game/glyphs/glyph-catalog.evilhack.generated.ts` — check the
    `kind` / `category` assigned to the shopkeeper glyph vs the
    367/5.0 catalogs.
  - `src/game/glyphs/behavior.ts` / `src/game/glyphs/registry.ts`
    classification.
  - `scripts/glyphs/catalog-generator.mjs` may need a special-case for
    EvilHack human-NPC glyph indices.

### 4. Autumn-tree glyph appearing as shadow under objects
- Symptom: in the EvilHack vault screenshot (2026-06-03) the floor tiles
  beneath the potions show brown autumn-tree sprites where the engine's
  item-shadow / item-base decoration should be.
- Likely cause: the "item shadow" / "object base" decoration in the 3D
  engine is sourcing the wrong glyph index for EvilHack — probably a
  glyph offset mismatch between catalogs (367/5.0/slashem/evilhack), or
  the shadow decoration index hardcoded for stock NetHack happens to
  land on the autumn-tree glyph in EvilHack.
- Suspects:
  - `src/game/Nethack3DEngine.ts` — search for the item-shadow /
    drop-shadow / base-decal code path.
  - `src/game/glyphs/glyph-catalog.evilhack.generated.ts` — verify
    `GLYPH_*_OFF` constants used for the shadow lookup.
  - `src/game/glyphs/registry.ts` — per-runtime glyph routing.

### 5. Audit `parseRaceEntries` for the same multi-array leak as `parseRoleEntries`
- EvilHack `race.c` may also define secondary arrays
  (e.g. `align_races[]`, `quest_races[]`).
- If so, the race parser will leak quest-only races into the primary
  race picker — same class of bug as Dark Knight.
- File: `scripts/game/generate-startup-character-rulesets.mjs`.
- Pattern to apply: add `"const struct Race "` to the `endPatterns` list
  in `parseRaceEntries`, matching the fix already applied to
  `parseRoleEntries`.

## Housekeeping

### 6. Update or remove `TODOs_fix_blackscreen.md`
- Phase 3 TODO 13 (upstream sync) is now done.
- Either delete the file or move outstanding items here.
