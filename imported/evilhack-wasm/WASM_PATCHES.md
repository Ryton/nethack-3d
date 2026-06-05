# EvilHack 0.9.3 WASM patches

All patches applied to the upstream `EvilHack-0.9.3` source tree to produce a
working WebAssembly build with the SHIM_GRAPHICS window provider.

The build entrypoint is `LOCAL_build.wasm.sh` (default `EVILHACK_VERSION=0.9.3`).
It expects two trees:

- `build/EvilHack-${V}_native/EvilHack-${V}/` — built with system `cc`,
  produces `util/makedefs`, `util/lev_comp`, `util/dgn_comp`, `util/dlb`,
  `util/tilemap` and runs them to generate headers + `dat/` files. These are
  copied into the wasm tree.
- `build/EvilHack-${V}_wasm/EvilHack-${V}/` — built with `emcc`, produces
  `src/evilhack.js` + `src/evilhack.wasm` via `phase3-relink.sh`.

Below: patches that **must be re-applied** to a fresh copy of EvilHack 0.9.3
when starting from scratch. Some are done by the build pipeline automatically
(category B). The rest are in-tree edits (category A) that need to be ported
manually because we don't keep a pristine vendor copy.

---

## Category A — Source patches (manual, in the 0.9.3 wasm tree)

Applied to `build/EvilHack-0.9.3_wasm/EvilHack-0.9.3/<file>` (these are NOT
applied to the native tree, only the wasm one).

### A1. `include/config.h` — enable SHIM_GRAPHICS under Emscripten

Around line 45, inside the `__EMSCRIPTEN__` guard, define:

```c
#ifdef __EMSCRIPTEN__
#define SHIM_GRAPHICS
#define DEFAULT_WINDOW_SYS "shim"
#define NOTTYGRAPHICS
#endif
```

Without this:
- `tty_procs` becomes an undefined link symbol
- makedefs refuses to build ("no windowing systems enabled")

### A2. `util/makedefs.c` — register SHIM_GRAPHICS in window_opts[]

Around line 1804, add an entry in the `window_opts[]` array:

```c
#ifdef SHIM_GRAPHICS
    { "shim", "WASM shim (JavaScript bridge)" },
#endif
```

### A3. `src/windows.c` — declare `shim_procs` and add winchoices entry

Around the other `extern struct window_procs` declarations:

```c
extern struct window_procs shim_procs;   /* defined in win/shim/winshim.c */
```

And in the `winchoices[]` array:

```c
{ &shim_procs, 0 CHAINR(0) },
```

### A4. `src/mail.c` — short-circuit `getmailstatus()` under Emscripten

Wrap the body of `getmailstatus()` (right after the opening brace) with:

```c
void
getmailstatus()
{
#ifdef __EMSCRIPTEN__
    /* WASM build: $MAIL is not meaningful in the browser and nh_getenv()
       may return a bogus pointer that crashes strlen(). Skip entirely. */
    return;
#else
    if (mailbox) {
        ...                  /* existing body */
    }
#endif /* __EMSCRIPTEN__ */
}
```

Without this, `main → getmailstatus → strlen` segfaults during startup
("index out of bounds" at `evilhack.wasm.strlen` / `getmailstatus`).

### A5. `src/dlb.c` — never bail out of `dlb_fopen()` when nhdat init fails

Two changes:

1. **Remove** the early bailout at the top of `dlb_fopen()`:

   ```c
   /* DELETE these lines: */
   if (!dlb_initialized)
       return (dlb *) 0;
   ```

2. **Gate** the archive lookup so direct-file fallback still runs:

   ```c
   /* OLD: */
   if (do_dlb_fopen(dp, name, mode))
   /* NEW: */
   if (dlb_initialized && do_dlb_fopen(dp, name, mode))
   ```

Without this, `init_dungeons()` immediately panics with
`Cannot open dungeon description - "dungeon" from "nhdat" file!` because the
wasm runtime never opens the nhdat archive (we instead embed individual files
in MEMFS via Emscripten `--embed-file`).

### A6. `win/shim/` — copy the entire directory from 0.9.2

The 0.9.3 upstream tree does NOT contain `win/shim/winshim.c`. Copy from 0.9.2:

```
cp -r build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/win/shim \
      build/EvilHack-0.9.3_wasm/EvilHack-0.9.3/win/shim
```

This file isn't the one we actually link (see B5) — but `win/shim/` is
referenced by some makefiles and useful as a reference layout.

### A7. `sys/unix/hints/linux-wasm` — restore unixmain.c + wire shim

The upstream wasm hints file in 0.9.3 OMITS `unixmain.c` from `SYSSRC`.
Without it the linker can't find `main`. Edit to:

