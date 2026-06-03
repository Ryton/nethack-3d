/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lev_comp.y"

/* NetHack 3.6  lev_comp.y	$NHDT-Date: 1543371691 2018/11/28 02:21:31 $  $NHDT-Branch: NetHack-3.6.2-beta01 $:$NHDT-Revision: 1.22 $ */
/*      Copyright (c) 1989 by Jean-Christophe Collet */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * This file contains the Level Compiler code
 * It may handle special mazes & special room-levels
 */

/* In case we're using bison in AIX.  This definition must be
 * placed before any other C-language construct in the file
 * excluding comments and preprocessor directives (thanks IBM
 * for this wonderful feature...).
 *
 * Note: some cpps barf on this 'undefined control' (#pragma).
 * Addition of the leading space seems to prevent barfage for now,
 * and AIX will still see the directive.
 */
#ifdef _AIX
 #pragma alloca         /* keep leading space! */
#endif

#define SPEC_LEV    /* for USE_OLDARGS (sp_lev.h) */
#include "hack.h"
#include "sp_lev.h"

#define ERR             (-1)
/* many types of things are put in chars for transference to NetHack.
 * since some systems will use signed chars, limit everybody to the
 * same number for portability.
 */
#define MAX_OF_TYPE     128

#define MAX_NESTED_IFS   20
#define MAX_SWITCH_CASES 20

#define New(type) \
        (type *) memset((genericptr_t) alloc(sizeof (type)), 0, sizeof (type))
#define NewTab(type, size)      (type **) alloc(sizeof (type *) * size)
#define Free(ptr)               free((genericptr_t) ptr)

extern void VDECL(lc_error, (const char *, ...));
extern void VDECL(lc_warning, (const char *, ...));
extern void FDECL(yyerror, (const char *));
extern void FDECL(yywarning, (const char *));
extern int NDECL(yylex);
int NDECL(yyparse);

extern int FDECL(get_floor_type, (CHAR_P));
extern int FDECL(get_room_type, (char *));
extern int FDECL(get_trap_type, (char *));
extern int FDECL(get_monster_id, (char *,CHAR_P));
extern int FDECL(get_object_id, (char *,CHAR_P));
extern boolean FDECL(check_monster_char, (CHAR_P));
extern boolean FDECL(check_object_char, (CHAR_P));
extern char FDECL(what_map_char, (CHAR_P));
extern void FDECL(scan_map, (char *, sp_lev *));
extern void FDECL(add_opcode, (sp_lev *, int, genericptr_t));
extern genericptr_t FDECL(get_last_opcode_data1, (sp_lev *, int));
extern genericptr_t FDECL(get_last_opcode_data2, (sp_lev *, int, int));
extern boolean FDECL(check_subrooms, (sp_lev *));
extern boolean FDECL(write_level_file, (char *,sp_lev *));
extern struct opvar *FDECL(set_opvar_int, (struct opvar *, long));
extern void VDECL(add_opvars, (sp_lev *, const char *, ...));
extern void FDECL(start_level_def, (sp_lev * *, char *));

extern struct lc_funcdefs *FDECL(funcdef_new, (long,char *));
extern void FDECL(funcdef_free_all, (struct lc_funcdefs *));
extern struct lc_funcdefs *FDECL(funcdef_defined, (struct lc_funcdefs *,
                                                   char *, int));
extern char *FDECL(funcdef_paramtypes, (struct lc_funcdefs *));
extern char *FDECL(decode_parm_str, (char *));

extern struct lc_vardefs *FDECL(vardef_new, (long,char *));
extern void FDECL(vardef_free_all, (struct lc_vardefs *));
extern struct lc_vardefs *FDECL(vardef_defined, (struct lc_vardefs *,
                                                 char *, int));

extern void NDECL(break_stmt_start);
extern void FDECL(break_stmt_end, (sp_lev *));
extern void FDECL(break_stmt_new, (sp_lev *, long));

extern void FDECL(splev_add_from, (sp_lev *, sp_lev *));

extern void FDECL(check_vardef_type, (struct lc_vardefs *, char *, long));
extern void FDECL(vardef_used, (struct lc_vardefs *, char *));
extern struct lc_vardefs *FDECL(add_vardef_type, (struct lc_vardefs *,
                                                  char *, long));

extern int FDECL(reverse_jmp_opcode, (int));

struct coord {
    long x;
    long y;
};

struct forloopdef {
    char *varname;
    long jmp_point;
};
static struct forloopdef forloop_list[MAX_NESTED_IFS];
static short n_forloops = 0;


sp_lev *splev = NULL;

static struct opvar *if_list[MAX_NESTED_IFS];

static short n_if_list = 0;

unsigned int max_x_map, max_y_map;
int obj_containment = 0;

int in_container_obj = 0;

/* integer value is possibly an inconstant value (eg. dice notation
   or a variable) */
int is_inconstant_number = 0;

int in_switch_statement = 0;
static struct opvar *switch_check_jump = NULL;
static struct opvar *switch_default_case = NULL;
static struct opvar *switch_case_list[MAX_SWITCH_CASES];
static long switch_case_value[MAX_SWITCH_CASES];
int n_switch_case_list = 0;

int allow_break_statements = 0;
struct lc_breakdef *break_list = NULL;

extern struct lc_vardefs *vardefs; /* variable definitions */


struct lc_vardefs *function_tmp_var_defs = NULL;
extern struct lc_funcdefs *function_definitions;
struct lc_funcdefs *curr_function = NULL;
struct lc_funcdefs_parm * curr_function_param = NULL;
int in_function_definition = 0;
sp_lev *function_splev_backup = NULL;

extern int fatal_error;
extern int got_errors;
extern int line_number;
extern const char *fname;
extern int is_rnd_vault;
extern int rnd_vault_freq;
extern int rnd_vault_mindepth;

extern char curr_token[512];


