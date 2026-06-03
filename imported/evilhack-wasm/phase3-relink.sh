#!/usr/bin/env bash
# phase3-relink.sh
# Phase 3: Re-link existing EvilHack WASM object files with correct emscripten flags.
#
# PREREQUISITES (must be done first — see LOCAL_build.wasm.sh for phases 1+2):
#   - 119+ .o files compiled in EH_BUILD/src/ (by LOCAL_build.wasm.sh phase 1)
#   - winshim_evil.o compiled (see step below)
#   - EH_BUILD/dat/nhdat built (by LOCAL_build.wasm.sh or `make dlb` equivalent)
#   - EH_BUILD/wasm-data/ populated (see step below)
#
# USAGE:
#   source ../../emsdk/emsdk_env.sh   # activate emcc first
#   ./phase3-relink.sh
#
# KEY LESSON: Never override LFLAGS on the make CLI — it silences all LFLAGS+=
# in the hints file. Always call emcc directly for the link step.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
# Default to EvilHack 0.9.3 (shipped to public/). Override with
# EVILHACK_VERSION=0.9.2 for the rollback build.
EVILHACK_VERSION="${EVILHACK_VERSION:-0.9.3}"
EH_BUILD="$SCRIPT_DIR/build/EvilHack-${EVILHACK_VERSION}_wasm/EvilHack-${EVILHACK_VERSION}"
echo "Building EvilHack ${EVILHACK_VERSION} from $EH_BUILD"
NH3D_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
WINSHIM_SRC="$SCRIPT_DIR/evilhack/wasm-wasm/win/winshim_evil.c"
OUTPUT_JS="$EH_BUILD/src/evilhack.js"
PUBLIC_JS="$NH3D_ROOT/public/evilhack.js"
PUBLIC_WASM="$NH3D_ROOT/public/evilhack.wasm"

# --- Verify emcc ---
if ! command -v emcc >/dev/null 2>&1; then
    echo "ERROR: emcc not found. Run: source emsdk/emsdk_env.sh"
    exit 1
fi
echo "Using: $(emcc --version | head -1)"

# --- Step 1: Compile winshim_evil.o (always recompile since source may change) ---
echo "--- Compiling winshim_evil.o ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DSHIM_GRAPHICS=1 \
    -DDEFAULT_WINDOW_SYS='"shim"' \
    -c "$WINSHIM_SRC" \
    -o "$EH_BUILD/src/winshim_evil.o"
echo "  done."

# --- Step 1b: Recompile windows.o with SHIM_GRAPHICS only (always) ---
# CRITICAL: windows.c was patched to add shim_procs to winchoices[].
# Must NOT include -DTTY_GRAPHICS — that pulls in tty_procs which is an
# undefined symbol at WASM link time. DEFAULT_WINDOW_SYS must be "shim"
# so unixmain.c calls choose_windows("shim") and finds shim_procs.
echo "--- Recompiling dlb.o with -DDLB (enables dlb_fopen/nhdat archive support) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -c "$EH_BUILD/src/dlb.c" \
    -o "$EH_BUILD/src/dlb.o"
echo "  done."

echo "--- Recompiling allmain.o (dlb_init call added before load_qtlist) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -DSHIM_GRAPHICS=1 \
    -c "$EH_BUILD/src/allmain.c" \
    -o "$EH_BUILD/src/allmain.o"
echo "  done."

echo "--- Recompiling dungeon.o (Knox kludge NULL-guard fix from EvilHack 0.9.3 commit 6ce6f4157) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -DSHIM_GRAPHICS=1 \
    -c "$EH_BUILD/src/dungeon.c" \
    -o "$EH_BUILD/src/dungeon.o"
echo "  done."

echo "--- Recompiling restore.o (dlb_init call added before load_qtlist) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -DSHIM_GRAPHICS=1 \
    -c "$EH_BUILD/src/restore.c" \
    -o "$EH_BUILD/src/restore.o"
echo "  done."

echo "--- Recompiling version.o ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -DSHIM_GRAPHICS=1 \
    -c "$EH_BUILD/src/version.c" \
    -o "$EH_BUILD/src/version.o"
