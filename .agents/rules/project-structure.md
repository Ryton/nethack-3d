# Project Structure Steering

This is a living steering doc. Update it whenever architecture, file ownership, or runtime contracts change.

## Related Steering Docs

- Input and player/cursor movement pipeline: `.agents/rules/movement-flow.md`
- Edit hotspots and change playbook: `.agents/rules/logic-hotspots.md`

## Top-Level Layout

- `index.html`: Vite HTML entry point.
- `src/main.tsx`: React app bootstrap and engine mount.
- `src/app.ts`: debug helper registration.
- `src/ui/App.tsx`: UI shell, dialogs, startup flow, update flow, and client options UI.
- `src/state/gameStore.ts`: Zustand store for live UI/game state.
- `src/state/engineUiAdapter.ts`: bridge from engine updates into the store.
- `src/game/Nethack3DEngine.ts`: main engine orchestration layer for rendering, input, camera, and runtime events.
- `src/game/index.ts`: public game barrel.
- `src/game/controller-bindings.ts`: controller action schema, defaults, parsing, and normalization.
- `src/game/tilesets.ts`: builtin, user, and Vulture tileset catalog and asset resolution.
- `src/game/user-tileset-storage.ts`: persistence for imported user tilesets.
- `src/game/helpers/startup-character-constraints.ts`: startup character selection helpers.
- `src/game/glyphs/index.ts`: public glyph helper barrel.
- `src/game/glyphs/registry.ts`: glyph catalog lookup and runtime-version selection.
- `src/game/glyphs/behavior.ts`: tile classification and default terrain glyph helpers.
- `src/game/glyphs/overrides.ts`: runtime glyph override registry.
- `src/game/glyphs/glyph-catalog.367.generated.ts`: checked-in generated glyph fallback/reference for NetHack 3.6.7 (not authoritative for all item-variation tiles).
- `src/game/glyphs/glyph-catalog.37.generated.ts`: checked-in generated glyph fallback/reference for NetHack 3.7 (not authoritative for all item-variation tiles).
- `src/game/vulture/translation.ts`: Vulture projection and tileset translation adapter.
- `src/game/vulture/nethack-object-tokens.ts`: Vulture object token bridge to imported NetHack data.
- `src/game/vulture/vulture-monster-keys.367.generated.ts`: generated Vulture monster lookup data.
- `src/audio/index.ts`: public audio barrel.
- `src/audio/FmodRuntime.ts`: FMOD runtime bootstrap and wrapper.
- `src/audio/sound-pack-storage.ts`: sound-pack persistence.
- `src/runtime/index.ts`: public runtime barrel.
- `src/runtime/LocalNetHackRuntime.ts`: NetHack callback adapter, input waits, menu/state logic, and runtime event emission.
- `src/runtime/runtime-worker.ts`: worker entry that hosts the runtime.
- `src/runtime/WorkerRuntimeBridge.ts`: main-thread worker bridge.
- `src/runtime/input/RuntimeInputBroker.ts`: broker for event, menu, and position input.
- `src/runtime/startup-init-options.ts`: startup option schema, normalization, serialization, and required token handling.
- `src/runtime/runtime-capabilities.ts`: runtime feature gates.
- `src/runtime/save-storage.ts`: save-path and database-name helpers.
- `src/runtime/displayFileCatalog.ts`: bundled help and display-file text catalog.
- `src/runtime/types.ts`: runtime commands, envelopes, and shared bridge types.
- `src/storage/client-options-storage.ts`: IndexedDB persistence plus localStorage migration for client options and startup preferences.
- `src/update/client-updater.ts`: client update check, apply, cancel, and progress handling.
- `src/update/manifest.ts`: update manifest parsing and resolution.
- `src/update/types.ts`: update type definitions.
- `public/assets/*`: shipped images, UI icons, and Vulture asset roots.
- `public/nethack-367.js`, `public/nethack-367.wasm`, `public/nethack-37.wasm`: checked-in runtime artifacts consumed by the browser build.
- `imported/nethack-3.6.7/*`: pinned NetHack source and data files used as reference inputs.
- `\\wsl.localhost\Ubuntu\home\james\Repos\forked\neth4ck-monorepo`: forked NetHack WASM monorepo reference in WSL.
- `\\wsl.localhost\Ubuntu\home\james\Repos\forked\neth4ck-monorepo\packages\wasm-367`: forked wasm-367 package reference in WSL.
- `\\wsl.localhost\Ubuntu\home\james\Repos\forked\neth4ck-monorepo\packages\wasm-367\NetHack`: forked NetHack source inside the wasm-367 package in WSL.
- `third_party/vulture/*`: vendored Vulture source reference.
- `scripts/glyphs/*`: glyph catalog generation and validation.
- `scripts/wasm/*`: WASM copy and packaging helpers.
- `scripts/updates/*`: update packaging helpers.
- `electron/*`: Electron entry points and packaging support.
- `android/*`: Capacitor Android project.
- `build/*`, `dist/*`, `release/*`: build and packaging outputs.