#line 223 "lev_comp.y.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "lev_comp.y.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CHAR = 3,                       /* CHAR  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_BOOLEAN = 5,                    /* BOOLEAN  */
  YYSYMBOL_PERCENT = 6,                    /* PERCENT  */
  YYSYMBOL_SPERCENT = 7,                   /* SPERCENT  */
  YYSYMBOL_MINUS_INTEGER = 8,              /* MINUS_INTEGER  */
  YYSYMBOL_PLUS_INTEGER = 9,               /* PLUS_INTEGER  */
  YYSYMBOL_MAZE_GRID_ID = 10,              /* MAZE_GRID_ID  */
  YYSYMBOL_SOLID_FILL_ID = 11,             /* SOLID_FILL_ID  */
  YYSYMBOL_MINES_ID = 12,                  /* MINES_ID  */
  YYSYMBOL_ROGUELEV_ID = 13,               /* ROGUELEV_ID  */
  YYSYMBOL_MESSAGE_ID = 14,                /* MESSAGE_ID  */
  YYSYMBOL_MAZE_ID = 15,                   /* MAZE_ID  */
  YYSYMBOL_LEVEL_ID = 16,                  /* LEVEL_ID  */
  YYSYMBOL_LEV_INIT_ID = 17,               /* LEV_INIT_ID  */
  YYSYMBOL_GEOMETRY_ID = 18,               /* GEOMETRY_ID  */
  YYSYMBOL_NOMAP_ID = 19,                  /* NOMAP_ID  */
  YYSYMBOL_OBJECT_ID = 20,                 /* OBJECT_ID  */
  YYSYMBOL_COBJECT_ID = 21,                /* COBJECT_ID  */
  YYSYMBOL_MONSTER_ID = 22,                /* MONSTER_ID  */
  YYSYMBOL_TRAP_ID = 23,                   /* TRAP_ID  */
  YYSYMBOL_DOOR_ID = 24,                   /* DOOR_ID  */
  YYSYMBOL_DRAWBRIDGE_ID = 25,             /* DRAWBRIDGE_ID  */
  YYSYMBOL_object_ID = 26,                 /* object_ID  */
  YYSYMBOL_monster_ID = 27,                /* monster_ID  */
  YYSYMBOL_terrain_ID = 28,                /* terrain_ID  */
  YYSYMBOL_MAZEWALK_ID = 29,               /* MAZEWALK_ID  */
  YYSYMBOL_WALLIFY_ID = 30,                /* WALLIFY_ID  */
  YYSYMBOL_REGION_ID = 31,                 /* REGION_ID  */
  YYSYMBOL_FILLING = 32,                   /* FILLING  */
  YYSYMBOL_IRREGULAR = 33,                 /* IRREGULAR  */
  YYSYMBOL_JOINED = 34,                    /* JOINED  */
  YYSYMBOL_ALTAR_ID = 35,                  /* ALTAR_ID  */
  YYSYMBOL_LADDER_ID = 36,                 /* LADDER_ID  */
  YYSYMBOL_STAIR_ID = 37,                  /* STAIR_ID  */
  YYSYMBOL_NON_DIGGABLE_ID = 38,           /* NON_DIGGABLE_ID  */
  YYSYMBOL_NON_PASSWALL_ID = 39,           /* NON_PASSWALL_ID  */
  YYSYMBOL_ROOM_ID = 40,                   /* ROOM_ID  */
  YYSYMBOL_PORTAL_ID = 41,                 /* PORTAL_ID  */
  YYSYMBOL_TELEPRT_ID = 42,                /* TELEPRT_ID  */
  YYSYMBOL_BRANCH_ID = 43,                 /* BRANCH_ID  */
  YYSYMBOL_LEV = 44,                       /* LEV  */
  YYSYMBOL_MINERALIZE_ID = 45,             /* MINERALIZE_ID  */
  YYSYMBOL_CORRIDOR_ID = 46,               /* CORRIDOR_ID  */
  YYSYMBOL_GOLD_ID = 47,                   /* GOLD_ID  */
  YYSYMBOL_ENGRAVING_ID = 48,              /* ENGRAVING_ID  */
  YYSYMBOL_FORGE_ID = 49,                  /* FORGE_ID  */
  YYSYMBOL_MAGIC_CHEST_ID = 50,            /* MAGIC_CHEST_ID  */
  YYSYMBOL_FOUNTAIN_ID = 51,               /* FOUNTAIN_ID  */
  YYSYMBOL_PUDDLE_ID = 52,                 /* PUDDLE_ID  */
  YYSYMBOL_SEWAGE_ID = 53,                 /* SEWAGE_ID  */
  YYSYMBOL_POOL_ID = 54,                   /* POOL_ID  */
  YYSYMBOL_SINK_ID = 55,                   /* SINK_ID  */
  YYSYMBOL_NONE = 56,                      /* NONE  */
  YYSYMBOL_RAND_CORRIDOR_ID = 57,          /* RAND_CORRIDOR_ID  */
  YYSYMBOL_DOOR_STATE = 58,                /* DOOR_STATE  */
  YYSYMBOL_LIGHT_STATE = 59,               /* LIGHT_STATE  */
  YYSYMBOL_CURSE_TYPE = 60,                /* CURSE_TYPE  */
  YYSYMBOL_ENGRAVING_TYPE = 61,            /* ENGRAVING_TYPE  */
  YYSYMBOL_DIRECTION = 62,                 /* DIRECTION  */
  YYSYMBOL_RANDOM_TYPE = 63,               /* RANDOM_TYPE  */
  YYSYMBOL_RANDOM_TYPE_BRACKET = 64,       /* RANDOM_TYPE_BRACKET  */
  YYSYMBOL_A_REGISTER = 65,                /* A_REGISTER  */
  YYSYMBOL_ALIGNMENT = 66,                 /* ALIGNMENT  */
  YYSYMBOL_LEFT_OR_RIGHT = 67,             /* LEFT_OR_RIGHT  */
  YYSYMBOL_CENTER = 68,                    /* CENTER  */
  YYSYMBOL_TOP_OR_BOT = 69,                /* TOP_OR_BOT  */
  YYSYMBOL_ALTAR_TYPE = 70,                /* ALTAR_TYPE  */
  YYSYMBOL_UP_OR_DOWN = 71,                /* UP_OR_DOWN  */
  YYSYMBOL_SUBROOM_ID = 72,                /* SUBROOM_ID  */
  YYSYMBOL_NAME_ID = 73,                   /* NAME_ID  */
  YYSYMBOL_FLAGS_ID = 74,                  /* FLAGS_ID  */
  YYSYMBOL_FLAG_TYPE = 75,                 /* FLAG_TYPE  */
  YYSYMBOL_MON_ATTITUDE = 76,              /* MON_ATTITUDE  */
  YYSYMBOL_MON_ALERTNESS = 77,             /* MON_ALERTNESS  */
  YYSYMBOL_MON_APPEARANCE = 78,            /* MON_APPEARANCE  */
  YYSYMBOL_ROOMDOOR_ID = 79,               /* ROOMDOOR_ID  */
  YYSYMBOL_IF_ID = 80,                     /* IF_ID  */
  YYSYMBOL_ELSE_ID = 81,                   /* ELSE_ID  */
  YYSYMBOL_TERRAIN_ID = 82,                /* TERRAIN_ID  */
  YYSYMBOL_HORIZ_OR_VERT = 83,             /* HORIZ_OR_VERT  */
  YYSYMBOL_REPLACE_TERRAIN_ID = 84,        /* REPLACE_TERRAIN_ID  */
  YYSYMBOL_EXIT_ID = 85,                   /* EXIT_ID  */
  YYSYMBOL_SHUFFLE_ID = 86,                /* SHUFFLE_ID  */
  YYSYMBOL_QUANTITY_ID = 87,               /* QUANTITY_ID  */
  YYSYMBOL_BURIED_ID = 88,                 /* BURIED_ID  */
  YYSYMBOL_LOOP_ID = 89,                   /* LOOP_ID  */
  YYSYMBOL_FOR_ID = 90,                    /* FOR_ID  */
  YYSYMBOL_TO_ID = 91,                     /* TO_ID  */
  YYSYMBOL_SWITCH_ID = 92,                 /* SWITCH_ID  */
  YYSYMBOL_CASE_ID = 93,                   /* CASE_ID  */
  YYSYMBOL_BREAK_ID = 94,                  /* BREAK_ID  */
  YYSYMBOL_DEFAULT_ID = 95,                /* DEFAULT_ID  */
  YYSYMBOL_ERODED_ID = 96,                 /* ERODED_ID  */
  YYSYMBOL_TRAPPED_STATE = 97,             /* TRAPPED_STATE  */
  YYSYMBOL_RECHARGED_ID = 98,              /* RECHARGED_ID  */
  YYSYMBOL_INVIS_ID = 99,                  /* INVIS_ID  */
  YYSYMBOL_GREASED_ID = 100,               /* GREASED_ID  */
  YYSYMBOL_FEMALE_ID = 101,                /* FEMALE_ID  */
  YYSYMBOL_CANCELLED_ID = 102,             /* CANCELLED_ID  */
  YYSYMBOL_REVIVED_ID = 103,               /* REVIVED_ID  */
  YYSYMBOL_AVENGE_ID = 104,                /* AVENGE_ID  */
  YYSYMBOL_FLEEING_ID = 105,               /* FLEEING_ID  */
  YYSYMBOL_BLINDED_ID = 106,               /* BLINDED_ID  */
  YYSYMBOL_PARALYZED_ID = 107,             /* PARALYZED_ID  */
  YYSYMBOL_STUNNED_ID = 108,               /* STUNNED_ID  */
  YYSYMBOL_CONFUSED_ID = 109,              /* CONFUSED_ID  */
  YYSYMBOL_SEENTRAPS_ID = 110,             /* SEENTRAPS_ID  */
  YYSYMBOL_DEAD_ID = 111,                  /* DEAD_ID  */
  YYSYMBOL_ALL_ID = 112,                   /* ALL_ID  */
  YYSYMBOL_MONTYPE_ID = 113,               /* MONTYPE_ID  */
  YYSYMBOL_GRAVE_ID = 114,                 /* GRAVE_ID  */
  YYSYMBOL_ERODEPROOF_ID = 115,            /* ERODEPROOF_ID  */
  YYSYMBOL_FUNCTION_ID = 116,              /* FUNCTION_ID  */
  YYSYMBOL_MSG_OUTPUT_TYPE = 117,          /* MSG_OUTPUT_TYPE  */
  YYSYMBOL_COMPARE_TYPE = 118,             /* COMPARE_TYPE  */
  YYSYMBOL_VAULTGEN_ID = 119,              /* VAULTGEN_ID  */
  YYSYMBOL_MINDEPTH_ID = 120,              /* MINDEPTH_ID  */
  YYSYMBOL_UNKNOWN_TYPE = 121,             /* UNKNOWN_TYPE  */
  YYSYMBOL_rect_ID = 122,                  /* rect_ID  */
  YYSYMBOL_fillrect_ID = 123,              /* fillrect_ID  */
  YYSYMBOL_line_ID = 124,                  /* line_ID  */
  YYSYMBOL_randline_ID = 125,              /* randline_ID  */
  YYSYMBOL_grow_ID = 126,                  /* grow_ID  */
  YYSYMBOL_selection_ID = 127,             /* selection_ID  */
  YYSYMBOL_flood_ID = 128,                 /* flood_ID  */
  YYSYMBOL_rndcoord_ID = 129,              /* rndcoord_ID  */
  YYSYMBOL_circle_ID = 130,                /* circle_ID  */
  YYSYMBOL_ellipse_ID = 131,               /* ellipse_ID  */
  YYSYMBOL_filter_ID = 132,                /* filter_ID  */
  YYSYMBOL_complement_ID = 133,            /* complement_ID  */
  YYSYMBOL_gradient_ID = 134,              /* gradient_ID  */
  YYSYMBOL_GRADIENT_TYPE = 135,            /* GRADIENT_TYPE  */
  YYSYMBOL_LIMITED = 136,                  /* LIMITED  */
  YYSYMBOL_HUMIDITY_TYPE = 137,            /* HUMIDITY_TYPE  */
  YYSYMBOL_138_ = 138,                     /* ','  */
  YYSYMBOL_139_ = 139,                     /* ':'  */
  YYSYMBOL_140_ = 140,                     /* '('  */
  YYSYMBOL_141_ = 141,                     /* ')'  */
  YYSYMBOL_142_ = 142,                     /* '['  */
  YYSYMBOL_143_ = 143,                     /* ']'  */
  YYSYMBOL_144_ = 144,                     /* '{'  */
  YYSYMBOL_145_ = 145,                     /* '}'  */
  YYSYMBOL_STRING = 146,                   /* STRING  */
  YYSYMBOL_MAP_ID = 147,                   /* MAP_ID  */
  YYSYMBOL_NQSTRING = 148,                 /* NQSTRING  */
  YYSYMBOL_VARSTRING = 149,                /* VARSTRING  */
  YYSYMBOL_CFUNC = 150,                    /* CFUNC  */
  YYSYMBOL_CFUNC_INT = 151,                /* CFUNC_INT  */
  YYSYMBOL_CFUNC_STR = 152,                /* CFUNC_STR  */
  YYSYMBOL_CFUNC_COORD = 153,              /* CFUNC_COORD  */
  YYSYMBOL_CFUNC_REGION = 154,             /* CFUNC_REGION  */
  YYSYMBOL_VARSTRING_INT = 155,            /* VARSTRING_INT  */
  YYSYMBOL_VARSTRING_INT_ARRAY = 156,      /* VARSTRING_INT_ARRAY  */
  YYSYMBOL_VARSTRING_STRING = 157,         /* VARSTRING_STRING  */
  YYSYMBOL_VARSTRING_STRING_ARRAY = 158,   /* VARSTRING_STRING_ARRAY  */
  YYSYMBOL_VARSTRING_VAR = 159,            /* VARSTRING_VAR  */
  YYSYMBOL_VARSTRING_VAR_ARRAY = 160,      /* VARSTRING_VAR_ARRAY  */
  YYSYMBOL_VARSTRING_COORD = 161,          /* VARSTRING_COORD  */
  YYSYMBOL_VARSTRING_COORD_ARRAY = 162,    /* VARSTRING_COORD_ARRAY  */
  YYSYMBOL_VARSTRING_REGION = 163,         /* VARSTRING_REGION  */
  YYSYMBOL_VARSTRING_REGION_ARRAY = 164,   /* VARSTRING_REGION_ARRAY  */
  YYSYMBOL_VARSTRING_MAPCHAR = 165,        /* VARSTRING_MAPCHAR  */
  YYSYMBOL_VARSTRING_MAPCHAR_ARRAY = 166,  /* VARSTRING_MAPCHAR_ARRAY  */
  YYSYMBOL_VARSTRING_MONST = 167,          /* VARSTRING_MONST  */
  YYSYMBOL_VARSTRING_MONST_ARRAY = 168,    /* VARSTRING_MONST_ARRAY  */
  YYSYMBOL_VARSTRING_OBJ = 169,            /* VARSTRING_OBJ  */
  YYSYMBOL_VARSTRING_OBJ_ARRAY = 170,      /* VARSTRING_OBJ_ARRAY  */
  YYSYMBOL_VARSTRING_SEL = 171,            /* VARSTRING_SEL  */
  YYSYMBOL_VARSTRING_SEL_ARRAY = 172,      /* VARSTRING_SEL_ARRAY  */
  YYSYMBOL_METHOD_INT = 173,               /* METHOD_INT  */
  YYSYMBOL_METHOD_INT_ARRAY = 174,         /* METHOD_INT_ARRAY  */
  YYSYMBOL_METHOD_STRING = 175,            /* METHOD_STRING  */
  YYSYMBOL_METHOD_STRING_ARRAY = 176,      /* METHOD_STRING_ARRAY  */
  YYSYMBOL_METHOD_VAR = 177,               /* METHOD_VAR  */
  YYSYMBOL_METHOD_VAR_ARRAY = 178,         /* METHOD_VAR_ARRAY  */
  YYSYMBOL_METHOD_COORD = 179,             /* METHOD_COORD  */
  YYSYMBOL_METHOD_COORD_ARRAY = 180,       /* METHOD_COORD_ARRAY  */
  YYSYMBOL_METHOD_REGION = 181,            /* METHOD_REGION  */
  YYSYMBOL_METHOD_REGION_ARRAY = 182,      /* METHOD_REGION_ARRAY  */
  YYSYMBOL_METHOD_MAPCHAR = 183,           /* METHOD_MAPCHAR  */
  YYSYMBOL_METHOD_MAPCHAR_ARRAY = 184,     /* METHOD_MAPCHAR_ARRAY  */
  YYSYMBOL_METHOD_MONST = 185,             /* METHOD_MONST  */
  YYSYMBOL_METHOD_MONST_ARRAY = 186,       /* METHOD_MONST_ARRAY  */
  YYSYMBOL_METHOD_OBJ = 187,               /* METHOD_OBJ  */
  YYSYMBOL_METHOD_OBJ_ARRAY = 188,         /* METHOD_OBJ_ARRAY  */
  YYSYMBOL_METHOD_SEL = 189,               /* METHOD_SEL  */
  YYSYMBOL_METHOD_SEL_ARRAY = 190,         /* METHOD_SEL_ARRAY  */
  YYSYMBOL_DICE = 191,                     /* DICE  */
  YYSYMBOL_192_ = 192,                     /* '+'  */
  YYSYMBOL_193_ = 193,                     /* '-'  */
  YYSYMBOL_194_ = 194,                     /* '*'  */
  YYSYMBOL_195_ = 195,                     /* '/'  */
  YYSYMBOL_196_ = 196,                     /* '%'  */
  YYSYMBOL_197_ = 197,                     /* '='  */
  YYSYMBOL_198_ = 198,                     /* '.'  */
  YYSYMBOL_199_ = 199,                     /* '|'  */
  YYSYMBOL_200_ = 200,                     /* '&'  */
  YYSYMBOL_YYACCEPT = 201,                 /* $accept  */
  YYSYMBOL_file = 202,                     /* file  */
  YYSYMBOL_levels = 203,                   /* levels  */
  YYSYMBOL_level = 204,                    /* level  */
  YYSYMBOL_level_def = 205,                /* level_def  */
  YYSYMBOL_mazefiller = 206,               /* mazefiller  */
  YYSYMBOL_lev_init = 207,                 /* lev_init  */
  YYSYMBOL_opt_limited = 208,              /* opt_limited  */
  YYSYMBOL_opt_coord_or_var = 209,         /* opt_coord_or_var  */
  YYSYMBOL_opt_fillchar = 210,             /* opt_fillchar  */
  YYSYMBOL_walled = 211,                   /* walled  */
  YYSYMBOL_flags = 212,                    /* flags  */
  YYSYMBOL_flag_list = 213,                /* flag_list  */
  YYSYMBOL_levstatements = 214,            /* levstatements  */
  YYSYMBOL_stmt_block = 215,               /* stmt_block  */
  YYSYMBOL_levstatement = 216,             /* levstatement  */
  YYSYMBOL_any_var_array = 217,            /* any_var_array  */
  YYSYMBOL_any_var = 218,                  /* any_var  */
  YYSYMBOL_any_var_or_arr = 219,           /* any_var_or_arr  */
  YYSYMBOL_any_var_or_unk = 220,           /* any_var_or_unk  */
  YYSYMBOL_shuffle_detail = 221,           /* shuffle_detail  */
  YYSYMBOL_variable_define = 222,          /* variable_define  */
  YYSYMBOL_encodeobj_list = 223,           /* encodeobj_list  */
  YYSYMBOL_encodemonster_list = 224,       /* encodemonster_list  */
  YYSYMBOL_mapchar_list = 225,             /* mapchar_list  */
  YYSYMBOL_encoderegion_list = 226,        /* encoderegion_list  */
  YYSYMBOL_encodecoord_list = 227,         /* encodecoord_list  */
  YYSYMBOL_integer_list = 228,             /* integer_list  */
  YYSYMBOL_string_list = 229,              /* string_list  */
  YYSYMBOL_function_define = 230,          /* function_define  */
  YYSYMBOL_231_1 = 231,                    /* $@1  */
  YYSYMBOL_232_2 = 232,                    /* $@2  */
  YYSYMBOL_function_call = 233,            /* function_call  */
  YYSYMBOL_exitstatement = 234,            /* exitstatement  */
  YYSYMBOL_opt_percent = 235,              /* opt_percent  */
  YYSYMBOL_comparestmt = 236,              /* comparestmt  */
  YYSYMBOL_switchstatement = 237,          /* switchstatement  */
  YYSYMBOL_238_3 = 238,                    /* $@3  */
  YYSYMBOL_239_4 = 239,                    /* $@4  */
  YYSYMBOL_switchcases = 240,              /* switchcases  */
  YYSYMBOL_switchcase = 241,               /* switchcase  */
  YYSYMBOL_242_5 = 242,                    /* $@5  */
  YYSYMBOL_243_6 = 243,                    /* $@6  */
  YYSYMBOL_breakstatement = 244,           /* breakstatement  */
  YYSYMBOL_for_to_span = 245,              /* for_to_span  */
  YYSYMBOL_forstmt_start = 246,            /* forstmt_start  */
  YYSYMBOL_forstatement = 247,             /* forstatement  */
  YYSYMBOL_248_7 = 248,                    /* $@7  */
  YYSYMBOL_loopstatement = 249,            /* loopstatement  */
  YYSYMBOL_250_8 = 250,                    /* $@8  */
  YYSYMBOL_chancestatement = 251,          /* chancestatement  */
  YYSYMBOL_252_9 = 252,                    /* $@9  */
  YYSYMBOL_ifstatement = 253,              /* ifstatement  */
  YYSYMBOL_254_10 = 254,                   /* $@10  */
  YYSYMBOL_if_ending = 255,                /* if_ending  */
  YYSYMBOL_256_11 = 256,                   /* $@11  */
  YYSYMBOL_vaultgen_stmt = 257,            /* vaultgen_stmt  */
  YYSYMBOL_mindepth_stmt = 258,            /* mindepth_stmt  */
  YYSYMBOL_message = 259,                  /* message  */
  YYSYMBOL_random_corridors = 260,         /* random_corridors  */
  YYSYMBOL_corridor = 261,                 /* corridor  */
  YYSYMBOL_corr_spec = 262,                /* corr_spec  */
  YYSYMBOL_room_begin = 263,               /* room_begin  */
  YYSYMBOL_subroom_def = 264,              /* subroom_def  */
  YYSYMBOL_265_12 = 265,                   /* $@12  */
  YYSYMBOL_room_def = 266,                 /* room_def  */
  YYSYMBOL_267_13 = 267,                   /* $@13  */
  YYSYMBOL_roomfill = 268,                 /* roomfill  */
  YYSYMBOL_room_pos = 269,                 /* room_pos  */
  YYSYMBOL_subroom_pos = 270,              /* subroom_pos  */
  YYSYMBOL_room_align = 271,               /* room_align  */
  YYSYMBOL_room_size = 272,                /* room_size  */
  YYSYMBOL_door_detail = 273,              /* door_detail  */
  YYSYMBOL_secret = 274,                   /* secret  */
  YYSYMBOL_door_wall = 275,                /* door_wall  */
  YYSYMBOL_dir_list = 276,                 /* dir_list  */
  YYSYMBOL_door_pos = 277,                 /* door_pos  */
  YYSYMBOL_map_definition = 278,           /* map_definition  */
  YYSYMBOL_h_justif = 279,                 /* h_justif  */
  YYSYMBOL_v_justif = 280,                 /* v_justif  */
  YYSYMBOL_monster_detail = 281,           /* monster_detail  */
  YYSYMBOL_282_14 = 282,                   /* $@14  */
  YYSYMBOL_monster_desc = 283,             /* monster_desc  */
  YYSYMBOL_monster_infos = 284,            /* monster_infos  */
  YYSYMBOL_monster_info = 285,             /* monster_info  */
  YYSYMBOL_seen_trap_mask = 286,           /* seen_trap_mask  */
  YYSYMBOL_object_detail = 287,            /* object_detail  */
  YYSYMBOL_288_15 = 288,                   /* $@15  */
  YYSYMBOL_object_desc = 289,              /* object_desc  */
  YYSYMBOL_object_infos = 290,             /* object_infos  */
  YYSYMBOL_object_info = 291,              /* object_info  */
  YYSYMBOL_trap_detail = 292,              /* trap_detail  */
  YYSYMBOL_drawbridge_detail = 293,        /* drawbridge_detail  */
  YYSYMBOL_mazewalk_detail = 294,          /* mazewalk_detail  */
  YYSYMBOL_wallify_detail = 295,           /* wallify_detail  */
  YYSYMBOL_ladder_detail = 296,            /* ladder_detail  */
  YYSYMBOL_stair_detail = 297,             /* stair_detail  */
  YYSYMBOL_stair_region = 298,             /* stair_region  */
  YYSYMBOL_portal_region = 299,            /* portal_region  */
  YYSYMBOL_teleprt_region = 300,           /* teleprt_region  */
  YYSYMBOL_branch_region = 301,            /* branch_region  */
  YYSYMBOL_teleprt_detail = 302,           /* teleprt_detail  */
  YYSYMBOL_forge_detail = 303,             /* forge_detail  */
  YYSYMBOL_magic_chest_detail = 304,       /* magic_chest_detail  */
  YYSYMBOL_fountain_detail = 305,          /* fountain_detail  */
  YYSYMBOL_sink_detail = 306,              /* sink_detail  */
  YYSYMBOL_puddle_detail = 307,            /* puddle_detail  */
  YYSYMBOL_sewage_detail = 308,            /* sewage_detail  */
  YYSYMBOL_pool_detail = 309,              /* pool_detail  */
  YYSYMBOL_terrain_type = 310,             /* terrain_type  */
  YYSYMBOL_replace_terrain_detail = 311,   /* replace_terrain_detail  */
  YYSYMBOL_terrain_detail = 312,           /* terrain_detail  */
  YYSYMBOL_diggable_detail = 313,          /* diggable_detail  */
  YYSYMBOL_passwall_detail = 314,          /* passwall_detail  */
  YYSYMBOL_region_detail = 315,            /* region_detail  */
  YYSYMBOL_316_16 = 316,                   /* @16  */
  YYSYMBOL_region_detail_end = 317,        /* region_detail_end  */
  YYSYMBOL_altar_detail = 318,             /* altar_detail  */
  YYSYMBOL_grave_detail = 319,             /* grave_detail  */
  YYSYMBOL_gold_detail = 320,              /* gold_detail  */
  YYSYMBOL_engraving_detail = 321,         /* engraving_detail  */
  YYSYMBOL_mineralize = 322,               /* mineralize  */
  YYSYMBOL_trap_name = 323,                /* trap_name  */
  YYSYMBOL_room_type = 324,                /* room_type  */
  YYSYMBOL_optroomregionflags = 325,       /* optroomregionflags  */
  YYSYMBOL_roomregionflags = 326,          /* roomregionflags  */
  YYSYMBOL_roomregionflag = 327,           /* roomregionflag  */
  YYSYMBOL_door_state = 328,               /* door_state  */
  YYSYMBOL_light_state = 329,              /* light_state  */
  YYSYMBOL_alignment = 330,                /* alignment  */
  YYSYMBOL_alignment_prfx = 331,           /* alignment_prfx  */
  YYSYMBOL_altar_type = 332,               /* altar_type  */
  YYSYMBOL_a_register = 333,               /* a_register  */
  YYSYMBOL_string_or_var = 334,            /* string_or_var  */
  YYSYMBOL_integer_or_var = 335,           /* integer_or_var  */
  YYSYMBOL_coord_or_var = 336,             /* coord_or_var  */
  YYSYMBOL_encodecoord = 337,              /* encodecoord  */
  YYSYMBOL_humidity_flags = 338,           /* humidity_flags  */
  YYSYMBOL_region_or_var = 339,            /* region_or_var  */
  YYSYMBOL_encoderegion = 340,             /* encoderegion  */
  YYSYMBOL_mapchar_or_var = 341,           /* mapchar_or_var  */
  YYSYMBOL_mapchar = 342,                  /* mapchar  */
  YYSYMBOL_monster_or_var = 343,           /* monster_or_var  */
  YYSYMBOL_encodemonster = 344,            /* encodemonster  */
  YYSYMBOL_object_or_var = 345,            /* object_or_var  */
  YYSYMBOL_encodeobj = 346,                /* encodeobj  */
  YYSYMBOL_string_expr = 347,              /* string_expr  */
  YYSYMBOL_math_expr_var = 348,            /* math_expr_var  */
  YYSYMBOL_func_param_type = 349,          /* func_param_type  */
  YYSYMBOL_func_param_part = 350,          /* func_param_part  */
  YYSYMBOL_func_param_list = 351,          /* func_param_list  */
  YYSYMBOL_func_params_list = 352,         /* func_params_list  */
  YYSYMBOL_func_call_param_part = 353,     /* func_call_param_part  */
  YYSYMBOL_func_call_param_list = 354,     /* func_call_param_list  */
  YYSYMBOL_func_call_params_list = 355,    /* func_call_params_list  */
  YYSYMBOL_ter_selection_x = 356,          /* ter_selection_x  */
  YYSYMBOL_ter_selection = 357,            /* ter_selection  */
  YYSYMBOL_dice = 358,                     /* dice  */
  YYSYMBOL_all_integers = 359,             /* all_integers  */
  YYSYMBOL_all_ints_push = 360,            /* all_ints_push  */
  YYSYMBOL_objectid = 361,                 /* objectid  */
  YYSYMBOL_monsterid = 362,                /* monsterid  */
  YYSYMBOL_terrainid = 363,                /* terrainid  */
  YYSYMBOL_engraving_type = 364,           /* engraving_type  */
  YYSYMBOL_lev_region = 365,               /* lev_region  */
  YYSYMBOL_region = 366                    /* region  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1050

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  201
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  166
/* YYNRULES -- Number of rules.  */
#define YYNRULES  419
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  891

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   438


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   196,   200,     2,
     140,   141,   194,   192,   138,   193,   198,   195,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   139,     2,
       2,   197,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   142,     2,   143,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   144,   199,   145,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   286,   286,   287,   290,   291,   294,   317,   325,   348,
     352,   358,   371,   383,   389,   420,   423,   430,   434,   441,
     444,   451,   452,   456,   459,   469,   473,   480,   483,   489,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   558,
     559,   560,   561,   562,   563,   564,   565,   566,   569,   570,
     571,   574,   575,   578,   594,   600,   606,   612,   618,   624,
     630,   636,   642,   652,   662,   672,   682,   692,   702,   714,
     719,   726,   731,   738,   743,   750,   754,   760,   765,   772,
     776,   782,   786,   793,   815,   792,   829,   884,   891,   894,
     900,   907,   911,   920,   924,   919,   987,   988,   992,   991,
    1005,  1004,  1019,  1029,  1030,  1033,  1071,  1070,  1105,  1104,
    1135,  1134,  1167,  1166,  1192,  1203,  1202,  1230,  1242,  1254,
    1260,  1265,  1270,  1277,  1284,  1293,  1301,  1313,  1312,  1331,
    1330,  1349,  1352,  1358,  1368,  1374,  1383,  1389,  1394,  1400,
    1405,  1411,  1422,  1428,  1429,  1432,  1433,  1436,  1440,  1446,
    1447,  1450,  1457,  1465,  1473,  1474,  1477,  1478,  1481,  1486,
    1485,  1499,  1506,  1513,  1521,  1526,  1532,  1538,  1544,  1550,
    1555,  1560,  1565,  1570,  1575,  1580,  1585,  1590,  1595,  1600,
    1606,  1613,  1622,  1626,  1639,  1648,  1647,  1665,  1675,  1681,
    1689,  1695,  1700,  1705,  1710,  1715,  1720,  1725,  1730,  1735,
    1746,  1752,  1757,  1762,  1767,  1774,  1780,  1809,  1814,  1822,
    1828,  1834,  1841,  1848,  1858,  1868,  1883,  1894,  1897,  1903,
    1909,  1914,  1920,  1926,  1932,  1938,  1944,  1949,  1956,  1963,
    1969,  1975,  1982,  1981,  2006,  2009,  2015,  2022,  2026,  2031,
    2038,  2044,  2051,  2055,  2062,  2070,  2073,  2083,  2087,  2090,
    2096,  2100,  2107,  2111,  2115,  2121,  2122,  2125,  2126,  2129,
    2130,  2131,  2137,  2138,  2139,  2145,  2146,  2149,  2158,  2163,
    2170,  2181,  2187,  2191,  2195,  2202,  2212,  2219,  2223,  2229,
    2233,  2241,  2245,  2252,  2262,  2275,  2279,  2286,  2296,  2305,
    2316,  2320,  2327,  2337,  2348,  2357,  2367,  2373,  2377,  2384,
    2394,  2405,  2414,  2424,  2431,  2432,  2438,  2442,  2446,  2450,
    2458,  2467,  2471,  2475,  2479,  2483,  2487,  2490,  2497,  2506,
    2539,  2540,  2543,  2544,  2547,  2551,  2558,  2565,  2576,  2579,
    2587,  2591,  2595,  2599,  2603,  2608,  2612,  2616,  2621,  2626,
    2631,  2635,  2640,  2645,  2649,  2653,  2658,  2662,  2669,  2675,
    2679,  2685,  2692,  2693,  2694,  2697,  2701,  2705,  2709,  2715,
    2716,  2719,  2720,  2723,  2724,  2727,  2728,  2731,  2735,  2761
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CHAR", "INTEGER",
  "BOOLEAN", "PERCENT", "SPERCENT", "MINUS_INTEGER", "PLUS_INTEGER",
  "MAZE_GRID_ID", "SOLID_FILL_ID", "MINES_ID", "ROGUELEV_ID", "MESSAGE_ID",
  "MAZE_ID", "LEVEL_ID", "LEV_INIT_ID", "GEOMETRY_ID", "NOMAP_ID",
  "OBJECT_ID", "COBJECT_ID", "MONSTER_ID", "TRAP_ID", "DOOR_ID",
  "DRAWBRIDGE_ID", "object_ID", "monster_ID", "terrain_ID", "MAZEWALK_ID",
  "WALLIFY_ID", "REGION_ID", "FILLING", "IRREGULAR", "JOINED", "ALTAR_ID",
  "LADDER_ID", "STAIR_ID", "NON_DIGGABLE_ID", "NON_PASSWALL_ID", "ROOM_ID",
  "PORTAL_ID", "TELEPRT_ID", "BRANCH_ID", "LEV", "MINERALIZE_ID",
  "CORRIDOR_ID", "GOLD_ID", "ENGRAVING_ID", "FORGE_ID", "MAGIC_CHEST_ID",
  "FOUNTAIN_ID", "PUDDLE_ID", "SEWAGE_ID", "POOL_ID", "SINK_ID", "NONE",
  "RAND_CORRIDOR_ID", "DOOR_STATE", "LIGHT_STATE", "CURSE_TYPE",
  "ENGRAVING_TYPE", "DIRECTION", "RANDOM_TYPE", "RANDOM_TYPE_BRACKET",
  "A_REGISTER", "ALIGNMENT", "LEFT_OR_RIGHT", "CENTER", "TOP_OR_BOT",
  "ALTAR_TYPE", "UP_OR_DOWN", "SUBROOM_ID", "NAME_ID", "FLAGS_ID",
  "FLAG_TYPE", "MON_ATTITUDE", "MON_ALERTNESS", "MON_APPEARANCE",
  "ROOMDOOR_ID", "IF_ID", "ELSE_ID", "TERRAIN_ID", "HORIZ_OR_VERT",
  "REPLACE_TERRAIN_ID", "EXIT_ID", "SHUFFLE_ID", "QUANTITY_ID",
  "BURIED_ID", "LOOP_ID", "FOR_ID", "TO_ID", "SWITCH_ID", "CASE_ID",
  "BREAK_ID", "DEFAULT_ID", "ERODED_ID", "TRAPPED_STATE", "RECHARGED_ID",
  "INVIS_ID", "GREASED_ID", "FEMALE_ID", "CANCELLED_ID", "REVIVED_ID",
  "AVENGE_ID", "FLEEING_ID", "BLINDED_ID", "PARALYZED_ID", "STUNNED_ID",
  "CONFUSED_ID", "SEENTRAPS_ID", "DEAD_ID", "ALL_ID", "MONTYPE_ID",
  "GRAVE_ID", "ERODEPROOF_ID", "FUNCTION_ID", "MSG_OUTPUT_TYPE",
  "COMPARE_TYPE", "VAULTGEN_ID", "MINDEPTH_ID", "UNKNOWN_TYPE", "rect_ID",
  "fillrect_ID", "line_ID", "randline_ID", "grow_ID", "selection_ID",
  "flood_ID", "rndcoord_ID", "circle_ID", "ellipse_ID", "filter_ID",
  "complement_ID", "gradient_ID", "GRADIENT_TYPE", "LIMITED",
  "HUMIDITY_TYPE", "','", "':'", "'('", "')'", "'['", "']'", "'{'", "'}'",
  "STRING", "MAP_ID", "NQSTRING", "VARSTRING", "CFUNC", "CFUNC_INT",
  "CFUNC_STR", "CFUNC_COORD", "CFUNC_REGION", "VARSTRING_INT",
  "VARSTRING_INT_ARRAY", "VARSTRING_STRING", "VARSTRING_STRING_ARRAY",
  "VARSTRING_VAR", "VARSTRING_VAR_ARRAY", "VARSTRING_COORD",
  "VARSTRING_COORD_ARRAY", "VARSTRING_REGION", "VARSTRING_REGION_ARRAY",
  "VARSTRING_MAPCHAR", "VARSTRING_MAPCHAR_ARRAY", "VARSTRING_MONST",
  "VARSTRING_MONST_ARRAY", "VARSTRING_OBJ", "VARSTRING_OBJ_ARRAY",
  "VARSTRING_SEL", "VARSTRING_SEL_ARRAY", "METHOD_INT", "METHOD_INT_ARRAY",
  "METHOD_STRING", "METHOD_STRING_ARRAY", "METHOD_VAR", "METHOD_VAR_ARRAY",
  "METHOD_COORD", "METHOD_COORD_ARRAY", "METHOD_REGION",
  "METHOD_REGION_ARRAY", "METHOD_MAPCHAR", "METHOD_MAPCHAR_ARRAY",
  "METHOD_MONST", "METHOD_MONST_ARRAY", "METHOD_OBJ", "METHOD_OBJ_ARRAY",
  "METHOD_SEL", "METHOD_SEL_ARRAY", "DICE", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'='", "'.'", "'|'", "'&'", "$accept", "file", "levels", "level",
  "level_def", "mazefiller", "lev_init", "opt_limited", "opt_coord_or_var",
  "opt_fillchar", "walled", "flags", "flag_list", "levstatements",
  "stmt_block", "levstatement", "any_var_array", "any_var",
  "any_var_or_arr", "any_var_or_unk", "shuffle_detail", "variable_define",
  "encodeobj_list", "encodemonster_list", "mapchar_list",
  "encoderegion_list", "encodecoord_list", "integer_list", "string_list",
  "function_define", "$@1", "$@2", "function_call", "exitstatement",
  "opt_percent", "comparestmt", "switchstatement", "$@3", "$@4",
  "switchcases", "switchcase", "$@5", "$@6", "breakstatement",
  "for_to_span", "forstmt_start", "forstatement", "$@7", "loopstatement",
  "$@8", "chancestatement", "$@9", "ifstatement", "$@10", "if_ending",
  "$@11", "vaultgen_stmt", "mindepth_stmt", "message", "random_corridors",
  "corridor", "corr_spec", "room_begin", "subroom_def", "$@12", "room_def",
  "$@13", "roomfill", "room_pos", "subroom_pos", "room_align", "room_size",
  "door_detail", "secret", "door_wall", "dir_list", "door_pos",
  "map_definition", "h_justif", "v_justif", "monster_detail", "$@14",
  "monster_desc", "monster_infos", "monster_info", "seen_trap_mask",
  "object_detail", "$@15", "object_desc", "object_infos", "object_info",
  "trap_detail", "drawbridge_detail", "mazewalk_detail", "wallify_detail",
  "ladder_detail", "stair_detail", "stair_region", "portal_region",
  "teleprt_region", "branch_region", "teleprt_detail", "forge_detail",
  "magic_chest_detail", "fountain_detail", "sink_detail", "puddle_detail",
  "sewage_detail", "pool_detail", "terrain_type", "replace_terrain_detail",
  "terrain_detail", "diggable_detail", "passwall_detail", "region_detail",
  "@16", "region_detail_end", "altar_detail", "grave_detail",
  "gold_detail", "engraving_detail", "mineralize", "trap_name",
  "room_type", "optroomregionflags", "roomregionflags", "roomregionflag",
  "door_state", "light_state", "alignment", "alignment_prfx", "altar_type",
  "a_register", "string_or_var", "integer_or_var", "coord_or_var",
  "encodecoord", "humidity_flags", "region_or_var", "encoderegion",
  "mapchar_or_var", "mapchar", "monster_or_var", "encodemonster",
  "object_or_var", "encodeobj", "string_expr", "math_expr_var",
  "func_param_type", "func_param_part", "func_param_list",
  "func_params_list", "func_call_param_part", "func_call_param_list",
  "func_call_params_list", "ter_selection_x", "ter_selection", "dice",
  "all_integers", "all_ints_push", "objectid", "monsterid", "terrainid",
  "engraving_type", "lev_region", "region", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-684)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-210)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     106,   -79,   -68,   100,  -684,   106,    39,     0,     4,  -684,
    -684,    21,   626,    79,  -684,    95,  -684,    41,    96,   116,
    -684,   171,   179,   183,   196,   198,   202,   206,   223,   227,
     248,   250,   252,   255,   267,   269,   271,   286,   290,   300,
     301,   304,   306,   321,   324,   326,   328,   329,   334,   348,
     351,   359,   362,    34,   363,   364,  -684,   365,    69,   762,
    -684,  -684,   369,   148,   370,   372,    72,   165,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   626,
    -684,  -684,   117,  -684,  -684,  -684,  -684,  -684,   373,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,    81,   263,  -684,   -59,   438,   297,
     188,   188,   235,   -21,    27,   -10,   -10,   456,   -57,   -10,
     -10,   256,   -57,   -57,    -6,    -3,    -3,    -3,    72,   279,
      72,   -10,   456,   456,   456,   456,   456,   456,   456,    73,
      -6,    70,  -684,   456,   -57,   764,    72,  -684,  -684,   241,
     302,   -10,   375,   487,   495,  -684,    65,  -684,   374,  -684,
     346,  -684,    32,  -684,    52,  -684,   377,  -684,  -684,  -684,
      95,  -684,  -684,   380,  -684,   330,   386,   391,   392,  -684,
    -684,   395,  -684,  -684,   403,   540,  -684,   411,   407,   416,
    -684,  -684,  -684,   555,  -684,  -684,   417,  -684,  -684,  -684,
    -684,  -684,  -684,   558,  -684,  -684,   420,   419,   426,  -684,
    -684,  -684,   432,  -684,  -684,   453,   454,   455,   -57,   -57,
     -10,   -10,   457,   -10,   458,   459,   460,   456,   462,    33,
    -684,  -684,   394,  -684,   599,  -684,   469,   474,  -684,   475,
     477,   476,   616,   483,   488,  -684,  -684,  -684,  -684,  -684,
     490,   619,   627,   501,   504,   514,   515,   442,   650,   520,
     261,   521,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,   522,  -684,  -684,   532,   377,   551,
     557,  -684,   553,    72,    72,   559,  -684,  -684,  -684,   560,
     156,    72,    72,  -684,    72,    72,    72,    72,    72,   330,
     442,  -684,   562,   572,  -684,  -684,  -684,  -684,  -684,  -684,
     563,   124,    28,  -684,  -684,   330,   442,   568,   575,   578,
     626,   626,  -684,  -684,    72,   -59,   696,    62,   716,   588,
     584,   456,   590,    72,   305,   724,   583,   598,    72,   600,
     377,   601,    72,   377,   -10,   -10,   456,   679,   682,  -684,
    -684,   625,   628,   687,  -684,   -10,   -10,   352,  -684,   612,
     623,   456,   631,    72,    64,   358,   694,   766,   633,   701,
      -3,   -28,  -684,   635,   638,    -3,    -3,    -3,    72,   639,
      42,   -10,   204,   -16,    27,   697,  -684,   128,   128,  -684,
     131,   656,    -4,   721,  -684,  -684,   240,   354,    87,    87,
    -684,  -684,  -684,    32,  -684,   456,   662,   -52,   -35,   -34,
     157,  -684,  -684,   330,   442,    31,   244,    92,  -684,   661,
     498,  -684,  -684,  -684,   804,  -684,   670,   395,  -684,   673,
     818,   539,  -684,  -684,   416,  -684,  -684,   680,   561,   280,
    -684,   691,   566,  -684,  -684,  -684,  -684,   695,   700,   -10,
     -10,   640,   702,   684,   703,   704,  -684,   705,   443,  -684,
     708,   706,  -684,   707,   709,  -684,  -684,   842,   609,  -684,
    -684,   713,  -684,   710,  -684,   715,  -684,  -684,   717,   850,
    -684,   718,  -684,   867,   734,    64,   869,   736,   737,  -684,
     756,   833,  -684,  -684,  -684,  -684,  -684,   759,  -684,   892,
     760,   761,   819,   898,  -684,   765,   377,  -684,   711,    72,
    -684,  -684,   330,   763,  -684,   767,   769,  -684,  -684,  -684,
    -684,   902,   768,  -684,    -1,  -684,    72,  -684,   -59,  -684,
      85,  -684,   246,  -684,    63,  -684,  -684,  -684,   774,   904,
    -684,  -684,   772,  -684,   771,   773,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,   796,   798,  -684,   799,  -684,   800,  -684,
    -684,   801,  -684,  -684,  -684,  -684,  -684,   802,  -684,   803,
      27,   937,  -684,   806,   883,   456,  -684,    72,    72,   456,
     808,    72,   456,   456,   807,   810,  -684,    -6,   945,   236,
     946,   -33,   880,   814,   -14,  -684,   815,   809,   885,  -684,
      72,   816,   -59,   820,   -11,   335,   377,   128,  -684,  -684,
     442,   813,   262,   721,  -684,    88,  -684,  -684,   442,   330,
     163,  -684,   166,  -684,   218,  -684,    64,   821,  -684,  -684,
    -684,   -59,    72,    72,    72,   235,  -684,   758,  -684,   822,
      72,  -684,   823,   414,   341,   824,    64,   636,   825,   826,
      72,   957,   830,   827,  -684,  -684,  -684,   831,   958,  -684,
     959,  -684,   360,   834,  -684,  -684,   835,    51,   330,   967,
    -684,   970,   830,  -684,   837,  -684,  -684,   838,   192,  -684,
    -684,  -684,  -684,   377,    85,  -684,   246,  -684,    63,  -684,
     836,   973,   330,  -684,  -684,  -684,  -684,   127,  -684,  -684,
    -684,   -59,  -684,  -684,  -684,  -684,  -684,   840,   841,   843,
    -684,  -684,   844,  -684,  -684,  -684,  -684,   330,   978,  -684,
     442,  -684,   952,  -684,    72,  -684,   845,  -684,  -684,  -684,
     529,   847,   299,  -684,  -684,   983,   851,   849,   853,   -11,
      72,  -684,  -684,   852,   854,   856,  -684,    51,   981,   396,
     857,   855,   192,  -684,  -684,  -684,  -684,  -684,   859,   929,
     330,    72,    72,    72,   -44,  -684,   858,   492,  -684,    72,
     994,  -684,  -684,  -684,  -684,   863,   377,   864,   999,  -684,
     305,   830,  -684,  -684,  -684,  1000,   377,  -684,  -684,   866,
    -684,  -684,  -684,  1001,  -684,  -684,  -684,  -684,  -684,   811,
    -684,  -684,   975,  -684,   175,   868,   299,  -684,  -684,  1004,
     870,   871,  -684,   872,  -684,  -684,   626,   876,   -44,   874,
     881,   875,  -684,  -684,   877,  -684,  -684,   377,  -684,   626,
    -684,    64,  -684,  -684,  -684,   882,  -684,  -684,  -684,   884,
     -10,    84,   886,  -684,  -684,   822,   -10,   878,  -684,  -684,
    -684
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     0,     0,     3,     4,    23,     0,     0,     1,
       5,     0,    27,     0,     7,     0,   140,     0,     0,     0,
     201,     0,     0,     0,     0,     0,     0,     0,   259,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   293,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     170,     0,     0,     0,     0,     0,   137,     0,     0,     0,
     143,   152,     0,     0,     0,     0,     0,     0,   100,    89,
      80,    90,    81,    91,    82,    92,    83,    93,    84,    94,
      85,    95,    86,    96,    87,    97,    88,    31,     6,    27,
      98,    99,     0,    37,    36,    54,    55,    52,     0,    47,
      53,   156,    48,    49,    51,    50,    56,    57,    30,    68,
      35,    71,    70,    39,    59,    61,    62,    78,    40,    60,
      79,    58,    75,    76,    67,    77,    34,    44,    45,    43,
      72,    64,    65,    66,    74,    73,    38,    63,    69,    32,
      33,    46,    41,    42,     0,    26,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   162,     0,     0,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,   356,     0,   359,     0,   401,
       0,   357,   378,    28,     0,   160,     0,    10,     9,     8,
       0,   318,   319,     0,   354,   169,     0,     0,     0,    13,
     327,     0,   204,   205,     0,     0,   324,     0,     0,   181,
     322,   351,   353,     0,   350,   348,     0,   234,   238,   347,
     235,   344,   346,     0,   343,   341,     0,   208,     0,   340,
     295,   294,     0,   305,   306,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     397,   380,   399,   260,     0,   332,     0,     0,   331,     0,
       0,     0,     0,     0,     0,   417,   280,   281,   297,   296,
       0,   138,     0,     0,     0,     0,     0,   321,     0,     0,
       0,     0,   269,   270,   271,   273,   274,   275,   272,   404,
     402,   403,   172,   171,     0,   193,   194,     0,     0,     0,
       0,   103,     0,     0,     0,   289,   133,   167,   168,     0,
       0,     0,     0,   142,     0,     0,     0,     0,     0,   375,
     374,   376,   379,     0,   410,   412,   409,   411,   413,   414,
       0,     0,     0,   110,   111,   106,   104,     0,     0,     0,
       0,    27,   157,    25,     0,     0,     0,     0,     0,   329,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   237,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   381,
     382,     0,     0,     0,   390,     0,     0,     0,   396,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   139,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   164,   163,     0,     0,   158,
       0,     0,     0,   372,   358,   366,     0,     0,   361,   362,
     363,   364,   365,     0,   136,     0,   356,     0,     0,     0,
       0,   127,   125,   131,   129,     0,     0,     0,   161,     0,
       0,   355,    12,   276,     0,    11,     0,     0,   328,     0,
       0,     0,   207,   206,   181,   182,   203,     0,     0,     0,
     236,     0,     0,   210,   212,   255,   192,     0,   257,     0,
       0,   197,     0,     0,     0,     0,   338,     0,     0,   336,
       0,     0,   335,     0,     0,   398,   400,     0,     0,   307,
     308,     0,   311,     0,   309,     0,   310,   261,     0,     0,
     262,     0,   184,     0,     0,     0,     0,     0,   267,   266,
       0,     0,   173,   174,   290,   415,   416,     0,   186,     0,
       0,     0,     0,     0,   279,     0,     0,   154,     0,     0,
     144,   288,   287,     0,   370,   373,     0,   360,   141,   377,
     105,     0,     0,   114,     0,   113,     0,   112,     0,   118,
       0,   109,     0,   108,     0,   107,    29,   320,     0,     0,
     330,   323,     0,   325,     0,     0,   349,   407,   405,   406,
     249,   246,   240,     0,     0,   245,     0,   250,     0,   252,
     253,     0,   248,   239,   254,   408,   242,     0,   342,   211,
       0,     0,   383,     0,     0,     0,   385,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   333,     0,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,     0,   265,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   153,
     155,     0,     0,     0,   134,     0,   126,   128,   130,   132,
       0,   119,     0,   121,     0,   123,     0,     0,   326,   202,
     352,     0,     0,     0,     0,     0,   345,     0,   256,    19,
       0,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   298,     0,   316,   315,   286,     0,     0,   263,
       0,   188,     0,     0,   264,   268,     0,     0,   291,     0,
     190,     0,   298,   196,     0,   195,   166,     0,   146,   367,
     368,   369,   371,     0,     0,   117,     0,   116,     0,   115,
       0,     0,   243,   244,   247,   251,   241,     0,   312,   215,
     216,     0,   220,   219,   221,   222,   223,     0,     0,     0,
     227,   228,     0,   230,   213,   217,   313,   214,     0,   258,
     384,   386,     0,   391,     0,   387,     0,   337,   389,   388,
       0,     0,     0,   282,   317,     0,     0,     0,     0,     0,
       0,   199,   200,     0,     0,     0,   177,     0,     0,     0,
       0,     0,   146,   135,   120,   122,   124,   277,     0,     0,
     218,     0,     0,     0,     0,    20,     0,     0,   339,     0,
       0,   302,   303,   304,   299,   300,   284,     0,     0,   183,
       0,   298,   292,   175,   185,     0,     0,   191,   278,     0,
     150,   145,   147,     0,   314,   224,   225,   226,   232,   231,
     229,   392,     0,   393,   362,     0,     0,   285,   283,     0,
       0,     0,   179,     0,   178,   148,    27,     0,     0,     0,
       0,     0,   334,   301,     0,   419,   187,     0,   189,    27,
     151,     0,   233,   394,    16,     0,   418,   180,   149,     0,
       0,     0,    17,    21,    22,    19,     0,     0,    14,    18,
     395
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -684,  -684,  1016,  -684,  -684,  -684,  -684,  -684,  -684,   138,
    -684,  -684,   817,   -89,  -316,   665,   846,   969,  -407,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,   976,  -684,  -684,  -684,   234,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,   610,   860,  -684,  -684,  -684,  -684,   564,  -684,  -684,
    -684,   253,  -684,  -684,  -684,  -544,   247,  -684,   331,   215,
    -684,  -684,  -684,  -684,  -684,   178,  -684,  -684,   888,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,   410,  -683,   195,  -684,  -386,  -517,  -684,
    -684,  -684,   366,   677,  -179,  -143,  -319,   577,   268,  -325,
    -413,  -535,  -425,  -529,   591,  -525,  -146,   -61,  -684,   397,
    -684,  -684,   602,  -684,  -684,   780,  -153,   569,  -417,  -684,
    -684,  -684,  -684,  -684,  -156,  -684
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     3,     4,     5,     6,   209,    87,   861,   887,   759,
     885,    12,   146,    88,   362,    89,    90,    91,    92,   189,
      93,    94,   660,   662,   664,   447,   448,   449,   450,    95,
     433,   723,    96,    97,   413,    98,    99,   190,   651,   791,
     792,   869,   856,   100,   549,   101,   102,   206,   103,   546,
     104,   360,   105,   318,   426,   542,   106,   107,   108,   109,
     110,   299,   290,   111,   826,   112,   867,   376,   524,   540,
     703,   712,   113,   317,   714,   492,   783,   114,   228,   474,
     115,   383,   247,   609,   754,   840,   116,   380,   237,   379,
     603,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   639,   127,   128,   129,   130,   131,   132,   133,   465,
     134,   135,   136,   137,   138,   816,   848,   139,   140,   141,
     142,   143,   252,   291,   773,   814,   815,   255,   511,   515,
     755,   696,   516,   214,   296,   271,   230,   370,   277,   278,
     501,   502,   248,   249,   238,   239,   339,   297,   721,   554,
     555,   556,   341,   342,   343,   272,   400,   201,   313,   606,
     357,   358,   359,   537,   284,   285
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     203,   215,   425,   533,   273,   200,   229,   322,   635,   293,
     294,   295,   256,   257,   544,   545,   279,   280,   283,   302,
     303,   304,   305,   306,   307,   308,   553,   452,   301,   786,
     319,   573,   195,   451,   231,   522,   195,   372,   541,   665,
      16,   281,   250,   663,   575,   661,   309,   538,   325,   701,
     310,   311,   710,   220,   221,   781,   195,   288,   355,   551,
       7,   353,   220,   221,   480,   463,   496,   483,   838,   195,
     681,     8,   344,   329,   345,   315,   195,   309,   346,   347,
     348,   310,   311,   274,   207,   253,   562,   211,   231,   883,
     254,   220,   221,   563,   232,   496,   220,   221,   212,   213,
       9,   715,   839,   564,   566,   698,   275,   276,   668,   300,
     565,   567,   523,    11,   782,   220,   221,   391,   392,   224,
     394,     1,     2,   509,   539,   251,   702,   510,   446,   711,
     225,   496,   329,   316,   349,   330,   312,   292,   852,   225,
     289,   340,   211,   356,   208,   431,    13,   884,   232,   730,
      14,   226,   227,   212,   213,   258,   259,   260,   261,   262,
      15,   263,   224,   264,   265,   266,   267,   268,   351,   766,
     145,   233,   196,   269,   211,   570,    66,   234,   211,   350,
     147,   224,   298,   197,   198,   212,   213,   197,   198,   212,
     213,   231,   351,   796,   226,   227,   352,   795,   211,   794,
     235,   236,   464,   543,   270,   196,   453,   197,   198,   212,
     213,   186,   196,   226,   227,   275,   276,   144,   469,   199,
     197,   198,   547,   199,   678,   233,   691,   197,   198,   668,
     648,   234,   543,   486,   717,   148,   574,   656,   241,   530,
     493,   484,   485,   199,   503,   657,   553,   241,   506,   241,
     736,   232,   494,   495,   521,   149,   199,   499,   500,   527,
     528,   529,   430,   199,   196,   535,   799,   536,   543,   628,
     436,   437,   459,   438,   439,   440,   441,   442,   534,   197,
     198,   336,   337,   338,   587,   789,   552,   790,   588,   589,
     330,   454,   560,   499,   500,   568,   192,   435,   242,   694,
     281,   724,   569,   460,   726,   202,   695,   242,   725,   242,
     150,   727,   471,   860,   204,   199,   -15,   478,   151,   220,
     221,   482,   152,   334,   335,   336,   337,   338,   233,   548,
     716,   811,   812,   813,   234,   153,   604,   154,   590,   591,
     592,   155,   508,   220,   221,   156,   612,   613,   334,   335,
     336,   337,   338,   593,   879,   496,   728,   235,   236,   497,
     220,   221,   157,   729,   222,   223,   158,   594,   595,   336,
     337,   338,   829,   472,   473,   243,   596,   597,   598,   599,
     600,   244,   340,   557,   243,   224,   243,   159,   572,   160,
     244,   161,   244,   601,   162,   602,   282,   491,   713,   421,
     309,   210,   245,   246,   310,   311,   163,   793,   164,   224,
     165,   245,   246,   719,   720,   220,   221,   226,   227,   298,
     225,   512,   659,   513,   514,   166,   224,   222,   223,   167,
     286,   287,   334,   335,   336,   337,   338,   225,   323,   168,
     169,   226,   227,   170,   324,   171,   620,   372,   216,   217,
     218,   219,   320,   334,   335,   336,   337,   338,   226,   227,
     172,   706,   682,   173,   332,   174,   685,   175,   176,   688,
     689,   199,   354,   177,   258,   259,   260,   261,   262,   764,
     263,   224,   264,   265,   266,   267,   268,   178,   650,   333,
     179,   327,   498,   733,   734,   735,   708,   558,   180,   328,
     847,   181,   183,   184,   185,   658,   220,   221,   191,   193,
     854,   194,   205,   226,   227,   326,   331,   499,   500,   220,
     221,   361,   364,   270,   366,   732,   389,   390,   365,   367,
     368,   757,   369,   334,   335,   336,   337,   338,   334,   335,
     336,   337,   338,   371,   372,   374,   334,   335,   336,   337,
     338,   877,   762,   373,   375,   763,   683,   684,   377,   378,
     687,   381,   382,  -209,   384,   258,   259,   260,   261,   262,
     385,   263,   224,   264,   265,   266,   267,   268,   258,   259,
     260,   261,   262,   269,   263,   224,   264,   265,   266,   267,
     268,   386,   387,   388,   401,   800,   269,   393,   395,   396,
     397,   822,   399,   402,   226,   227,   334,   335,   336,   337,
     338,   403,   404,   405,   270,   406,   407,   226,   227,   760,
     408,   409,   835,   836,   837,   412,   410,   270,   411,   770,
     842,   414,    16,   843,   334,   335,   336,   337,   338,   415,
      17,   577,   416,    18,    19,    20,    21,    22,    23,    24,
      25,    26,   417,   418,   419,    27,    28,    29,   420,   422,
     423,    30,    31,    32,    33,    34,    35,    36,    37,    38,
     424,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,   583,    50,   334,   335,   336,   337,   338,   427,
     334,   335,   336,   337,   338,   428,   429,   432,    51,   462,
     443,   434,   445,   807,   586,    52,    53,   455,    54,   608,
      55,    56,    57,   444,   456,    58,    59,   457,    60,   466,
      61,   334,   809,   336,   337,   338,   467,   468,   470,   475,
     476,   334,   335,   336,   337,   338,   477,   882,   479,   481,
      62,   487,    63,   889,   488,    64,    65,   504,   844,   491,
     220,   221,   626,   334,   335,   336,   337,   338,   334,   335,
     336,   337,   338,   489,   505,   517,   490,   870,    66,   507,
     518,   519,   520,   525,    67,    68,   526,   531,  -165,   767,
     878,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,   550,
     561,   334,   335,   336,   337,   338,   576,   578,   579,   258,
     259,   260,   261,   262,   581,   263,   224,   264,   265,   266,
     267,   268,   582,   737,   738,   616,   585,   269,   334,   335,
     336,   337,   338,   610,   739,   740,   741,   607,   611,   614,
     615,   617,   618,   619,   622,   623,   625,   624,   226,   227,
     621,   627,   628,   629,   631,   630,   632,   742,   270,   743,
     744,   745,   746,   747,   748,   749,   750,   751,   752,   753,
      68,   633,   634,   636,   637,   638,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,   640,   641,   643,   642,   644,   645,
     646,   620,   652,   647,   211,   653,   655,   667,   274,   649,
     654,   187,   666,   668,   670,   212,   213,    69,   669,    71,
      70,    73,    72,    75,    74,    77,    76,    79,    78,    81,
      80,    83,    82,    85,    84,   671,    86,   672,   673,   674,
     675,   677,   679,   676,   680,   491,   686,   690,   691,   693,
     697,   699,   700,   698,   707,   704,   705,   718,   709,   731,
     758,   771,   776,   777,   761,   765,   768,   769,   772,   775,
     774,   784,   779,   780,   785,   787,   788,   797,   798,   801,
     802,   805,   803,   804,   806,   810,   808,   817,   828,   818,
     819,   820,   834,   823,   825,   824,   830,   833,   845,   841,
     831,   846,   849,   850,   853,   855,   857,   859,   864,   862,
     858,   865,   866,   868,   871,   873,   875,   874,   876,   890,
     880,    10,   881,   888,   886,   458,   832,   363,   188,   182,
     532,   321,   821,   778,   827,   851,   872,   692,   584,   240,
     314,   863,   461,   756,   580,   559,   571,   398,   605,     0,
     722
};

