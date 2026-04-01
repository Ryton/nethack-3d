# Movement And Position Flow

This is a living steering doc. Update it whenever movement, input broker behavior, or position-mode flows change.

This document is the source of truth for movement and position input behavior after the runtime interaction overhaul.

It focuses on:

- Browser key intake and movement mapping.
- Runtime single-consume input broker flow.
- Shared callback consumption path for event, position, and question input.
- Far-look position FSM behavior.
- Player and cursor update emission.

## Main Files

- `src/game/Nethack3DEngine.ts`
  - `handleKeyDown`
  - `sendInput`
  - `sendInputSequence`
  - `sendMouseInput`
  - `handleRuntimeEvent`
  - `updateTile`
  - `recordPlayerMovement`
  - `updateCamera`
- `src/runtime/WorkerRuntimeBridge.ts`
  - `sendInput`
  - `sendInputSequence`
  - `sendMouseInput`
- `src/runtime/runtime-worker.ts`
  - command forwarding for `send_input`, `send_input_sequence`, and `send_mouse_input`
- `src/runtime/LocalNetHackRuntime.ts`
  - `handleClientInput`
  - `requestInputCode`
  - `consumeInputResult`
  - `handleShimGetNhEvent`
  - `handleShimNhGetch`
  - `handleShimYnFunction`
  - `handleShimNhPoskey`
  - `shim_cliparound`
  - `shim_curs`
- `src/runtime/input/RuntimeInputBroker.ts`
  - broker queue and waiter coordination

## Runtime Movement Assumptions

Runtime boot config includes:

- `number_pad:1`: can be changed by the user mid-game.
- `pickup_types:$`

`number_pad:1` is still required because both engine and runtime translate directional input using numpad semantics.

## End-To-End Flow (Normal Movement Key)

1. Browser keydown enters `Nethack3DEngine.handleKeyDown`.
2. Engine applies input gates and remaps for dialogs, direction prompts, movement remaps, command shortcuts, and meta handling.
3. Engine sends input via `sendInput`, or `sendInputSequence` for synthetic multi-key flows, or `sendMouseInput` for click-based actions.
4. `WorkerRuntimeBridge` posts `send_input`, `send_input_sequence`, or `send_mouse_input` to the worker.
5. `runtime-worker.ts` forwards the command to `LocalNetHackRuntime`.
6. `LocalNetHackRuntime.handleClientInput` normalizes the key and enqueues it into `RuntimeInputBroker` as an `InputToken`.
7. NetHack callback waits request input through `requestInputCode(kind)`.
8. The broker returns exactly one token for exactly one request, in FIFO order, when the token matches the request kind.
9. Runtime converts the key with `processKey` and returns one keycode to NetHack.
10. NetHack advances state and emits updates such as `shim_cliparound`, `shim_print_glyph`, status updates, menus, and text callbacks.
11. Runtime emits worker events like `player_position`, `map_glyph_batch`, `position_cursor`, and `status_update`.
12. Engine consumes runtime events in `handleRuntimeEvent`.

## Runtime Input Broker Model

### Core Types

- `InputToken`: `{ key, source, createdAt, targetKinds?, mouseX?, mouseY?, mouseMod? }`
- `InputRequestKind`: `event`, `position`, or `menu`
- `InputConsumeResult`: request outcome or cancel code

### Invariants

- Single consume: one token is consumed by one waiter only.
- FIFO ordering: input order is stable across callbacks.
- Kind-aware routing: tokens can be tagged for specific callback kinds using `targetKinds`.
- No replay: there is no cooldown-based latest-input reuse.
- Shared path: event, position, and question waits all consume through the broker.
- Queue bound: the broker drops overflow once the queue reaches its max size.

### API

- `enqueueTokens(tokens)`
- `requestNext(requestKind)`
- `cancelAll(cancelCode)`
- `drain()`
- `dequeueToken()` and `prependToken()` for extended-command parsing

## Callback Consumption Rules

### `shim_get_nh_event`

- This callback is a non-blocking event pump hook.
- It should not consume command input.
- It is used to keep NetHack's event loop moving while other waits own the actual input requests.

### `shim_nhgetch`

