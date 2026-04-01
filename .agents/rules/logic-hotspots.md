# Logic Hotspots Steering

This is a living steering doc. Update it whenever hotspots, ownership, or edit playbooks change.

Use this file when deciding where to implement a change.
Detailed movement and cursor flow reference: `.agents/rules/movement-flow.md`.

## If You Need To Change Rendering

- Start in `src/game/Nethack3DEngine.ts` (`updateTile`, `applyGlyphMaterial`, `createGlyphTexture`, `ensureGlyphOverlay`).
- Glyph resolution and classification should prioritize live runtime data and NetHack/WASM callback paths whenever possible. Use these files for mapping/orchestration:
  - `src/game/glyphs/index.ts`
  - `src/game/glyphs/registry.ts`
  - `src/game/glyphs/behavior.ts`
  - `src/game/glyphs/glyph-catalog.367.generated.ts` (generated fallback/reference; not authoritative for all variant item tiles)
  - `src/game/glyphs/glyph-catalog.37.generated.ts` (generated fallback/reference; not authoritative for all variant item tiles)
- Tileset selection and asset resolution live in `src/game/tilesets.ts`.
- User tileset persistence lives in `src/game/user-tileset-storage.ts`.
- Vulture projection helpers live in `src/game/vulture/translation.ts`.
- If tile appearance changes affect overlays or material reuse, check the glyph overlay and reveal-fade code paths near `ensureGlyphOverlay`, `createGlyphTexture`, `applyGlyphMaterial`, and the tile reveal timing fields.

## If You Need To Change Runtime Event Behavior

- Runtime event emit points are in `src/runtime/LocalNetHackRuntime.ts` (`emit(...)` sites, mostly inside `handleUICallback`).
- Worker transport lives in `src/runtime/runtime-worker.ts` and `src/runtime/WorkerRuntimeBridge.ts`.
- Engine receive and dispatch is `handleRuntimeEvent` in `src/game/Nethack3DEngine.ts`.
- Add or update event payloads in runtime and engine in one commit.
- Keep `src/runtime/types.ts` in sync when the command or envelope surface changes.

### Under-Player Top-Item Refresh Is A Hot Path

- The "item shown under the player" is not just a render concern. It is a runtime-to-engine contract between:
  - `LocalNetHackRuntime.ts`
  - `Nethack3DEngine.ts`
  - the WASM helper functions `topItemGlyphUnderPlayer` and `topItemTileIndexUnderPlayer`
- The runtime emits:
  - `under_player_item_glyph`
  - `under_player_item_glyph_cleared`
- The engine consumes those in `handleRuntimeEvent` and updates:
  - `flatFeatureUnderPlayerCache`
  - `fpsAuthoritativeUnderPlayerFallbackSuppressedKeys`
  - the affected tile via `refreshTileVisualFromStateCache(...)`

### How It Is Supposed To Work

- There are two refresh paths, and both matter:
  - Specific post-action refresh:
    - Runtime arms `pendingPostActionPlayerTileRefreshReason`
    - Later callbacks like `shim_nh_poskey` or `shim_update_inventory` call `maybeRefreshPendingPostActionPlayerTile(...)`
  - General inventory mutation fallback:
    - `shim_update_inventory` should still re-check the top item under the player even if no pending reason was armed
- This exists because actions like pickup, drop, eat, autopickup, and some menu-confirmed inventory mutations can change the top-of-pile item on the player tile without a clean terrain redraw.

### Common Break Pattern

- Symptom:
  - An item under the player does not disappear after pickup/eat/use.
  - A new top item under the player does not appear after drop/autopickup/menu-confirmed changes.
- Most common cause:
  - The runtime armed no `pendingPostActionPlayerTileRefreshReason`, so the later callback had nothing to consume.
  - Or the engine received no `under_player_item_glyph` / cleared event, so `flatFeatureUnderPlayerCache` stayed stale.
- Less common cause:
  - The runtime helper lookup failed, so the runtime never emitted the top-item event.
  - The engine classified the returned glyph as something that should not be cached under the player and cleared it immediately.