static const yytype_int16 yycheck[] =
{
      89,   147,   318,   420,   157,    66,   149,   186,   525,   165,
     166,   167,   155,   156,   427,   428,   159,   160,   161,   172,
     173,   174,   175,   176,   177,   178,   433,   352,   171,   712,
     183,   456,     4,   352,     3,    63,     4,     4,   424,   574,
       6,    44,    63,   572,   457,   570,     4,    63,   191,    63,
       8,     9,    63,    63,    64,     4,     4,    63,   204,    63,
     139,   204,    63,    64,   380,     3,     3,   383,   112,     4,
     614,   139,    20,     8,    22,     5,     4,     4,    26,    27,
      28,     8,     9,   140,     3,    58,   138,   146,     3,     5,
      63,    63,    64,   145,    63,     3,    63,    64,   157,   158,
       0,   645,   146,   138,   138,   138,   163,   164,   141,   170,
     145,   145,   140,    74,    63,    63,    64,   260,   261,   129,
     263,    15,    16,    59,   140,   146,   140,    63,     4,   140,
     140,     3,     8,    63,    82,   196,    63,   140,   821,   140,
     146,   202,   146,   204,    63,   324,   146,    63,    63,   666,
     146,   161,   162,   157,   158,   122,   123,   124,   125,   126,
     139,   128,   129,   130,   131,   132,   133,   134,   140,   686,
      75,   140,   140,   140,   146,   144,   142,   146,   146,   127,
     139,   129,   140,   155,   156,   157,   158,   155,   156,   157,
     158,     3,   140,   728,   161,   162,   144,   726,   146,   724,
     169,   170,   140,   140,   171,   140,   352,   155,   156,   157,
     158,   142,   140,   161,   162,   163,   164,   138,   371,   191,
     155,   156,    91,   191,   610,   140,   138,   155,   156,   141,
     546,   146,   140,   386,   647,   139,   144,   562,     3,   418,
     393,   384,   385,   191,   397,   564,   653,     3,   401,     3,
     675,    63,   395,   396,   410,   139,   191,   165,   166,   415,
     416,   417,   323,   191,   140,    61,   139,    63,   140,   142,
     331,   332,   361,   334,   335,   336,   337,   338,   421,   155,
     156,   194,   195,   196,     4,    93,   432,    95,     8,     9,
     351,   352,   445,   165,   166,   138,   148,   141,    63,    63,
      44,   138,   145,   364,   138,   140,    70,    63,   145,    63,
     139,   145,   373,   138,   197,   191,   141,   378,   139,    63,
      64,   382,   139,   192,   193,   194,   195,   196,   140,   198,
     646,    32,    33,    34,   146,   139,   479,   139,    58,    59,
      60,   139,   403,    63,    64,   139,   489,   490,   192,   193,
     194,   195,   196,    73,   871,     3,   138,   169,   170,     7,
      63,    64,   139,   145,    67,    68,   139,    87,    88,   194,
     195,   196,   789,    68,    69,   140,    96,    97,    98,    99,
     100,   146,   443,   143,   140,   129,   140,   139,   144,   139,
     146,   139,   146,   113,   139,   115,   140,    62,    63,   138,
       4,   138,   167,   168,     8,     9,   139,   723,   139,   129,
     139,   167,   168,   151,   152,    63,    64,   161,   162,   140,
     140,    63,   568,    65,    66,   139,   129,    67,    68,   139,
     162,   163,   192,   193,   194,   195,   196,   140,   197,   139,
     139,   161,   162,   139,   142,   139,     3,     4,    10,    11,
      12,    13,   184,   192,   193,   194,   195,   196,   161,   162,
     139,   640,   615,   139,   118,   139,   619,   139,   139,   622,
     623,   191,   204,   139,   122,   123,   124,   125,   126,   138,
     128,   129,   130,   131,   132,   133,   134,   139,   549,   143,
     139,     4,   140,   672,   673,   674,   642,   143,   139,     4,
     816,   139,   139,   139,   139,   566,    63,    64,   139,   139,
     826,   139,   139,   161,   162,   140,   142,   165,   166,    63,
      64,   144,   142,   171,   138,   671,   258,   259,   198,   138,
     138,   677,   137,   192,   193,   194,   195,   196,   192,   193,
     194,   195,   196,   140,     4,   138,   192,   193,   194,   195,
     196,   867,   138,   142,   138,   141,   617,   618,     3,   142,
     621,     3,   142,   144,   138,   122,   123,   124,   125,   126,
     138,   128,   129,   130,   131,   132,   133,   134,   122,   123,
     124,   125,   126,   140,   128,   129,   130,   131,   132,   133,
     134,   138,   138,   138,   200,   741,   140,   140,   140,   140,
     140,   780,   140,     4,   161,   162,   192,   193,   194,   195,
     196,   142,   138,   138,   171,   138,   140,   161,   162,   680,
       4,   138,   801,   802,   803,     6,   138,   171,   138,   690,
     138,     4,     6,   141,   192,   193,   194,   195,   196,   138,
      14,   143,   138,    17,    18,    19,    20,    21,    22,    23,
      24,    25,   138,   138,     4,    29,    30,    31,   138,   138,
     138,    35,    36,    37,    38,    39,    40,    41,    42,    43,
     138,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,   143,    57,   192,   193,   194,   195,   196,   138,
     192,   193,   194,   195,   196,   138,   143,   138,    72,     3,
     138,   141,   139,   764,   143,    79,    80,   139,    82,   143,
      84,    85,    86,   141,   139,    89,    90,   139,    92,     3,
      94,   192,   193,   194,   195,   196,   138,   143,   138,     5,
     147,   192,   193,   194,   195,   196,   138,   880,   138,   138,
     114,    62,   116,   886,    62,   119,   120,   135,   809,    62,
      63,    64,   143,   192,   193,   194,   195,   196,   192,   193,
     194,   195,   196,   138,   141,    71,   138,   856,   142,   138,
       4,   138,    71,   138,   148,   149,   138,   138,    81,   143,
     869,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   143,
     138,   192,   193,   194,   195,   196,   145,     3,   138,   122,
     123,   124,   125,   126,   141,   128,   129,   130,   131,   132,
     133,   134,     4,    65,    66,   141,   146,   140,   192,   193,
     194,   195,   196,   138,    76,    77,    78,   146,   138,   199,
     138,   138,   138,   138,   138,   138,     4,   138,   161,   162,
     142,   138,   142,   138,     4,   138,   138,    99,   171,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     149,     4,   138,     4,   138,   138,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   138,    62,     4,   138,   138,   138,
      81,     3,   139,   138,   146,   138,     4,     3,   140,   198,
     141,   149,   138,   141,   141,   157,   158,   155,   147,   157,
     156,   159,   158,   161,   160,   163,   162,   165,   164,   167,
     166,   169,   168,   171,   170,   139,   172,   139,   139,   139,
     139,   138,     5,   141,   138,    62,   138,   140,   138,     4,
       4,    71,   138,   138,   138,   146,    71,   144,   138,   138,
     138,     4,     4,     4,   141,   141,   141,   141,   138,   138,
     143,     4,   138,   138,     4,   138,   138,   141,     5,   139,
     139,     3,   139,   139,    32,   138,   141,     4,     7,   138,
     141,   138,    63,   141,   138,   141,   139,   138,     4,   141,
     145,   138,   138,     4,     4,   139,     5,    32,     4,   141,
     199,   141,   141,   141,   138,   141,   141,   136,   141,   141,
     138,     5,   138,   885,   138,   360,   792,   210,    59,    53,
     420,   185,   779,   702,   787,   820,   858,   627,   474,   151,
     180,   846,   365,   677,   467,   443,   455,   267,   479,    -1,
     653
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,    15,    16,   202,   203,   204,   205,   139,   139,     0,
     203,    74,   212,   146,   146,   139,     6,    14,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    29,    30,    31,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      57,    72,    79,    80,    82,    84,    85,    86,    89,    90,
      92,    94,   114,   116,   119,   120,   142,   148,   149,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   207,   214,   216,
     217,   218,   219,   221,   222,   230,   233,   234,   236,   237,
     244,   246,   247,   249,   251,   253,   257,   258,   259,   260,
     261,   264,   266,   273,   278,   281,   287,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   303,   304,   305,
     306,   307,   308,   309,   311,   312,   313,   314,   315,   318,
     319,   320,   321,   322,   138,    75,   213,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   236,   139,   139,   139,   142,   149,   218,   220,
     238,   139,   148,   139,   139,     4,   140,   155,   156,   191,
     348,   358,   140,   214,   197,   139,   248,     3,    63,   206,
     138,   146,   157,   158,   334,   347,    10,    11,    12,    13,
      63,    64,    67,    68,   129,   140,   161,   162,   279,   336,
     337,     3,    63,   140,   146,   169,   170,   289,   345,   346,
     289,     3,    63,   140,   146,   167,   168,   283,   343,   344,
      63,   146,   323,    58,    63,   328,   336,   336,   122,   123,
     124,   125,   126,   128,   130,   131,   132,   133,   134,   140,
     171,   336,   356,   357,   140,   163,   164,   339,   340,   336,
     336,    44,   140,   336,   365,   366,   339,   339,    63,   146,
     263,   324,   140,   365,   365,   365,   335,   348,   140,   262,
     348,   336,   357,   357,   357,   357,   357,   357,   357,     4,
       8,     9,    63,   359,   263,     5,    63,   274,   254,   357,
     339,   217,   335,   197,   142,   336,   140,     4,     4,     8,
     348,   142,   118,   143,   192,   193,   194,   195,   196,   347,
     348,   353,   354,   355,    20,    22,    26,    27,    28,    82,
     127,   140,   144,   336,   339,   347,   348,   361,   362,   363,
     252,   144,   215,   213,   142,   198,   138,   138,   138,   137,
     338,   140,     4,   142,   138,   138,   268,     3,   142,   290,
     288,     3,   142,   282,   138,   138,   138,   138,   138,   339,
     339,   336,   336,   140,   336,   140,   140,   140,   356,   140,
     357,   200,     4,   142,   138,   138,   138,   140,     4,   138,
     138,   138,     6,   235,     4,   138,   138,   138,   138,     4,
     138,   138,   138,   138,   138,   215,   255,   138,   138,   143,
     348,   335,   138,   231,   141,   141,   348,   348,   348,   348,
     348,   348,   348,   138,   141,   139,     4,   226,   227,   228,
     229,   337,   340,   347,   348,   139,   139,   139,   216,   214,
     348,   334,     3,     3,   140,   310,     3,   138,   143,   357,
     138,   348,    68,    69,   280,     5,   147,   138,   348,   138,
     215,   138,   348,   215,   336,   336,   357,    62,    62,   138,
     138,    62,   276,   357,   336,   336,     3,     7,   140,   165,
     166,   341,   342,   357,   135,   141,   357,   138,   348,    59,
      63,   329,    63,    65,    66,   330,   333,    71,     4,   138,
      71,   365,    63,   140,   269,   138,   138,   365,   365,   365,
     335,   138,   262,   359,   336,    61,    63,   364,    63,   140,
     270,   328,   256,   140,   341,   341,   250,    91,   198,   245,
     143,    63,   347,   219,   350,   351,   352,   143,   143,   353,
     357,   138,   138,   145,   138,   145,   138,   145,   138,   145,
     144,   345,   144,   343,   144,   341,   145,   143,     3,   138,
     338,   141,     4,   143,   268,   146,   143,     4,     8,     9,
      58,    59,    60,    73,    87,    88,    96,    97,    98,    99,
     100,   113,   115,   291,   336,   358,   360,   146,   143,   284,
     138,   138,   336,   336,   199,   138,   141,   138,   138,   138,
       3,   142,   138,   138,   138,     4,   143,   138,   142,   138,
     138,     4,   138,     4,   138,   329,     4,   138,   138,   302,
     138,    62,   138,     4,   138,   138,    81,   138,   215,   198,
     348,   239,   139,   138,   141,     4,   340,   337,   348,   347,
     223,   346,   224,   344,   225,   342,   138,     3,   141,   147,
     141,   139,   139,   139,   139,   139,   141,   138,   328,     5,
     138,   276,   357,   348,   348,   357,   138,   348,   357,   357,
     140,   138,   324,     4,    63,    70,   332,     4,   138,    71,
     138,    63,   140,   271,   146,    71,   335,   138,   347,   138,
      63,   140,   272,    63,   275,   276,   215,   341,   144,   151,
     152,   349,   350,   232,   138,   145,   138,   145,   138,   145,
     329,   138,   347,   335,   335,   335,   343,    65,    66,    76,
      77,    78,    99,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   285,   331,   333,   347,   138,   210,
     348,   141,   138,   141,   138,   141,   329,   143,   141,   141,
     348,     4,   138,   325,   143,   138,     4,     4,   279,   138,
     138,     4,    63,   277,     4,     4,   325,   138,   138,    93,
      95,   240,   241,   215,   346,   344,   342,   141,     5,   139,
     347,   139,   139,   139,   139,     3,    32,   348,   141,   193,
     138,    32,    33,    34,   326,   327,   316,     4,   138,   141,
     138,   272,   335,   141,   141,   138,   265,   277,     7,   359,
     139,   145,   240,   138,    63,   335,   335,   335,   112,   146,
     286,   141,   138,   141,   348,     4,   138,   215,   317,   138,
       4,   280,   325,     4,   215,   139,   243,     5,   199,    32,
     138,   208,   141,   326,     4,   141,   141,   267,   141,   242,
     214,   138,   286,   141,   136,   141,   141,   215,   214,   329,
     138,   138,   336,     5,    63,   211,   138,   209,   210,   336,
     141
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   201,   202,   202,   203,   203,   204,   205,   205,   206,
     206,   207,   207,   207,   207,   208,   208,   209,   209,   210,
     210,   211,   211,   212,   212,   213,   213,   214,   214,   215,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   219,   219,
     219,   220,   220,   221,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   223,
     223,   224,   224,   225,   225,   226,   226,   227,   227,   228,
     228,   229,   229,   231,   232,   230,   233,   234,   235,   235,
     236,   236,   236,   238,   239,   237,   240,   240,   242,   241,
     243,   241,   244,   245,   245,   246,   248,   247,   250,   249,
     252,   251,   254,   253,   255,   256,   255,   257,   258,   259,
     260,   260,   260,   261,   261,   262,   263,   265,   264,   267,
     266,   268,   268,   269,   269,   270,   270,   271,   271,   272,
     272,   273,   273,   274,   274,   275,   275,   276,   276,   277,
     277,   278,   278,   278,   279,   279,   280,   280,   281,   282,
     281,   283,   284,   284,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   286,   286,   286,   287,   288,   287,   289,   290,   290,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   292,   293,   294,   294,   295,
     295,   296,   297,   298,   299,   300,   301,   302,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   310,   311,   312,
     313,   314,   316,   315,   317,   317,   318,   319,   319,   319,
     320,   321,   322,   322,   323,   323,   324,   324,   325,   325,
     326,   326,   327,   327,   327,   328,   328,   329,   329,   330,
     330,   330,   331,   331,   331,   332,   332,   333,   334,   334,
     334,   335,   336,   336,   336,   336,   337,   337,   337,   338,
     338,   339,   339,   339,   340,   341,   341,   341,   342,   342,
     343,   343,   343,   344,   344,   344,   344,   345,   345,   345,
     346,   346,   346,   346,   347,   347,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   349,   349,   350,
     351,   351,   352,   352,   353,   353,   354,   354,   355,   355,
     356,   356,   356,   356,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   356,   356,   356,   356,   357,
     357,   358,   359,   359,   359,   360,   360,   360,   360,   361,
     361,   362,   362,   363,   363,   364,   364,   365,   365,   366
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     3,     3,     5,     1,
       1,     5,     5,     3,    16,     0,     2,     0,     2,     0,
       2,     1,     1,     0,     3,     3,     1,     0,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     5,     3,     5,     5,     5,
       3,     3,     5,     5,     5,     7,     7,     7,     5,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     0,     0,     8,     4,     1,     0,     1,
       1,     5,     3,     0,     0,     9,     0,     2,     0,     5,
       0,     4,     1,     2,     1,     6,     0,     3,     0,     6,
       0,     4,     0,     4,     1,     0,     4,     3,     3,     3,
       1,     3,     3,     5,     5,     7,     4,     0,    10,     0,
      12,     0,     2,     5,     1,     5,     1,     5,     1,     5,
       1,     9,     5,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     7,     5,     1,     1,     1,     1,     3,     0,
       5,     4,     0,     3,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     1,     3,
       1,     1,     1,     3,     3,     0,     5,     2,     0,     3,
       1,     3,     1,     3,     3,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     5,     7,     5,     8,     1,
       3,     5,     5,     7,     7,     6,     5,     0,     2,     3,
       3,     3,     3,     3,     3,     3,     1,     5,     9,     5,
       3,     3,     0,    10,     0,     1,     7,     5,     5,     3,
       5,     7,     9,     1,     1,     1,     1,     1,     0,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     4,     1,     1,
       4,     1,     1,     4,     1,     4,     5,     1,     3,     1,
       3,     1,     1,     4,     9,     1,     1,     4,     1,     5,
       1,     1,     4,     1,     1,     5,     1,     1,     1,     4,
       1,     1,     5,     1,     1,     3,     1,     1,     3,     1,
       4,     3,     3,     3,     3,     3,     3,     1,     1,     3,
       1,     3,     0,     1,     1,     1,     1,     3,     0,     1,
       1,     2,     2,     4,     6,     4,     6,     6,     6,     6,
       2,     6,     8,     8,    10,    14,     2,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,    10,     9
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 6: /* level: level_def flags levstatements  */
#line 295 "lev_comp.y"
                  {
			if (fatal_error > 0) {
				(void) fprintf(stderr,
              "%s: %d errors detected for level \"%s\". No output created!\n",
					       fname, fatal_error, (yyvsp[-2].map));
				fatal_error = 0;
				got_errors++;
			} else if (!got_errors) {
				if (!write_level_file((yyvsp[-2].map), splev)) {
                                    lc_error("Can't write output file for '%s'!",
                                             (yyvsp[-2].map));
				    exit(EXIT_FAILURE);
				}
			}
			Free((yyvsp[-2].map));
			Free(splev);
			splev = NULL;
			vardef_free_all(vardefs);
			vardefs = NULL;
		  }
#line 2309 "lev_comp.y.c"
    break;

  case 7: /* level_def: LEVEL_ID ':' STRING  */
#line 318 "lev_comp.y"
                  {
		      start_level_def(&splev, (yyvsp[0].map));
                      rnd_vault_freq = 1;
                      rnd_vault_mindepth = 0;
                      is_rnd_vault = 0;
		      (yyval.map) = (yyvsp[0].map);
		  }
#line 2321 "lev_comp.y.c"
    break;

  case 8: /* level_def: MAZE_ID ':' STRING ',' mazefiller  */
#line 326 "lev_comp.y"
                  {
		      start_level_def(&splev, (yyvsp[-2].map));
		      if ((yyvsp[0].i) == -1) {
			  add_opvars(splev, "iiiiiiiio",
				     VA_PASS9(LVLINIT_MAZEGRID, HWALL, 0,0,
					      0,0,0,0, SPO_INITLEVEL));
		      } else {
			  int bg = (int) what_map_char((char) (yyvsp[0].i));

			  add_opvars(splev, "iiiiiiiio",
				     VA_PASS9(LVLINIT_SOLIDFILL, bg, 0,0,
					      0,0,0,0, SPO_INITLEVEL));
		      }
		      add_opvars(splev, "io",
				 VA_PASS2(MAZELEVEL, SPO_LEVEL_FLAGS));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;

		      (yyval.map) = (yyvsp[-2].map);
		  }
#line 2346 "lev_comp.y.c"
    break;

  case 9: /* mazefiller: RANDOM_TYPE  */
#line 349 "lev_comp.y"
                  {
		      (yyval.i) = -1;
		  }
#line 2354 "lev_comp.y.c"
    break;

  case 10: /* mazefiller: CHAR  */
#line 353 "lev_comp.y"
                  {
		      (yyval.i) = what_map_char((char) (yyvsp[0].i));
		  }
#line 2362 "lev_comp.y.c"
    break;

  case 11: /* lev_init: LEV_INIT_ID ':' SOLID_FILL_ID ',' terrain_type  */
#line 359 "lev_comp.y"
                  {
		      int filling = (int) (yyvsp[0].terr).ter;

		      if (filling == INVALID_TYPE || filling >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid fill char type.");
		      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_SOLIDFILL, filling,
                                          0, (int) (yyvsp[0].terr).lit,
                                          0,0,0,0, SPO_INITLEVEL));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  }