echo "  done."

echo "--- Recompiling mail.o (WASM: stub getmailstatus to avoid NULL strlen crash) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -DSHIM_GRAPHICS=1 \
    -c "$EH_BUILD/src/mail.c" \
    -o "$EH_BUILD/src/mail.o"
echo "  done."

echo "--- Recompiling mklev.o (WASM: makerooms bailout diagnostic) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -DSHIM_GRAPHICS=1 \
    -c "$EH_BUILD/src/mklev.c" \
    -o "$EH_BUILD/src/mklev.o"
echo "  done."

echo "--- Recompiling rnd.o (WASM: rn2(0) diagnostic) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -DSHIM_GRAPHICS=1 \
    -c "$EH_BUILD/src/rnd.c" \
    -o "$EH_BUILD/src/rnd.o"
echo "  done."

echo "--- Recompiling windows.o (SHIM_GRAPHICS only, no TTY) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DSHIM_GRAPHICS=1 \
    -DDLB \
    -DDEFAULT_WINDOW_SYS='"shim"' \
    -c "$EH_BUILD/src/windows.c" \
    -o "$EH_BUILD/src/windows.o"
echo "  done."

# --- Step 2: Build native tools (dgn_comp, dlb_tool) and dungeon data ---
# These are native x86 tools used to compile the dungeon layout and pack nhdat.
#
# KEY LESSONS:
#   - The pre-built dlb binary has no DLBLIB support (compiled without -DDLB) — useless.
#     Must compile dlb_tool from source with -DDLB.
#   - The pre-built dgn_comp binary was stale (pre-RNDLEVEL grammar). Must regenerate
#     dgn_lex.c and dgn_yacc.c from .l/.y with flex/bison, then update include/dgn_comp.h
#     to match bison's token numbers (bison reserves 257 for YYUNDEF, shifting all +1).
#   - src/*.o are WASM format — cannot link into native tools. alloc.c must be
#     compiled natively with gcc separately.

UTIL="$EH_BUILD/util"
DAT="$EH_BUILD/dat"

echo "--- Building native dlb_tool ---"
(cd "$UTIL" && \
    gcc -DDLB -c -o dlb_main.o dlb_main.c -I../include && \
    gcc -DDLB -c -o dlb_obj.o ../src/dlb.c -I../include && \
    gcc -c -o alloc_native.o ../src/alloc.c -I../include && \
    gcc -c -o panic.o panic.c -I../include && \
    gcc -o dlb_tool dlb_main.o dlb_obj.o alloc_native.o panic.o)
echo "  dlb_tool: $(wc -c < "$UTIL/dlb_tool") bytes"

echo "--- Building native dgn_comp (flex/bison from sources) ---"
# bison reserves token 257 for YYUNDEF, shifting all tokens +1 vs old yacc.
# Patch include/dgn_comp.h to match bison's token numbers (idempotent sed).
sed -i \
    -e 's/^#define INTEGER 257$/#define INTEGER 258/' \
    -e 's/^#define A_DUNGEON 258$/#define A_DUNGEON 259/' \
    -e 's/^#define BRANCH 259$/#define BRANCH 260/' \
    -e 's/^#define CHBRANCH 260$/#define CHBRANCH 261/' \
    -e 's/^#define LEVEL 261$/#define LEVEL 262/' \
    -e 's/^#define RNDLEVEL 262$/#define RNDLEVEL 263/' \
    -e 's/^#define CHLEVEL 263$/#define CHLEVEL 264/' \
    -e 's/^#define RNDCHLEVEL 264$/#define RNDCHLEVEL 265/' \
    -e 's/^#define UP_OR_DOWN 265$/#define UP_OR_DOWN 266/' \
    -e 's/^#define PROTOFILE 266$/#define PROTOFILE 267/' \
    -e 's/^#define DESCRIPTION 267$/#define DESCRIPTION 268/' \
    -e 's/^#define DESCRIPTOR 268$/#define DESCRIPTOR 269/' \
    -e 's/^#define LEVELDESC 269$/#define LEVELDESC 270/' \
    -e 's/^#define ALIGNMENT 270$/#define ALIGNMENT 271/' \
    -e 's/^#define LEVALIGN 271$/#define LEVALIGN 272/' \
    -e 's/^#define ENTRY 272$/#define ENTRY 273/' \
    -e 's/^#define STAIR 273$/#define STAIR 274/' \
    -e 's/^#define NO_UP 274$/#define NO_UP 275/' \
    -e 's/^#define NO_DOWN 275$/#define NO_DOWN 276/' \
    -e 's/^#define PORTAL 276$/#define PORTAL 277/' \
    -e 's/^#define STRING 277$/#define STRING 278/' \
    "$EH_BUILD/include/dgn_comp.h"
