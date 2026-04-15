// ===== NetHack3D WASM Entry Stubs (modeled after NetHack 3.7.0 WASM) =====

// Called to initialize the game (JS side)
int hack_init(void) {
    // TODO: Initialize EvilHack game state, allocate resources, etc.
    return 0;
}

// Called to cleanly exit the game (JS side)
int hack_exit(void) {
    // TODO: Clean up EvilHack state, save if needed, free resources
    return 0;
}

// Called to advance the game by one tick/turn
int hack_tick(void) {
    // TODO: Call moveloop(0) or similar to advance game logic
    // moveloop(0); // Uncomment and implement as needed
    return 0;
}

// Called when a key is pressed (from JS)
int hack_key(int key, int mod) {
    // TODO: Inject key event into EvilHack input system
    return 0;
}

// Called when a mouse event occurs (from JS)
int hack_mouse(int x, int y, int button, int mod) {
    // TODO: Inject mouse event into EvilHack input system
    return 0;
}

// Called when the game window is resized (from JS)
int hack_resize(int w, int h) {
    // TODO: Handle window resize, update UI/layout as needed
    return 0;
}

// Called to set clipboard contents (from JS)
int hack_clipboard(const char* str) {
    // TODO: Handle clipboard integration if needed
    return 0;
}

// Called for debug commands or state (from JS)
int hack_debug(int code, int val) {
    // TODO: Implement debug hooks, logging, etc.
    return 0;
}
/* evilhack-graphics-shim.c
 * Graphics shim interface for EvilHack WASM build
 * Provides callback interface for NetHack 3D graphics system
 * 
 * NOTE: EvilHack already has mapglyph and other rendering functions.
 * This shim only provides the NetHack 3D-specific callback interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External functions from EvilHack that exist and we can call */
extern void u_init(void);
extern void init_symbols(void);
extern void decl_init(void);

/* ===== Graphics Callback Setup (NetHack 3D specific) ===== */

/**
 * Register a callback function to be called with game state updates
 * This is called once during initialization to set up the UI callback
 * NetHack 3D requires this to communicate with the game engine
 */
void shim_graphics_set_callback(const char *callback_name) {
    /* Store the callback name for later use if needed */
    if (callback_name) {
        /* In a real implementation, this would look up the callback by name
         * and store a function pointer. For now, just acknowledge it. */
    }
}

/* ===== NetHack 3D Query Functions ===== */

/**
 * Get glyph at a specific map position
 * Used during rendering to get the appropriate glyph for a location
 */
int nh3d_glyph_at(int x, int y) {
    /* This would normally query the game state for the glyph at (x, y)
     * Stub for now - actual implementation would access game memory */
    return 0;
}

/**
 * Get the top item glyph under the player
 * Used to determine what item is being picked up/interacted with
 */
int nh_top_item_glyph_under_player(void) {
    /* Stub - would normally scan the object list at player position */
    return 0;
}

/* ===== Checkpoint/Save Functions (NetHack 3D specific) ===== */

/**
 * Recover from a saved checkpoint
 * Allows resuming a game from a previously saved state
 */
int recover_savefile(void) {
    /* Stub - would check for and restore checkpoint save data */
    return 0;
}

/**
 * Resume from a checkpoint save
 * Called after recover_savefile to actually load the checkpoint
 */
int resume_checkpoint_save(void) {
    /* Stub - would load checkpoint data into game state */
    return 0;
}


// Forward declarations for EvilHack core save/restore functions
int dosave(void); // dosave takes no arguments in EvilHack
int dorestore(void); // dorestore is EvilHack's restore function
void u_init(void); // u_init returns void

// NetHack3D WASM entrypoints
int hack_save(void) {
    return dosave();
}

int hack_restore(int fd, int stuckid, int steedid) {
    // Ignore arguments for now; EvilHack's dorestore handles restore
    return dorestore();
}

/**
 * Initialize EvilHack game for WASM
 * This is the main entry point that gets called from JavaScript.
 * It initializes the game engine and returns ready for gameplay.
 */
int nh_wasm_init(void) {
    /* Call game initialization functions to force linker to include them */
    /* These are no-ops during WASM init but they pull in all dependencies */
    decl_init();     /* Initialize declarations */
    init_symbols();  /* Initialize game symbols */
    u_init();        /* Initialize player data structures */
    /* Return success */
    return 0;
}

/**
 * Main entry point - required for proper linking
 * Even though we use MODULARIZE, having main() ensures the linker
 * includes the full game engine instead of performing dead code elimination.
 */
int main(int argc, char **argv) {
    /* Initialize game */
    return nh_wasm_init();
}

/* ===== End graphics shim ===== */