## Runtime Architecture

1. `src/main.tsx` mounts React and creates `Nethack3DEngine`.
2. `src/ui/App.tsx` creates the engine controller and UI adapter.
3. `Nethack3DEngine` creates a `WorkerRuntimeBridge`.
4. `WorkerRuntimeBridge` starts `src/runtime/runtime-worker.ts` as a module worker.
5. The worker creates `LocalNetHackRuntime`.
6. `LocalNetHackRuntime` loads the NetHack runtime artifacts, applies startup init options, and routes shim callbacks through `handleUICallback`.
7. Runtime events flow back to `Nethack3DEngine.handleRuntimeEvent` for rendering and UI updates.

## Useful Commands

- Install dependencies: `npm i`
- Type-check only: `npm run check:tsc`
- Dev server: `npm run dev`
- Preview production build: `npm run preview`

## Reference Commands

- Build, packaging, and update commands live in `package.json`, including `npm run build`, `npm run build:electron`, `npm run update`, `npm run electron:*`, and `npm run android:*`.
- Agents should not run the build or packaging commands unless the user explicitly asks for that work.

## Runtime Logic Map

### `src/runtime/LocalNetHackRuntime.ts`

- Input intake from the engine: `sendInput`, `sendInputSequence`, `sendMouseInput`, `handleClientInput`.
- Input broker and wait flow: `requestInputCode`, `consumeInputResult`, `waitForQuestionInput`.
- NetHack callback switchboard: `handleUICallback`.
- Key callbacks: `handleShimGetNhEvent`, `handleShimNhGetch`, `handleShimYnFunction`, `handleShimNhPoskey`, `handleShimGetlin`.
- Menu callbacks: `shim_start_menu`, `shim_add_menu`, `shim_end_menu`, `shim_select_menu`.
- Map and position callbacks: `shim_print_glyph`, `shim_cliparound`, `shim_curs`, `shim_clear_nhwindow`.
- Status batching: `shim_status_update`, `statusPending`, `latestStatusUpdates`.
- Runtime bookkeeping: `pendingMenuSelection`, `menuSelectionReadyCount`, `pendingExtendedCommandRequest`, `pendingTextRequest`, `farLookMode`, `farLookOrigin`, `pendingLookMenuFarLookArm`.

### `src/game/Nethack3DEngine.ts`

- Engine setup: constructor, `initThreeJS`, and `connectToRuntime`.
- Runtime event dispatcher: `handleRuntimeEvent`.
- Rendering path: `updateTile`, `applyGlyphMaterial`, `createGlyphTexture`, `ensureGlyphOverlay`.
- Camera path: `updateCamera`, pan inertia, and mouse handlers.
- HUD and stats: `updatePlayerStats`, `updateStatsDisplay`.
- Dialog systems: `showQuestion`, `showDirectionQuestion`, `showInventoryDialog`, `showInfoMenuDialog`.
- Input path: `handleKeyDown`, `sendInput`, `sendInputSequence`, `sendMouseInput`.
- Runtime/application state: `applyClientOptions`, `setClientOptions`, `clearScene`, `recordPlayerMovement`.

## Runtime Event Contract