```make
SYSSRC = \
    ../sys/share/ioctl.c \
    ../sys/unix/unixmain.c \
    ../sys/unix/unixunix.c ../sys/unix/unixres.c
SYSOBJ = ioctl.o unixmain.o unixunix.o unixres.o
```

Add `winshim_evil.o` to WINOBJ and a build rule for it:

```make
WINSRC = tile.c ../../../../evilhack/wasm-wasm/win/winshim_evil.c
WINOBJ = tile.o winshim_evil.o

winshim_evil.o: ../../../../evilhack/wasm-wasm/win/winshim_evil.c $(HACK_H)
	$(CC) $(CFLAGS) -DSHIM_GRAPHICS=1 -DDEFAULT_WINDOW_SYS='"shim"' -c -o $@ $<
```

(The shim source `evilhack/wasm-wasm/win/winshim_evil.c` is already in our
repo and gets symlinked/path-referenced from there; not a vendored EvilHack
file.)

### A8. `src/mklev.c` — defensive vault-load fallback under Emscripten

In `makerooms()`, `load_special()` historically fails silently on
`vlt-*.lev` in wasm32 (no room added, `rndvault_failed` never set →
infinite loop). Replace the previous blanket-bypass (`fnam = NULL`) with a
detect-and-fallback guard. Around line 372, inside the
`if (fnam) { ... }` branch and after `Sprintf(protofile, ...)`:

```c
#ifdef __EMSCRIPTEN__
    int prev_nroom = nroom;
    static boolean wasm_vault_silentfail_warned = FALSE;
#endif
    Sprintf(protofile, "%s", fnam);
    Strcat(protofile, LEV_EXT);
    in_mk_rndvault = TRUE;
    rndvault_failed = FALSE;
    (void) load_special(protofile);
    in_mk_rndvault = FALSE;
    if (rndvault_failed)
        return;
#ifdef __EMSCRIPTEN__
    if (nroom == prev_nroom) {
        if (!wasm_vault_silentfail_warned) {
            wasm_vault_silentfail_warned = TRUE;
            impossible(
                "WASM: vault %s loaded silently (no room, no rndvault_failed); using create_room fallback",
                protofile);
        }
        if (!create_room(-1, -1, -1, -1, -1, -1, OROOM, -1))
            return;
    }
#endif
```

Recompiled by `phase3-relink.sh` (B-section automation already in place).

### A9. `sys/unix/unixmain.c` — allow `WIZARDS=*` when `pw` is NULL

Under emscripten `getpwuid()` returns NULL, so the upstream
`if (pw && sysopt.wizards && ...)` short-circuit never even reaches the
wildcard check in `check_user_string("*")` and wizard mode is silently
denied. Around line 614, prepend a wildcard fast-path:

```c
boolean
authorize_wizard_mode()
{
    struct passwd *pw = get_unix_pw();

#ifdef __EMSCRIPTEN__
    /* WASM: getpwuid()/getpwnam() return NULL under emscripten (no /etc/passwd),
       so the upstream `pw && sysopt.wizards` short-circuit always fails — even
       when sysconf has WIZARDS=*. Honor the wildcard explicitly here. */
    if (sysopt.wizards && sysopt.wizards[0] == '*' && !sysopt.wizards[1])
        return TRUE;
#endif
    if (pw && sysopt.wizards && sysopt.wizards[0]) {
        ...
    }
    ...
}
```

Recompiled by `phase3-relink.sh` (see B10).

---

## Category B — Pipeline / build-script patches (already automated)

These are handled automatically by `LOCAL_build.wasm.sh` and
`phase3-relink.sh`. No manual work required — but listed so we know what is
happening behind the scenes.

### B1. Header symlinks (`scripts/00_prepare_build.sh`)

Symlinks `include/*.h` and `util/*.h` into `src/`, `util/`, `sys/share/`,
`sys/include`. Idempotent (skips existing symlinks even if broken).

### B2. YACC/LEX regeneration (Phase 1)

0.9.3 `.des` files use grammar features the vendored `sys/share/lev_yacc.c`
bootstrap doesn't support (goblintown.des breaks). The build re-runs
`bison -y` + `flex` on `lev_comp.y` / `lev_comp.l` before native make.

### B3. Native dat/ build, then copy → wasm tree (Phase 1b/1c)

Native tools run `lev_comp` and `makedefs` against `dat/*.des` to produce
all `.lev` files, `dungeon`, `bogusmon`, `data`, `oracles`, `options`,
`quest.dat`, `rumors`, `tribute`, `vaults.dat`, etc. These are copied
into the wasm tree because the wasm-built `makedefs` can't access the host
filesystem in its `dat/` working directory.

