# EvilHack WASM Entrypoints Implementation Plan

This document outlines a step-by-step plan to implement **non-stub** versions of the required EvilHack WASM entrypoints, based on the source code in `../EvilHack/src` and examples in `./important/NethackShim.winshim*.c`. This plan follows the guidelines from `.agents/rules/AGENTS.md`.

## 1. Overview

The following entrypoints must be implemented:
- hack_init
- hack_exit
- hack_tick
- hack_key
- hack_mouse
- hack_save
- hack_restore
- hack_resize
- hack_clipboard
- hack_debug
- malloc
- free
- realloc
- memcpy
- memset

## 2. General Guidelines
- **No stubs:** Each function must perform its intended logic, not just return or log a message.
- **Reference implementations:** Use `../EvilHack/src` for core logic and `./important/NethackShim.winshim*.c` for WASM/JS glue patterns.
- **Documentation:** Each function should be documented with its purpose, parameters, and expected behavior.
- **Testing:** Add basic tests or validation for each entrypoint.
- **Incremental integration:** Implement and test entrypoints one by one.

## 3. Implementation Steps

### Step 1: Analyze Existing Code
- Review `../EvilHack/src` for the logic of each entrypoint.
- Review `./important/NethackShim.winshim*.c` for WASM export patterns and glue code.
- Identify dependencies and required data structures for each entrypoint.

### Step 2: Design WASM-Compatible Interfaces
- Define C function signatures for each entrypoint, ensuring they are WASM-exportable (e.g., `EMSCRIPTEN_KEEPALIVE`).
- Ensure parameter types are compatible with WASM/JS (e.g., use `int`, `char*`, etc.).

### Step 3: Implement Entrypoints
For each entrypoint:
1. Locate or design the function in `../EvilHack/src`.
2. Adapt or wrap the function for WASM export (using Emscripten macros if needed).
3. Implement the function logic (no stubs).
4. Add documentation comments.
5. Add to the WASM export list (e.g., in the Emscripten build config or CMakeLists.txt).

#### Example (for `hack_init`):
- Find or implement `hack_init` in C.
- Annotate with `EMSCRIPTEN_KEEPALIVE`.
- Ensure it initializes the game state as expected.
- Document parameters and return value.

### Step 4: Memory Functions
- For `malloc`, `free`, `realloc`, `memcpy`, `memset`, use standard C library implementations, but ensure they are exported and available to WASM/JS.

### Step 5: Build and Export
- Update the build system to export all required entrypoints.
- Build the WASM module and verify exports using `check-evilhack-exports.mjs`.

### Step 6: Test Integration
- Write or adapt tests to call each entrypoint from JS and verify correct behavior.
- Check for missing or extra exports.

### Step 7: Documentation and Review
- Document each function and its integration in this file.
- Review against `.agents/rules/AGENTS.md` for compliance.

## 4. Example Entrypoint Table
| Entrypoint      | Source Location         | Notes/Dependencies           |
|-----------------|------------------------|------------------------------|
| hack_init       | EvilHack/src/init.c    | Game state initialization    |
| hack_exit       | EvilHack/src/end.c     | Cleanup and exit logic       |
| hack_tick       | EvilHack/src/main.c    | Main game loop tick          |
| hack_key        | EvilHack/src/input.c   | Keyboard input handling      |
| hack_mouse      | EvilHack/src/input.c   | Mouse input handling         |
| hack_save       | EvilHack/src/save.c    | Save game state              |
| hack_restore    | EvilHack/src/save.c    | Restore game state           |
| hack_resize     | EvilHack/src/ui.c      | Handle window resize         |
| hack_clipboard  | EvilHack/src/ui.c      | Clipboard integration        |
| hack_debug      | EvilHack/src/debug.c   | Debugging utilities          |
| malloc          | libc/stdlib            | Standard memory allocation   |
| free            | libc/stdlib            | Standard memory free         |
| realloc         | libc/stdlib            | Standard memory reallocation |
| memcpy          | libc/string            | Standard memory copy         |
| memset          | libc/string            | Standard memory set          |

## 5. Next Steps
1. Confirm entrypoint list and update as needed.
2. Begin with `hack_init` and proceed down the list.
3. Track progress and issues in this document.

---

*This plan is living documentation. Update as implementation progresses.*
