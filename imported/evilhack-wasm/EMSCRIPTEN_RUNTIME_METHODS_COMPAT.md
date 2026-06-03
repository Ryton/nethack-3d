# Emscripten EXPORTED_RUNTIME_METHODS Compatibility Note

## Context

Recent Emscripten versions (2025+) have removed or internalized several runtime methods that were previously exportable via `-sEXPORTED_RUNTIME_METHODS`. Notably, `IDBFS` and `updateMemoryViews` are no longer valid for export and will cause build failures if included in the list.

## What Changed
- **IDBFS**: The filesystem is still available for mounting and use, but the runtime method `IDBFS` is not exportable. Use the standard FS API for persistent storage.
- **updateMemoryViews**: This is now internal to Emscripten and should not be exported. If you need similar functionality, consult the latest Emscripten documentation for alternatives.

## Migration Guidance
- Remove `IDBFS` and `updateMemoryViews` from `EXPORTED_RUNTIME_METHODS` in your build scripts.
- If you require IDBFS or persistent storage, mount the filesystem in your JavaScript/WASM code as per Emscripten's current documentation.
- If Nethack3D or other code later requires a specific runtime method, check the Emscripten changelog and docs for the new approach or use a JavaScript polyfill/workaround.

## Example (2026):
```sh
export EMCC_CFLAGS="-sEXPORTED_RUNTIME_METHODS='[\"cwrap\",\"ccall\",\"addFunction\",\"removeFunction\",\"UTF8ToString\",\"stringToUTF8\",\"getValue\",\"setValue\",\"ENV\",\"FS\"]' $EMCC_CFLAGS"
```

## References
- [Emscripten Changelog](https://github.com/emscripten-core/emscripten/blob/main/ChangeLog.md)
- [Emscripten EXPORTED_RUNTIME_METHODS Docs](https://emscripten.org/docs/api_reference/advanced-apis.html#emscripten-runtime-methods)

---
This note was added to clarify why certain runtime methods are omitted from the build configuration. Update as needed for future Emscripten releases.
