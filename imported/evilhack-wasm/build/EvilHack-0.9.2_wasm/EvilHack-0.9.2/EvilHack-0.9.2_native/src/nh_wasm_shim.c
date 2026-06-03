
// nh_wasm_shim.c - EvilHack WASM window port shim (callback-based, like Slash'EM)
#include "hack.h"
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


// Always declare local_callback before macro usage
#ifdef __EMSCRIPTEN__
EM_JS(void, local_callback,
	  (const char *cb_name, const char *shim_name, void *ret_ptr,
	   const char *fmt_str, void *args), {
	// TODO: Port full JS body from Slash'EM winshim.c if needed
});
#else
// Fallback for non-Emscripten builds
static void local_callback(const char *cb_name, const char *shim_name, void *ret_ptr,
	   const char *fmt_str, void *args) {
	(void)cb_name; (void)shim_name; (void)ret_ptr; (void)fmt_str; (void)args;
}
#endif

#undef SHIM_DEBUG

#ifdef SHIM_DEBUG
#define debugf printf
#else
#define debugf(...)
#endif

#ifdef __EMSCRIPTEN__
static char *shim_callback_name = (char *) 0;
EMSCRIPTEN_KEEPALIVE void shim_graphics_set_callback(char *cb_name) {
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
typedef void (*shim_callback_t)(const char *name, void *ret_ptr, const char *fmt, ...);
static shim_callback_t shim_graphics_callback = (shim_callback_t) 0;
void shim_graphics_set_callback(shim_callback_t cb) {
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


// Window port callback stubs (expand as needed)
VDECLCB(shim_player_selection, (void), "v")
VDECLCB(shim_askname, (void), "v")
VDECLCB(shim_get_nh_event, (void), "v")
VDECLCB(shim_exit_nhwindows, (const char *str), "vs", P2V str)
VDECLCB(shim_suspend_nhwindows, (const char *str), "vs", P2V str)
VDECLCB(shim_resume_nhwindows, (void), "v")
DECLCB(int, shim_create_nhwindow, (int type), "ii", A2P type)
VDECLCB(shim_clear_nhwindow, (int window), "vi", A2P window)
VDECLCB(shim_display_nhwindow, (int window, int blocking), "vib", A2P window, A2P blocking)
VDECLCB(shim_destroy_nhwindow, (int window), "vi", A2P window)
VDECLCB(shim_curs, (int a, int x, int y), "viii", A2P a, A2P x, A2P y)
VDECLCB(shim_putstr, (int w, int attr, const char *str), "viis", A2P w, A2P attr, P2V str)
VDECLCB(shim_display_file, (const char *name, int complain), "vsb", P2V name, A2P complain)
VDECLCB(shim_start_menu, (int window), "vi", A2P window)
VDECLCB(shim_add_menu, (int window, int glyph, void *identifier, char ch, char gch, int attr, const char *str, int preselected), "viipccisb", A2P window, A2P glyph, P2V identifier, A2P ch, A2P gch, A2P attr, P2V str, A2P preselected)
VDECLCB(shim_end_menu, (int window, const char *prompt), "vis", A2P window, P2V prompt)
DECLCB(int, shim_select_menu, (int window, int how, void **menu_list), "iiip", A2P window, A2P how, P2V menu_list)
DECLCB(char, shim_message_menu, (char let, int how, const char *mesg), "ciis", A2P let, A2P how, P2V mesg)
VDECLCB(shim_update_inventory, (void), "v")
VDECLCB(shim_mark_synch, (void), "v")
VDECLCB(shim_wait_synch, (void), "v")
VDECLCB(shim_print_glyph, (int w, int x, int y, int glyph), "viiii", A2P w, A2P x, A2P y, A2P glyph)
VDECLCB(shim_raw_print, (const char *str), "vs", P2V str)
VDECLCB(shim_raw_print_bold, (const char *str), "vs", P2V str)
DECLCB(int, shim_nhgetch, (void), "i")
DECLCB(int, shim_nh_poskey, (int *x, int *y, int *mod), "ippp", P2V x, P2V y, P2V mod)
VDECLCB(shim_nhbell, (void), "v")
DECLCB(int, shim_doprev_message, (void), "i")
DECLCB(char, shim_yn_function, (const char *query, const char *resp, char def), "cssc", P2V query, P2V resp, A2P def)
VDECLCB(shim_getlin, (const char *query, char *bufp), "vsp", P2V query, P2V bufp)
DECLCB(int, shim_get_ext_cmd, (void), "i")
VDECLCB(shim_number_pad, (int state), "vi", A2P state)
VDECLCB(shim_delay_output, (void), "v")
VDECLCB(shim_status_init, (void), "v")
VDECLCB(shim_status_enablefield, (int fieldidx, const char *nm, const char *fmt, int enable), "vippb", A2P fieldidx, P2V nm, P2V fmt, A2P enable)
VDECLCB(shim_status_update, (int fldidx, void *ptr, int chg, int percent, int color, unsigned long *colormasks), "vipiiip", A2P fldidx, P2V ptr, A2P chg, A2P percent, A2P color, P2V colormasks)
VDECLCB(shim_start_screen, (void), "v")
VDECLCB(shim_end_screen, (void), "v")
VDECLCB(shim_outrip, (int tmpwin, int how), "vii", A2P tmpwin, A2P how)
VDECLCB(shim_preference_update, (const char *pref), "vs", P2V pref)
