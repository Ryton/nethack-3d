#!/bin/bash
set -e
EMCC_TMPDIR="$(mktemp -d)"
export PATH="$EMCC_TMPDIR:$PATH"
export EMCC_ORIG=$(command -v emcc)
cat > "$EMCC_TMPDIR/emcc" <<'EOF'
#!/bin/bash
echo "=== EMCC WRAPPER USED ===" >&2
echo "[EMCC INVOCATION] $EMCC_ORIG $@" >&2
exec $EMCC_ORIG "$@"
EOF
chmod +x "$EMCC_TMPDIR/emcc"
echo "[INFO] EMCC wrapper set up at $EMCC_TMPDIR"