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
- Generated glyph catalogs are fallback references, not the final source of truth.
  If live runtime payloads disagree with the catalog, especially for item-like
  top-of-pile results, prefer the runtime payload.
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

### Under-Player Loot / Flat-Feature Refresh Is A Hot Path

- The "item shown under the player" is a runtime-to-engine contract between:
  - `src/runtime/LocalNetHackRuntime.ts`
  - `src/game/Nethack3DEngine.ts`
  - the WASM helper functions `topItemGlyphUnderPlayer` and `topItemTileIndexUnderPlayer`
- Those helper functions are authoritative for the visible top-of-pile item on the
  current player tile. After partial pickup, drop, or any other stack mutation,
  the helper result wins over cached snapshots.
- The runtime emits:
  - `under_player_item_glyph`
  - `under_player_item_glyph_cleared`
- For authoritative under-player item events, the runtime now also carries
  live item-classification hints such as runtime `kind` and `glyphFlags`.
  The engine should preserve and reuse those hints instead of re-deriving kind
  solely from the generated glyph catalog.
- The engine consumes those in `handleRuntimeEvent` and updates:
  - `authoritativeUnderPlayerItemSnapshots`
  - `flatFeatureUnderPlayerCache`
  - `fpsAuthoritativeUnderPlayerFallbackSuppressedKeys`
  - the affected tile via `refreshTileVisualFromStateCache(...)`

### Runtime Model

- The runtime now tracks three pieces of pending state:
  - `pendingPostActionPlayerTileRefreshReason`
  - `pendingPostActionPlayerTileRefreshTarget`
  - `pendingPostActionPlayerTileRefreshSnapshot`
- The reason is priority-based. High-confidence pickup/loot intents should not be stomped by lower-priority fallbacks like `monster-like-vacated-tile`.
- The target matters for multi-step travel. If the player has not reached the armed tile yet, `maybeRefreshPendingPostActionPlayerTile(...)` must wait instead of refreshing the current tile.
- The snapshot matters for "moved onto loot but did not pick it up" cases. The runtime can replay the remembered loot glyph from the clicked target tile even when helper queries would now see only `@`.

### How It Currently Works

- Intent arming happens before NetHack finishes the action:
  - Mouse left-click on a remote loot-like tile arms `move-onto-lootlike-tile`.
  - Keyboard movement onto an adjacent loot-like tile arms `move-onto-lootlike-tile`.
  - Clicking the current player tile or pressing `,` arms `pickup-current-player-tile`.
  - Menu/question-driven inventory mutations still arm the older action-specific reasons.
- Stack mutations on the current tile do not trust the old snapshot after success:
  - partial pickup from a pile must re-query `topItemGlyphUnderPlayer` so the next
    remaining item becomes visible under the player
  - dropping onto the current tile must also re-query `topItemGlyphUnderPlayer`
    so the newly dropped item can become the visible top item immediately
  - eating or any other player action that can remove, add, or reorder the
    current-tile stack should also end in an authoritative helper refresh rather
    than trusting the stale snapshot
- Consume points are:
  - `handleShimNhPoskey`
  - `shim_update_inventory`
- `maybeRefreshPendingPostActionPlayerTile(...)` behaves differently by reason:
  - `move-onto-lootlike-tile` with a stored snapshot replays that snapshot once the player reaches the armed target.
  - Other reasons query helpers and emit the real current top item or a clear event.
- Successful pickup/autopickup uses raw text as an authoritative success signal:
  - Modern/3.4.3-style inventory assignment text like `f - a tripe ration.` or `$ - 7 gold pieces.` clears the pending target/current tile immediately.
  - Slash'EM also needs a runtime-specific bare-gold case like `28 gold pieces.` because it does not always use the inventory-assignment format.
- Slash'EM legacy drop flows can route through a `yn_function` prompt followed by
  a questionless `WIN_INVEN` menu after `*`. In that case, the runtime must use
  the active Y/N prompt text (`lastQuestionText`) as the action context when
  `currentMenuQuestionText` is empty, or the drop refresh will never arm.
- This split is intentional:
  - intent arming decides when we should care about a tile
  - raw-print pickup success decides when the loot is definitely gone
  - helper queries/snapshots decide what should remain visible under the player

### Engine Model

- The engine keeps three distinct layers of state:
  - `authoritativeUnderPlayerItemSnapshots`: runtime-confirmed item-under-player state
  - `flatFeatureUnderPlayerCache`: generic cached under-player flat features and loot-like visuals
  - `lastKnownTerrain`: remembered terrain/floor state
- `authoritativeUnderPlayerItemSnapshots` may now carry runtime-side item-kind
  hints (`kind`, `glyphFlags`) in addition to `glyph`, `char`, `color`,
  `tileIndex`, and `symidx`.
- `classifyTileBehavior(...)` / `resolveGlyph(...)` should treat those runtime
  hints as authoritative when present, especially for under-player item events.
- `fpsAuthoritativeUnderPlayerFallbackSuppressedKeys` prevents generic loot fallback from resurrecting stale loot after the runtime has explicitly cleared it.
- `getFpsPlayerTileUnderlaySnapshotFromCache(...)` now prefers:
  - authoritative under-player item
  - generic under-player flat feature cache, unless suppressed
  - runtime floor underlay / remembered terrain
- Player position updates prune `authoritativeUnderPlayerItemSnapshots` to the current tile so stale authoritative loot does not leak across movement.

