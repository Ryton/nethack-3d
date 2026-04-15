## TODO: Data build phase skipped in build.wasm.sh

The following build steps are currently commented out in build.wasm.sh due to errors with castle.des (MAGIC_CHEST syntax error):

```
make -C "$EVILHACK_DIR/dat" \
    -f Makefile -f ../sys/unix/hints/linux-wasm \
    "${NATIVE_TOOL_OVERRIDES[@]}"

python3 "$VALIDATION_SCRIPT" "$EVILHACK_DIR/dat"
```

Problem: lev_comp fails on castle.des due to unrecognized "MAGIC_CHEST" keyword.

Action needed: Update lev_comp or patch castle.des to resolve this, then re-enable the above lines.