### B4. Preserve native host tools across phase 3 (Phase 4 prep)

Phase 3's wasm-tree make rebuilds `util/makedefs` etc. as wasm/node scripts.
Phase 4 (phase3-relink) needs to invoke them on the host. The build script
re-copies the native binaries into `util/` right before phase3-relink.

Generated headers are also bumped with `touch -d "+1 hour"` to stop the
wasm-tree make from regenerating them via the wasm makedefs (which would
fail).

### B5. WASM-side compile-time recompiles (`phase3-relink.sh`)

Several files need WASM-specific compile flags or local edits. The script
recompiles them with `emcc`:

- `winshim_evil.o` — from `evilhack/wasm-wasm/win/winshim_evil.c`
  (the real shim that defines `shim_procs`)
- `dlb.o` — `-DDLB` to enable archive lookup paths
- `allmain.o` — calls `dlb_init()` before `load_qtlist()`
- `dungeon.o` — Knox-kludge NULL-guard fix (EvilHack commit 6ce6f4157)
- `restore.o` — `dlb_init()` call added
- `version.o`, `windows.o`, `mklev.o`, `rnd.o`, `mail.o` — various
- `tile.o` — `-DUSE_TILES` so `glyph2tile[]` is emitted

### B6. WASM-side data regeneration

- `dungeon` is patched in place (5×u64 → 5×u32 header) because native
  `dgn_comp` writes 64-bit longs but the wasm runtime reads 32-bit longs.
- All `.lev` files are regenerated via a **wasm-built** `lev_comp-wasm.js`
  so internal `long` offsets use the 4-byte wasm ABI.
- `quest.dat` is regenerated via a wasm-built `makedefs` for the same
  reason.
- `vaults.dat` is extracted from the **native** nhdat (lev_comp doesn't
  produce it standalone) if not already present.
- All embedded data files are written to `wasm-data/` and consumed via
  Emscripten `--embed-file wasm-data@/`.

### B7. Shim file restoration (`scripts/wasm/evilhack-wasm-shims.c`)

If accidentally deleted, restore via:

```
git show 01c559a:scripts/wasm/evilhack-wasm-shims.c > scripts/wasm/evilhack-wasm-shims.c
```

The hints file (A7) expects it at
`../../../../scripts/wasm/evilhack-wasm-shims.c` relative to `src/`. A
symlink at `imported/evilhack-wasm/scripts/wasm/evilhack-wasm-shims.c`
points back to `scripts/wasm/evilhack-wasm-shims.c` for convenience.

### B8. Problematic `.des` files (currently commented out)

`castle.des` and `gehennom.des` are temporarily commented out of the native
`dat/Makefile` `spec_levs` target by the build script:

```
PROBLEM_DES_LIST=( castle gehennom )
```

Reason: WASM-side `lev_comp` previously choked on them. To re-test removal,
delete the entries from `PROBLEM_DES_LIST` in `LOCAL_build.wasm.sh` and
rebuild. (The wasm-built lev_comp in B6 may now be capable of compiling
them — confirm by running phase 4 and checking `.lev` count.)

### B9. Skip `make dlb` in native tree

`phase3-relink.sh` rebuilds `nhdat` in the wasm tree with explicit file
lists, so the native `dat/Makefile`'s `make dlb` target is not invoked
(it would fail on the `castle-?.lev` glob because of B8).

### B10. `sysconf` WIZARDS=*, larger stack, unixmain.o recompile

`phase3-relink.sh` automatically:

- Rewrites `wasm-data/sysconf` to `WIZARDS=*` (so `playmode:debug` from
  the startup-init UI is accepted; pairs with A9).
- Links with `-sSTACK_SIZE=1048576` (default 64 KB overflows in
  `parseoptions()`'s comma-recursion on long NETHACKOPTIONS strings,
  especially when the `playmode:debug` token is added).
- Recompiles `sys/unix/unixmain.c → src/unixmain.o` so the A9 patch lands
  in the link.

---

## Quick re-bootstrap recipe

If starting from a fresh 0.9.3 source tree:

1. Drop sources into `build/EvilHack-0.9.3_wasm/EvilHack-0.9.3/`.
2. Apply A1 through A7 in order (about 20 lines of edits total).
3. Run `EVILHACK_VERSION=0.9.3 bash imported/evilhack-wasm/LOCAL_build.wasm.sh`.
4. Expect `public/evilhack.js` (~226K) + `public/evilhack.wasm` (~11M).
5. Smoke-test in browser; verify init reaches the name-prompt screen.

If the build breaks somewhere, the iteration order that worked the first
time was A1 → A7 → A2 → A6 → A3 → A5 → A4 (each surfaced its blocker only
after the previous one was fixed).