#line 2379 "lev_comp.y.c"
    break;

  case 12: /* lev_init: LEV_INIT_ID ':' MAZE_GRID_ID ',' CHAR  */
#line 372 "lev_comp.y"
                  {
		      int filling = (int) what_map_char((char) (yyvsp[0].i));

		      if (filling == INVALID_TYPE || filling >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid fill char type.");
                      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_MAZEGRID, filling, 0,0,
					  0,0,0,0, SPO_INITLEVEL));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  }
#line 2395 "lev_comp.y.c"
    break;

  case 13: /* lev_init: LEV_INIT_ID ':' ROGUELEV_ID  */
#line 384 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_ROGUE,0,0,0,
					  0,0,0,0, SPO_INITLEVEL));
		  }
#line 2405 "lev_comp.y.c"
    break;

  case 14: /* lev_init: LEV_INIT_ID ':' MINES_ID ',' CHAR ',' CHAR ',' BOOLEAN ',' BOOLEAN ',' light_state ',' walled opt_fillchar  */
#line 390 "lev_comp.y"
                  {
                      int fg = (int) what_map_char((char) (yyvsp[-11].i)),
                          bg = (int) what_map_char((char) (yyvsp[-9].i));
                      int smoothed = (int) (yyvsp[-7].i),
                          joined = (int) (yyvsp[-5].i),
                          lit = (int) (yyvsp[-3].i),
                          walled = (int) (yyvsp[-1].i),
                          filling = (int) (yyvsp[0].i);

		      if (fg == INVALID_TYPE || fg >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid foreground type.");
		      if (bg == INVALID_TYPE || bg >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid background type.");
		      if (joined && fg != CORR && fg != ROOM && fg != PUDDLE
			  && fg != SEWAGE && fg != GRASS && fg != SAND)
			  lc_error("INIT_MAP: Invalid foreground type for joined map.");

		      if (filling == INVALID_TYPE)
			  lc_error("INIT_MAP: Invalid fill char type.");

		      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_MINES, filling, walled, lit,
					  joined, smoothed, bg, fg,
					  SPO_INITLEVEL));
			max_x_map = COLNO-1;
			max_y_map = ROWNO;
		  }
#line 2437 "lev_comp.y.c"
    break;

  case 15: /* opt_limited: %empty  */
#line 420 "lev_comp.y"
                  {
		      (yyval.i) = 0;
		  }
#line 2445 "lev_comp.y.c"
    break;

  case 16: /* opt_limited: ',' LIMITED  */
#line 424 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[0].i);
		  }
#line 2453 "lev_comp.y.c"
    break;

  case 17: /* opt_coord_or_var: %empty  */
#line 430 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_COPY));
		      (yyval.i) = 0;
		  }
#line 2462 "lev_comp.y.c"
    break;

  case 18: /* opt_coord_or_var: ',' coord_or_var  */
#line 435 "lev_comp.y"
                  {
		      (yyval.i) = 1;
		  }
#line 2470 "lev_comp.y.c"
    break;

  case 19: /* opt_fillchar: %empty  */
#line 441 "lev_comp.y"
                  {
		      (yyval.i) = -1;
		  }
#line 2478 "lev_comp.y.c"
    break;

  case 20: /* opt_fillchar: ',' CHAR  */
#line 445 "lev_comp.y"
                  {
		      (yyval.i) = what_map_char((char) (yyvsp[0].i));
		  }
#line 2486 "lev_comp.y.c"
    break;

  case 23: /* flags: %empty  */
#line 456 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(0, SPO_LEVEL_FLAGS));
		  }
#line 2494 "lev_comp.y.c"
    break;

  case 24: /* flags: FLAGS_ID ':' flag_list  */
#line 460 "lev_comp.y"
                  {
		      if ((yyvsp[0].i) & FLAG_RNDVAULT) {
			  is_rnd_vault = 1;
		      }
		      add_opvars(splev, "io",
                                 VA_PASS2((int) (yyvsp[0].i), SPO_LEVEL_FLAGS));
		  }
#line 2506 "lev_comp.y.c"
    break;

  case 25: /* flag_list: FLAG_TYPE ',' flag_list  */
#line 470 "lev_comp.y"
                  {
		      (yyval.i) = ((yyvsp[-2].i) | (yyvsp[0].i));
		  }
#line 2514 "lev_comp.y.c"
    break;

  case 26: /* flag_list: FLAG_TYPE  */
#line 474 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[0].i);
		  }
#line 2522 "lev_comp.y.c"
    break;

  case 27: /* levstatements: %empty  */
