/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LEV_COMP_Y_H_INCLUDED
# define YY_YY_LEV_COMP_Y_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CHAR = 258,                    /* CHAR  */
    INTEGER = 259,                 /* INTEGER  */
    BOOLEAN = 260,                 /* BOOLEAN  */
    PERCENT = 261,                 /* PERCENT  */
    SPERCENT = 262,                /* SPERCENT  */
    MINUS_INTEGER = 263,           /* MINUS_INTEGER  */
    PLUS_INTEGER = 264,            /* PLUS_INTEGER  */
    MAZE_GRID_ID = 265,            /* MAZE_GRID_ID  */
    SOLID_FILL_ID = 266,           /* SOLID_FILL_ID  */
    MINES_ID = 267,                /* MINES_ID  */
    ROGUELEV_ID = 268,             /* ROGUELEV_ID  */
    MESSAGE_ID = 269,              /* MESSAGE_ID  */
    MAZE_ID = 270,                 /* MAZE_ID  */
    LEVEL_ID = 271,                /* LEVEL_ID  */
    LEV_INIT_ID = 272,             /* LEV_INIT_ID  */
    GEOMETRY_ID = 273,             /* GEOMETRY_ID  */
    NOMAP_ID = 274,                /* NOMAP_ID  */
    OBJECT_ID = 275,               /* OBJECT_ID  */
    COBJECT_ID = 276,              /* COBJECT_ID  */
    MONSTER_ID = 277,              /* MONSTER_ID  */
    TRAP_ID = 278,                 /* TRAP_ID  */
    DOOR_ID = 279,                 /* DOOR_ID  */
    DRAWBRIDGE_ID = 280,           /* DRAWBRIDGE_ID  */
    object_ID = 281,               /* object_ID  */
    monster_ID = 282,              /* monster_ID  */
    terrain_ID = 283,              /* terrain_ID  */
    MAZEWALK_ID = 284,             /* MAZEWALK_ID  */
    WALLIFY_ID = 285,              /* WALLIFY_ID  */
    REGION_ID = 286,               /* REGION_ID  */
    FILLING = 287,                 /* FILLING  */
    IRREGULAR = 288,               /* IRREGULAR  */
    JOINED = 289,                  /* JOINED  */
    ALTAR_ID = 290,                /* ALTAR_ID  */
    LADDER_ID = 291,               /* LADDER_ID  */
    STAIR_ID = 292,                /* STAIR_ID  */
    NON_DIGGABLE_ID = 293,         /* NON_DIGGABLE_ID  */
    NON_PASSWALL_ID = 294,         /* NON_PASSWALL_ID  */
    ROOM_ID = 295,                 /* ROOM_ID  */
    PORTAL_ID = 296,               /* PORTAL_ID  */
    TELEPRT_ID = 297,              /* TELEPRT_ID  */
    BRANCH_ID = 298,               /* BRANCH_ID  */
    LEV = 299,                     /* LEV  */
    MINERALIZE_ID = 300,           /* MINERALIZE_ID  */
    CORRIDOR_ID = 301,             /* CORRIDOR_ID  */
    GOLD_ID = 302,                 /* GOLD_ID  */
    ENGRAVING_ID = 303,            /* ENGRAVING_ID  */
    FORGE_ID = 304,                /* FORGE_ID  */
    MAGIC_CHEST_ID = 305,          /* MAGIC_CHEST_ID  */
    FOUNTAIN_ID = 306,             /* FOUNTAIN_ID  */
    PUDDLE_ID = 307,               /* PUDDLE_ID  */
    SEWAGE_ID = 308,               /* SEWAGE_ID  */
    POOL_ID = 309,                 /* POOL_ID  */
    SINK_ID = 310,                 /* SINK_ID  */
    NONE = 311,                    /* NONE  */
    RAND_CORRIDOR_ID = 312,        /* RAND_CORRIDOR_ID  */
    DOOR_STATE = 313,              /* DOOR_STATE  */
    LIGHT_STATE = 314,             /* LIGHT_STATE  */
    CURSE_TYPE = 315,              /* CURSE_TYPE  */
    ENGRAVING_TYPE = 316,          /* ENGRAVING_TYPE  */
    DIRECTION = 317,               /* DIRECTION  */
    RANDOM_TYPE = 318,             /* RANDOM_TYPE  */
    RANDOM_TYPE_BRACKET = 319,     /* RANDOM_TYPE_BRACKET  */
    A_REGISTER = 320,              /* A_REGISTER  */
    ALIGNMENT = 321,               /* ALIGNMENT  */
    LEFT_OR_RIGHT = 322,           /* LEFT_OR_RIGHT  */
    CENTER = 323,                  /* CENTER  */
    TOP_OR_BOT = 324,              /* TOP_OR_BOT  */
    ALTAR_TYPE = 325,              /* ALTAR_TYPE  */
    UP_OR_DOWN = 326,              /* UP_OR_DOWN  */
    SUBROOM_ID = 327,              /* SUBROOM_ID  */
    NAME_ID = 328,                 /* NAME_ID  */
    FLAGS_ID = 329,                /* FLAGS_ID  */
    FLAG_TYPE = 330,               /* FLAG_TYPE  */
    MON_ATTITUDE = 331,            /* MON_ATTITUDE  */
    MON_ALERTNESS = 332,           /* MON_ALERTNESS  */
    MON_APPEARANCE = 333,          /* MON_APPEARANCE  */
    ROOMDOOR_ID = 334,             /* ROOMDOOR_ID  */
    IF_ID = 335,                   /* IF_ID  */
    ELSE_ID = 336,                 /* ELSE_ID  */
    TERRAIN_ID = 337,              /* TERRAIN_ID  */
    HORIZ_OR_VERT = 338,           /* HORIZ_OR_VERT  */
    REPLACE_TERRAIN_ID = 339,      /* REPLACE_TERRAIN_ID  */
    EXIT_ID = 340,                 /* EXIT_ID  */
    SHUFFLE_ID = 341,              /* SHUFFLE_ID  */
    QUANTITY_ID = 342,             /* QUANTITY_ID  */
    BURIED_ID = 343,               /* BURIED_ID  */
    LOOP_ID = 344,                 /* LOOP_ID  */
    FOR_ID = 345,                  /* FOR_ID  */
    TO_ID = 346,                   /* TO_ID  */
    SWITCH_ID = 347,               /* SWITCH_ID  */
    CASE_ID = 348,                 /* CASE_ID  */
    BREAK_ID = 349,                /* BREAK_ID  */
    DEFAULT_ID = 350,              /* DEFAULT_ID  */
    ERODED_ID = 351,               /* ERODED_ID  */
    TRAPPED_STATE = 352,           /* TRAPPED_STATE  */
    RECHARGED_ID = 353,            /* RECHARGED_ID  */
    INVIS_ID = 354,                /* INVIS_ID  */
    GREASED_ID = 355,              /* GREASED_ID  */
    FEMALE_ID = 356,               /* FEMALE_ID  */
    CANCELLED_ID = 357,            /* CANCELLED_ID  */
    REVIVED_ID = 358,              /* REVIVED_ID  */
    AVENGE_ID = 359,               /* AVENGE_ID  */
    FLEEING_ID = 360,              /* FLEEING_ID  */
    BLINDED_ID = 361,              /* BLINDED_ID  */
    PARALYZED_ID = 362,            /* PARALYZED_ID  */
    STUNNED_ID = 363,              /* STUNNED_ID  */
    CONFUSED_ID = 364,             /* CONFUSED_ID  */
    SEENTRAPS_ID = 365,            /* SEENTRAPS_ID  */
    DEAD_ID = 366,                 /* DEAD_ID  */
    ALL_ID = 367,                  /* ALL_ID  */
    MONTYPE_ID = 368,              /* MONTYPE_ID  */
    GRAVE_ID = 369,                /* GRAVE_ID  */
    ERODEPROOF_ID = 370,           /* ERODEPROOF_ID  */
    FUNCTION_ID = 371,             /* FUNCTION_ID  */
    MSG_OUTPUT_TYPE = 372,         /* MSG_OUTPUT_TYPE  */
    COMPARE_TYPE = 373,            /* COMPARE_TYPE  */
    VAULTGEN_ID = 374,             /* VAULTGEN_ID  */
    MINDEPTH_ID = 375,             /* MINDEPTH_ID  */
    UNKNOWN_TYPE = 376,            /* UNKNOWN_TYPE  */
    rect_ID = 377,                 /* rect_ID  */
    fillrect_ID = 378,             /* fillrect_ID  */
    line_ID = 379,                 /* line_ID  */
    randline_ID = 380,             /* randline_ID  */
    grow_ID = 381,                 /* grow_ID  */
    selection_ID = 382,            /* selection_ID  */
    flood_ID = 383,                /* flood_ID  */
    rndcoord_ID = 384,             /* rndcoord_ID  */
    circle_ID = 385,               /* circle_ID  */
    ellipse_ID = 386,              /* ellipse_ID  */
    filter_ID = 387,               /* filter_ID  */
    complement_ID = 388,           /* complement_ID  */
    gradient_ID = 389,             /* gradient_ID  */
    GRADIENT_TYPE = 390,           /* GRADIENT_TYPE  */
    LIMITED = 391,                 /* LIMITED  */
    HUMIDITY_TYPE = 392,           /* HUMIDITY_TYPE  */
    STRING = 393,                  /* STRING  */
    MAP_ID = 394,                  /* MAP_ID  */
    NQSTRING = 395,                /* NQSTRING  */
    VARSTRING = 396,               /* VARSTRING  */
    CFUNC = 397,                   /* CFUNC  */
    CFUNC_INT = 398,               /* CFUNC_INT  */
    CFUNC_STR = 399,               /* CFUNC_STR  */
    CFUNC_COORD = 400,             /* CFUNC_COORD  */
    CFUNC_REGION = 401,            /* CFUNC_REGION  */
    VARSTRING_INT = 402,           /* VARSTRING_INT  */
    VARSTRING_INT_ARRAY = 403,     /* VARSTRING_INT_ARRAY  */
    VARSTRING_STRING = 404,        /* VARSTRING_STRING  */
    VARSTRING_STRING_ARRAY = 405,  /* VARSTRING_STRING_ARRAY  */
    VARSTRING_VAR = 406,           /* VARSTRING_VAR  */
    VARSTRING_VAR_ARRAY = 407,     /* VARSTRING_VAR_ARRAY  */
    VARSTRING_COORD = 408,         /* VARSTRING_COORD  */
    VARSTRING_COORD_ARRAY = 409,   /* VARSTRING_COORD_ARRAY  */
    VARSTRING_REGION = 410,        /* VARSTRING_REGION  */
    VARSTRING_REGION_ARRAY = 411,  /* VARSTRING_REGION_ARRAY  */
    VARSTRING_MAPCHAR = 412,       /* VARSTRING_MAPCHAR  */
    VARSTRING_MAPCHAR_ARRAY = 413, /* VARSTRING_MAPCHAR_ARRAY  */
    VARSTRING_MONST = 414,         /* VARSTRING_MONST  */
    VARSTRING_MONST_ARRAY = 415,   /* VARSTRING_MONST_ARRAY  */
    VARSTRING_OBJ = 416,           /* VARSTRING_OBJ  */
    VARSTRING_OBJ_ARRAY = 417,     /* VARSTRING_OBJ_ARRAY  */
    VARSTRING_SEL = 418,           /* VARSTRING_SEL  */
    VARSTRING_SEL_ARRAY = 419,     /* VARSTRING_SEL_ARRAY  */
    METHOD_INT = 420,              /* METHOD_INT  */
    METHOD_INT_ARRAY = 421,        /* METHOD_INT_ARRAY  */
    METHOD_STRING = 422,           /* METHOD_STRING  */
    METHOD_STRING_ARRAY = 423,     /* METHOD_STRING_ARRAY  */
    METHOD_VAR = 424,              /* METHOD_VAR  */
    METHOD_VAR_ARRAY = 425,        /* METHOD_VAR_ARRAY  */
    METHOD_COORD = 426,            /* METHOD_COORD  */
    METHOD_COORD_ARRAY = 427,      /* METHOD_COORD_ARRAY  */
    METHOD_REGION = 428,           /* METHOD_REGION  */
    METHOD_REGION_ARRAY = 429,     /* METHOD_REGION_ARRAY  */
    METHOD_MAPCHAR = 430,          /* METHOD_MAPCHAR  */
    METHOD_MAPCHAR_ARRAY = 431,    /* METHOD_MAPCHAR_ARRAY  */
    METHOD_MONST = 432,            /* METHOD_MONST  */
    METHOD_MONST_ARRAY = 433,      /* METHOD_MONST_ARRAY  */
    METHOD_OBJ = 434,              /* METHOD_OBJ  */
    METHOD_OBJ_ARRAY = 435,        /* METHOD_OBJ_ARRAY  */
    METHOD_SEL = 436,              /* METHOD_SEL  */
    METHOD_SEL_ARRAY = 437,        /* METHOD_SEL_ARRAY  */
    DICE = 438                     /* DICE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 154 "lev_comp.y"

    long    i;
    char    *map;
    struct {
        long room;
        long wall;
        long door;
    } corpos;
    struct {
        long area;
        long x1;
        long y1;
        long x2;
        long y2;
    } lregn;
    struct {
        long x;
        long y;
    } crd;
    struct {
        long ter;
        long lit;
    } terr;
    struct {
        long height;
        long width;
    } sze;
    struct {
        long die;
        long num;
    } dice;
    struct {
        long cfunc;
        char *varstr;
    } meth;

#line 284 "lev_comp.y.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LEV_COMP_Y_H_INCLUDED  */