### Common Break Patterns

- Multi-step travel onto loot hides the loot under the player:
  - The runtime armed no target/snapshot for `move-onto-lootlike-tile`, or consumed it before the player reached the target.
- Clicking the current player tile or pressing `,` does not clear picked-up loot:
  - `pickup-current-player-tile` was never armed, often because helpers were unavailable during an active `nh_poskey`.
- Pickup succeeds but the loot reappears immediately:
  - A raw-print pickup-success message was treated like a later recheck instead of an authoritative clear.
  - Or the engine kept using `flatFeatureUnderPlayerCache` because suppression was not set.
- Partial pickup from a stack leaves the old top item under the player, or clears
  the pile entirely:
  - the runtime reused a stale snapshot instead of re-querying `topItemGlyphUnderPlayer`
  - or the helper result was unavailable in the loaded runtime artifact
  - or the engine reclassified a live runtime item result through the generated
    glyph catalog and treated it as a non-item
- Dropping onto the current tile does not show the new top item until the player
  moves away:
  - the drop action never armed a post-action refresh
  - or a legacy questionless inventory menu lost its question context and failed
    to classify as `drop-question`
  - or a live top-of-pile item result was decoded from runtime tile metadata
    but then downgraded by static catalog classification
- A stale current-tile pickup arm affects later travel:
  - `pickup-current-player-tile` was not cleared when a new remote target was chosen.
- 3.6.7 helper behavior seems impossible or inconsistent with source:
  - `copy-wasm` only copies `packages/wasm-367/build/nethack.js`; it does not
    rebuild it
  - if WSL source changed but the build artifact did not, the checked-in public
    runtime can be stale and miss helper installs like `topItemGlyphUnderPlayer`

### First Places To Check

- Runtime arm/clear points in `src/runtime/LocalNetHackRuntime.ts`:
  - `armPendingPostActionPlayerTileRefreshByReason`
  - `clearPendingPostActionPlayerTileRefreshByReason`
  - `clearPendingPostActionPlayerTileRefresh`
  - `clearPendingCurrentPlayerPickupRefreshIfTargetDiffers`
  - `maybeArmPendingPostActionPlayerTileRefreshForLootMoveTarget`
  - `maybeArmPendingPostActionPlayerTileRefreshForCurrentPlayerLoot`
  - `resolvePostActionPlayerTileRefreshQuestionContext`
- Runtime consume / result points in `src/runtime/LocalNetHackRuntime.ts`:
  - `maybeRefreshPendingPostActionPlayerTile`
  - `handleShimNhPoskey`
  - `shim_update_inventory`
  - `armPendingPostActionPlayerTileRefreshForAutopickupRawPrint`
  - `isAutopickupInventoryAssignmentRawPrint`
  - `emitUnderPlayerItemGlyphFromPendingSnapshot`
  - `emitUnderPlayerItemGlyphIfAvailableAt`
- Runtime artifact/source-of-truth checks:
  - `scripts/wasm/copy-wasm.mjs`
  - `public/nethack-367.js`
  - `\\wsl.localhost\Ubuntu\home\james\Repos\forked\neth4ck-monorepo\packages\wasm-367\build\nethack.js`
- Engine receive/cache/render in `src/game/Nethack3DEngine.ts`:
  - `applyUnderPlayerItemGlyphEvent`
  - `clearUnderPlayerItemGlyphEvent`
  - `getAuthoritativeUnderPlayerItemSnapshot`
  - `getFpsPlayerTileUnderlaySnapshotFromCache`
  - `shouldRenderFlatFeatureUnderPlayer`
  - `updateTile`
  - `refreshTileVisualFromStateCache`
- Shared glyph resolution/classification:
  - `resolveGlyph`
  - `classifyTileBehavior`
- Runtime event decode helpers in `src/runtime/LocalNetHackRuntime.ts`:
  - `extractGlyphInfoTileIndex`
  - `extractGlyphInfoSymidx`
  - `extractGlyphInfoGlyphFlags`

### Rules To Preserve

- Keep intent arming and pickup-success handling separate. Do not try to infer every pickup from raw text alone.
- If you add a new way to move onto loot, arm `move-onto-lootlike-tile` with both target and snapshot.
- If you add a new way to pick up loot on the current tile, arm `pickup-current-player-tile` even when helpers are temporarily unavailable.
- After any successful stack mutation on the current tile, prefer the authoritative
  helper result over the old snapshot. This includes partial pickup, drop, eat,
  and any other player action that can mutate the visible pile.
- When the runtime provides authoritative item metadata for an under-player item
  event, do not let the generated glyph catalog override it back to a non-item
  kind. The catalog is a fallback, not the arbiter, in that path.
- If you add a new pickup success text variant, teach `isAutopickupInventoryAssignmentRawPrint(...)` about it only for the runtime that needs it.
- If a legacy runtime shows a questionless inventory menu immediately after a Y/N
  prompt, preserve the prompt context by falling back to `lastQuestionText` when
  arming the post-action refresh reason.
- Do not let generic `flatFeatureUnderPlayerCache` reintroduce loot after a runtime clear. Preserve the suppression-key behavior.
- If you change under-player event names or payloads, update runtime emitters and engine consumers in the same commit.
- If you change `shouldRenderFlatFeatureUnderPlayer`, verify pickup/drop/eat/use/autopickup on the player tile in both FPS and overhead tiles modes.

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