#line 480 "lev_comp.y"
                  {
		      (yyval.i) = 0;
		  }
#line 2530 "lev_comp.y.c"
    break;

  case 28: /* levstatements: levstatement levstatements  */
#line 484 "lev_comp.y"
                  {
		      (yyval.i) = 1 + (yyvsp[0].i);
		  }
#line 2538 "lev_comp.y.c"
    break;

  case 29: /* stmt_block: '{' levstatements '}'  */
#line 490 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[-1].i);
		  }
#line 2546 "lev_comp.y.c"
    break;

  case 103: /* shuffle_detail: SHUFFLE_ID ':' any_var_array  */
#line 579 "lev_comp.y"
                  {
		      struct lc_vardefs *vd;

		      if ((vd = vardef_defined(vardefs, (yyvsp[0].map), 1))) {
			  if (!(vd->var_type & SPOVAR_ARRAY))
			      lc_error("Trying to shuffle non-array variable '%s'",
                                       (yyvsp[0].map));
		      } else
                          lc_error("Trying to shuffle undefined variable '%s'",
                                   (yyvsp[0].map));
		      add_opvars(splev, "so", VA_PASS2((yyvsp[0].map), SPO_SHUFFLE_ARRAY));
		      Free((yyvsp[0].map));
		  }
#line 2564 "lev_comp.y.c"
    break;

  case 104: /* variable_define: any_var_or_arr '=' math_expr_var  */
#line 595 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-2].map), SPOVAR_INT);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-2].map), SPO_VAR_INIT));
		      Free((yyvsp[-2].map));
		  }
#line 2574 "lev_comp.y.c"
    break;

  case 105: /* variable_define: any_var_or_arr '=' selection_ID ':' ter_selection  */
#line 601 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map), SPOVAR_SEL);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2584 "lev_comp.y.c"
    break;

  case 106: /* variable_define: any_var_or_arr '=' string_expr  */
#line 607 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-2].map), SPOVAR_STRING);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-2].map), SPO_VAR_INIT));
		      Free((yyvsp[-2].map));
		  }
#line 2594 "lev_comp.y.c"
    break;

  case 107: /* variable_define: any_var_or_arr '=' terrainid ':' mapchar_or_var  */
#line 613 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map), SPOVAR_MAPCHAR);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2604 "lev_comp.y.c"
    break;

  case 108: /* variable_define: any_var_or_arr '=' monsterid ':' monster_or_var  */
#line 619 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map), SPOVAR_MONST);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2614 "lev_comp.y.c"
    break;

  case 109: /* variable_define: any_var_or_arr '=' objectid ':' object_or_var  */
#line 625 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map), SPOVAR_OBJ);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2624 "lev_comp.y.c"
    break;

  case 110: /* variable_define: any_var_or_arr '=' coord_or_var  */
#line 631 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-2].map), SPOVAR_COORD);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-2].map), SPO_VAR_INIT));
		      Free((yyvsp[-2].map));
		  }
#line 2634 "lev_comp.y.c"
    break;

  case 111: /* variable_define: any_var_or_arr '=' region_or_var  */
#line 637 "lev_comp.y"
                  {
		      vardefs = add_vardef_type(vardefs, (yyvsp[-2].map), SPOVAR_REGION);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-2].map), SPO_VAR_INIT));
		      Free((yyvsp[-2].map));
		  }
#line 2644 "lev_comp.y.c"
    break;

  case 112: /* variable_define: any_var_or_arr '=' '{' integer_list '}'  */
#line 643 "lev_comp.y"
                  {
		      int n_items = (int) (yyvsp[-1].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map),
                                                SPOVAR_INT | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2658 "lev_comp.y.c"
    break;

  case 113: /* variable_define: any_var_or_arr '=' '{' encodecoord_list '}'  */
#line 653 "lev_comp.y"
                  {
		      int n_items = (int) (yyvsp[-1].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map),
                                                SPOVAR_COORD | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2672 "lev_comp.y.c"
    break;

  case 114: /* variable_define: any_var_or_arr '=' '{' encoderegion_list '}'  */
#line 663 "lev_comp.y"
                  {
                      int n_items = (int) (yyvsp[-1].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map),
                                                SPOVAR_REGION | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2686 "lev_comp.y.c"
    break;

  case 115: /* variable_define: any_var_or_arr '=' terrainid ':' '{' mapchar_list '}'  */
#line 673 "lev_comp.y"
                  {
                      int n_items = (int) (yyvsp[-1].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[-6].map),
                                                SPOVAR_MAPCHAR | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[-6].map), SPO_VAR_INIT));
		      Free((yyvsp[-6].map));
		  }
#line 2700 "lev_comp.y.c"
    break;

  case 116: /* variable_define: any_var_or_arr '=' monsterid ':' '{' encodemonster_list '}'  */
#line 683 "lev_comp.y"
                  {
		      int n_items = (int) (yyvsp[-1].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[-6].map),
                                                SPOVAR_MONST | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[-6].map), SPO_VAR_INIT));
		      Free((yyvsp[-6].map));
		  }
#line 2714 "lev_comp.y.c"
    break;

  case 117: /* variable_define: any_var_or_arr '=' objectid ':' '{' encodeobj_list '}'  */
#line 693 "lev_comp.y"
                  {
                      int n_items = (int) (yyvsp[-1].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[-6].map),
                                                SPOVAR_OBJ | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[-6].map), SPO_VAR_INIT));
		      Free((yyvsp[-6].map));
		  }
#line 2728 "lev_comp.y.c"
    break;

  case 118: /* variable_define: any_var_or_arr '=' '{' string_list '}'  */
#line 703 "lev_comp.y"
                  {
                      int n_items = (int) (yyvsp[-1].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map),
                                                SPOVAR_STRING | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[-4].map), SPO_VAR_INIT));
		      Free((yyvsp[-4].map));
		  }
#line 2742 "lev_comp.y.c"
    break;

  case 119: /* encodeobj_list: encodeobj  */
#line 715 "lev_comp.y"
                  {
		      add_opvars(splev, "O", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1;
		  }
#line 2751 "lev_comp.y.c"
    break;

  case 120: /* encodeobj_list: encodeobj_list ',' encodeobj  */
#line 720 "lev_comp.y"
                  {
		      add_opvars(splev, "O", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1 + (yyvsp[-2].i);
		  }
#line 2760 "lev_comp.y.c"
    break;

  case 121: /* encodemonster_list: encodemonster  */
#line 727 "lev_comp.y"
                  {
		      add_opvars(splev, "M", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1;
		  }
#line 2769 "lev_comp.y.c"
    break;

  case 122: /* encodemonster_list: encodemonster_list ',' encodemonster  */
#line 732 "lev_comp.y"
                  {
		      add_opvars(splev, "M", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1 + (yyvsp[-2].i);
		  }
#line 2778 "lev_comp.y.c"
    break;

  case 123: /* mapchar_list: mapchar  */
#line 739 "lev_comp.y"
                  {
		      add_opvars(splev, "m", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1;
		  }
#line 2787 "lev_comp.y.c"
    break;

  case 124: /* mapchar_list: mapchar_list ',' mapchar  */
#line 744 "lev_comp.y"
                  {
		      add_opvars(splev, "m", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1 + (yyvsp[-2].i);
		  }
#line 2796 "lev_comp.y.c"
    break;

  case 125: /* encoderegion_list: encoderegion  */
#line 751 "lev_comp.y"
                  {
		      (yyval.i) = 1;
		  }
#line 2804 "lev_comp.y.c"
    break;

  case 126: /* encoderegion_list: encoderegion_list ',' encoderegion  */
#line 755 "lev_comp.y"
                  {
		      (yyval.i) = 1 + (yyvsp[-2].i);
		  }
#line 2812 "lev_comp.y.c"
    break;

  case 127: /* encodecoord_list: encodecoord  */
#line 761 "lev_comp.y"
                  {
		      add_opvars(splev, "c", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1;
		  }
#line 2821 "lev_comp.y.c"
    break;

  case 128: /* encodecoord_list: encodecoord_list ',' encodecoord  */
#line 766 "lev_comp.y"
                  {
		      add_opvars(splev, "c", VA_PASS1((yyvsp[0].i)));
		      (yyval.i) = 1 + (yyvsp[-2].i);
		  }
#line 2830 "lev_comp.y.c"
    break;

  case 129: /* integer_list: math_expr_var  */
#line 773 "lev_comp.y"
                  {
		      (yyval.i) = 1;
		  }
#line 2838 "lev_comp.y.c"
    break;

  case 130: /* integer_list: integer_list ',' math_expr_var  */
#line 777 "lev_comp.y"
                  {
		      (yyval.i) = 1 + (yyvsp[-2].i);
		  }
#line 2846 "lev_comp.y.c"
    break;

  case 131: /* string_list: string_expr  */
#line 783 "lev_comp.y"
                  {
		      (yyval.i) = 1;
		  }
#line 2854 "lev_comp.y.c"
    break;

  case 132: /* string_list: string_list ',' string_expr  */
#line 787 "lev_comp.y"
                  {
		      (yyval.i) = 1 + (yyvsp[-2].i);
		  }
#line 2862 "lev_comp.y.c"
    break;

  case 133: /* $@1: %empty  */
#line 793 "lev_comp.y"
                  {
		      struct lc_funcdefs *funcdef;

		      if (in_function_definition)
			  lc_error("Recursively defined functions not allowed (function %s).", (yyvsp[-1].map));

		      in_function_definition++;

		      if (funcdef_defined(function_definitions, (yyvsp[-1].map), 1))
			  lc_error("Function '%s' already defined once.", (yyvsp[-1].map));

		      funcdef = funcdef_new(-1, (yyvsp[-1].map));
		      funcdef->next = function_definitions;
		      function_definitions = funcdef;
		      function_splev_backup = splev;
		      splev = &(funcdef->code);
		      Free((yyvsp[-1].map));
		      curr_function = funcdef;
		      function_tmp_var_defs = vardefs;
		      vardefs = NULL;
		  }
#line 2888 "lev_comp.y.c"
    break;

  case 134: /* $@2: %empty  */
#line 815 "lev_comp.y"
                  {
		      /* nothing */
		  }
#line 2896 "lev_comp.y.c"
    break;

  case 135: /* function_define: FUNCTION_ID NQSTRING '(' $@1 func_params_list ')' $@2 stmt_block  */
#line 819 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(0, SPO_RETURN));
		      splev = function_splev_backup;
		      in_function_definition--;
		      curr_function = NULL;
		      vardef_free_all(vardefs);
		      vardefs = function_tmp_var_defs;
		  }
#line 2909 "lev_comp.y.c"
    break;

  case 136: /* function_call: NQSTRING '(' func_call_params_list ')'  */
#line 830 "lev_comp.y"
                  {
		      struct lc_funcdefs *tmpfunc;

		      tmpfunc = funcdef_defined(function_definitions, (yyvsp[-3].map), 1);
		      if (tmpfunc) {
			  int l;
			  int nparams = (int) strlen((yyvsp[-1].map));
			  char *fparamstr = funcdef_paramtypes(tmpfunc);

			  if (strcmp((yyvsp[-1].map), fparamstr)) {
			      char *tmps = strdup(decode_parm_str(fparamstr));

			      lc_error("Function '%s' requires params '%s', got '%s' instead.",
                                       (yyvsp[-3].map), tmps, decode_parm_str((yyvsp[-1].map)));
			      Free(tmps);
			  }
			  Free(fparamstr);
			  Free((yyvsp[-1].map));
			  if (!(tmpfunc->n_called)) {
			      /* we haven't called the function yet, so insert it in the code */
			      struct opvar *jmp = New(struct opvar);

			      set_opvar_int(jmp, splev->n_opcodes+1);
			      add_opcode(splev, SPO_PUSH, jmp);
                              /* we must jump past it first, then CALL it, due to RETURN. */
			      add_opcode(splev, SPO_JMP, NULL);

			      tmpfunc->addr = splev->n_opcodes;

			      { /* init function parameter variables */
				  struct lc_funcdefs_parm *tfp = tmpfunc->params;
				  while (tfp) {
				      add_opvars(splev, "iso",
						 VA_PASS3(0, tfp->name,
							  SPO_VAR_INIT));
				      tfp = tfp->next;
				  }
			      }

			      splev_add_from(splev, &(tmpfunc->code));
			      set_opvar_int(jmp,
                                            splev->n_opcodes - jmp->vardata.l);
			  }
			  l = (int) (tmpfunc->addr - splev->n_opcodes - 2);
			  add_opvars(splev, "iio",
				     VA_PASS3(nparams, l, SPO_CALL));
			  tmpfunc->n_called++;
		      } else {
			  lc_error("Function '%s' not defined.", (yyvsp[-3].map));
		      }
		      Free((yyvsp[-3].map));
		  }
#line 2966 "lev_comp.y.c"
    break;

  case 137: /* exitstatement: EXIT_ID  */
#line 885 "lev_comp.y"
                  {
		      add_opcode(splev, SPO_EXIT, NULL);
		  }
#line 2974 "lev_comp.y.c"
    break;

  case 138: /* opt_percent: %empty  */
#line 891 "lev_comp.y"
                  {
		      (yyval.i) = 100;
		  }
#line 2982 "lev_comp.y.c"
    break;

  case 139: /* opt_percent: PERCENT  */
#line 895 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[0].i);
		  }
#line 2990 "lev_comp.y.c"
    break;

  case 140: /* comparestmt: PERCENT  */
#line 901 "lev_comp.y"
                  {
		      /* val > rn2(100) */
		      add_opvars(splev, "iio",
				 VA_PASS3((int) (yyvsp[0].i), 100, SPO_RN2));
		      (yyval.i) = SPO_JG;
                  }
#line 3001 "lev_comp.y.c"
    break;

  case 141: /* comparestmt: '[' math_expr_var COMPARE_TYPE math_expr_var ']'  */
#line 908 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[-2].i);
                  }
#line 3009 "lev_comp.y.c"
    break;

  case 142: /* comparestmt: '[' math_expr_var ']'  */
#line 912 "lev_comp.y"
                  {
		      /* boolean, explicit foo != 0 */
		      add_opvars(splev, "i", VA_PASS1(0));
		      (yyval.i) = SPO_JNE;
                  }
#line 3019 "lev_comp.y.c"
    break;

  case 143: /* $@3: %empty  */
#line 920 "lev_comp.y"
                  {
		      is_inconstant_number = 0;
		  }
#line 3027 "lev_comp.y.c"
    break;

  case 144: /* $@4: %empty  */
#line 924 "lev_comp.y"
                  {
		      struct opvar *chkjmp;

		      if (in_switch_statement > 0)
			  lc_error("Cannot nest switch-statements.");

		      in_switch_statement++;

		      n_switch_case_list = 0;
		      switch_default_case = NULL;

		      if (!is_inconstant_number)
			  add_opvars(splev, "o", VA_PASS1(SPO_RN2));
		      is_inconstant_number = 0;

		      chkjmp = New(struct opvar);
		      set_opvar_int(chkjmp, splev->n_opcodes+1);
		      switch_check_jump = chkjmp;
		      add_opcode(splev, SPO_PUSH, chkjmp);
		      add_opcode(splev, SPO_JMP, NULL);
		      break_stmt_start();
		  }
#line 3054 "lev_comp.y.c"
    break;

  case 145: /* switchstatement: SWITCH_ID $@3 '[' integer_or_var ']' $@4 '{' switchcases '}'  */
#line 947 "lev_comp.y"
                  {
		      struct opvar *endjump = New(struct opvar);
		      int i;

		      set_opvar_int(endjump, splev->n_opcodes+1);

		      add_opcode(splev, SPO_PUSH, endjump);
		      add_opcode(splev, SPO_JMP, NULL);

		      set_opvar_int(switch_check_jump,
			     splev->n_opcodes - switch_check_jump->vardata.l);

		      for (i = 0; i < n_switch_case_list; i++) {
			  add_opvars(splev, "oio",
				     VA_PASS3(SPO_COPY,
					      switch_case_value[i], SPO_CMP));
			  set_opvar_int(switch_case_list[i],
			 switch_case_list[i]->vardata.l - splev->n_opcodes-1);
			  add_opcode(splev, SPO_PUSH, switch_case_list[i]);
			  add_opcode(splev, SPO_JE, NULL);
		      }

		      if (switch_default_case) {
			  set_opvar_int(switch_default_case,
			 switch_default_case->vardata.l - splev->n_opcodes-1);
			  add_opcode(splev, SPO_PUSH, switch_default_case);
			  add_opcode(splev, SPO_JMP, NULL);
		      }

		      set_opvar_int(endjump, splev->n_opcodes - endjump->vardata.l);

		      break_stmt_end(splev);

		      add_opcode(splev, SPO_POP, NULL); /* get rid of the value in stack */
		      in_switch_statement--;


		  }
#line 3097 "lev_comp.y.c"
    break;

  case 148: /* $@5: %empty  */
#line 992 "lev_comp.y"
                  {
		      if (n_switch_case_list < MAX_SWITCH_CASES) {
			  struct opvar *tmppush = New(struct opvar);

			  set_opvar_int(tmppush, splev->n_opcodes);
			  switch_case_value[n_switch_case_list] = (yyvsp[-1].i);
			  switch_case_list[n_switch_case_list++] = tmppush;
		      } else lc_error("Too many cases in a switch.");
		  }
#line 3111 "lev_comp.y.c"
    break;

  case 149: /* switchcase: CASE_ID all_integers ':' $@5 levstatements  */
#line 1002 "lev_comp.y"
                  {
		  }
#line 3118 "lev_comp.y.c"
    break;

  case 150: /* $@6: %empty  */
#line 1005 "lev_comp.y"
                  {
		      struct opvar *tmppush = New(struct opvar);

		      if (switch_default_case)
			  lc_error("Switch default case already used.");

		      set_opvar_int(tmppush, splev->n_opcodes);
		      switch_default_case = tmppush;
		  }
#line 3132 "lev_comp.y.c"
    break;

  case 151: /* switchcase: DEFAULT_ID ':' $@6 levstatements  */
#line 1015 "lev_comp.y"
                  {
		  }
#line 3139 "lev_comp.y.c"
    break;

  case 152: /* breakstatement: BREAK_ID  */
#line 1020 "lev_comp.y"
                  {
		      if (!allow_break_statements)
			  lc_error("Cannot use BREAK outside a statement block.");
		      else {
			  break_stmt_new(splev, splev->n_opcodes);
		      }
		  }
#line 3151 "lev_comp.y.c"
    break;

  case 155: /* forstmt_start: FOR_ID any_var_or_unk '=' math_expr_var for_to_span math_expr_var  */
#line 1034 "lev_comp.y"
                  {
		      char buf[256], buf2[256];

		      if (n_forloops >= MAX_NESTED_IFS) {
			  lc_error("FOR: Too deeply nested loops.");
			  n_forloops = MAX_NESTED_IFS - 1;
		      }

		      /* first, define a variable for the for-loop end value */
		      Sprintf(buf, "%s end", (yyvsp[-4].map));
		      /* the value of which is already in stack (the 2nd math_expr) */
		      add_opvars(splev, "iso", VA_PASS3(0, buf, SPO_VAR_INIT));

		      vardefs = add_vardef_type(vardefs, (yyvsp[-4].map), SPOVAR_INT);
		      /* define the for-loop variable. value is in stack (1st math_expr) */
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[-4].map), SPO_VAR_INIT));

		      /* calculate value for the loop "step" variable */
		      Sprintf(buf2, "%s step", (yyvsp[-4].map));
		      /* end - start */
		      add_opvars(splev, "vvo",
				 VA_PASS3(buf, (yyvsp[-4].map), SPO_MATH_SUB));
		      /* sign of that */
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_SIGN));
		      /* save the sign into the step var */
		      add_opvars(splev, "iso",
				 VA_PASS3(0, buf2, SPO_VAR_INIT));

		      forloop_list[n_forloops].varname = strdup((yyvsp[-4].map));
		      forloop_list[n_forloops].jmp_point = splev->n_opcodes;

		      n_forloops++;
		      Free((yyvsp[-4].map));
		  }
#line 3190 "lev_comp.y.c"
    break;

  case 156: /* $@7: %empty  */
#line 1071 "lev_comp.y"
                  {
		      /* nothing */
		      break_stmt_start();
		  }
#line 3199 "lev_comp.y.c"
    break;

  case 157: /* forstatement: forstmt_start $@7 stmt_block  */
#line 1076 "lev_comp.y"
                  {
                      int l;
		      char buf[256], buf2[256];

		      n_forloops--;
		      Sprintf(buf, "%s step", forloop_list[n_forloops].varname);
		      Sprintf(buf2, "%s end", forloop_list[n_forloops].varname);
		      /* compare for-loop var to end value */
		      add_opvars(splev, "vvo",
				 VA_PASS3(forloop_list[n_forloops].varname,
					  buf2, SPO_CMP));
		      /* var + step */
		      add_opvars(splev, "vvo",
				VA_PASS3(buf, forloop_list[n_forloops].varname,
					 SPO_MATH_ADD));
		      /* for-loop var = (for-loop var + step) */
		      add_opvars(splev, "iso",
				 VA_PASS3(0, forloop_list[n_forloops].varname,
					  SPO_VAR_INIT));
		      /* jump back if compared values were not equal */
                      l = (int) (forloop_list[n_forloops].jmp_point
                                 - splev->n_opcodes - 1);
		      add_opvars(splev, "io", VA_PASS2(l, SPO_JNE));
		      Free(forloop_list[n_forloops].varname);
		      break_stmt_end(splev);
		  }
#line 3230 "lev_comp.y.c"
    break;

  case 158: /* $@8: %empty  */
#line 1105 "lev_comp.y"
                  {
		      struct opvar *tmppush = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  lc_error("LOOP: Too deeply nested conditionals.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }
		      set_opvar_int(tmppush, splev->n_opcodes);
		      if_list[n_if_list++] = tmppush;

		      add_opvars(splev, "o", VA_PASS1(SPO_DEC));
		      break_stmt_start();
		  }
#line 3248 "lev_comp.y.c"
    break;

  case 159: /* loopstatement: LOOP_ID '[' integer_or_var ']' $@8 stmt_block  */
#line 1119 "lev_comp.y"
                  {
		      struct opvar *tmppush;

		      add_opvars(splev, "oio", VA_PASS3(SPO_COPY, 0, SPO_CMP));

		      tmppush = (struct opvar *) if_list[--n_if_list];
		      set_opvar_int(tmppush,
                                    tmppush->vardata.l - splev->n_opcodes-1);
		      add_opcode(splev, SPO_PUSH, tmppush);
		      add_opcode(splev, SPO_JG, NULL);
		      add_opcode(splev, SPO_POP, NULL); /* discard count */
		      break_stmt_end(splev);
		  }
#line 3266 "lev_comp.y.c"
    break;

  case 160: /* $@9: %empty  */
#line 1135 "lev_comp.y"
                  {
		      struct opvar *tmppush2 = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  lc_error("IF: Too deeply nested conditionals.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }

		      add_opcode(splev, SPO_CMP, NULL);

		      set_opvar_int(tmppush2, splev->n_opcodes+1);

		      if_list[n_if_list++] = tmppush2;

		      add_opcode(splev, SPO_PUSH, tmppush2);

		      add_opcode(splev, reverse_jmp_opcode( (yyvsp[-1].i) ), NULL);

		  }
#line 3290 "lev_comp.y.c"
    break;

  case 161: /* chancestatement: comparestmt ':' $@9 levstatement  */
#line 1155 "lev_comp.y"
                  {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;

			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush,
                                        splev->n_opcodes - tmppush->vardata.l);
		      } else lc_error("IF: Huh?!  No start address?");
		  }
