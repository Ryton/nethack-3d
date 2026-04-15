# EvilHack WASM Custom Entrypoint Mappings

This table documents the mapping between NetHack3D-required WASM exports and the actual EvilHack C functions used in the WASM build. This is essential for integration and debugging.

| NetHack3D Entrypoint | EvilHack Function Used      | Notes                                  |
|----------------------|----------------------------|----------------------------------------|
| hack_save            | dosave                     | Save game state                        |
| hack_restore         | dorestore                  | Restore game state                     |
| hack_init            | (stub or custom)           | Needs implementation or stub            |
| hack_exit            | (stub or custom)           | Needs implementation or stub            |
| hack_tick            | (stub or custom)           | Needs implementation or stub            |
| hack_key             | (stub or custom)           | Needs implementation or stub            |
| hack_mouse           | (stub or custom)           | Needs implementation or stub            |
| hack_resize          | (stub or custom)           | Needs implementation or stub            |
| hack_clipboard       | (stub or custom)           | Needs implementation or stub            |
| hack_debug           | (stub or custom)           | Needs implementation or stub            |

- If a mapping is marked as "stub or custom", it means the function is not yet implemented and should be provided as a stub or with custom logic as needed for NetHack3D integration.
- Update this table as you add or change mappings.
