
# --- MANUAL .o BUILD AND LINK FOR WASM/JS OUTPUT ---
# If the Makefile does not rebuild all .o files by default:
#   1. Manually build all object files:
#        for f in src/*.c; do emcc -c $f -o $(basename $f .c).o; done
#      (Adjust path/flags as needed for your project)
#   2. Link all .o files into evilhack.js/evilhack.wasm:
#        emcc *.o -s MODULARIZE=1 -s EXPORT_ES6=1 -o evilhack.js
#   3. This produces evilhack.js and evilhack.wasm as ES6 modules, ready for deployment.
#   4. Long-term: Patch Makefile.src to automate these steps.
# --- FULL EVILHACK WASM SPLIT-BUILD SESSION LOG (STUBS & PATCH LOGIC) ---
#
# 1. Create split build directories:
#      mkdir -p build/EvilHack-0.9.2_native
#      mkdir -p build/EvilHack-0.9.2_wasm
#
# 2. Copy source to build dirs:
#      cp -a imported/evilhack-wasm/EvilHack-0.9.2/. build/EvilHack-0.9.2_native/
#      cp -a imported/evilhack-wasm/EvilHack-0.9.2/. build/EvilHack-0.9.2_wasm/
#
# 3. Patch Makefile.src for WASM:
#      # a) Use absolute paths for all src/*.c rules (emcc requirement)
#      # b) Remove duplicate/relative entries in HACKCSRC and other lists
#      # c) Fix references to monst.c, objects.c, etc. to use correct locations
#      # d) Remove/comment install/permission logic (save/whereis/chmod) for WASM
#      # e) Ensure dungeon and related files are never deleted or rebuilt in WASM
#      # f) Fix Makefile syntax errors from previous edits
#      # g) Add ES6 glue flags for emcc:
#      #      LDFLAGS_WASM = -s MODULARIZE=1 -s EXPORT_ES6=1 -o evilhack.js
#      # h) Example sed/patch command (to be automated):
#      #      sed -i 's|monst.c|$(EVILHACK_ABSROOT)/src/monst.c|g' sys/unix/Makefile.src
#      #      # ...repeat for all src/*.c and include/*.h as needed
#
# 4. Build/test/fix cycle:
#      cd build/EvilHack-0.9.2_wasm/EvilHack-0.9.2
#      make -f sys/unix/Makefile.src
#      # If errors, patch Makefile.src as above and repeat
#      # If evilhack.js is not ES6 module, ensure emcc flags are correct and relink
#
# 5. Clean build outputs (if needed):
#      find . -name '*.o' -delete
#      rm -f evilhack.js evilhack.wasm
#      make -f sys/unix/Makefile.src
#
# 6. Copy outputs to public/:
#      cp evilhack.js evilhack.wasm ~/repos/nethack-3d/public/
#
# 7. Troubleshooting:
#      # If Makefile.src is missing, restore from backup or regenerate from templates, then reapply patches
#      # If loader fails with 'Module default export is not a function', evilhack.js is not ES6—rebuild with correct emcc flags
#      # If dungeon files are deleted, patch spotless/clean rules
#
# 8. Backup/restore:
#      # Always back up patched Makefile.src after successful build:
#      cp sys/unix/Makefile.src BACKUP_wasm_sys_unix_makefile.src
#
# 9. TODO: Convert all manual patching to automated sed/patch commands or patch files for full reproducibility.
#
# --- END OF SESSION LOG ---
# --- CRITICAL: Preserve Patched Makefile.src ---
# The sys/unix/Makefile.src in the WASM build directory is the result of all split-build patches:
#   - Absolute src/*.c paths, duplicate/relative entry removal, dungeon/install logic, ES6 glue, etc.
#   - This file is NOT present in the original source and must be preserved for reproducibility!
#
# To back up the patched Makefile.src:
#   cp imported/evilhack-wasm/build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/sys/unix/Makefile.src Makefile.src.patched.bak
#
# If you ever need to recreate it, follow the patch steps in this script, but restoring this backup is fastest.
#
#!/bin/bash
# build.split.sh - EvilHack split build orchestrator (stub)
#
# This script will automate the split build process for EvilHack (native and WASM).
#