#line 3304 "lev_comp.y.c"
    break;

  case 162: /* $@10: %empty  */
#line 1167 "lev_comp.y"
                  {
		      struct opvar *tmppush2 = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  lc_error("IF: Too deeply nested conditionals.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }

		      add_opcode(splev, SPO_CMP, NULL);

		      set_opvar_int(tmppush2, splev->n_opcodes+1);

		      if_list[n_if_list++] = tmppush2;

		      add_opcode(splev, SPO_PUSH, tmppush2);

		      add_opcode(splev, reverse_jmp_opcode( (yyvsp[0].i) ), NULL);

		  }
#line 3328 "lev_comp.y.c"
    break;

  case 163: /* ifstatement: IF_ID comparestmt $@10 if_ending  */
#line 1187 "lev_comp.y"
                  {
		     /* do nothing */
		  }
#line 3336 "lev_comp.y.c"
    break;

  case 164: /* if_ending: stmt_block  */
#line 1193 "lev_comp.y"
                  {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;

			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush,
                                        splev->n_opcodes - tmppush->vardata.l);
		      } else lc_error("IF: Huh?!  No start address?");
		  }
#line 3350 "lev_comp.y.c"
    break;

  case 165: /* $@11: %empty  */
#line 1203 "lev_comp.y"
                  {
		      if (n_if_list > 0) {
			  struct opvar *tmppush = New(struct opvar);
			  struct opvar *tmppush2;

			  set_opvar_int(tmppush, splev->n_opcodes+1);
			  add_opcode(splev, SPO_PUSH, tmppush);

			  add_opcode(splev, SPO_JMP, NULL);

			  tmppush2 = (struct opvar *) if_list[--n_if_list];

			  set_opvar_int(tmppush2,
                                      splev->n_opcodes - tmppush2->vardata.l);
			  if_list[n_if_list++] = tmppush;
		      } else lc_error("IF: Huh?!  No else-part address?");
		  }
#line 3372 "lev_comp.y.c"
    break;

  case 166: /* if_ending: stmt_block $@11 ELSE_ID stmt_block  */
#line 1221 "lev_comp.y"
                  {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;
			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush, splev->n_opcodes - tmppush->vardata.l);
		      } else lc_error("IF: Huh?! No end address?");
		  }
#line 3384 "lev_comp.y.c"
    break;

  case 167: /* vaultgen_stmt: VAULTGEN_ID ':' INTEGER  */
#line 1231 "lev_comp.y"
                  {
		      if (is_rnd_vault) {
			  if ((yyvsp[0].i) > 0)
			      rnd_vault_freq = (yyvsp[0].i);
			  else
			      lc_error("Invalid VAULTGEN frequency.");
		      } else
			  lc_error("VAULTGEN without rndvault FLAG.");
		  }
#line 3398 "lev_comp.y.c"
    break;

  case 168: /* mindepth_stmt: MINDEPTH_ID ':' INTEGER  */
#line 1243 "lev_comp.y"
                  {
                      if (is_rnd_vault) {
                          if ((yyvsp[0].i) > 0)
                              rnd_vault_mindepth = (yyvsp[0].i);
                          else
                              lc_error("Invalid MINDEPTH value.");
                      } else
                          lc_error("MINDEPTH without rndvault FLAG.");
                  }
#line 3412 "lev_comp.y.c"
    break;

  case 169: /* message: MESSAGE_ID ':' string_expr  */
#line 1255 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MESSAGE));
		  }
#line 3420 "lev_comp.y.c"
    break;

  case 170: /* random_corridors: RAND_CORRIDOR_ID  */
#line 1261 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiiiio",
			      VA_PASS7(-1,  0, -1, -1, -1, -1, SPO_CORRIDOR));
		  }
#line 3429 "lev_comp.y.c"
    break;

  case 171: /* random_corridors: RAND_CORRIDOR_ID ':' all_integers  */
#line 1266 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiiiio",
			      VA_PASS7(-1, (yyvsp[0].i), -1, -1, -1, -1, SPO_CORRIDOR));
		  }
#line 3438 "lev_comp.y.c"
    break;

  case 172: /* random_corridors: RAND_CORRIDOR_ID ':' RANDOM_TYPE  */
#line 1271 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiiiio",
			      VA_PASS7(-1, -1, -1, -1, -1, -1, SPO_CORRIDOR));
		  }
#line 3447 "lev_comp.y.c"
    break;

  case 173: /* corridor: CORRIDOR_ID ':' corr_spec ',' corr_spec  */
#line 1278 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiiiio",
				 VA_PASS7((yyvsp[-2].corpos).room, (yyvsp[-2].corpos).door, (yyvsp[-2].corpos).wall,
					  (yyvsp[0].corpos).room, (yyvsp[0].corpos).door, (yyvsp[0].corpos).wall,
					  SPO_CORRIDOR));
		  }
#line 3458 "lev_comp.y.c"
    break;

  case 174: /* corridor: CORRIDOR_ID ':' corr_spec ',' all_integers  */
#line 1285 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiiiio",
				 VA_PASS7((yyvsp[-2].corpos).room, (yyvsp[-2].corpos).door, (yyvsp[-2].corpos).wall,
					  -1, -1, (long)(yyvsp[0].i),
					  SPO_CORRIDOR));
		  }
#line 3469 "lev_comp.y.c"
    break;

  case 175: /* corr_spec: '(' INTEGER ',' DIRECTION ',' door_pos ')'  */
#line 1294 "lev_comp.y"
                  {
			(yyval.corpos).room = (yyvsp[-5].i);
			(yyval.corpos).wall = (yyvsp[-3].i);
			(yyval.corpos).door = (yyvsp[-1].i);
		  }
#line 3479 "lev_comp.y.c"
    break;

  case 176: /* room_begin: room_type opt_percent ',' light_state  */
#line 1302 "lev_comp.y"
                  {
		      if (((yyvsp[-2].i) < 100) && ((yyvsp[-3].i) == OROOM))
			  lc_error("Only typed rooms can have a chance.");
		      else {
			  add_opvars(splev, "iii",
				     VA_PASS3((long)(yyvsp[-3].i), (long)(yyvsp[-2].i), (long)(yyvsp[0].i)));
		      }
                  }
#line 3492 "lev_comp.y.c"
    break;

  case 177: /* $@12: %empty  */
#line 1313 "lev_comp.y"
                  {
		      long rflags = (yyvsp[0].i);

		      if (rflags == -1) rflags = (1 << 0);
		      add_opvars(splev, "iiiiiiio",
				 VA_PASS8(rflags, ERR, ERR,
					  (yyvsp[-3].crd).x, (yyvsp[-3].crd).y, (yyvsp[-1].sze).width, (yyvsp[-1].sze).height,
					  SPO_SUBROOM));
		      break_stmt_start();
		  }
#line 3507 "lev_comp.y.c"
    break;

  case 178: /* subroom_def: SUBROOM_ID ':' room_begin ',' subroom_pos ',' room_size optroomregionflags $@12 stmt_block  */
#line 1324 "lev_comp.y"
                  {
		      break_stmt_end(splev);
		      add_opcode(splev, SPO_ENDROOM, NULL);
		  }
#line 3516 "lev_comp.y.c"
    break;

  case 179: /* $@13: %empty  */
#line 1331 "lev_comp.y"
                  {
		      long rflags = (yyvsp[-2].i);

		      if (rflags == -1) rflags = (1 << 0);
		      add_opvars(splev, "iiiiiiio",
				 VA_PASS8(rflags,
					  (yyvsp[-3].crd).x, (yyvsp[-3].crd).y, (yyvsp[-5].crd).x, (yyvsp[-5].crd).y,
					  (yyvsp[-1].sze).width, (yyvsp[-1].sze).height, SPO_ROOM));
		      break_stmt_start();
		  }
#line 3531 "lev_comp.y.c"
    break;

  case 180: /* room_def: ROOM_ID ':' room_begin ',' room_pos ',' room_align ',' room_size optroomregionflags $@13 stmt_block  */
#line 1342 "lev_comp.y"
                  {
		      break_stmt_end(splev);
		      add_opcode(splev, SPO_ENDROOM, NULL);
		  }
#line 3540 "lev_comp.y.c"
    break;

  case 181: /* roomfill: %empty  */
#line 1349 "lev_comp.y"
                  {
			(yyval.i) = 1;
		  }
#line 3548 "lev_comp.y.c"
    break;

  case 182: /* roomfill: ',' BOOLEAN  */
#line 1353 "lev_comp.y"
                  {
			(yyval.i) = (yyvsp[0].i);
		  }
#line 3556 "lev_comp.y.c"
    break;

  case 183: /* room_pos: '(' INTEGER ',' INTEGER ')'  */
#line 1359 "lev_comp.y"
                  {
			if ( (yyvsp[-3].i) < 1 || (yyvsp[-3].i) > 5 ||
			    (yyvsp[-1].i) < 1 || (yyvsp[-1].i) > 5 ) {
			    lc_error("Room positions should be between 1-5: (%li,%li)!", (yyvsp[-3].i), (yyvsp[-1].i));
			} else {
			    (yyval.crd).x = (yyvsp[-3].i);
			    (yyval.crd).y = (yyvsp[-1].i);
			}
		  }
#line 3570 "lev_comp.y.c"
    break;

  case 184: /* room_pos: RANDOM_TYPE  */
#line 1369 "lev_comp.y"
                  {
			(yyval.crd).x = (yyval.crd).y = ERR;
		  }
#line 3578 "lev_comp.y.c"
    break;

  case 185: /* subroom_pos: '(' INTEGER ',' INTEGER ')'  */
#line 1375 "lev_comp.y"
                  {
			if ( (yyvsp[-3].i) < 0 || (yyvsp[-1].i) < 0) {
			    lc_error("Invalid subroom position (%li,%li)!", (yyvsp[-3].i), (yyvsp[-1].i));
			} else {
			    (yyval.crd).x = (yyvsp[-3].i);
			    (yyval.crd).y = (yyvsp[-1].i);
			}
		  }
#line 3591 "lev_comp.y.c"
    break;

  case 186: /* subroom_pos: RANDOM_TYPE  */
#line 1384 "lev_comp.y"
                  {
			(yyval.crd).x = (yyval.crd).y = ERR;
		  }
#line 3599 "lev_comp.y.c"
    break;

  case 187: /* room_align: '(' h_justif ',' v_justif ')'  */
#line 1390 "lev_comp.y"
                  {
		      (yyval.crd).x = (yyvsp[-3].i);
		      (yyval.crd).y = (yyvsp[-1].i);
		  }
#line 3608 "lev_comp.y.c"
    break;

  case 188: /* room_align: RANDOM_TYPE  */
#line 1395 "lev_comp.y"
                  {
		      (yyval.crd).x = (yyval.crd).y = ERR;
		  }
#line 3616 "lev_comp.y.c"
    break;

  case 189: /* room_size: '(' INTEGER ',' INTEGER ')'  */
#line 1401 "lev_comp.y"
                  {
			(yyval.sze).width = (yyvsp[-3].i);
			(yyval.sze).height = (yyvsp[-1].i);
		  }
#line 3625 "lev_comp.y.c"
    break;

  case 190: /* room_size: RANDOM_TYPE  */
#line 1406 "lev_comp.y"
                  {
			(yyval.sze).height = (yyval.sze).width = ERR;
		  }
#line 3633 "lev_comp.y.c"
    break;

  case 191: /* door_detail: ROOMDOOR_ID ':' secret ',' door_state ',' door_wall ',' door_pos  */
#line 1412 "lev_comp.y"
                  {
			/* ERR means random here */
			if ((yyvsp[-2].i) == ERR && (yyvsp[0].i) != ERR) {
			    lc_error("If the door wall is random, so must be its pos!");
			} else {
			    add_opvars(splev, "iiiio",
				       VA_PASS5((long)(yyvsp[0].i), (long)(yyvsp[-4].i), (long)(yyvsp[-6].i),
						(long)(yyvsp[-2].i), SPO_ROOM_DOOR));
			}
		  }
#line 3648 "lev_comp.y.c"
    break;

  case 192: /* door_detail: DOOR_ID ':' door_state ',' ter_selection  */
#line 1423 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2((long)(yyvsp[-2].i), SPO_DOOR));
		  }
#line 3656 "lev_comp.y.c"
    break;

  case 197: /* dir_list: DIRECTION  */
#line 1437 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[0].i);
		  }
#line 3664 "lev_comp.y.c"
    break;

  case 198: /* dir_list: DIRECTION '|' dir_list  */
#line 1441 "lev_comp.y"
                  {
		      (yyval.i) = ((yyvsp[-2].i) | (yyvsp[0].i));
		  }
#line 3672 "lev_comp.y.c"
    break;

  case 201: /* map_definition: NOMAP_ID  */
#line 1451 "lev_comp.y"
                  {
		      add_opvars(splev, "ciisiio",
				 VA_PASS7(0, 0, 1, (char *) 0, 0, 0, SPO_MAP));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  }
#line 3683 "lev_comp.y.c"
    break;

  case 202: /* map_definition: GEOMETRY_ID ':' h_justif ',' v_justif roomfill MAP_ID  */
#line 1458 "lev_comp.y"
                  {
		      add_opvars(splev, "cii",
				 VA_PASS3(SP_COORD_PACK(((yyvsp[-4].i)), ((yyvsp[-2].i))),
					  1, (int) (yyvsp[-1].i)));
		      scan_map((yyvsp[0].map), splev);
		      Free((yyvsp[0].map));
		  }
#line 3695 "lev_comp.y.c"
    break;

  case 203: /* map_definition: GEOMETRY_ID ':' coord_or_var roomfill MAP_ID  */
#line 1466 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(2, (int) (yyvsp[-1].i)));
		      scan_map((yyvsp[0].map), splev);
		      Free((yyvsp[0].map));
		  }
#line 3705 "lev_comp.y.c"
    break;

  case 208: /* monster_detail: MONSTER_ID ':' monster_desc  */
#line 1482 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(0, SPO_MONSTER));
		  }
#line 3713 "lev_comp.y.c"
    break;

  case 209: /* $@14: %empty  */
#line 1486 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(1, SPO_MONSTER));
		      in_container_obj++;
		      break_stmt_start();
		  }
#line 3723 "lev_comp.y.c"
    break;

  case 210: /* monster_detail: MONSTER_ID ':' monster_desc $@14 stmt_block  */
#line 1492 "lev_comp.y"
                 {
		     break_stmt_end(splev);
		     in_container_obj--;
		     add_opvars(splev, "o", VA_PASS1(SPO_END_MONINVENT));
		 }
#line 3733 "lev_comp.y.c"
    break;

  case 211: /* monster_desc: monster_or_var ',' coord_or_var monster_infos  */
#line 1500 "lev_comp.y"
                  {
		      /* nothing */
		  }
#line 3741 "lev_comp.y.c"
    break;

  case 212: /* monster_infos: %empty  */
#line 1506 "lev_comp.y"
                  {
		      struct opvar *stopit = New(struct opvar);

		      set_opvar_int(stopit, SP_M_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x0000;
		  }
#line 3753 "lev_comp.y.c"
    break;

  case 213: /* monster_infos: monster_infos ',' monster_info  */
#line 1514 "lev_comp.y"
                  {
		      if (( (yyvsp[-2].i) & (yyvsp[0].i) ))
			  lc_error("MONSTER extra info defined twice, or conflicting.");
		      (yyval.i) = ( (yyvsp[-2].i) | (yyvsp[0].i) );
		  }
#line 3763 "lev_comp.y.c"
    break;

  case 214: /* monster_info: string_expr  */
#line 1522 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_NAME));
		      (yyval.i) = 0x0001;
		  }
#line 3772 "lev_comp.y.c"
    break;

  case 215: /* monster_info: MON_ATTITUDE  */
#line 1527 "lev_comp.y"
                  {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[0].i), SP_M_V_PEACEFUL));
		      (yyval.i) = 0x0002;
		  }
#line 3782 "lev_comp.y.c"
    break;

  case 216: /* monster_info: MON_ALERTNESS  */
#line 1533 "lev_comp.y"
                  {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[0].i), SP_M_V_ASLEEP));
		      (yyval.i) = 0x0004;
		  }
#line 3792 "lev_comp.y.c"
    break;

  case 217: /* monster_info: alignment_prfx  */
#line 1539 "lev_comp.y"
                  {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[0].i), SP_M_V_ALIGN));
		      (yyval.i) = 0x0008;
		  }
#line 3802 "lev_comp.y.c"
    break;

  case 218: /* monster_info: MON_APPEARANCE string_expr  */
#line 1545 "lev_comp.y"
                  {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[-1].i), SP_M_V_APPEAR));
		      (yyval.i) = 0x0010;
		  }
#line 3812 "lev_comp.y.c"
    break;

  case 219: /* monster_info: FEMALE_ID  */
#line 1551 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_FEMALE));
		      (yyval.i) = 0x0020;
		  }
#line 3821 "lev_comp.y.c"
    break;

  case 220: /* monster_info: INVIS_ID  */
#line 1556 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_INVIS));
		      (yyval.i) = 0x0040;
		  }
#line 3830 "lev_comp.y.c"
    break;

  case 221: /* monster_info: CANCELLED_ID  */
#line 1561 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_CANCELLED));
		      (yyval.i) = 0x0080;
		  }
#line 3839 "lev_comp.y.c"
    break;

  case 222: /* monster_info: REVIVED_ID  */
#line 1566 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_REVIVED));
		      (yyval.i) = 0x0100;
		  }
#line 3848 "lev_comp.y.c"
    break;

  case 223: /* monster_info: AVENGE_ID  */
#line 1571 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_AVENGE));
		      (yyval.i) = 0x0200;
		  }
#line 3857 "lev_comp.y.c"
    break;

  case 224: /* monster_info: FLEEING_ID ':' integer_or_var  */
#line 1576 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_FLEEING));
		      (yyval.i) = 0x0400;
		  }
#line 3866 "lev_comp.y.c"
    break;

  case 225: /* monster_info: BLINDED_ID ':' integer_or_var  */
#line 1581 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_BLINDED));
		      (yyval.i) = 0x0800;
		  }
#line 3875 "lev_comp.y.c"
    break;

  case 226: /* monster_info: PARALYZED_ID ':' integer_or_var  */
#line 1586 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_PARALYZED));
		      (yyval.i) = 0x1000;
		  }
#line 3884 "lev_comp.y.c"
    break;

  case 227: /* monster_info: STUNNED_ID  */
#line 1591 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_STUNNED));
		      (yyval.i) = 0x2000;
		  }
#line 3893 "lev_comp.y.c"
    break;

  case 228: /* monster_info: CONFUSED_ID  */
#line 1596 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_CONFUSED));
		      (yyval.i) = 0x4000;
		  }
#line 3902 "lev_comp.y.c"
    break;

  case 229: /* monster_info: SEENTRAPS_ID ':' seen_trap_mask  */
#line 1601 "lev_comp.y"
                  {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[0].i), SP_M_V_SEENTRAPS));
		      (yyval.i) = 0x8000;
		  }
#line 3912 "lev_comp.y.c"
    break;

  case 230: /* monster_info: DEAD_ID  */
#line 1607 "lev_comp.y"
                  {
                      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_DEAD));
                      (yyval.i) = 0xFFFF; /* being dead conflicts with all other params */
                  }
#line 3921 "lev_comp.y.c"
    break;

  case 231: /* seen_trap_mask: STRING  */
#line 1614 "lev_comp.y"
                  {
		      int token = get_trap_type((yyvsp[0].map));

		      if (token == ERR || token == 0)
			  lc_error("Unknown trap type '%s'!", (yyvsp[0].map));
                      Free((yyvsp[0].map));
		      (yyval.i) = (1L << (token - 1));
		  }
#line 3934 "lev_comp.y.c"
    break;

  case 232: /* seen_trap_mask: ALL_ID  */
#line 1623 "lev_comp.y"
                  {
		      (yyval.i) = (long) ~0;
		  }
#line 3942 "lev_comp.y.c"
    break;

  case 233: /* seen_trap_mask: STRING '|' seen_trap_mask  */
#line 1627 "lev_comp.y"
                  {
		      int token = get_trap_type((yyvsp[-2].map));
		      if (token == ERR || token == 0)
			  lc_error("Unknown trap type '%s'!", (yyvsp[-2].map));

		      if ((1L << (token - 1)) & (yyvsp[0].i))
			  lc_error("Monster seen_traps, trap '%s' listed twice.", (yyvsp[-2].map));
                      Free((yyvsp[-2].map));
		      (yyval.i) = ((1L << (token - 1)) | (yyvsp[0].i));
		  }
#line 3957 "lev_comp.y.c"
    break;

  case 234: /* object_detail: OBJECT_ID ':' object_desc  */
#line 1640 "lev_comp.y"
                  {
		      int cnt = 0;

		      if (in_container_obj)
                          cnt |= SP_OBJ_CONTENT;
		      add_opvars(splev, "io", VA_PASS2(cnt, SPO_OBJECT));
		  }
#line 3969 "lev_comp.y.c"
    break;

  case 235: /* $@15: %empty  */
#line 1648 "lev_comp.y"
                  {
		      int cnt = SP_OBJ_CONTAINER;

		      if (in_container_obj)
                          cnt |= SP_OBJ_CONTENT;
		      add_opvars(splev, "io", VA_PASS2(cnt, SPO_OBJECT));
		      in_container_obj++;
		      break_stmt_start();
		  }
#line 3983 "lev_comp.y.c"
    break;

  case 236: /* object_detail: COBJECT_ID ':' object_desc $@15 stmt_block  */
#line 1658 "lev_comp.y"
                 {
		     break_stmt_end(splev);
		     in_container_obj--;
		     add_opcode(splev, SPO_POP_CONTAINER, NULL);
		 }
#line 3993 "lev_comp.y.c"
    break;

  case 237: /* object_desc: object_or_var object_infos  */
#line 1666 "lev_comp.y"
                  {
		      if (( (yyvsp[0].i) & 0x4000) && in_container_obj)
                          lc_error("Object cannot have a coord when contained.");
		      else if (!( (yyvsp[0].i) & 0x4000) && !in_container_obj)
                          lc_error("Object needs a coord when not contained.");
		  }
#line 4004 "lev_comp.y.c"
    break;

  case 238: /* object_infos: %empty  */
#line 1675 "lev_comp.y"
                  {
		      struct opvar *stopit = New(struct opvar);
		      set_opvar_int(stopit, SP_O_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x00;
		  }
#line 4015 "lev_comp.y.c"
    break;

  case 239: /* object_infos: object_infos ',' object_info  */
#line 1682 "lev_comp.y"
                  {
		      if (( (yyvsp[-2].i) & (yyvsp[0].i) ))
			  lc_error("OBJECT extra info '%s' defined twice.", curr_token);
		      (yyval.i) = ( (yyvsp[-2].i) | (yyvsp[0].i) );
		  }
#line 4025 "lev_comp.y.c"
    break;

  case 240: /* object_info: CURSE_TYPE  */
#line 1690 "lev_comp.y"
                  {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[0].i), SP_O_V_CURSE));
		      (yyval.i) = 0x0001;
		  }
#line 4035 "lev_comp.y.c"
    break;

  case 241: /* object_info: MONTYPE_ID ':' monster_or_var  */
#line 1696 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_CORPSENM));
		      (yyval.i) = 0x0002;
		  }
#line 4044 "lev_comp.y.c"
    break;

  case 242: /* object_info: all_ints_push  */
#line 1701 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_SPE));
		      (yyval.i) = 0x0004;
		  }
#line 4053 "lev_comp.y.c"
    break;

  case 243: /* object_info: NAME_ID ':' string_expr  */