(cd "$UTIL" && \
    flex -o dgn_lex.c dgn_comp.l && \
    bison -d -o dgn_yacc.c dgn_comp.y && \
    gcc -c -o dgn_lex.o dgn_lex.c -I../include && \
    gcc -c -o dgn_yacc.o dgn_yacc.c -I../include && \
    gcc -c -o dgn_main.o dgn_main.c -I../include && \
    gcc -o dgn_comp dgn_yacc.o dgn_lex.o dgn_main.o alloc_native.o panic.o)
echo "  dgn_comp: $(wc -c < "$UTIL/dgn_comp") bytes"

echo "--- Compiling dungeon layout ---"
(cd "$DAT" && \
    "$UTIL/makedefs" -e && \
    rm -f dungeon && \
    "$UTIL/dgn_comp" dungeon.pdf)
echo "  dungeon: $(wc -c < "$DAT/dungeon") bytes"

# Patch dungeon header: native dgn_comp (64-bit) writes version_info as 5×uint64 (40 bytes).
# WASM binary (wasm32 ABI) reads version_info as 5×uint32 (20 bytes) — unsigned long is 32-bit.
# Keep the lower 32 bits of each field so WASM's check_version() sees the correct values.
echo "--- Patching dungeon header (64-bit → 32-bit for WASM) ---"
python3 -c "
import struct, sys
p = '${DAT}/dungeon'
d = open(p, 'rb').read()
if len(d) < 40: sys.exit('dungeon too small: ' + str(len(d)))
f5 = struct.unpack_from('<5Q', d, 0)
d2 = struct.pack('<5I', *(v & 0xFFFFFFFF for v in f5)) + d[40:]
open(p, 'wb').write(d2)
names = ['incarnation', 'feature_set', 'entity_count', 'struct_sizes1', 'struct_sizes2']
for n, v in zip(names, f5): print(f'  {n} = {hex(v & 0xFFFFFFFF)}')
print(f'  patched: {len(d)} -> {len(d2)} bytes')
"
echo "  dungeon patched: $(wc -c < "$DAT/dungeon") bytes"

# Regenerate quest.dat using a WASM-built makedefs so that the embedded
# `long` offsets inside the binary match the WASM runtime's 4-byte `long`.
# (Patching headers is not enough — quest.dat has many embedded long fields
# inside the struct qtmsg layout, not just the 5-field version header.)
echo "--- Building wasm-makedefs (runs under node) ---"
(cd "$UTIL" && \
    emcc -O2 \
        -DMAKEDEFS_C -DUNIX \
        -I../include \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s NODERAWFS=1 \
        -s EXIT_RUNTIME=1 \
        makedefs.c ../src/monst.c ../src/objects.c \
        -o makedefs-wasm.js)
echo "  wasm-makedefs: $(wc -c < "$UTIL/makedefs-wasm.js") bytes JS, $(wc -c < "$UTIL/makedefs-wasm.wasm") bytes WASM"

echo "--- Regenerating quest.dat via wasm-makedefs ---"
(cd "$DAT" && node "$UTIL/makedefs-wasm.js" -q)
echo "  quest.dat: $(wc -c < "$DAT/quest.dat") bytes"

