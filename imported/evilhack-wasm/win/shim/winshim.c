/* Slash'EM winshim.c
 * Shim window port for WASM builds. All window callbacks are forwarded
 * through a single JavaScript function name via Asyncify.
 */

#include "hack.h"
#include <string.h>

#ifdef SHIM_GRAPHICS
#include <stdarg.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#undef SHIM_DEBUG

#ifdef SHIM_DEBUG
#define debugf printf
#else
#define debugf(...)
#endif

#define NH3D_TRACKED_MONSTER_NONE (-1)
#define NH3D_TRACKED_PLAYER_ID 0
#define NH3D_MONSTER_ATTACK_TRACKING_MAX 128
#define NH3D_MONSTER_KILLER_STACK_MAX 8

struct nh3d_recent_attack {
	unsigned attacker_id;
	int target_id;
	long turn;
};

static struct nh3d_recent_attack
	nh3d_recent_attacks[NH3D_MONSTER_ATTACK_TRACKING_MAX];
static int nh3d_monster_killer_stack[NH3D_MONSTER_KILLER_STACK_MAX];
static int nh3d_monster_killer_depth = 0;

static boolean nh3d_monster_has_trackable_glyph(struct monst *);
static int nh3d_monster_id_from_tile(XCHAR_P, XCHAR_P, int);
static int nh3d_get_recent_attack_target_id(int);
static void nh3d_record_recent_attack(unsigned, int);
static void nh3d_queue_shim_notification(const char *, int, int, int, int);

void nh3d_note_monster_attack(struct monst *, struct monst *);
void nh3d_push_monster_killer(struct monst *);
void nh3d_pop_monster_killer(void);
int nh3d_get_current_monster_killer_id(void);
void nh3d_emit_monster_killed(int, int, int, int);

enum shim_status_fields {
	SHIM_BL_CHARACTERISTICS = -3,
	SHIM_BL_RESET = -2,
	SHIM_BL_FLUSH = -1,
	SHIM_BL_TITLE = 0,
	SHIM_BL_STR,
	SHIM_BL_DX,
	SHIM_BL_CO,
	SHIM_BL_IN,
	SHIM_BL_WI,
	SHIM_BL_CH,
	SHIM_BL_ALIGN,
	SHIM_BL_SCORE,
	SHIM_BL_CAP,
	SHIM_BL_GOLD,
	SHIM_BL_ENE,
	SHIM_BL_ENEMAX,
	SHIM_BL_XP,
	SHIM_BL_AC,
	SHIM_BL_HD,
	SHIM_BL_TIME,
	SHIM_BL_HUNGER,
	SHIM_BL_HP,
	SHIM_BL_HPMAX,
	SHIM_BL_LEVELDESC,
	SHIM_BL_EXP,
	SHIM_BL_CONDITION,
	SHIM_MAXBLSTATS
};

#define SHIM_RAW_STAT_HELD 0x00000100UL

static void FDECL(shim_status_raw_bridge, (int, int, const char **));
static void NDECL(shim_status_bridge_reconfig);
static void FDECL(shim_status_bridge_emit_string, (int, const char *));
static void FDECL(shim_status_bridge_emit_mask, (unsigned long));
static void NDECL(shim_status_bridge_flush);

#ifdef __EMSCRIPTEN__
static char *shim_callback_name = (char *) 0;
void shim_graphics_set_callback(char *cb_name);
void local_callback(const char *cb_name, const char *shim_name,
					void *ret_ptr, const char *fmt_str, void *args);

void
shim_graphics_set_callback(char *cb_name)
{
	if (shim_callback_name != 0)
		free(shim_callback_name);
	if (cb_name && *cb_name)
		shim_callback_name = strdup(cb_name);
	else
		shim_callback_name = (char *) 0;
}

#define A2P &
#define P2V (void *)
#define DECLCB(ret_type, name, fn_args, fmt, ...) \
ret_type name fn_args; \
ret_type name fn_args { \
	void *args[] = { __VA_ARGS__ }; \
	ret_type ret = (ret_type) 0; \
	debugf("SHIM GRAPHICS: " #name "\n"); \
	if (!shim_callback_name) return ret; \
	local_callback(shim_callback_name, #name, (void *) &ret, fmt, args); \
	return ret; \
}

#define VDECLCB(name, fn_args, fmt, ...) \
void name fn_args; \
void name fn_args { \
	void *args[] = { __VA_ARGS__ }; \
	debugf("SHIM GRAPHICS: " #name "\n"); \
	if (!shim_callback_name) return; \
	local_callback(shim_callback_name, #name, (void *) 0, fmt, args); \
}

#else
typedef void (*shim_callback_t)(const char *name, void *ret_ptr,
								const char *fmt, ...);
static shim_callback_t shim_graphics_callback = (shim_callback_t) 0;
void shim_graphics_set_callback(shim_callback_t cb);

void
shim_graphics_set_callback(shim_callback_t cb)
{
	shim_graphics_callback = cb;
}

#define A2P
#define P2V
#define DECLCB(ret_type, name, fn_args, fmt, ...) \
ret_type name fn_args; \
ret_type name fn_args { \
	ret_type ret = (ret_type) 0; \
	debugf("SHIM GRAPHICS: " #name "\n"); \
	if (!shim_graphics_callback) return ret; \
	shim_graphics_callback(#name, (void *) &ret, fmt, ## __VA_ARGS__); \
	return ret; \
}

#define VDECLCB(name, fn_args, fmt, ...) \
void name fn_args; \
void name fn_args { \
	debugf("SHIM GRAPHICS: " #name "\n"); \
	if (!shim_graphics_callback) return; \
	shim_graphics_callback(#name, (void *) 0, fmt, ## __VA_ARGS__); \
}
#endif

// ...rest of winshim.c code from SlashEM...