#line 1706 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_NAME));
		      (yyval.i) = 0x0008;
		  }
#line 4062 "lev_comp.y.c"
    break;

  case 244: /* object_info: QUANTITY_ID ':' integer_or_var  */
#line 1711 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_QUAN));
		      (yyval.i) = 0x0010;
		  }
#line 4071 "lev_comp.y.c"
    break;

  case 245: /* object_info: BURIED_ID  */
#line 1716 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_BURIED));
		      (yyval.i) = 0x0020;
		  }
#line 4080 "lev_comp.y.c"
    break;

  case 246: /* object_info: LIGHT_STATE  */
#line 1721 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2((int) (yyvsp[0].i), SP_O_V_LIT));
		      (yyval.i) = 0x0040;
		  }
#line 4089 "lev_comp.y.c"
    break;

  case 247: /* object_info: ERODED_ID ':' integer_or_var  */
#line 1726 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_ERODED));
		      (yyval.i) = 0x0080;
		  }
#line 4098 "lev_comp.y.c"
    break;

  case 248: /* object_info: ERODEPROOF_ID  */
#line 1731 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(-1, SP_O_V_ERODED));
		      (yyval.i) = 0x0080;
		  }
#line 4107 "lev_comp.y.c"
    break;

  case 249: /* object_info: DOOR_STATE  */
#line 1736 "lev_comp.y"
                  {
		      if ((yyvsp[0].i) == D_LOCKED) {
			  add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_LOCKED));
			  (yyval.i) = 0x0100;
		      } else if ((yyvsp[0].i) == D_BROKEN) {
			  add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_BROKEN));
			  (yyval.i) = 0x0200;
		      } else
			  lc_error("DOOR state can only be locked or broken.");
		  }
#line 4122 "lev_comp.y.c"
    break;

  case 250: /* object_info: TRAPPED_STATE  */
#line 1747 "lev_comp.y"
                  {
		      add_opvars(splev, "ii",
                                 VA_PASS2((int) (yyvsp[0].i), SP_O_V_TRAPPED));
		      (yyval.i) = 0x0400;
		  }
#line 4132 "lev_comp.y.c"
    break;

  case 251: /* object_info: RECHARGED_ID ':' integer_or_var  */
#line 1753 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_RECHARGED));
		      (yyval.i) = 0x0800;
		  }
#line 4141 "lev_comp.y.c"
    break;

  case 252: /* object_info: INVIS_ID  */
#line 1758 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_INVIS));
		      (yyval.i) = 0x1000;
		  }
#line 4150 "lev_comp.y.c"
    break;

  case 253: /* object_info: GREASED_ID  */
#line 1763 "lev_comp.y"
                  {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_GREASED));
		      (yyval.i) = 0x2000;
		  }
#line 4159 "lev_comp.y.c"
    break;

  case 254: /* object_info: coord_or_var  */
#line 1768 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_COORD));
		      (yyval.i) = 0x4000;
		  }
#line 4168 "lev_comp.y.c"
    break;

  case 255: /* trap_detail: TRAP_ID ':' trap_name ',' coord_or_var  */
#line 1775 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2((int) (yyvsp[-2].i), SPO_TRAP));
		  }
#line 4176 "lev_comp.y.c"
    break;

  case 256: /* drawbridge_detail: DRAWBRIDGE_ID ':' coord_or_var ',' DIRECTION ',' door_state  */
#line 1781 "lev_comp.y"
                   {
		       long dir, state = 0;

		       /* convert dir from a DIRECTION to a DB_DIR */
		       dir = (yyvsp[-2].i);
		       switch (dir) {
		       case W_NORTH: dir = DB_NORTH; break;
		       case W_SOUTH: dir = DB_SOUTH; break;
		       case W_EAST:  dir = DB_EAST;  break;
		       case W_WEST:  dir = DB_WEST;  break;
		       default:
			   lc_error("Invalid drawbridge direction.");
			   break;
		       }

		       if ( (yyvsp[0].i) == D_ISOPEN )
			   state = 1;
		       else if ( (yyvsp[0].i) == D_CLOSED )
			   state = 0;
		       else if ( (yyvsp[0].i) == -1 )
			   state = -1;
		       else
			   lc_error("A drawbridge can only be open, closed or random!");
		       add_opvars(splev, "iio",
				  VA_PASS3(state, dir, SPO_DRAWBRIDGE));
		   }
#line 4207 "lev_comp.y.c"
    break;

  case 257: /* mazewalk_detail: MAZEWALK_ID ':' coord_or_var ',' DIRECTION  */
#line 1810 "lev_comp.y"
                  {
		      add_opvars(splev, "iiio",
				 VA_PASS4((int) (yyvsp[0].i), 1, 0, SPO_MAZEWALK));
		  }
#line 4216 "lev_comp.y.c"
    break;

  case 258: /* mazewalk_detail: MAZEWALK_ID ':' coord_or_var ',' DIRECTION ',' BOOLEAN opt_fillchar  */
#line 1815 "lev_comp.y"
                  {
		      add_opvars(splev, "iiio",
				 VA_PASS4((int) (yyvsp[-3].i), (int) (yyvsp[-1].i),
					  (int) (yyvsp[0].i), SPO_MAZEWALK));
		  }
#line 4226 "lev_comp.y.c"
    break;

  case 259: /* wallify_detail: WALLIFY_ID  */
#line 1823 "lev_comp.y"
                  {
		      add_opvars(splev, "rio",
				 VA_PASS3(SP_REGION_PACK(-1,-1,-1,-1),
					  0, SPO_WALLIFY));
		  }
#line 4236 "lev_comp.y.c"
    break;

  case 260: /* wallify_detail: WALLIFY_ID ':' ter_selection  */
#line 1829 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(1, SPO_WALLIFY));
		  }
#line 4244 "lev_comp.y.c"
    break;

  case 261: /* ladder_detail: LADDER_ID ':' coord_or_var ',' UP_OR_DOWN  */
#line 1835 "lev_comp.y"
                  {
		      add_opvars(splev, "io",
				 VA_PASS2((int) (yyvsp[0].i), SPO_LADDER));
		  }
#line 4253 "lev_comp.y.c"
    break;

  case 262: /* stair_detail: STAIR_ID ':' coord_or_var ',' UP_OR_DOWN  */
#line 1842 "lev_comp.y"
                  {
		      add_opvars(splev, "io",
				 VA_PASS2((int) (yyvsp[0].i), SPO_STAIR));
		  }
#line 4262 "lev_comp.y.c"
    break;

  case 263: /* stair_region: STAIR_ID ':' lev_region ',' lev_region ',' UP_OR_DOWN  */
#line 1849 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[-4].lregn).x1, (yyvsp[-4].lregn).y1, (yyvsp[-4].lregn).x2, (yyvsp[-4].lregn).y2, (yyvsp[-4].lregn).area,
					   (yyvsp[-2].lregn).x1, (yyvsp[-2].lregn).y1, (yyvsp[-2].lregn).x2, (yyvsp[-2].lregn).y2, (yyvsp[-2].lregn).area,
				     (long) (((yyvsp[0].i)) ? LR_UPSTAIR : LR_DOWNSTAIR),
					   0, (char *) 0, SPO_LEVREGION));
		  }
#line 4274 "lev_comp.y.c"
    break;

  case 264: /* portal_region: PORTAL_ID ':' lev_region ',' lev_region ',' STRING  */
#line 1859 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[-4].lregn).x1, (yyvsp[-4].lregn).y1, (yyvsp[-4].lregn).x2, (yyvsp[-4].lregn).y2, (yyvsp[-4].lregn).area,
					   (yyvsp[-2].lregn).x1, (yyvsp[-2].lregn).y1, (yyvsp[-2].lregn).x2, (yyvsp[-2].lregn).y2, (yyvsp[-2].lregn).area,
					   LR_PORTAL, 0, (yyvsp[0].map), SPO_LEVREGION));
		      Free((yyvsp[0].map));
		  }
#line 4286 "lev_comp.y.c"
    break;

  case 265: /* teleprt_region: TELEPRT_ID ':' lev_region ',' lev_region teleprt_detail  */
#line 1869 "lev_comp.y"
                  {
		      long rtyp = 0;
		      switch((yyvsp[0].i)) {
		      case -1: rtyp = LR_TELE; break;
		      case  0: rtyp = LR_DOWNTELE; break;
		      case  1: rtyp = LR_UPTELE; break;
		      }
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[-3].lregn).x1, (yyvsp[-3].lregn).y1, (yyvsp[-3].lregn).x2, (yyvsp[-3].lregn).y2, (yyvsp[-3].lregn).area,
					   (yyvsp[-1].lregn).x1, (yyvsp[-1].lregn).y1, (yyvsp[-1].lregn).x2, (yyvsp[-1].lregn).y2, (yyvsp[-1].lregn).area,
					   rtyp, 0, (char *)0, SPO_LEVREGION));
		  }
#line 4303 "lev_comp.y.c"
    break;

  case 266: /* branch_region: BRANCH_ID ':' lev_region ',' lev_region  */
#line 1884 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[-2].lregn).x1, (yyvsp[-2].lregn).y1, (yyvsp[-2].lregn).x2, (yyvsp[-2].lregn).y2, (yyvsp[-2].lregn).area,
					   (yyvsp[0].lregn).x1, (yyvsp[0].lregn).y1, (yyvsp[0].lregn).x2, (yyvsp[0].lregn).y2, (yyvsp[0].lregn).area,
					   (long) LR_BRANCH, 0,
					   (char *) 0, SPO_LEVREGION));
		  }
#line 4315 "lev_comp.y.c"
    break;

  case 267: /* teleprt_detail: %empty  */
#line 1894 "lev_comp.y"
                  {
			(yyval.i) = -1;
		  }
#line 4323 "lev_comp.y.c"
    break;

  case 268: /* teleprt_detail: ',' UP_OR_DOWN  */
#line 1898 "lev_comp.y"
                  {
			(yyval.i) = (yyvsp[0].i);
		  }
#line 4331 "lev_comp.y.c"
    break;

  case 269: /* forge_detail: FORGE_ID ':' ter_selection  */
#line 1904 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_FORGE));
		  }
#line 4339 "lev_comp.y.c"
    break;

  case 270: /* magic_chest_detail: MAGIC_CHEST_ID ':' ter_selection  */
#line 1910 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MAGIC_CHEST));
		  }
#line 4347 "lev_comp.y.c"
    break;

  case 271: /* fountain_detail: FOUNTAIN_ID ':' ter_selection  */
#line 1915 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_FOUNTAIN));
		  }
#line 4355 "lev_comp.y.c"
    break;

  case 272: /* sink_detail: SINK_ID ':' ter_selection  */
#line 1921 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SINK));
		  }
#line 4363 "lev_comp.y.c"
    break;

  case 273: /* puddle_detail: PUDDLE_ID ':' ter_selection  */
#line 1927 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_PUDDLE));
		  }
#line 4371 "lev_comp.y.c"
    break;

  case 274: /* sewage_detail: SEWAGE_ID ':' ter_selection  */
#line 1933 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEWAGE));
		  }
#line 4379 "lev_comp.y.c"
    break;

  case 275: /* pool_detail: POOL_ID ':' ter_selection  */
#line 1939 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_POOL));
		  }
#line 4387 "lev_comp.y.c"
    break;

  case 276: /* terrain_type: CHAR  */
#line 1945 "lev_comp.y"
                  {
		      (yyval.terr).lit = -2;
		      (yyval.terr).ter = what_map_char((char) (yyvsp[0].i));
		  }
#line 4396 "lev_comp.y.c"
    break;

  case 277: /* terrain_type: '(' CHAR ',' light_state ')'  */
#line 1950 "lev_comp.y"
                  {
		      (yyval.terr).lit = (yyvsp[-1].i);
		      (yyval.terr).ter = what_map_char((char) (yyvsp[-3].i));
		  }
#line 4405 "lev_comp.y.c"
    break;

  case 278: /* replace_terrain_detail: REPLACE_TERRAIN_ID ':' region_or_var ',' mapchar_or_var ',' mapchar_or_var ',' SPERCENT  */
#line 1957 "lev_comp.y"
                  {
		      add_opvars(splev, "io",
				 VA_PASS2((yyvsp[0].i), SPO_REPLACETERRAIN));
		  }
#line 4414 "lev_comp.y.c"
    break;

  case 279: /* terrain_detail: TERRAIN_ID ':' ter_selection ',' mapchar_or_var  */
#line 1964 "lev_comp.y"
                 {
		     add_opvars(splev, "o", VA_PASS1(SPO_TERRAIN));
		 }
#line 4422 "lev_comp.y.c"
    break;

  case 280: /* diggable_detail: NON_DIGGABLE_ID ':' region_or_var  */
#line 1970 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_NON_DIGGABLE));
		  }
#line 4430 "lev_comp.y.c"
    break;

  case 281: /* passwall_detail: NON_PASSWALL_ID ':' region_or_var  */
#line 1976 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_NON_PASSWALL));
		  }
#line 4438 "lev_comp.y.c"
    break;

  case 282: /* @16: %empty  */
#line 1982 "lev_comp.y"
                  {
		      long irr;
		      long rt = (yyvsp[-1].i);
		      long rflags = (yyvsp[0].i);

		      if (rflags == -1) rflags = (1 << 0);
		      if (!(rflags & 1)) rt += MAXRTYPE+1;
		      irr = ((rflags & 2) != 0);
		      add_opvars(splev, "iiio",
				 VA_PASS4((long)(yyvsp[-3].i), rt, rflags, SPO_REGION));
		      (yyval.i) = (irr || (rflags & 1) || rt != OROOM);
		      break_stmt_start();
		  }
#line 4456 "lev_comp.y.c"
    break;

  case 283: /* region_detail: REGION_ID ':' region_or_var ',' light_state ',' room_type optroomregionflags @16 region_detail_end  */
#line 1996 "lev_comp.y"
                  {
		      break_stmt_end(splev);
		      if ( (yyvsp[-1].i) ) {
			  add_opcode(splev, SPO_ENDROOM, NULL);
		      } else if ( (yyvsp[0].i) )
			  lc_error("Cannot use lev statements in non-permanent REGION");
		  }
#line 4468 "lev_comp.y.c"
    break;

  case 284: /* region_detail_end: %empty  */
#line 2006 "lev_comp.y"
                  {
		      (yyval.i) = 0;
		  }
#line 4476 "lev_comp.y.c"
    break;

  case 285: /* region_detail_end: stmt_block  */
#line 2010 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[0].i);
		  }
#line 4484 "lev_comp.y.c"
    break;

  case 286: /* altar_detail: ALTAR_ID ':' coord_or_var ',' alignment ',' altar_type  */
#line 2016 "lev_comp.y"
                  {
		      add_opvars(splev, "iio",
				 VA_PASS3((long)(yyvsp[0].i), (long)(yyvsp[-2].i), SPO_ALTAR));
		  }
#line 4493 "lev_comp.y.c"
    break;

  case 287: /* grave_detail: GRAVE_ID ':' coord_or_var ',' string_expr  */
#line 2023 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(2, SPO_GRAVE));
		  }
#line 4501 "lev_comp.y.c"
    break;

  case 288: /* grave_detail: GRAVE_ID ':' coord_or_var ',' RANDOM_TYPE  */
#line 2027 "lev_comp.y"
                  {
		      add_opvars(splev, "sio",
				 VA_PASS3((char *)0, 1, SPO_GRAVE));
		  }
#line 4510 "lev_comp.y.c"
    break;

  case 289: /* grave_detail: GRAVE_ID ':' coord_or_var  */
#line 2032 "lev_comp.y"
                  {
		      add_opvars(splev, "sio",
				 VA_PASS3((char *)0, 0, SPO_GRAVE));
		  }
#line 4519 "lev_comp.y.c"
    break;

  case 290: /* gold_detail: GOLD_ID ':' math_expr_var ',' coord_or_var  */
#line 2039 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_GOLD));
		  }
#line 4527 "lev_comp.y.c"
    break;

  case 291: /* engraving_detail: ENGRAVING_ID ':' coord_or_var ',' engraving_type ',' string_expr  */
#line 2045 "lev_comp.y"
                  {
		      add_opvars(splev, "io",
				 VA_PASS2((long)(yyvsp[-2].i), SPO_ENGRAVING));
		  }
#line 4536 "lev_comp.y.c"
    break;

  case 292: /* mineralize: MINERALIZE_ID ':' integer_or_var ',' integer_or_var ',' integer_or_var ',' integer_or_var  */
#line 2052 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MINERALIZE));
		  }
#line 4544 "lev_comp.y.c"
    break;

  case 293: /* mineralize: MINERALIZE_ID  */
#line 2056 "lev_comp.y"
                  {
		      add_opvars(splev, "iiiio",
				 VA_PASS5(-1L, -1L, -1L, -1L, SPO_MINERALIZE));
		  }
#line 4553 "lev_comp.y.c"
    break;

  case 294: /* trap_name: STRING  */
#line 2063 "lev_comp.y"
                  {
			int token = get_trap_type((yyvsp[0].map));
			if (token == ERR)
			    lc_error("Unknown trap type '%s'!", (yyvsp[0].map));
			(yyval.i) = token;
			Free((yyvsp[0].map));
		  }
#line 4565 "lev_comp.y.c"
    break;

  case 296: /* room_type: STRING  */
#line 2074 "lev_comp.y"
                  {
			int token = get_room_type((yyvsp[0].map));
			if (token == ERR) {
			    lc_warning("Unknown room type \"%s\"!  Making ordinary room...", (yyvsp[0].map));
				(yyval.i) = OROOM;
			} else
				(yyval.i) = token;
			Free((yyvsp[0].map));
		  }
#line 4579 "lev_comp.y.c"
    break;

  case 298: /* optroomregionflags: %empty  */
#line 2087 "lev_comp.y"
                  {
			(yyval.i) = -1;
		  }
#line 4587 "lev_comp.y.c"
    break;

  case 299: /* optroomregionflags: ',' roomregionflags  */
#line 2091 "lev_comp.y"
                  {
			(yyval.i) = (yyvsp[0].i);
		  }
#line 4595 "lev_comp.y.c"
    break;

  case 300: /* roomregionflags: roomregionflag  */
#line 2097 "lev_comp.y"
                  {
			(yyval.i) = (yyvsp[0].i);
		  }
#line 4603 "lev_comp.y.c"
    break;

  case 301: /* roomregionflags: roomregionflag ',' roomregionflags  */
#line 2101 "lev_comp.y"
                  {
			(yyval.i) = (yyvsp[-2].i) | (yyvsp[0].i);
		  }
#line 4611 "lev_comp.y.c"
    break;

  case 302: /* roomregionflag: FILLING  */
#line 2108 "lev_comp.y"
                  {
		      (yyval.i) = ((yyvsp[0].i) << 0);
		  }
#line 4619 "lev_comp.y.c"
    break;

  case 303: /* roomregionflag: IRREGULAR  */
#line 2112 "lev_comp.y"
                  {
		      (yyval.i) = ((yyvsp[0].i) << 1);
		  }
#line 4627 "lev_comp.y.c"
    break;

  case 304: /* roomregionflag: JOINED  */
#line 2116 "lev_comp.y"
                  {
		      (yyval.i) = ((yyvsp[0].i) << 2);
		  }
#line 4635 "lev_comp.y.c"
    break;

  case 311: /* alignment: RANDOM_TYPE  */
#line 2132 "lev_comp.y"
                  {
			(yyval.i) = - MAX_REGISTERS - 1;
		  }
#line 4643 "lev_comp.y.c"
    break;

  case 314: /* alignment_prfx: A_REGISTER ':' RANDOM_TYPE  */
#line 2140 "lev_comp.y"
                  {
			(yyval.i) = - MAX_REGISTERS - 1;
		  }
#line 4651 "lev_comp.y.c"
    break;

  case 317: /* a_register: A_REGISTER '[' INTEGER ']'  */
#line 2150 "lev_comp.y"
                  {
			if ( (yyvsp[-1].i) >= 3 )
				lc_error("Register Index overflow!");
			else
				(yyval.i) = - (yyvsp[-1].i) - 1;
		  }
#line 4662 "lev_comp.y.c"
    break;

  case 318: /* string_or_var: STRING  */
#line 2159 "lev_comp.y"
                  {
		      add_opvars(splev, "s", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 4671 "lev_comp.y.c"
    break;

  case 319: /* string_or_var: VARSTRING_STRING  */
#line 2164 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_STRING);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 4682 "lev_comp.y.c"
    break;

  case 320: /* string_or_var: VARSTRING_STRING_ARRAY '[' math_expr_var ']'  */
#line 2171 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[-3].map),
                                        SPOVAR_STRING | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[-3].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[-3].map)));
		      Free((yyvsp[-3].map));
		  }
#line 4694 "lev_comp.y.c"
    break;

  case 321: /* integer_or_var: math_expr_var  */
#line 2182 "lev_comp.y"
                  {
		      /* nothing */
		  }
#line 4702 "lev_comp.y.c"
    break;

  case 322: /* coord_or_var: encodecoord  */
#line 2188 "lev_comp.y"
                  {
		      add_opvars(splev, "c", VA_PASS1((yyvsp[0].i)));
		  }
#line 4710 "lev_comp.y.c"
    break;

  case 323: /* coord_or_var: rndcoord_ID '(' ter_selection ')'  */
#line 2192 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_RNDCOORD));
		  }
#line 4718 "lev_comp.y.c"
    break;

  case 324: /* coord_or_var: VARSTRING_COORD  */
#line 2196 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_COORD);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 4729 "lev_comp.y.c"
    break;

  case 325: /* coord_or_var: VARSTRING_COORD_ARRAY '[' math_expr_var ']'  */
#line 2203 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[-3].map),
                                        SPOVAR_COORD | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[-3].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[-3].map)));
		      Free((yyvsp[-3].map));
		  }
#line 4741 "lev_comp.y.c"
    break;

  case 326: /* encodecoord: '(' INTEGER ',' INTEGER ')'  */
#line 2213 "lev_comp.y"
                  {
		      if ((yyvsp[-3].i) < 0 || (yyvsp[-1].i) < 0 || (yyvsp[-3].i) >= COLNO || (yyvsp[-1].i) >= ROWNO)
                          lc_error("Coordinates (%li,%li) out of map range!",
                                   (yyvsp[-3].i), (yyvsp[-1].i));
		      (yyval.i) = SP_COORD_PACK((yyvsp[-3].i), (yyvsp[-1].i));
		  }
#line 4752 "lev_comp.y.c"
    break;

  case 327: /* encodecoord: RANDOM_TYPE  */
#line 2220 "lev_comp.y"
                  {
		      (yyval.i) = SP_COORD_PACK_RANDOM(0);
		  }
#line 4760 "lev_comp.y.c"
    break;

  case 328: /* encodecoord: RANDOM_TYPE_BRACKET humidity_flags ']'  */
#line 2224 "lev_comp.y"
                  {
		      (yyval.i) = SP_COORD_PACK_RANDOM((yyvsp[-1].i));
		  }
#line 4768 "lev_comp.y.c"
    break;

  case 329: /* humidity_flags: HUMIDITY_TYPE  */
#line 2230 "lev_comp.y"
                  {
		      (yyval.i) = (yyvsp[0].i);
		  }
#line 4776 "lev_comp.y.c"
    break;

  case 330: /* humidity_flags: HUMIDITY_TYPE ',' humidity_flags  */
#line 2234 "lev_comp.y"
                  {
		      if (((yyvsp[-2].i) & (yyvsp[0].i)))
			  lc_warning("Humidity flag used twice.");
		      (yyval.i) = ((yyvsp[-2].i) | (yyvsp[0].i));
		  }