# Regenerate ALL .lev files using a WASM-built lev_comp so that the embedded
# `long` fields throughout each level file (not just the version header) use
# the WASM ABI's 4-byte long. Otherwise load_special() reads garbage room
# coordinates → no rooms added → makerooms() loops forever, identical hang
# signature to the original 64-bit-header issue but persisting even after
# header-only patching.
echo "--- Building wasm-lev_comp (runs under node) ---"
(cd "$UTIL" && \
    bison -d -o lev_yacc.c lev_comp.y && \
    flex -o lev_lex.c lev_comp.l && \
    cp lev_yacc.h ../include/lev_comp.h && \
    emcc -O2 \
        -DUNIX \
        -I../include \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s NODERAWFS=1 \
        -s EXIT_RUNTIME=1 \
        -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
        lev_yacc.c lev_lex.c lev_main.c \
        ../src/alloc.c panic.c \
        ../src/drawing.c ../src/decl.c ../src/monst.c ../src/objects.c \
        -o lev_comp-wasm.js)
echo "  lev_comp-wasm: $(wc -c < "$UTIL/lev_comp-wasm.js") bytes JS, $(wc -c < "$UTIL/lev_comp-wasm.wasm") bytes WASM"

echo "--- Regenerating all .lev files via wasm-lev_comp ---"
(cd "$DAT" && \
    rm -f *.lev vaults.dat && \
    for f in *.des; do
        node "$UTIL/lev_comp-wasm.js" "$f" >/dev/null 2>&1 || echo "  WARN: failed on $f"
    done)
echo "  .lev files: $(ls "$DAT"/*.lev 2>/dev/null | wc -l) regenerated, vaults.dat: $(wc -c < "$DAT/vaults.dat" 2>/dev/null || echo MISSING) bytes"

# Header patching is no longer needed for .lev or vaults.dat — wasm-lev_comp
# above produces them with the correct 5×u32 = 20-byte header and 4-byte longs
# throughout. `dungeon` is patched in-place above (still produced by native
# dgn_comp). `quest.dat` is regenerated by wasm-makedefs above (no version
# header). Re-running the 5×u64→5×u32 loop on already-correct 20-byte-headered
# files would CORRUPT them (the heuristic can't distinguish a real 20-byte
# header from a 40-byte header whose high halves happen to be non-zero).

# --- Step 2b: Build nhdat and populate wasm-data ---
# Always rebuild nhdat to pick up the freshly compiled dungeon file.
# vaults.dat is not in dat/ by default — extract it from native nhdat if needed.
NATIVE="$EH_BUILD/EvilHack-${EVILHACK_VERSION}_native"
if [ ! -f "$DAT/vaults.dat" ] && [ -f "$NATIVE/dat/nhdat" ]; then
    echo "--- Extracting vaults.dat from native nhdat ---"
    (cd "$DAT" && "$UTIL/dlb_tool" xvf "$NATIVE/dat/nhdat" vaults.dat)
fi

echo "--- Building nhdat game data archive ---"
(cd "$DAT" && LC_ALL=C "$UTIL/dlb_tool" cf nhdat \
    help hh cmdhelp keyhelp history opthelp wizhelp \
    dungeon \
    tribute \
    bigrm-*.lev castle-?.lev hellfill.lev nymph.lev forest.lev \
    knox-?.lev medusa-?.lev minend-?.lev minefill.lev \
    vlt-*.lev hdgn.lev hella-?.lev hellb-?.lev hellc-?.lev \
    minetn-?.lev oracle-?.lev orcus.lev sanctum.lev soko?-?.lev \
    goblintown*.lev icequeen-?.lev vecna-?.lev purgatory-?.lev \
    tower?.lev valley.lev wizard?.lev wizportal.lev astral.lev \
    air.lev earth.lev fire.lev water.lev \
    ???-goal.lev ???-fil?.lev ???-loca.lev ???-strt.lev \
    bogusmon data engrave epitaph oracles options quest.dat rumors vaults.dat \
    2>&1)
echo "  nhdat: $(wc -c < "$DAT/nhdat") bytes"

mkdir -p "$EH_BUILD/wasm-data"
rm -f "$EH_BUILD/wasm-data/dummy.txt"
cp "$DAT/nhdat" "$EH_BUILD/wasm-data/nhdat"
# Embed all text data files standalone so dlb_fopen falls back to direct fopen
# if nhdat open fails (DLB init failure). Covers quest.dat, help texts, etc.
for f in dungeon quest.dat data bogusmon engrave epitaph oracles options \
          rumors tribute help hh cmdhelp keyhelp history opthelp wizhelp \
          vaults.dat; do
    [ -f "$DAT/$f" ] && cp "$DAT/$f" "$EH_BUILD/wasm-data/$f"