### First Places To Check

- Runtime arm points in `src/runtime/LocalNetHackRuntime.ts`:
  - `getPostActionPlayerTileRefreshReasonForMenuItem`
  - `getPostActionPlayerTileRefreshReasonForQuestion`
  - `getPostActionPlayerTileRefreshReasonForAnsweredYnQuestion`
  - `armPendingPostActionPlayerTileRefreshByReason`
- Runtime consume points in `src/runtime/LocalNetHackRuntime.ts`:
  - `maybeRefreshPendingPostActionPlayerTile`
  - `maybeRefreshUnderPlayerTopItemAfterInventoryUpdate`
  - `handleShimNhPoskey`
  - `shim_update_inventory`
- Runtime helper decode/emission in `src/runtime/LocalNetHackRuntime.ts`:
  - `emitUnderPlayerItemGlyphIfAvailableAt`
- Engine receive/cache/render in `src/game/Nethack3DEngine.ts`:
  - `applyUnderPlayerItemGlyphEvent`
  - `clearUnderPlayerItemGlyphEvent`
  - `shouldRenderFlatFeatureUnderPlayer`
  - `getFpsPlayerTileUnderlaySnapshotFromCache`
  - `resolveFpsFloorUnderlayBehaviorFromCache`
  - `refreshTileVisualFromStateCache`

### Rules To Preserve

- Do not rely only on action-specific arming. Keep an inventory-update fallback recheck in the runtime.
- If you add a new inventory mutation flow, either:
  - arm `pendingPostActionPlayerTileRefreshReason`, or
  - ensure `shim_update_inventory` or an equivalent later callback will still force a top-item recheck.
- If you change `shouldRenderFlatFeatureUnderPlayer`, verify pickup/drop/eat/use on the player tile in both FPS and overhead tiles modes.
- If you change event names or payload shape for under-player item refresh, update runtime emitters and engine consumers in the same commit.

## If You Need To Change Input Or Menus

- Browser key mapping and dialog gating: `src/game/Nethack3DEngine.ts` (`handleKeyDown`).
- Runtime input broker implementation: `src/runtime/input/RuntimeInputBroker.ts`.
- Runtime key normalization and enqueue path: `handleClientInput` in `src/runtime/LocalNetHackRuntime.ts`.
- Runtime consume path: `requestInputCode`, `consumeInputResult`, `waitForQuestionInput` in `src/runtime/LocalNetHackRuntime.ts`.
- Runtime callback-kind targeting (`targetKinds`) should be preserved for synthetic, meta, and menu key sequences.
- Key callbacks:
  - `handleShimGetNhEvent`: non-blocking NetHack event-pump hook; does not consume command input.
  - `handleShimNhGetch`: blocking "get one key" wait for general event input.
  - `handleShimYnFunction`: y/n (and direction-style) question handler that emits question events and waits for response.
  - `handleShimNhPoskey`: position/direction input wait (x, y, mod pointers) used for far-look and cursor targeting.
  - `handleShimGetlin`: free-text prompt handler that emits `text_request` and writes the response buffer.
- Menu callbacks:
  - `shim_start_menu`: begins menu capture for a window.
  - `shim_add_menu`: appends a selectable menu row/item to the active menu.
  - `shim_end_menu`: finalizes menu content and prompt text before selection.
  - `shim_select_menu`: waits for/collects menu picks and writes selected items back to NetHack.
- Menu waiter isolation state:
  - `pendingMenuSelection`
  - `menuSelectionReadyCount`
  - `pendingExtendedCommandRequest`
- Position and far-look state:
  - `farLookMode` (`none | armed | active`)
  - `farLookOrigin`
  - `pendingLookMenuFarLookArm`
  - `positionInputModeActive` on the engine side
  - `position_input_state` and `position_cursor` emit paths

## If You Need To Change Inventory UX

- Runtime inventory updates and inventory-help menus are produced in `shim_end_menu` handling for window 4 in `src/runtime/LocalNetHackRuntime.ts`.
- Engine inventory handling:
  - event handling: `inventory_update` case in `handleRuntimeEvent`
  - UI display: `updateInventoryDisplay`, `showInventoryDialog`