#line 4786 "lev_comp.y.c"
    break;

  case 331: /* region_or_var: encoderegion  */
#line 2242 "lev_comp.y"
                  {
		      /* nothing */
		  }
#line 4794 "lev_comp.y.c"
    break;

  case 332: /* region_or_var: VARSTRING_REGION  */
#line 2246 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_REGION);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 4805 "lev_comp.y.c"
    break;

  case 333: /* region_or_var: VARSTRING_REGION_ARRAY '[' math_expr_var ']'  */
#line 2253 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[-3].map),
                                        SPOVAR_REGION | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[-3].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[-3].map)));
		      Free((yyvsp[-3].map));
		  }
#line 4817 "lev_comp.y.c"
    break;

  case 334: /* encoderegion: '(' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ')'  */
#line 2263 "lev_comp.y"
                  {
		      long r = SP_REGION_PACK((yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));

		      if ((yyvsp[-7].i) > (yyvsp[-3].i) || (yyvsp[-5].i) > (yyvsp[-1].i))
			  lc_error("Region start > end: (%ld,%ld,%ld,%ld)!",
                                   (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));

		      add_opvars(splev, "r", VA_PASS1(r));
		      (yyval.i) = r;
		  }
#line 4832 "lev_comp.y.c"
    break;

  case 335: /* mapchar_or_var: mapchar  */
#line 2276 "lev_comp.y"
                  {
		      add_opvars(splev, "m", VA_PASS1((yyvsp[0].i)));
		  }
#line 4840 "lev_comp.y.c"
    break;

  case 336: /* mapchar_or_var: VARSTRING_MAPCHAR  */
#line 2280 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_MAPCHAR);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 4851 "lev_comp.y.c"
    break;

  case 337: /* mapchar_or_var: VARSTRING_MAPCHAR_ARRAY '[' math_expr_var ']'  */
#line 2287 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[-3].map),
                                        SPOVAR_MAPCHAR | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[-3].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[-3].map)));
		      Free((yyvsp[-3].map));
		  }
#line 4863 "lev_comp.y.c"
    break;

  case 338: /* mapchar: CHAR  */
#line 2297 "lev_comp.y"
                  {
		      if (what_map_char((char) (yyvsp[0].i)) != INVALID_TYPE)
			  (yyval.i) = SP_MAPCHAR_PACK(what_map_char((char) (yyvsp[0].i)), -2);
		      else {
			  lc_error("Unknown map char type '%c'!", (yyvsp[0].i));
			  (yyval.i) = SP_MAPCHAR_PACK(STONE, -2);
		      }
		  }
#line 4876 "lev_comp.y.c"
    break;

  case 339: /* mapchar: '(' CHAR ',' light_state ')'  */
#line 2306 "lev_comp.y"
                  {
		      if (what_map_char((char) (yyvsp[-3].i)) != INVALID_TYPE)
			  (yyval.i) = SP_MAPCHAR_PACK(what_map_char((char) (yyvsp[-3].i)), (yyvsp[-1].i));
		      else {
			  lc_error("Unknown map char type '%c'!", (yyvsp[-3].i));
			  (yyval.i) = SP_MAPCHAR_PACK(STONE, (yyvsp[-1].i));
		      }
		  }
#line 4889 "lev_comp.y.c"
    break;

  case 340: /* monster_or_var: encodemonster  */
#line 2317 "lev_comp.y"
                  {
		      add_opvars(splev, "M", VA_PASS1((yyvsp[0].i)));
		  }
#line 4897 "lev_comp.y.c"
    break;

  case 341: /* monster_or_var: VARSTRING_MONST  */
#line 2321 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_MONST);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 4908 "lev_comp.y.c"
    break;

  case 342: /* monster_or_var: VARSTRING_MONST_ARRAY '[' math_expr_var ']'  */
#line 2328 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[-3].map),
                                        SPOVAR_MONST | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[-3].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[-3].map)));
		      Free((yyvsp[-3].map));
		  }
#line 4920 "lev_comp.y.c"
    break;

  case 343: /* encodemonster: STRING  */
#line 2338 "lev_comp.y"
                  {
                      long m = get_monster_id((yyvsp[0].map), (char)0);
                      if (m == ERR) {
                          lc_error("Unknown monster \"%s\"!", (yyvsp[0].map));
                          (yyval.i) = -1;
                      } else
                          (yyval.i) = SP_MONST_PACK(m,
                                         def_monsyms[(int) mons[m].mlet].sym);
                      Free((yyvsp[0].map));
                  }
#line 4935 "lev_comp.y.c"
    break;

  case 344: /* encodemonster: CHAR  */
#line 2349 "lev_comp.y"
                  {
                        if (check_monster_char((char) (yyvsp[0].i)))
                            (yyval.i) = SP_MONST_PACK(-1, (yyvsp[0].i));
                        else {
                            lc_error("Unknown monster class '%c'!", (yyvsp[0].i));
                            (yyval.i) = -1;
                        }
                  }
#line 4948 "lev_comp.y.c"
    break;

  case 345: /* encodemonster: '(' CHAR ',' STRING ')'  */
#line 2358 "lev_comp.y"
                  {
                      long m = get_monster_id((yyvsp[-1].map), (char) (yyvsp[-3].i));
                      if (m == ERR) {
                          lc_error("Unknown monster ('%c', \"%s\")!", (yyvsp[-3].i), (yyvsp[-1].map));
                          (yyval.i) = -1;
                      } else
                          (yyval.i) = SP_MONST_PACK(m, (yyvsp[-3].i));
                      Free((yyvsp[-1].map));
                  }
#line 4962 "lev_comp.y.c"
    break;

  case 346: /* encodemonster: RANDOM_TYPE  */
#line 2368 "lev_comp.y"
                  {
                      (yyval.i) = -1;
                  }
#line 4970 "lev_comp.y.c"
    break;

  case 347: /* object_or_var: encodeobj  */
#line 2374 "lev_comp.y"
                  {
		      add_opvars(splev, "O", VA_PASS1((yyvsp[0].i)));
		  }
#line 4978 "lev_comp.y.c"
    break;

  case 348: /* object_or_var: VARSTRING_OBJ  */
#line 2378 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_OBJ);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 4989 "lev_comp.y.c"
    break;

  case 349: /* object_or_var: VARSTRING_OBJ_ARRAY '[' math_expr_var ']'  */
#line 2385 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[-3].map),
                                        SPOVAR_OBJ | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[-3].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[-3].map)));
		      Free((yyvsp[-3].map));
		  }
#line 5001 "lev_comp.y.c"
    break;

  case 350: /* encodeobj: STRING  */
#line 2395 "lev_comp.y"
                  {
		      long m = get_object_id((yyvsp[0].map), (char)0);
		      if (m == ERR) {
			  lc_error("Unknown object \"%s\"!", (yyvsp[0].map));
			  (yyval.i) = -1;
		      } else
                          /* obj class != 0 to force generation of a specific item */
                          (yyval.i) = SP_OBJ_PACK(m, 1);
                      Free((yyvsp[0].map));
		  }
#line 5016 "lev_comp.y.c"
    break;

  case 351: /* encodeobj: CHAR  */
#line 2406 "lev_comp.y"
                  {
			if (check_object_char((char) (yyvsp[0].i)))
			    (yyval.i) = SP_OBJ_PACK(-1, (yyvsp[0].i));
			else {
			    lc_error("Unknown object class '%c'!", (yyvsp[0].i));
			    (yyval.i) = -1;
			}
		  }
#line 5029 "lev_comp.y.c"
    break;

  case 352: /* encodeobj: '(' CHAR ',' STRING ')'  */
#line 2415 "lev_comp.y"
                  {
		      long m = get_object_id((yyvsp[-1].map), (char) (yyvsp[-3].i));
		      if (m == ERR) {
			  lc_error("Unknown object ('%c', \"%s\")!", (yyvsp[-3].i), (yyvsp[-1].map));
			  (yyval.i) = -1;
		      } else
			  (yyval.i) = SP_OBJ_PACK(m, (yyvsp[-3].i));
                      Free((yyvsp[-1].map));
		  }
#line 5043 "lev_comp.y.c"
    break;

  case 353: /* encodeobj: RANDOM_TYPE  */
#line 2425 "lev_comp.y"
                  {
		      (yyval.i) = -1;
		  }
#line 5051 "lev_comp.y.c"
    break;

  case 354: /* string_expr: string_or_var  */
#line 2431 "lev_comp.y"
                                                { }
#line 5057 "lev_comp.y.c"
    break;

  case 355: /* string_expr: string_expr '.' string_or_var  */
#line 2433 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_ADD));
		  }
#line 5065 "lev_comp.y.c"
    break;

  case 356: /* math_expr_var: INTEGER  */
#line 2439 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[0].i)));
		  }
#line 5073 "lev_comp.y.c"
    break;

  case 357: /* math_expr_var: dice  */
#line 2443 "lev_comp.y"
                  {
		      is_inconstant_number = 1;
		  }
#line 5081 "lev_comp.y.c"
    break;

  case 358: /* math_expr_var: '(' MINUS_INTEGER ')'  */
#line 2447 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[-1].i)));
		  }
#line 5089 "lev_comp.y.c"
    break;

  case 359: /* math_expr_var: VARSTRING_INT  */
#line 2451 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_INT);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		      is_inconstant_number = 1;
		  }
#line 5101 "lev_comp.y.c"
    break;

  case 360: /* math_expr_var: VARSTRING_INT_ARRAY '[' math_expr_var ']'  */
#line 2459 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[-3].map),
					SPOVAR_INT | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[-3].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[-3].map)));
		      Free((yyvsp[-3].map));
		      is_inconstant_number = 1;
		  }
#line 5114 "lev_comp.y.c"
    break;

  case 361: /* math_expr_var: math_expr_var '+' math_expr_var  */
#line 2468 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_ADD));
		  }
#line 5122 "lev_comp.y.c"
    break;

  case 362: /* math_expr_var: math_expr_var '-' math_expr_var  */
#line 2472 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_SUB));
		  }
#line 5130 "lev_comp.y.c"
    break;

  case 363: /* math_expr_var: math_expr_var '*' math_expr_var  */
#line 2476 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_MUL));
		  }
#line 5138 "lev_comp.y.c"
    break;

  case 364: /* math_expr_var: math_expr_var '/' math_expr_var  */
#line 2480 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_DIV));
		  }
#line 5146 "lev_comp.y.c"
    break;

  case 365: /* math_expr_var: math_expr_var '%' math_expr_var  */
#line 2484 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_MOD));
		  }
#line 5154 "lev_comp.y.c"
    break;

  case 366: /* math_expr_var: '(' math_expr_var ')'  */
#line 2487 "lev_comp.y"
                                                    { }
#line 5160 "lev_comp.y.c"
    break;

  case 367: /* func_param_type: CFUNC_INT  */
#line 2491 "lev_comp.y"
                  {
		      if (!strcmp("int", (yyvsp[0].map)) || !strcmp("integer", (yyvsp[0].map))) {
			  (yyval.i) = (int)'i';
		      } else
			  lc_error("Unknown function parameter type '%s'", (yyvsp[0].map));
		  }
#line 5171 "lev_comp.y.c"
    break;

  case 368: /* func_param_type: CFUNC_STR  */
#line 2498 "lev_comp.y"
                  {
		      if (!strcmp("str", (yyvsp[0].map)) || !strcmp("string", (yyvsp[0].map))) {
			  (yyval.i) = (int)'s';
		      } else
			  lc_error("Unknown function parameter type '%s'", (yyvsp[0].map));
		  }
#line 5182 "lev_comp.y.c"
    break;

  case 369: /* func_param_part: any_var_or_arr ':' func_param_type  */
#line 2507 "lev_comp.y"
                  {
		      struct lc_funcdefs_parm *tmp = New(struct lc_funcdefs_parm);

		      if (!curr_function) {
			  lc_error("Function parameters outside function definition.");
		      } else if (!tmp) {
			  lc_error("Could not alloc function params.");
		      } else {
			  long vt = SPOVAR_NULL;

			  tmp->name = strdup((yyvsp[-2].map));
			  tmp->parmtype = (char) (yyvsp[0].i);
			  tmp->next = curr_function->params;
			  curr_function->params = tmp;
			  curr_function->n_params++;
			  switch (tmp->parmtype) {
			  case 'i':
                              vt = SPOVAR_INT;
                              break;
			  case 's':
                              vt = SPOVAR_STRING;
                              break;
			  default:
                              lc_error("Unknown func param conversion.");
                              break;
			  }
			  vardefs = add_vardef_type( vardefs, (yyvsp[-2].map), vt);
		      }
		      Free((yyvsp[-2].map));
		  }
#line 5217 "lev_comp.y.c"
    break;

  case 374: /* func_call_param_part: math_expr_var  */
#line 2548 "lev_comp.y"
                          {
			      (yyval.i) = (int)'i';
			  }
#line 5225 "lev_comp.y.c"
    break;

  case 375: /* func_call_param_part: string_expr  */
#line 2552 "lev_comp.y"
                          {
			      (yyval.i) = (int)'s';
			  }
#line 5233 "lev_comp.y.c"
    break;

  case 376: /* func_call_param_list: func_call_param_part  */
#line 2559 "lev_comp.y"
                          {
			      char tmpbuf[2];
			      tmpbuf[0] = (char) (yyvsp[0].i);
			      tmpbuf[1] = '\0';
			      (yyval.map) = strdup(tmpbuf);
			  }
#line 5244 "lev_comp.y.c"
    break;

  case 377: /* func_call_param_list: func_call_param_list ',' func_call_param_part  */
#line 2566 "lev_comp.y"
                          {
			      long len = strlen( (yyvsp[-2].map) );
			      char *tmp = (char *) alloc(len + 2);
			      sprintf(tmp, "%c%s", (char) (yyvsp[0].i), (yyvsp[-2].map) );
			      Free( (yyvsp[-2].map) );
			      (yyval.map) = tmp;
			  }
#line 5256 "lev_comp.y.c"
    break;

  case 378: /* func_call_params_list: %empty  */
#line 2576 "lev_comp.y"
                          {
			      (yyval.map) = strdup("");
			  }
#line 5264 "lev_comp.y.c"
    break;

  case 379: /* func_call_params_list: func_call_param_list  */
#line 2580 "lev_comp.y"
                          {
			      char *tmp = strdup( (yyvsp[0].map) );
			      Free( (yyvsp[0].map) );
			      (yyval.map) = tmp;
			  }
#line 5274 "lev_comp.y.c"
    break;

  case 380: /* ter_selection_x: coord_or_var  */
#line 2588 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_POINT));
		  }
#line 5282 "lev_comp.y.c"
    break;

  case 381: /* ter_selection_x: rect_ID region_or_var  */
#line 2592 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_RECT));
		  }
#line 5290 "lev_comp.y.c"
    break;

  case 382: /* ter_selection_x: fillrect_ID region_or_var  */
#line 2596 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_FILLRECT));
		  }
#line 5298 "lev_comp.y.c"
    break;

  case 383: /* ter_selection_x: line_ID coord_or_var ',' coord_or_var  */
#line 2600 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_LINE));
		  }
#line 5306 "lev_comp.y.c"
    break;

  case 384: /* ter_selection_x: randline_ID coord_or_var ',' coord_or_var ',' math_expr_var  */
#line 2604 "lev_comp.y"
                  {
		      /* randline (x1,y1),(x2,y2), roughness */
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_RNDLINE));
		  }
#line 5315 "lev_comp.y.c"
    break;

  case 385: /* ter_selection_x: grow_ID '(' ter_selection ')'  */
#line 2609 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(W_ANY, SPO_SEL_GROW));
		  }
#line 5323 "lev_comp.y.c"
    break;

  case 386: /* ter_selection_x: grow_ID '(' dir_list ',' ter_selection ')'  */
#line 2613 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2((yyvsp[-3].i), SPO_SEL_GROW));
		  }
#line 5331 "lev_comp.y.c"
    break;

  case 387: /* ter_selection_x: filter_ID '(' SPERCENT ',' ter_selection ')'  */
#line 2617 "lev_comp.y"
                  {
		      add_opvars(splev, "iio",
			     VA_PASS3((yyvsp[-3].i), SPOFILTER_PERCENT, SPO_SEL_FILTER));
		  }
#line 5340 "lev_comp.y.c"
    break;

  case 388: /* ter_selection_x: filter_ID '(' ter_selection ',' ter_selection ')'  */
#line 2622 "lev_comp.y"
                  {
		      add_opvars(splev, "io",
			       VA_PASS2(SPOFILTER_SELECTION, SPO_SEL_FILTER));
		  }
#line 5349 "lev_comp.y.c"
    break;

  case 389: /* ter_selection_x: filter_ID '(' mapchar_or_var ',' ter_selection ')'  */
#line 2627 "lev_comp.y"
                  {
		      add_opvars(splev, "io",
				 VA_PASS2(SPOFILTER_MAPCHAR, SPO_SEL_FILTER));
		  }
#line 5358 "lev_comp.y.c"
    break;

  case 390: /* ter_selection_x: flood_ID coord_or_var  */
#line 2632 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_FLOOD));
		  }
#line 5366 "lev_comp.y.c"
    break;

  case 391: /* ter_selection_x: circle_ID '(' coord_or_var ',' math_expr_var ')'  */
#line 2636 "lev_comp.y"
                  {
		      add_opvars(splev, "oio",
				 VA_PASS3(SPO_COPY, 1, SPO_SEL_ELLIPSE));
		  }
#line 5375 "lev_comp.y.c"
    break;

  case 392: /* ter_selection_x: circle_ID '(' coord_or_var ',' math_expr_var ',' FILLING ')'  */
#line 2641 "lev_comp.y"
                  {
		      add_opvars(splev, "oio",
				 VA_PASS3(SPO_COPY, (yyvsp[-1].i), SPO_SEL_ELLIPSE));
		  }
#line 5384 "lev_comp.y.c"
    break;

  case 393: /* ter_selection_x: ellipse_ID '(' coord_or_var ',' math_expr_var ',' math_expr_var ')'  */
#line 2646 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2(1, SPO_SEL_ELLIPSE));
		  }
#line 5392 "lev_comp.y.c"
    break;

  case 394: /* ter_selection_x: ellipse_ID '(' coord_or_var ',' math_expr_var ',' math_expr_var ',' FILLING ')'  */
#line 2650 "lev_comp.y"
                  {
		      add_opvars(splev, "io", VA_PASS2((yyvsp[-1].i), SPO_SEL_ELLIPSE));
		  }
#line 5400 "lev_comp.y.c"
    break;

  case 395: /* ter_selection_x: gradient_ID '(' GRADIENT_TYPE ',' '(' math_expr_var '-' math_expr_var opt_limited ')' ',' coord_or_var opt_coord_or_var ')'  */
#line 2654 "lev_comp.y"
                  {
		      add_opvars(splev, "iio",
				 VA_PASS3((yyvsp[-5].i), (yyvsp[-11].i), SPO_SEL_GRADIENT));
		  }
#line 5409 "lev_comp.y.c"
    break;

  case 396: /* ter_selection_x: complement_ID ter_selection_x  */
#line 2659 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_COMPLEMENT));
		  }
#line 5417 "lev_comp.y.c"
    break;

  case 397: /* ter_selection_x: VARSTRING_SEL  */
#line 2663 "lev_comp.y"
                  {
		      check_vardef_type(vardefs, (yyvsp[0].map), SPOVAR_SEL);
		      vardef_used(vardefs, (yyvsp[0].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[0].map)));
		      Free((yyvsp[0].map));
		  }
#line 5428 "lev_comp.y.c"
    break;

  case 398: /* ter_selection_x: '(' ter_selection ')'  */
#line 2670 "lev_comp.y"
                  {
		      /* nothing */
		  }
#line 5436 "lev_comp.y.c"
    break;

  case 399: /* ter_selection: ter_selection_x  */
#line 2676 "lev_comp.y"
                  {
		      /* nothing */
		  }
#line 5444 "lev_comp.y.c"
    break;

  case 400: /* ter_selection: ter_selection_x '&' ter_selection  */
#line 2680 "lev_comp.y"
                  {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_ADD));
		  }
#line 5452 "lev_comp.y.c"
    break;

  case 401: /* dice: DICE  */
#line 2686 "lev_comp.y"
                  {
		      add_opvars(splev, "iio",
				 VA_PASS3((yyvsp[0].dice).num, (yyvsp[0].dice).die, SPO_DICE));
		  }
#line 5461 "lev_comp.y.c"
    break;

  case 405: /* all_ints_push: MINUS_INTEGER  */
#line 2698 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[0].i)));
		  }
#line 5469 "lev_comp.y.c"
    break;

  case 406: /* all_ints_push: PLUS_INTEGER  */
#line 2702 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[0].i)));
		  }
#line 5477 "lev_comp.y.c"
    break;

  case 407: /* all_ints_push: INTEGER  */
#line 2706 "lev_comp.y"
                  {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[0].i)));
		  }
#line 5485 "lev_comp.y.c"
    break;

  case 408: /* all_ints_push: dice  */
#line 2710 "lev_comp.y"
                  {
		      /* nothing */
		  }
#line 5493 "lev_comp.y.c"
    break;

  case 417: /* lev_region: region  */
#line 2732 "lev_comp.y"
                  {
			(yyval.lregn) = (yyvsp[0].lregn);
		  }
#line 5501 "lev_comp.y.c"
    break;

  case 418: /* lev_region: LEV '(' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ')'  */
#line 2736 "lev_comp.y"
                  {
			if ((yyvsp[-7].i) <= 0 || (yyvsp[-7].i) >= COLNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (x1)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			else if ((yyvsp[-5].i) < 0 || (yyvsp[-5].i) >= ROWNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (y1)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			else if ((yyvsp[-3].i) <= 0 || (yyvsp[-3].i) >= COLNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (x2)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			else if ((yyvsp[-1].i) < 0 || (yyvsp[-1].i) >= ROWNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (y2)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			(yyval.lregn).x1 = (yyvsp[-7].i);
			(yyval.lregn).y1 = (yyvsp[-5].i);
			(yyval.lregn).x2 = (yyvsp[-3].i);
			(yyval.lregn).y2 = (yyvsp[-1].i);
			(yyval.lregn).area = 1;
		  }
#line 5529 "lev_comp.y.c"
    break;

  case 419: /* region: '(' INTEGER ',' INTEGER ',' INTEGER ',' INTEGER ')'  */
#line 2762 "lev_comp.y"
                  {
/* This series of if statements is a hack for MSC 5.1.  It seems that its
   tiny little brain cannot compile if these are all one big if statement. */
			if ((yyvsp[-7].i) < 0 || (yyvsp[-7].i) > (int) max_x_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (x1)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			else if ((yyvsp[-5].i) < 0 || (yyvsp[-5].i) > (int) max_y_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (y1)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			else if ((yyvsp[-3].i) < 0 || (yyvsp[-3].i) > (int) max_x_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (x2)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			else if ((yyvsp[-1].i) < 0 || (yyvsp[-1].i) > (int) max_y_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (y2)!",
                                     (yyvsp[-7].i), (yyvsp[-5].i), (yyvsp[-3].i), (yyvsp[-1].i));
			(yyval.lregn).area = 0;
			(yyval.lregn).x1 = (yyvsp[-7].i);
			(yyval.lregn).y1 = (yyvsp[-5].i);
			(yyval.lregn).x2 = (yyvsp[-3].i);
			(yyval.lregn).y2 = (yyvsp[-1].i);
		  }
#line 5559 "lev_comp.y.c"
    break;


#line 5563 "lev_comp.y.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2790 "lev_comp.y"


/*lev_comp.y*/
