#!/bin/bash
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SCRIPTS_DIR="$SCRIPT_DIR/scripts"
"$SCRIPTS_DIR/01_setup_emcc_wrapper.sh"
"$SCRIPTS_DIR/02_build_native_tools.sh"
"$SCRIPTS_DIR/03_build_wasm_objects.sh"
"$SCRIPTS_DIR/04_patch_js_glue.sh"
"$SCRIPTS_DIR/05_copy_artifacts.sh"
echo "Full build complete."