# --- EvilHack Split Build Process (as performed in this session) ---
#
# 1. Split source: Created two separate build directories:
#      build/EvilHack-0.9.2_native  (for native build)
#      build/EvilHack-0.9.2_wasm    (for WASM build)
#    - Copied EvilHack-0.9.2 source into each (never touch original after copy).
#
# 2. Makefile cleanup and patching:
#    - Patched sys/unix/Makefile.src in WASM dir to:
#        * Use absolute paths for all src/*.c rules (required for emcc).
#        * Remove duplicate/relative entries in HACKCSRC and other lists.
#        * Fix references to monst.c, objects.c, etc. to use correct locations.
#        * Remove or comment out install/permission logic (save/whereis/chmod) for WASM.
#        * Ensure dungeon and related files are never deleted or rebuilt in WASM.
#        * Fix Makefile syntax errors from previous edits.
#
# 3. File safety:
#    - Ensured all .o files for WASM are built with emcc and correct include paths.
#    - Symlinked or copied config1.h, hack.h, and other headers as needed.
#    - Verified dungeon files are only built in native, then copied to WASM as needed.
#
# 4. Build/test/fix cycle (detailed):
#    a) Run make (or build script) in WASM dir.
#    b) Capture and analyze all errors/warnings.
#    c) For each error:
#         - If missing header/source: patch Makefile to fix include/src path (use absolute paths for emcc).
#         - If object file format error: ensure all .o files are built with emcc, not native cc.
#         - If missing symbol (e.g., _main): check entry point and Makefile rules.
#         - If Makefile syntax error: fix duplicate/relative entries, trailing backslashes, or misplaced colons.
#         - If dungeon file is rebuilt/deleted: comment out or patch spotless/clean rules and install logic.
#         - If evilhack.js is not ES6 module: patch Makefile.src to add:
#               LDFLAGS_WASM = -s MODULARIZE=1 -s EXPORT_ES6=1 -o evilhack.js
#           and ensure the link step uses these flags for WASM build.
#           Then rebuild.
#           (See Makefile.src patch in sys/unix/ for details.)
#    d) After each patch, rerun build and repeat until evilhack.wasm and evilhack.js are produced with no critical errors.
#    e) After successful build, copy evilhack.wasm and evilhack.js to public/.
#    f) Validate outputs by running in browser or test harness.
#    g) Document every Makefile or script change:
#         - Inline as comments in Makefile.src or build.split.sh (with before/after snippets).
#         - Optionally, keep backup copies (e.g., Makefile.src.bak) or link to patch diffs.
#         - Example patch (absolute src/*.c):
#             # Before:
#             HACKCSRC = monst.c objects.c ...
#             # After:
#             HACKCSRC = $(EVILHACK_ABSROOT)/src/monst.c $(EVILHACK_ABSROOT)/src/objects.c ...
#         - Example patch (remove install logic):
#             # Comment out lines with save/whereis/chmod in install rules.
#         - Example patch (skip dungeon in WASM):
#             # Add conditional or comment out dungeon build steps in Makefile.src.
#    h) Keep this process documented and reproducible—never rely on memory or ad-hoc fixes.
#
# 5. Persistent agent behavior:
#    - All steps automated as much as possible, following "don't ask, do" policy.
#    - All changes made only in build dirs, never in original source.
#    - Agent behavior guidelines codified in /memories/greeting.md.
#
# --- End of process summary ---

set -e

# --- STUB: Only reporting steps done so far ---
echo "[build.split.sh] Build directories created."
echo "[build.split.sh] Native copy: success."
echo "[build.split.sh] WASM copy: failed (missing or incorrect path)."
# --- End stub ---

# Exit for now
exit 0
