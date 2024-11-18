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
#line 1 "syntax.y"

#include <stdio.h>
#include <iostream>
#include <string>
#include "Node.hpp"
extern int yyparse();
extern int yylex();
extern FILE* yyin;
Node* root = nullptr;
void yyerror(const std::string& s);

#line 83 "syntax.tab.c"

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

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INVALID = 3,                    /* INVALID  */
  YYSYMBOL_TYPE = 4,                       /* TYPE  */
  YYSYMBOL_STRUCT = 5,                     /* STRUCT  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_INCLUDE = 11,                   /* INCLUDE  */
  YYSYMBOL_DOT = 12,                       /* DOT  */
  YYSYMBOL_SEMI = 13,                      /* SEMI  */
  YYSYMBOL_COLON = 14,                     /* COLON  */
  YYSYMBOL_COMMA = 15,                     /* COMMA  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_LE = 18,                        /* LE  */
  YYSYMBOL_GT = 19,                        /* GT  */
  YYSYMBOL_GE = 20,                        /* GE  */
  YYSYMBOL_NE = 21,                        /* NE  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_PLUS = 23,                      /* PLUS  */
  YYSYMBOL_MINUS = 24,                     /* MINUS  */
  YYSYMBOL_MUL = 25,                       /* MUL  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_NOT = 29,                       /* NOT  */
  YYSYMBOL_LP = 30,                        /* LP  */
  YYSYMBOL_RP = 31,                        /* RP  */
  YYSYMBOL_LB = 32,                        /* LB  */
  YYSYMBOL_RB = 33,                        /* RB  */
  YYSYMBOL_LC = 34,                        /* LC  */
  YYSYMBOL_RC = 35,                        /* RC  */
  YYSYMBOL_ID = 36,                        /* ID  */
  YYSYMBOL_INTEGER = 37,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 38,                     /* FLOAT  */
  YYSYMBOL_CHAR = 39,                      /* CHAR  */
  YYSYMBOL_SINGLE_LINE_COMMENT = 40,       /* SINGLE_LINE_COMMENT  */
  YYSYMBOL_MULTI_LINE_COMMENT = 41,        /* MULTI_LINE_COMMENT  */
  YYSYMBOL_LOWER_ELSE = 42,                /* LOWER_ELSE  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_Program = 44,                   /* Program  */
  YYSYMBOL_ExtDefList = 45,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 46,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 47,                /* ExtDecList  */
  YYSYMBOL_Specifier = 48,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 49,           /* StructSpecifier  */
  YYSYMBOL_VarDec = 50,                    /* VarDec  */
  YYSYMBOL_FunDec = 51,                    /* FunDec  */
  YYSYMBOL_VarList = 52,                   /* VarList  */
  YYSYMBOL_ParamDec = 53,                  /* ParamDec  */
  YYSYMBOL_CompSt = 54,                    /* CompSt  */
  YYSYMBOL_StmtList = 55,                  /* StmtList  */
  YYSYMBOL_Stmt = 56,                      /* Stmt  */
  YYSYMBOL_DefList = 57,                   /* DefList  */
  YYSYMBOL_Def = 58,                       /* Def  */
  YYSYMBOL_DecList = 59,                   /* DecList  */
  YYSYMBOL_Dec = 60,                       /* Dec  */
  YYSYMBOL_Exp = 61,                       /* Exp  */
  YYSYMBOL_Args = 62,                      /* Args  */
  YYSYMBOL_Var = 63                        /* Var  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   832

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    41,    41,    43,    44,    47,    48,    49,    50,    51,
      52,    55,    56,    60,    61,    64,    65,    66,    67,    71,
      72,    73,    74,    75,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    90,    91,    94,    98,    99,   103,
     104,   105,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   131,   132,   135,   136,   139,   140,   143,   144,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   184,   186,   190,   192,   194,
     197,   198,   201,   202,   203,   204,   205
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
  "\"end of file\"", "error", "\"invalid token\"", "INVALID", "TYPE",
  "STRUCT", "IF", "ELSE", "WHILE", "FOR", "RETURN", "INCLUDE", "DOT",
  "SEMI", "COLON", "COMMA", "ASSIGN", "LT", "LE", "GT", "GE", "NE", "EQ",
  "PLUS", "MINUS", "MUL", "DIV", "AND", "OR", "NOT", "LP", "RP", "LB",
  "RB", "LC", "RC", "ID", "INTEGER", "FLOAT", "CHAR",
  "SINGLE_LINE_COMMENT", "MULTI_LINE_COMMENT", "LOWER_ELSE", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args",
  "Var", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      86,   -72,   -72,   -12,   -72,    29,   -72,    86,    32,    10,
     -72,    -7,   167,   -72,   -72,   -72,   -72,    63,   -72,   122,
      94,    35,    11,    67,    39,   165,    11,    45,   165,   123,
     -72,   129,   -72,   -72,   -72,   165,   -72,   -72,     2,   -72,
       6,    -6,   150,    72,   -72,   -72,   -72,   -72,    11,    43,
      96,   -72,   -72,    50,   440,   -72,   -72,   -72,   -72,   468,
     -72,   -72,    11,   -10,   -72,   -72,   165,   -72,   -72,   -72,
     105,   440,   112,   468,   -72,   468,   468,   468,   468,    84,
     -72,   -72,   -72,   -72,    31,   403,   526,   -72,   750,   -72,
     -72,   468,   457,   -72,   468,   468,   554,   181,   181,    56,
     582,    47,   -72,   -72,   -72,   165,   -72,   468,    93,   -72,
     120,   144,   161,   185,   202,   226,   243,   267,   284,   308,
     325,   349,   366,   468,   672,   130,   614,   698,   646,   -72,
     -72,   -72,   -72,   -72,   -72,   724,    66,   440,   767,   -72,
     -72,   767,   -72,   368,   -72,   368,   -72,   368,   -72,   368,
     -72,   368,   -72,   368,   -72,   181,   -72,   181,   -72,    56,
     -72,    56,   -72,   800,   -72,   784,   498,   440,   -72,   440,
     102,   440,   440,   440,   468,   -72,   -72,   -72,   -72,   -72,
     139,   141,   148,   154,   -72,   -72,   -72,   -72,   440,   440,
     440,   440,   -72,   -72,   -72,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    23,    13,     0,    19,     0,     2,     3,     0,     0,
      14,    11,    16,     1,     4,    10,     9,    23,     6,    19,
       0,     0,     0,     0,     0,    62,     0,     0,    62,     0,
      32,     0,    27,     8,     5,    62,     7,    12,     0,    22,
       0,    68,     0,    66,    18,    63,    33,    30,     0,     0,
      35,    28,    25,     0,    39,    21,    20,    17,    15,     0,
      65,    64,     0,    36,    31,    29,     0,    26,    24,   116,
       0,     0,     0,     0,    42,     0,     0,     0,     0,   113,
     112,   114,   115,    44,     0,    39,     0,    91,    69,    67,
      34,     0,     0,    61,     0,     0,     0,    84,    85,    86,
       0,     0,    38,    37,    40,    62,    49,     0,     0,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,    50,
      45,   106,    83,   108,    88,   111,     0,    39,   105,    90,
      92,    70,    95,    73,    96,    74,    97,    75,    98,    76,
      99,    77,   100,    78,   101,    79,   102,    80,   103,    81,
     104,    82,    93,    71,    94,    72,     0,     0,    52,     0,
       0,     0,     0,     0,     0,   107,    87,    41,   109,    89,
      55,    57,    53,    46,    59,    60,    48,   110,     0,     0,
       0,     0,    56,    58,    54,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   158,   -72,    70,     9,   -72,   -20,   -72,   -27,
     -72,   145,   -64,   -71,   -23,    90,   114,   -72,   -58,     3,
     -72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    26,    10,    11,    21,    49,
      50,    83,    84,    85,    27,    28,    42,    43,    86,   136,
      87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      93,    88,    40,    55,    53,    45,    41,    57,    22,     9,
      59,    16,    54,    17,     1,    96,     9,    97,    98,    99,
     100,   104,    23,    18,    12,    23,    23,    24,    63,    13,
      24,    24,   102,   124,   126,    56,   127,   128,    48,    90,
      48,    58,    41,   135,    64,    15,    19,     4,   133,   138,
      69,    67,   141,   143,   145,   147,   149,   151,   153,   155,
     157,   159,   161,   163,   165,   166,   103,   175,   108,    35,
      75,    76,    39,   177,    65,    48,    77,    78,   134,    20,
      44,    68,   137,    79,    80,    81,    82,    62,   123,     1,
       2,     3,    37,    29,    30,    33,   180,   176,   181,   183,
     184,   185,   186,   182,    38,    69,    91,    34,    70,    71,
      72,    66,    73,    94,   101,    74,   135,   192,   193,   194,
     195,   140,     4,    69,    46,    75,    76,     2,     3,   139,
      51,    77,    78,     2,     3,    92,    35,   168,    79,    80,
      81,    82,    95,    75,    76,   142,   188,    69,   189,    77,
      78,    60,    31,    32,    47,   190,    79,    80,    81,    82,
      52,   191,   144,    61,    69,    14,    36,    75,    76,     2,
       3,     2,     3,    77,    78,   105,    89,   187,     0,     0,
      79,    80,    81,    82,    75,    76,   146,     0,    69,     0,
      77,    78,     0,   108,     0,     0,     0,    79,    80,    81,
      82,    25,   -62,   148,     0,    69,   119,   120,    75,    76,
       0,     0,     0,   123,    77,    78,     0,     0,     0,     0,
       0,    79,    80,    81,    82,    75,    76,   150,     0,    69,
       0,    77,    78,     0,     0,     0,     0,     0,    79,    80,
      81,    82,     0,     0,   152,     0,    69,     0,     0,    75,
      76,     0,     0,     0,     0,    77,    78,     0,     0,     0,
       0,     0,    79,    80,    81,    82,    75,    76,   154,     0,
      69,     0,    77,    78,     0,     0,     0,     0,     0,    79,
      80,    81,    82,     0,     0,   156,     0,    69,     0,     0,
      75,    76,     0,     0,     0,     0,    77,    78,     0,     0,
       0,     0,     0,    79,    80,    81,    82,    75,    76,   158,
       0,    69,     0,    77,    78,     0,     0,     0,     0,     0,
      79,    80,    81,    82,     0,     0,   160,     0,    69,     0,
       0,    75,    76,     0,     0,     0,     0,    77,    78,     0,
       0,     0,     0,     0,    79,    80,    81,    82,    75,    76,
     162,     0,    69,     0,    77,    78,     0,     0,     0,     0,
       0,    79,    80,    81,    82,     0,     0,   164,     0,    69,
       0,     0,    75,    76,     0,     0,     0,     0,    77,    78,
     108,     0,     0,     0,     0,    79,    80,    81,    82,    75,
      76,   117,   118,   119,   120,    77,    78,     0,     0,     0,
     123,     0,    79,    80,    81,    82,    69,     2,     3,    70,
      71,    72,     0,    73,     0,     0,    74,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,    76,     0,     0,
       0,     0,    77,    78,     0,     0,     0,    35,     0,    79,
      80,    81,    82,    69,     0,     0,    70,    71,    72,     0,
      73,     0,     0,    74,     0,     0,     0,     0,     0,     0,
      69,     0,     0,    75,    76,     0,     0,     0,     0,    77,
      78,    69,     0,     0,    35,     0,    79,    80,    81,    82,
      75,    76,     0,     0,     0,     0,    77,    78,   125,     0,
       0,    75,    76,    79,    80,    81,    82,    77,    78,   178,
       0,   107,     0,     0,    79,    80,    81,    82,     0,     0,
     108,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   106,     0,   107,
     123,   179,     0,     0,     0,     0,     0,     0,   108,   109,
       0,     0,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   129,     0,   107,   123,     0,
       0,     0,     0,     0,     0,     0,   108,   130,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   131,     0,   107,   123,     0,     0,     0,
       0,     0,     0,     0,   108,     0,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,     0,     0,   132,   123,   169,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,     0,     0,   170,   123,   172,     0,   107,
       0,     0,     0,     0,     0,     0,     0,     0,   108,     0,
       0,     0,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   107,     0,   173,   123,     0,
       0,     0,     0,     0,   108,     0,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   107,     0,   167,   123,     0,     0,     0,     0,     0,
     108,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   107,     0,   171,
     123,     0,     0,     0,     0,     0,   108,     0,     0,   174,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   107,     0,     0,   123,     0,     0,     0,
       0,     0,   108,     0,     0,     0,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   108,
       0,     0,   123,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   108,     0,     0,   123,
       0,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   108,     0,     0,     0,   123,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     0,     0,     0,
       0,     0,   123
};

static const yytype_int16 yycheck[] =
{
      71,    59,    25,     1,    31,    28,    26,     1,    15,     0,
      16,     1,    35,     3,     3,    73,     7,    75,    76,    77,
      78,    85,    32,    13,    36,    32,    32,    37,    48,     0,
      37,    37,     1,    91,    92,    33,    94,    95,    29,    66,
      31,    35,    62,   101,     1,    13,    36,    36,     1,   107,
       3,     1,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,    35,     1,    12,    34,
      23,    24,    33,   137,    31,    66,    29,    30,    31,     9,
      35,    31,   105,    36,    37,    38,    39,    15,    32,     3,
       4,     5,    22,    30,    31,     1,   167,    31,   169,   170,
     171,   172,   173,     1,    37,     3,     1,    13,     6,     7,
       8,    15,    10,     1,    30,    13,   174,   188,   189,   190,
     191,     1,    36,     3,     1,    23,    24,     4,     5,    36,
       1,    29,    30,     4,     5,    30,    34,     7,    36,    37,
      38,    39,    30,    23,    24,     1,     7,     3,     7,    29,
      30,     1,    30,    31,    31,     7,    36,    37,    38,    39,
      31,     7,     1,    13,     3,     7,    21,    23,    24,     4,
       5,     4,     5,    29,    30,    85,    62,   174,    -1,    -1,
      36,    37,    38,    39,    23,    24,     1,    -1,     3,    -1,
      29,    30,    -1,    12,    -1,    -1,    -1,    36,    37,    38,
      39,    34,    35,     1,    -1,     3,    25,    26,    23,    24,
      -1,    -1,    -1,    32,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    23,    24,     1,    -1,     3,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    -1,     1,    -1,     3,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    23,    24,     1,    -1,
       3,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    -1,     1,    -1,     3,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    23,    24,     1,
      -1,     3,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    -1,     1,    -1,     3,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    23,    24,
       1,    -1,     3,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    -1,     1,    -1,     3,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      12,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    23,
      24,    23,    24,    25,    26,    29,    30,    -1,    -1,    -1,
      32,    -1,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,    -1,    10,    -1,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    -1,    -1,    -1,    34,    -1,    36,
      37,    38,    39,     3,    -1,    -1,     6,     7,     8,    -1,
      10,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,     3,    -1,    -1,    34,    -1,    36,    37,    38,    39,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      -1,    23,    24,    36,    37,    38,    39,    29,    30,     1,
      -1,     3,    -1,    -1,    36,    37,    38,    39,    -1,    -1,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     1,    -1,     3,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     1,    -1,     3,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    -1,    -1,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     1,    -1,     3,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,     1,    -1,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,     1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     3,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     3,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     3,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     3,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    12,
      -1,    -1,    32,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    12,    -1,    -1,    32,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    12,    -1,    -1,    -1,    32,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    36,    44,    45,    46,    47,    48,
      49,    50,    36,     0,    45,    13,     1,     3,    13,    36,
      47,    51,    15,    32,    37,    34,    48,    57,    58,    30,
      31,    30,    31,     1,    13,    34,    54,    47,    37,    33,
      57,    50,    59,    60,    35,    57,     1,    31,    48,    52,
      53,     1,    31,    52,    57,     1,    33,     1,    35,    16,
       1,    13,    15,    50,     1,    31,    15,     1,    31,     3,
       6,     7,     8,    10,    13,    23,    24,    29,    30,    36,
      37,    38,    39,    54,    55,    56,    61,    63,    61,    59,
      52,     1,    30,    56,     1,    30,    61,    61,    61,    61,
      61,    30,     1,    35,    55,    58,     1,     3,    12,    13,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    32,    61,    31,    61,    61,    61,     1,
      13,     1,    31,     1,    31,    61,    62,    57,    61,    36,
       1,    61,     1,    61,     1,    61,     1,    61,     1,    61,
       1,    61,     1,    61,     1,    61,     1,    61,     1,    61,
       1,    61,     1,    61,     1,    61,    61,    31,     7,     1,
      31,    31,     1,    31,    15,     1,    31,    55,     1,    33,
      56,    56,     1,    56,    56,    56,    56,    62,     7,     7,
       7,     7,    56,    56,    56,    56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    50,
      50,    50,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    54,    54,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      62,    62,    63,    63,    63,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     3,     2,
       2,     1,     3,     1,     1,     5,     2,     5,     4,     1,
       4,     4,     3,     1,     4,     3,     4,     2,     3,     4,
       3,     4,     2,     3,     3,     1,     2,     4,     4,     0,
       2,     4,     1,     2,     1,     3,     5,     7,     5,     2,
       3,     3,     4,     5,     7,     5,     7,     5,     7,     5,
       5,     2,     0,     2,     3,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     4,     3,     4,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     4,
       3,     1,     1,     1,     1,     1,     1
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
  case 2: /* Program: ExtDefList  */