- Contextual inventory actions in the runtime use `pendingInventoryContextSelection` to route follow-up menu picks.
- Multi-pickup uses `isInMultiPickup`, `menuSelections`, and `menuSelectionReadyCount`.

## If You Need To Change Stats Or HUD

- Runtime status decode and flush batching:
  - `shim_status_update`: receives status field/value updates and batches them until flush/reset markers.
  - `statusPending`
  - `latestStatusUpdates`
- Engine field mapping and parsing: `updatePlayerStats`.
- Rendering HUD bars and labels: `updateStatsDisplay`.
- If status changes affect reconnects, check `runtime_globals_snapshot` and the store hydration path in `src/state/gameStore.ts`.

## If You Need To Change Camera Or Controls

- Keyboard movement mappings and dialog-aware suppression: `src/game/Nethack3DEngine.ts` (`handleKeyDown`).
- Mouse zoom, rotate, pan, and click-look handlers: `src/game/Nethack3DEngine.ts` mouse handlers.
- Camera transform calculation: `updateCamera`.
- Controller bindings and action labels live in `src/game/controller-bindings.ts` and are surfaced in `src/ui/App.tsx`.

## If You Need To Change Tiles, Glyphs, Or World Classification

- Tile behavior decisions live in `src/game/glyphs/behavior.ts` and are consumed by `updateTile`.
- Glyph resolution/version selection lives in `src/game/glyphs/registry.ts`.
- Glyph catalogs are versioned, checked-in generated fallback references. They are useful for static mapping and debugging, but can be wrong for some item-variation tiles; prefer proper live WASM NetHack calls whenever possible.
- World/terrain helpers and tile classification assumptions should be verified against `src/runtime/displayFileCatalog.ts` and the imported NetHack data under `imported/nethack-3.6.7` when behavior depends on canonical game text or object data.

## If You Need To Change Startup Options, Saves, Or Updates

- Startup init option schema, defaults, normalization, and serialization live in `src/runtime/startup-init-options.ts`.
- Client option schema/defaults/normalization live in `src/game/ui-types.ts`.
- Client option UI, tab grouping, and draft/apply flow live in `src/ui/App.tsx`.
- Persisted client options and localStorage-to-IndexedDB migration live in `src/storage/client-options-storage.ts`.
- Engine-side application of options at runtime lives in `src/game/Nethack3DEngine.ts` (`setClientOptions`, `applyClientOptions`).
- Save database naming and mount logic live in `src/runtime/save-storage.ts`.
- Runtime checkpoint recovery support is gated in `src/runtime/runtime-capabilities.ts`.
- Update check/apply/cancel/progress flow lives in `src/update/client-updater.ts`, `src/update/manifest.ts`, and `src/update/types.ts`.

## If You Need To Change Level Transition Behavior

- Runtime triggers clear on map window reset: `shim_clear_nhwindow` in `src/runtime/LocalNetHackRuntime.ts` (window-clear callback; map clears should emit `clear_scene`).
- Engine clear path: `clearScene` and the `clear_scene` event case in `handleRuntimeEvent`.
- Player movement reconciliation is handled by `recordPlayerMovement` and the player position update branch.

## Sanity Checklist For Agents

- If changing the worker protocol, verify `src/runtime/types.ts`, `src/runtime/runtime-worker.ts`, `src/runtime/WorkerRuntimeBridge.ts`, `src/runtime/LocalNetHackRuntime.ts`, and `src/game/Nethack3DEngine.ts` together.
- If changing runtime artifacts or glyph catalogs, make sure the generated files stay aligned with the loaded runtime version.
- If changing menus or input, confirm Esc and Enter flow, direction prompts, inventory selection, far-look transitions, and extended commands still work.
- If changing broker behavior, ensure no callback bypasses `requestInputCode(...)` for key-consuming waits.
- If changing tile logic, verify player tracking, map refresh, and tile reveal behavior.
- If changing status updates, verify flush-trigger ordering and reconnect snapshot consistency.