- Uses `handleShimNhGetch` and calls `requestInputCode("event")`.
- This is one of the main event-key waits.

### `shim_yn_function`

- Uses `handleShimYnFunction`.
- For direction questions and normal y/n prompts, waits through `waitForQuestionInput()`, which internally uses `requestInputCode("event")`.
- Some prompts are auto-answered in runtime before the broker wait, such as container-related and checkpoint recovery flows.

### `shim_nh_poskey`

- Uses `handleShimNhPoskey` and calls `requestInputCode("position")`.
- Integrates with the explicit far-look FSM below.
- No duplicate consumption from queue and cached input mix.

## Far-Look Position FSM

`farLookMode` values:

- `none`
- `armed`
- `active`

Transitions:

1. `none -> armed` when `;` is consumed.
2. `armed -> active` when the next `shim_nh_poskey` begins.
3. `active -> none` on far-look exit input such as `Escape` or `Enter`, or when the runtime resolves the follow-up position request.

Related state and events:

- `farLookOrigin` tracks whether the far-look request came from a direct action or a look-menu path.
- `pendingLookMenuFarLookArm` preserves the arm state across look-menu routing.
- `position_input_state` is emitted when entering or exiting active position mode.
- `position_cursor` is emitted from `shim_curs` and cliparound-in-position context.

## Menu Input Isolation

Menu selection state is isolated from the general broker path:

- `pendingMenuSelection` tracks only the active menu completion wait.
- `menuSelectionReadyCount` stores the completion result until `shim_select_menu` consumes it.
- Multi-pickup toggle keys are handled in menu mode without leaking into unrelated event waits.
- `pendingInventoryContextSelection` tracks contextual inventory actions such as drop/wear/use follow-ups.

`shim_select_menu` still writes `menu_item` structs via pointer arguments, but waiting and resolution are centralized to menu-specific state.

## Meta And Extended Commands

- Meta input remains encoded as deterministic token expansion.
- Standard meta behavior: enqueue `Escape` then the primary key token.
- Bound meta extended commands enqueue `#`, command text, then `Enter`.
- Extended command parsing consumes from the broker queue and pushes back non-command tokens using `prependToken()`.

## Status Updates And Player Tracking

- `shim_status_update` accumulates updates in `statusPending`.
- On flush or reset pseudo-fields, runtime emits batched `status_update` events in stable field order.
- `latestStatusUpdates` remains the reconnect snapshot source.
- `player_position` comes from `shim_cliparound`.
- `recordPlayerMovement` keeps the engine movement-dependent UX aligned with the runtime consume model.
- `positionInputModeActive` on the engine controls whether movement keys are routed as player movement or position selection.

## Camera Follow Behavior

Camera behavior is unchanged:

- follows `playerPos` each frame with smoothing
- pan offsets remain additive
- far-look cursor does not retarget the camera

## Invariants To Preserve

- Keep public worker command names stable: `send_input`, `send_input_sequence`, `send_mouse_input`.
- Keep runtime event payload shapes stable for engine consumers.
- Keep all key-consuming callbacks routed through broker request flow.
- Do not reintroduce cooldown or latest-input replay logic.
- Keep menu waiters isolated from non-menu input waiters.
- Keep far-look state transitions deterministic and observable.
- Keep under-player top-item refresh wired after inventory mutations:
  - action-specific path via `pendingPostActionPlayerTileRefreshReason`
  - fallback path via `shim_update_inventory`
  - runtime events `under_player_item_glyph` / `under_player_item_glyph_cleared`

## Manual Validation Checklist

1. Cardinal movement with `hjkl`, arrows, and numpad.
2. Diagonal movement with `yubn`, numpad, `Home`, `PageUp`, `End`, and `PageDown`.
3. Hold-to-repeat movement without an extra step on release.
4. Wait behavior with `.` and Space.
5. Direction prompts and closure behavior.
6. Far-look `;` flow, cursor motion, and clean exit.
7. Multi-pickup toggles, confirm, and cancel.
8. Inventory and single-select question flows.
9. Meta, Alt, and extended command entry.
10. Escape across menus, questions, and position mode.
11. Pickup, drop, eat, and autopickup updating the item shown under the player.