#line 41 "syntax.y"
                     {  (yyval.node) = Node::makeNode(NodeType::Program, {(yyvsp[0].node)});root = (yyval.node);std::cout<<"result:"<<*root<<std::endl;}
#line 1391 "syntax.tab.c"
    break;

  case 3: /* ExtDefList: %empty  */
#line 43 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::ExtDefList);}
#line 1397 "syntax.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 44 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::ExtDefList,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1403 "syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 47 "syntax.y"
                                    { (yyval.node) = Node::makeNode(NodeType::ExtDef,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1409 "syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 48 "syntax.y"
                                    { (yyval.node) = Node::makeNode(NodeType::ExtDef,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1415 "syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 49 "syntax.y"
                                    { (yyval.node) = Node::makeNode(NodeType::ExtDef,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1421 "syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier ExtDecList error  */
#line 50 "syntax.y"
                                    { (yyval.node) = Node::makeNode(NodeType::ExtDef); yyerror("Type B,Missing semicolon \';\'") ;}
#line 1427 "syntax.tab.c"
    break;

  case 9: /* ExtDef: Specifier error  */
#line 51 "syntax.y"
                                    { (yyval.node) = Node::makeNode(NodeType::ExtDef);   yyerror("Type B,Missing semicolon \';\'"); }
#line 1433 "syntax.tab.c"
    break;

  case 10: /* ExtDef: ExtDecList SEMI  */
#line 52 "syntax.y"
                              { (yyval.node) = Node::makeNode(NodeType::ExtDef);  yyerror("Type B,Missing specifier \';\'"); }
#line 1439 "syntax.tab.c"
    break;

  case 11: /* ExtDecList: VarDec  */
#line 55 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::ExtDecList,{(yyvsp[0].node)}); }
#line 1445 "syntax.tab.c"
    break;

  case 12: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 56 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::ExtDecList,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1451 "syntax.tab.c"
    break;

  case 13: /* Specifier: TYPE  */
#line 60 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Specifier,{(yyvsp[0].node)}); }
#line 1457 "syntax.tab.c"
    break;

  case 14: /* Specifier: StructSpecifier  */
#line 61 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Specifier,{(yyvsp[0].node)}); }
#line 1463 "syntax.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT ID LC DefList RC  */
#line 64 "syntax.y"
                                            { (yyval.node) = Node::makeNode(NodeType::StructSpecifier,{(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1469 "syntax.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT ID  */
#line 65 "syntax.y"
                                            { (yyval.node) = Node::makeNode(NodeType::StructSpecifier,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1475 "syntax.tab.c"
    break;

  case 17: /* StructSpecifier: STRUCT ID LC DefList error  */
#line 66 "syntax.y"
                                            { (yyval.node) = Node::makeNode(NodeType::StructSpecifier);  yyerror("Type B,Missing closing curly braces \'}\'") ;}
#line 1481 "syntax.tab.c"
    break;

  case 18: /* StructSpecifier: STRUCT ID DefList RC  */
#line 67 "syntax.y"
                                            { (yyval.node) = Node::makeNode(NodeType::StructSpecifier);   yyerror("Type B,Missing closing curly braces \'{\'") ; }
#line 1487 "syntax.tab.c"
    break;

  case 19: /* VarDec: ID  */
#line 71 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::VarDec,{(yyvsp[0].node)}); }
#line 1493 "syntax.tab.c"
    break;

  case 20: /* VarDec: VarDec LB INTEGER RB  */
#line 72 "syntax.y"
                               { (yyval.node) = Node::makeNode(NodeType::VarDec,{(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1499 "syntax.tab.c"
    break;

  case 21: /* VarDec: VarDec LB INTEGER error  */
#line 73 "syntax.y"
                               { (yyval.node) = Node::makeNode(NodeType::VarDec); yyerror("Type B,Missing closing braces \']\'");}
#line 1505 "syntax.tab.c"
    break;

  case 22: /* VarDec: VarDec INTEGER RB  */
#line 74 "syntax.y"
                               { (yyval.node) = Node::makeNode(NodeType::VarDec);  yyerror("Type B,Missing closing braces \']\'");}
#line 1511 "syntax.tab.c"
    break;

  case 23: /* VarDec: INVALID  */
#line 75 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::VarDec);  }
#line 1517 "syntax.tab.c"
    break;

  case 24: /* FunDec: ID LP VarList RP  */
#line 78 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::FunDec,{(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1523 "syntax.tab.c"
    break;

  case 25: /* FunDec: ID LP RP  */
#line 79 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::FunDec,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1529 "syntax.tab.c"
    break;

  case 26: /* FunDec: ID LP VarList error  */
#line 80 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \')\'") ;}
#line 1535 "syntax.tab.c"
    break;

  case 27: /* FunDec: ID RP  */
#line 81 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \'(\'") ;}
#line 1541 "syntax.tab.c"
    break;

  case 28: /* FunDec: ID LP error  */
#line 82 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \')\'"); }
#line 1547 "syntax.tab.c"
    break;

  case 29: /* FunDec: INVALID LP VarList RP  */
#line 83 "syntax.y"
                              { (yyval.node) = Node::makeNode(NodeType::FunDec);  }
#line 1553 "syntax.tab.c"
    break;

  case 30: /* FunDec: INVALID LP RP  */
#line 84 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::FunDec);  }
#line 1559 "syntax.tab.c"
    break;

  case 31: /* FunDec: INVALID LP VarList error  */
#line 85 "syntax.y"
                                 { (yyval.node) = Node::makeNode(NodeType::FunDec);  }
#line 1565 "syntax.tab.c"
    break;

  case 32: /* FunDec: INVALID RP  */
#line 86 "syntax.y"
                                 { (yyval.node) = Node::makeNode(NodeType::FunDec);  }
#line 1571 "syntax.tab.c"
    break;

  case 33: /* FunDec: INVALID LP error  */
#line 87 "syntax.y"
                                 { (yyval.node) = Node::makeNode(NodeType::FunDec);  }
#line 1577 "syntax.tab.c"
    break;

  case 34: /* VarList: ParamDec COMMA VarList  */
#line 90 "syntax.y"
                                    { (yyval.node) = Node::makeNode(NodeType::VarList,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1583 "syntax.tab.c"
    break;

  case 35: /* VarList: ParamDec  */
#line 91 "syntax.y"
                                    { (yyval.node) = Node::makeNode(NodeType::VarList,{(yyvsp[0].node)}); }
#line 1589 "syntax.tab.c"
    break;

  case 36: /* ParamDec: Specifier VarDec  */
#line 94 "syntax.y"
                            { (yyval.node) = Node::makeNode(NodeType::ParamDec,{(yyvsp[-1].node),(yyvsp[0].node)});  }
#line 1595 "syntax.tab.c"
    break;

  case 37: /* CompSt: LC DefList StmtList RC  */
#line 98 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::CompSt,{(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1601 "syntax.tab.c"
    break;

  case 38: /* CompSt: LC DefList StmtList error  */
#line 99 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::CompSt); yyerror("Type B,Missing closing curly bracket \'}\'") ;}
#line 1607 "syntax.tab.c"
    break;

  case 39: /* StmtList: %empty  */
#line 103 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::StmtList);  }
#line 1613 "syntax.tab.c"
    break;

  case 40: /* StmtList: Stmt StmtList  */
#line 104 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::StmtList,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1619 "syntax.tab.c"
    break;

  case 41: /* StmtList: Stmt Def DefList StmtList  */
#line 105 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::StmtList); yyerror("Type B,Missing specifier") ;}
#line 1625 "syntax.tab.c"
    break;

  case 42: /* Stmt: SEMI  */
#line 108 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt,{(yyvsp[0].node)}); }
#line 1631 "syntax.tab.c"
    break;

  case 43: /* Stmt: Exp SEMI  */
#line 109 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1637 "syntax.tab.c"
    break;

  case 44: /* Stmt: CompSt  */
#line 110 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt,{(yyvsp[0].node)});}
#line 1643 "syntax.tab.c"
    break;

  case 45: /* Stmt: RETURN Exp SEMI  */
#line 111 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1649 "syntax.tab.c"
    break;

  case 46: /* Stmt: IF LP Exp RP Stmt  */
#line 112 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt,{(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1655 "syntax.tab.c"
    break;

  case 47: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 113 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt,{(yyvsp[-6].node),(yyvsp[-5].node),(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});  }
#line 1661 "syntax.tab.c"
    break;

  case 48: /* Stmt: WHILE LP Exp RP Stmt  */
#line 114 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt,{(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1667 "syntax.tab.c"
    break;

  case 49: /* Stmt: Exp error  */
#line 115 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt); yyerror("Type B,Missing semicolon \';\'") ;}
#line 1673 "syntax.tab.c"
    break;

  case 50: /* Stmt: RETURN Exp error  */
#line 116 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing semicolon \';\'") ; }
#line 1679 "syntax.tab.c"
    break;

  case 51: /* Stmt: IF LP RP  */
#line 117 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing condition \';\'") ; }
#line 1685 "syntax.tab.c"
    break;

  case 52: /* Stmt: IF LP RP ELSE  */
#line 118 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing condition \';\'") ; }
#line 1691 "syntax.tab.c"
    break;

  case 53: /* Stmt: IF LP Exp RP error  */
#line 119 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expect Stmt after if") ; }
#line 1697 "syntax.tab.c"
    break;

  case 54: /* Stmt: IF LP Exp RP error ELSE Stmt  */
#line 120 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expect Stmt after if") ;  }
#line 1703 "syntax.tab.c"
    break;

  case 55: /* Stmt: IF error Exp RP Stmt  */
#line 121 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'if\'") ; }
#line 1709 "syntax.tab.c"
    break;

  case 56: /* Stmt: IF error Exp RP Stmt ELSE Stmt  */
#line 122 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'if\'") ; }
#line 1715 "syntax.tab.c"
    break;

  case 57: /* Stmt: IF LP Exp error Stmt  */
#line 123 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ; }
#line 1721 "syntax.tab.c"
    break;

  case 58: /* Stmt: IF LP Exp error Stmt ELSE Stmt  */
#line 124 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ;  }
#line 1727 "syntax.tab.c"
    break;

  case 59: /* Stmt: WHILE error Exp RP Stmt  */
#line 125 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'while\'") ; }
#line 1733 "syntax.tab.c"
    break;

  case 60: /* Stmt: WHILE LP Exp error Stmt  */
#line 126 "syntax.y"
                                                { (yyval.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ; }
#line 1739 "syntax.tab.c"
    break;

  case 61: /* Stmt: ELSE Stmt  */
#line 127 "syntax.y"
                { (yyval.node) = Node::makeNode(NodeType::Stmt); yyerror("Type B,Expected \'if\' before \'else\'"); }
#line 1745 "syntax.tab.c"
    break;

  case 62: /* DefList: %empty  */
#line 131 "syntax.y"
                    { (yyval.node) = Node::makeNode(NodeType::DefList); }
#line 1751 "syntax.tab.c"
    break;

  case 63: /* DefList: Def DefList  */
#line 132 "syntax.y"
                    { (yyval.node) = Node::makeNode(NodeType::DefList,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1757 "syntax.tab.c"
    break;

  case 64: /* Def: Specifier DecList SEMI  */
#line 135 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::Def,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});  }
#line 1763 "syntax.tab.c"
    break;

  case 65: /* Def: Specifier DecList error  */
#line 136 "syntax.y"
                                { (yyval.node) = Node::makeNode(NodeType::Def,{(yyvsp[-2].node),(yyvsp[-1].node)}); yyerror("Type B,Missing semicolon \';\'");}
#line 1769 "syntax.tab.c"
    break;

  case 66: /* DecList: Dec  */
#line 139 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::DecList,{(yyvsp[0].node)}); }
#line 1775 "syntax.tab.c"
    break;

  case 67: /* DecList: Dec COMMA DecList  */
#line 140 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::DecList,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1781 "syntax.tab.c"
    break;

  case 68: /* Dec: VarDec  */
#line 143 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Dec,{(yyvsp[0].node)});}
#line 1787 "syntax.tab.c"
    break;

  case 69: /* Dec: VarDec ASSIGN Exp  */
#line 144 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Dec,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1793 "syntax.tab.c"
    break;

  case 70: /* Exp: Exp ASSIGN Exp  */
#line 148 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1799 "syntax.tab.c"
    break;

  case 71: /* Exp: Exp AND Exp  */
#line 149 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1805 "syntax.tab.c"
    break;

  case 72: /* Exp: Exp OR Exp  */
#line 150 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1811 "syntax.tab.c"
    break;

  case 73: /* Exp: Exp LT Exp  */
#line 151 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1817 "syntax.tab.c"
    break;

  case 74: /* Exp: Exp LE Exp  */
#line 152 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1823 "syntax.tab.c"
    break;

  case 75: /* Exp: Exp GT Exp  */
#line 153 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1829 "syntax.tab.c"
    break;

  case 76: /* Exp: Exp GE Exp  */
#line 154 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1835 "syntax.tab.c"
    break;

  case 77: /* Exp: Exp NE Exp  */
#line 155 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1841 "syntax.tab.c"
    break;

  case 78: /* Exp: Exp EQ Exp  */
#line 156 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1847 "syntax.tab.c"
    break;

  case 79: /* Exp: Exp PLUS Exp  */
#line 157 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1853 "syntax.tab.c"
    break;

  case 80: /* Exp: Exp MINUS Exp  */
#line 158 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1859 "syntax.tab.c"
    break;

  case 81: /* Exp: Exp MUL Exp  */
#line 159 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1865 "syntax.tab.c"
    break;

  case 82: /* Exp: Exp DIV Exp  */
#line 160 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1871 "syntax.tab.c"
    break;

  case 83: /* Exp: LP Exp RP  */
#line 161 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1877 "syntax.tab.c"
    break;

  case 84: /* Exp: PLUS Exp  */
#line 162 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1883 "syntax.tab.c"
    break;

  case 85: /* Exp: MINUS Exp  */
#line 163 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1889 "syntax.tab.c"
    break;

  case 86: /* Exp: NOT Exp  */
#line 164 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1895 "syntax.tab.c"
    break;

  case 87: /* Exp: ID LP Args RP  */
#line 165 "syntax.y"
                        {  (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1901 "syntax.tab.c"
    break;

  case 88: /* Exp: ID LP RP  */
#line 166 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1907 "syntax.tab.c"
    break;

  case 89: /* Exp: Exp LB Exp RB  */
#line 167 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)});}
#line 1913 "syntax.tab.c"
    break;

  case 90: /* Exp: Exp DOT ID  */
#line 168 "syntax.y"
                        {(yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 1919 "syntax.tab.c"
    break;

  case 91: /* Exp: Var  */
#line 169 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp,{(yyvsp[0].node)}); }
#line 1925 "syntax.tab.c"
    break;

  case 92: /* Exp: Exp ASSIGN error  */
#line 170 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp); yyerror("Type B,Missing right operand");}
#line 1931 "syntax.tab.c"
    break;

  case 93: /* Exp: Exp AND error  */
#line 171 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand"); }
#line 1937 "syntax.tab.c"
    break;

  case 94: /* Exp: Exp OR error  */
#line 172 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand"); }
#line 1943 "syntax.tab.c"
    break;

  case 95: /* Exp: Exp LT error  */
#line 173 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1949 "syntax.tab.c"
    break;

  case 96: /* Exp: Exp LE error  */
#line 174 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1955 "syntax.tab.c"
    break;

  case 97: /* Exp: Exp GT error  */
#line 175 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1961 "syntax.tab.c"
    break;

  case 98: /* Exp: Exp GE error  */
#line 176 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1967 "syntax.tab.c"
    break;

  case 99: /* Exp: Exp NE error  */
#line 177 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1973 "syntax.tab.c"
    break;

  case 100: /* Exp: Exp EQ error  */
#line 178 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1979 "syntax.tab.c"
    break;

  case 101: /* Exp: Exp PLUS error  */
#line 179 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1985 "syntax.tab.c"
    break;

  case 102: /* Exp: Exp MINUS error  */
#line 180 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1991 "syntax.tab.c"
    break;

  case 103: /* Exp: Exp MUL error  */
#line 181 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1997 "syntax.tab.c"
    break;

  case 104: /* Exp: Exp DIV error  */
#line 182 "syntax.y"
                          { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 2003 "syntax.tab.c"
    break;

  case 105: /* Exp: Exp INVALID Exp  */
#line 184 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp);  }
#line 2009 "syntax.tab.c"
    break;

  case 106: /* Exp: LP Exp error  */
#line 186 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Missing closing parenthesis \')\'") ; }
#line 2015 "syntax.tab.c"
    break;

  case 107: /* Exp: ID LP Args error  */
#line 190 "syntax.y"
                        {(yyval.node) = Node::makeNode(NodeType::Exp);   yyerror("Missing closing parenthesis \')\'") ; }
#line 2021 "syntax.tab.c"
    break;

  case 108: /* Exp: ID LP error  */
#line 192 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp);   yyerror("Missing closing parenthesis \')\'") ; }
#line 2027 "syntax.tab.c"
    break;

  case 109: /* Exp: Exp LB Exp error  */
#line 194 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing closing braces \']\'") ; }
#line 2033 "syntax.tab.c"
    break;

  case 110: /* Args: Exp COMMA Args  */
#line 197 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Args,{(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)}); }
#line 2039 "syntax.tab.c"
    break;

  case 111: /* Args: Exp  */
#line 198 "syntax.y"
                        { (yyval.node) = Node::makeNode(NodeType::Args,{(yyvsp[0].node)}); }
#line 2045 "syntax.tab.c"
    break;

  case 112: /* Var: INTEGER  */
#line 201 "syntax.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2051 "syntax.tab.c"
    break;

  case 113: /* Var: ID  */
#line 202 "syntax.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2057 "syntax.tab.c"
    break;

  case 114: /* Var: FLOAT  */
#line 203 "syntax.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2063 "syntax.tab.c"
    break;

  case 115: /* Var: CHAR  */
#line 204 "syntax.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2069 "syntax.tab.c"
    break;

  case 116: /* Var: INVALID  */
#line 205 "syntax.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2075 "syntax.tab.c"
    break;


#line 2079 "syntax.tab.c"

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

#line 208 "syntax.y"


void yyerror(const std::string& s) {
    
    std::cerr << "Error: " << s << std::endl;
}

int main() {
    yyin = stdin;
    do {
        yyparse();
    } while (!feof(yyin));
    return 0;
}