done
touch "$EH_BUILD/wasm-data/perm" "$EH_BUILD/wasm-data/record" \
      "$EH_BUILD/wasm-data/logfile" "$EH_BUILD/wasm-data/paniclog"
echo "  wasm-data populated."

# Always refresh sysconf and serverseed (small files, no cost)
# sysconf: SYSCF_FILE="sysconf" — game reads it at startup from HACKDIR (/)
# serverseed: integer file referenced by SERVERSEED_FILE=serverseed in sysconf
cp "$EH_BUILD/sys/unix/sysconf" "$EH_BUILD/wasm-data/sysconf"
echo "100" > "$EH_BUILD/wasm-data/serverseed"

# --- Step 3: Phase 3 re-link ---
# Compile tile.o — provides glyph2tile[] array referenced by glyph_to_tile() in winshim_evil.c
# (USE_TILES is required so tile.c emits glyph2tile rather than empty stubs)
echo "--- Compiling tile.o (provides glyph2tile[]) ---"
emcc -O3 \
    -I"$EH_BUILD/include" \
    -DDLB \
    -c "$EH_BUILD/src/tile.c" \
    -o "$EH_BUILD/src/tile.o"
echo "  done."

# Include evilhack-wasm-shims.o — provides tty_procs stub + other shim symbols
# (windows.c is compiled with TTY_GRAPHICS via config.h, so it references
# tty_procs even with our SHIM_GRAPHICS-only recompile).
echo "--- Phase 3: Linking $(ls "$EH_BUILD/src"/*.o | wc -l) object files ---"
OBJS=$(ls "$EH_BUILD/src"/*.o | tr '\n' ' ')

emcc $OBJS \
    -O2 \
    -g \
    --profiling-funcs \
    -s ASSERTIONS=2 \
    -s STACK_OVERFLOW_CHECK=2 \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -s EXPORT_NAME=Module \
    -s ASYNCIFY=1 \
    -s ASYNCIFY_ADVISE=1 \
    -s 'ASYNCIFY_IMPORTS=["local_callback"]' \
    -s ASYNCIFY_STACK_SIZE=65536 \
    -s ALLOW_TABLE_GROWTH=1 \
    -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
    -s 'EXPORTED_FUNCTIONS=["_main","_malloc","_free","_shim_graphics_set_callback","_nh3d_glyph_at","_nh_top_item_glyph_under_player","_recover_savefile","_resume_checkpoint_save","_hack_save","_hack_restore","_nh_wasm_init","_mapglyph","_glyph_to_tile"]' \
    -s 'EXPORTED_RUNTIME_METHODS=["cwrap","ccall","addFunction","removeFunction","UTF8ToString","stringToUTF8","getValue","setValue","ENV","FS","IDBFS","HEAP8","HEAPU8","HEAP16","HEAPU16","HEAP32","HEAPU32","HEAPF32","HEAPF64","noExitRuntime"]' \
    -lidbfs.js \
    --embed-file "$EH_BUILD/wasm-data@/" \
    -o "$OUTPUT_JS"

echo "  Link complete."
echo "  JS:   $(wc -c < "$OUTPUT_JS") bytes"
echo "  WASM: $(wc -c < "${OUTPUT_JS%.js}.wasm") bytes"

# --- Step 4: Copy to public/ ---
echo "--- Copying to public/ ---"
cp "$OUTPUT_JS" "$PUBLIC_JS"
cp "${OUTPUT_JS%.js}.wasm" "$PUBLIC_WASM"

echo "=== Done ==="
echo "  public/evilhack.js:   $(wc -c < "$PUBLIC_JS") bytes"
echo "  public/evilhack.wasm: $(wc -c < "$PUBLIC_WASM") bytes"
echo ""
echo "Verify exports:"
grep -o '"_[a-zA-Z0-9_]*"' "$PUBLIC_JS" | sort -u
