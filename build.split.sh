

# build.split.sh - EvilHack split build orchestrator (one-step build+deploy)
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

echo "[build.split.sh] === EvilHack WASM+JS one-step build+deploy ==="

# 1. Run the full WASM+JS build (cleans, patches, builds, links)
echo "[build.split.sh] Running build.wasm.sh..."
"$SCRIPT_DIR/imported/evilhack-wasm/build.wasm.sh"

# 2. Copy outputs to public/
echo "[build.split.sh] Copying evilhack.js and evilhack.wasm to public/..."
"$SCRIPT_DIR/imported/evilhack-wasm/copy-evilhack-wasm_js.sh"

echo "[build.split.sh] === Build and deploy complete ==="