- Common map events: `map_glyph`, `map_glyph_batch`, `player_position`, `map_cursor`, `tile_not_found`, `area_refresh_complete`, `clear_scene`.
- Common UI events: `text`, `raw_print`, `question`, `direction_question`, `position_request`, `name_request`, `inventory_update`, `info_menu`, `extended_commands`.
- Common state events: `position_input_state`, `position_cursor`, `number_pad_mode`, `status_update`, `runtime_globals_snapshot`, `runtime_object_tile_map`, `damage_event`, `game_over_complete`, `inventory_updated_signal`.
- Transport/runtime events: `runtime_ready`, `runtime_error`, `runtime_terminated`.

## Runtime Command Contract

- `send_input`
- `send_input_sequence`
- `send_mouse_input`
- `request_tile_update`
- `request_area_update`
- `request_runtime_globals_snapshot`
- `set_logging`

## WASM Pointer Contract

- Pointer arguments with callback format type `p` are treated as direct WASM pointers (no extra dereference) in `src/runtime/LocalNetHackRuntime.ts`.
- Runtime pointer ABI tags are build-defined in `vite.config.ts` as `VITE_NH3D_WASM_367_POINTER_ABI_TAG` and `VITE_NH3D_WASM_37_POINTER_ABI_TAG`; pointer-sensitive callback/struct handling must align with these tags.
- `LocalNetHackRuntime` validates callback argument shapes and pointer layouts (menu_item, extcmd table, glyphinfo) against the active ABI contract and fails closed on mismatches.
- Current fork note: wasm-367 `shim_print_glyph` uses 5 callback args `(winid, x, y, glyph, bkglyph)` (not a glyphinfo pointer payload).
- Current fork note: wasm-367 `shim_get_ext_cmd` format is `iv`, so callback args appear as `[undefined]` and that is expected.
- Current fork note: wasm-37 `shim_add_menu` format is `vipi00iisi` (9 args); menu text is arg index `7`, item flags are arg index `8`, and identifier is delivered as a value (not pointer slot).
- Current fork note: wasm-37 `shim_print_glyph` format is `vi11pp` and uses glyphinfo pointers at args `3` and `4`.
- 3.6.7 extended command resolution order (`LocalNetHackRuntime`):
  1. Decode extcmd entries from `globalThis.nethackGlobal.pointers.extcmdlist` using the active extcmd layout contract.
  2. Extcmd layout source: app-owned 3.6.7 ABI profile (`stride=24`, `textPtrOffset=4`, `flagsOffset=16`, pointer mode `direct_or_slot`).
  3. Match typed text against decoded names (exact match, then unique-prefix match) and return the corresponding extcmd index.
  4. Validation is fail-closed (`minEntries`, required names), and unresolved commands return `-1` (no command).
- 3.7 extended command layout currently matches 3.6.7 for WASM32 (`struct ext_func_tab` stride `24`, `ef_txt` offset `4`, flags offset `16`), and uses the same decode/validation path.
- Troubleshooting and quick-fix steps: see `docs/pointer-abi-troubleshooting.md`.
- Do not scan arbitrary heap memory to discover command tables or silently fall back to hardcoded command indices, because that can misroute commands after WASM updates.

## High-Risk Zones

- Async input state in runtime: `activeInputRequest`, `awaitingQuestionInput`, `pendingTextRequest`, `pendingExtendedCommandRequest`, `pendingMenuSelection`.
- Position and far-look state: `positionInputModeActive`, `farLookMode`, `farLookOrigin`, `pendingLookMenuFarLookArm`.
- Tile classification: `src/game/glyphs/behavior.ts`, `src/game/glyphs/registry.ts`, and `updateTile` orchestration.
- Generated runtime catalogs (fallback/reference data): `src/game/glyphs/glyph-catalog.367.generated.ts`, `src/game/glyphs/glyph-catalog.37.generated.ts`, `src/game/tilesets.generated.ts`, `src/game/vulture/vulture-monster-keys.367.generated.ts`.
- Update flow: `src/update/*` plus the UI in `src/ui/App.tsx`.
- Startup options and checkpoint recovery: `src/runtime/startup-init-options.ts`, `src/runtime/runtime-capabilities.ts`, and `src/storage/client-options-storage.ts`.
