/* A Bison parser, made by GNU Bison 3.7.5.  */

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/workspace/SYsU-lang/parser/build/parser.y"

#include "parser.hh"
#include "asg.hpp"
#include <vector>
#include <cstring>
#include <memory>
#include <llvm/Support/JSON.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <cassert>

#define yyerror(x)                                                             \
  do {                                                                         \
    llvm::errs() << (x);                                                       \
  } while (0)

namespace {
auto llvmin = llvm::MemoryBuffer::getFileOrSTDIN("-");
auto input = llvmin.get() -> getBuffer();
auto end = input.end(), it = input.begin();
auto wk_getline(char endline = "\n"[0]) {
  auto beg = it;
  while (it != end && *it != endline && *it != -1)
    ++it;
  auto len = it - beg;
  if (it != end && *it == endline && *it != -1)
    ++it;
  return llvm::StringRef(beg, len);
}
} // namespace

Obj* root;
Mgr gMgr;

auto yylex() {
  auto tk = wk_getline();
  if(tk.empty())
    return YYEOF;
  auto b = tk.find("'") + 1, e = tk.rfind("'");
  auto s = tk.substr(b, e - b).str(), t = tk.substr(0, tk.find(" ")).str();
  if (t == "void")
    return T_VOID;
  if (t == "const")
    return T_CONST;
  if (t == "char")
    return T_CHAR;
  if (t == "long")
    return T_LONG;
  if (t == "int")
    return T_INT;
  if (t == "float")
    return T_FLOAT;
  if (t == "double")
    return T_DOUBLE;  
  if (t == "if")
    return T_IF;
  if (t == "else")
    return T_ELSE;
  if (t == "do")
    return T_DO;
  if (t == "while")
    return T_WHILE;
  if (t == "break")
    return T_BREAK;
  if (t == "continue")
    return T_CONTINUE;
  if (t == "return")
    return T_RETURN;
  if (t == "l_paren")
    return T_LEFT_PAREN;
  if (t == "r_paren")
    return T_RIGHT_PAREN;
  if (t == "l_square")
    return T_LEFT_SQUARE;
  if (t == "r_square")
    return T_RIGHT_SQUARE;
  if (t == "l_brace")
    return T_LEFT_BRACE;
  if (t == "r_brace")
    return T_RIGHT_BRACE;
  if (t == "comma")
    return T_COMMA;
  if (t == "semi")
    return T_SEMI;
  if (t == "equal")
    return T_EQUAL;  
  if (t == "exclaim")
    return T_EXCLAIM;
  if (t == "plus")
    return T_PLUS;  
  if (t == "minus")
    return T_MINUS;
  if (t == "star")
    return T_STAR;
  if (t == "slash")
    return T_SLASH;  
  if (t == "percent")
    return T_PERCENT;  
  if (t == "less")
    return T_LESS;  
  if (t == "greater")
    return T_GREATER;  
  if (t == "lessequal")
    return T_LESSEQUAL;
  if (t == "greaterequal")
    return T_GREATEREQUAL;
  if (t == "equalequal")
    return T_EQUALEQUAL;
  if (t == "exclaimequal")
    return T_EXCLAIMEQUAL;
  if (t == "ampamp")
    return T_AMPAMP;
  if (t == "pipepipe")
    return T_PIPEPIPE;
  if (t == "ellipsis")
    return T_ELLIPSIS;
  if (t == "identifier") { //TODO
    auto decl = gMgr.make<Decl>();
    decl->name = s;
    yylval.decl = decl;
    return T_IDENTIFIER;
  }    
  if (t == "numeric_constant") { //TODO
    //浮点数
    if (s.find('.') != std::string::npos || s.find('p') != std::string::npos || s.find('e') != std::string::npos)
    {
      auto expr = gMgr.make<FloatingLiteral>();
      expr->type.basic_type = Type::my_double;
      expr->kind = "FloatingLiteral";
      expr->value = s;
      expr->val = std::stod((std::string)(s));      
      llvm::StringRef str(expr->value);
      llvm::APFloat apf(0.0);
      auto status = apf.convertFromString(str, llvm::APFloat::rmNearestTiesToEven); // 检查返回值
      llvm::SmallString<16> Buffer;
      apf.toString(Buffer);
      expr->value = Buffer.c_str();
      yylval.expr = expr;
      return T_FLOATING_LITERAL;
    }
    else{ //整数
      auto expr = gMgr.make<IntegerLiteral>();
      expr->type.basic_type = Type::my_int;
      expr->kind = "IntegerLiteral";
      if(s[0] == '0' && (s[1] == 'x' || s[1] == 'X')){
        expr->val = std::stoi((std::string)(s), 0, 16);
        expr->value = std::to_string(expr->val);
      }
      else{
        expr->val = std::stoi((std::string)(s));
        expr->value = std::to_string(expr->val);
      }
      expr->type.basic_type = Type::my_int;
      yylval.expr = expr;
      return T_INTEGER_LITERAL;
    }
  }  
  if (t == "string_literal") { //TODO
    auto expr = gMgr.make<StringLiteral>();
    expr->type.basic_type = Type::my_char;
    expr->kind = "StringLiteral";
    expr->value = s;
    expr->type.basic_type = Type::my_char;
    expr->type.is_array = 1;
    expr->type.dim.push_back(s.size());
    yylval.expr = expr;
    return T_STRING_LITERAL;
  }
  if (t == "char_constant") { //TODO
    auto expr = gMgr.make<CharacterLiteral>();
    expr->type.basic_type = Type::my_char;
    expr->kind = "CharacterLiteral";
    expr->value = s;
    if(s[1] != '\\')
      expr->val = s[1];
    else if(s[2] == 'n')
      expr->val = '\n';
    expr->type.basic_type = Type::my_int;
    yylval.expr = expr;
    return T_CHAR_LITERAL;
  }
  if (t == "eof") { //TODO
    return T_EOF;
  }
  return YYEOF;
}



#line 261 "/workspace/SYsU-lang/parser/build/parser.cc"

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

#include "parser.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_VOID = 3,                     /* T_VOID  */
  YYSYMBOL_T_CONST = 4,                    /* T_CONST  */
  YYSYMBOL_T_CHAR = 5,                     /* T_CHAR  */
  YYSYMBOL_T_LONG = 6,                     /* T_LONG  */
  YYSYMBOL_T_INT = 7,                      /* T_INT  */
  YYSYMBOL_T_FLOAT = 8,                    /* T_FLOAT  */
  YYSYMBOL_T_DOUBLE = 9,                   /* T_DOUBLE  */
  YYSYMBOL_T_IF = 10,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 11,                    /* T_ELSE  */
  YYSYMBOL_T_DO = 12,                      /* T_DO  */
  YYSYMBOL_T_WHILE = 13,                   /* T_WHILE  */
  YYSYMBOL_T_BREAK = 14,                   /* T_BREAK  */
  YYSYMBOL_T_CONTINUE = 15,                /* T_CONTINUE  */
  YYSYMBOL_T_RETURN = 16,                  /* T_RETURN  */
  YYSYMBOL_T_LEFT_BRACE = 17,              /* T_LEFT_BRACE  */
  YYSYMBOL_T_RIGHT_BRACE = 18,             /* T_RIGHT_BRACE  */
  YYSYMBOL_T_SEMI = 19,                    /* T_SEMI  */
  YYSYMBOL_T_EOF = 20,                     /* T_EOF  */
  YYSYMBOL_T_COMMA = 21,                   /* T_COMMA  */
  YYSYMBOL_T_EQUAL = 22,                   /* T_EQUAL  */
  YYSYMBOL_T_PIPEPIPE = 23,                /* T_PIPEPIPE  */
  YYSYMBOL_T_AMPAMP = 24,                  /* T_AMPAMP  */
  YYSYMBOL_T_EQUALEQUAL = 25,              /* T_EQUALEQUAL  */
  YYSYMBOL_T_EXCLAIMEQUAL = 26,            /* T_EXCLAIMEQUAL  */
  YYSYMBOL_T_LESS = 27,                    /* T_LESS  */
  YYSYMBOL_T_GREATER = 28,                 /* T_GREATER  */
  YYSYMBOL_T_LESSEQUAL = 29,               /* T_LESSEQUAL  */
  YYSYMBOL_T_GREATEREQUAL = 30,            /* T_GREATEREQUAL  */
  YYSYMBOL_T_PLUS = 31,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 32,                   /* T_MINUS  */
  YYSYMBOL_T_STAR = 33,                    /* T_STAR  */
  YYSYMBOL_T_SLASH = 34,                   /* T_SLASH  */
  YYSYMBOL_T_PERCENT = 35,                 /* T_PERCENT  */
  YYSYMBOL_T_EXCLAIM = 36,                 /* T_EXCLAIM  */
  YYSYMBOL_UOP = 37,                       /* UOP  */
  YYSYMBOL_T_LEFT_SQUARE = 38,             /* T_LEFT_SQUARE  */
  YYSYMBOL_T_RIGHT_SQUARE = 39,            /* T_RIGHT_SQUARE  */
  YYSYMBOL_T_LEFT_PAREN = 40,              /* T_LEFT_PAREN  */
  YYSYMBOL_T_RIGHT_PAREN = 41,             /* T_RIGHT_PAREN  */
  YYSYMBOL_T_ELLIPSIS = 42,                /* T_ELLIPSIS  */
  YYSYMBOL_T_IDENTIFIER = 43,              /* T_IDENTIFIER  */
  YYSYMBOL_T_INTEGER_LITERAL = 44,         /* T_INTEGER_LITERAL  */
  YYSYMBOL_T_FLOATING_LITERAL = 45,        /* T_FLOATING_LITERAL  */
  YYSYMBOL_T_STRING_LITERAL = 46,          /* T_STRING_LITERAL  */
  YYSYMBOL_T_CHAR_LITERAL = 47,            /* T_CHAR_LITERAL  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_start = 49,                     /* start  */
  YYSYMBOL_translationunitdecl = 50,       /* translationunitdecl  */
  YYSYMBOL_declarationseq = 51,            /* declarationseq  */
  YYSYMBOL_declaration = 52,               /* declaration  */
  YYSYMBOL_emptydecl = 53,                 /* emptydecl  */
  YYSYMBOL_vardeclseq = 54,                /* vardeclseq  */
  YYSYMBOL_declaratorlist = 55,            /* declaratorlist  */
  YYSYMBOL_declarator = 56,                /* declarator  */
  YYSYMBOL_uninitdeclarator = 57,          /* uninitdeclarator  */
  YYSYMBOL_arrayuninitdeclaratorlist = 58, /* arrayuninitdeclaratorlist  */
  YYSYMBOL_ptruninitdeclarator = 59,       /* ptruninitdeclarator  */
  YYSYMBOL_functiondecl = 60,              /* functiondecl  */
  YYSYMBOL_paramslist = 61,                /* paramslist  */
  YYSYMBOL_parmvardecl = 62,               /* parmvardecl  */
  YYSYMBOL_typespecifier = 63,             /* typespecifier  */
  YYSYMBOL_typemodifier = 64,              /* typemodifier  */
  YYSYMBOL_simpletypespecifier = 65,       /* simpletypespecifier  */
  YYSYMBOL_primaryexpr = 66,               /* primaryexpr  */
  YYSYMBOL_numexpr = 67,                   /* numexpr  */
  YYSYMBOL_literalexpr = 68,               /* literalexpr  */
  YYSYMBOL_unaryoperator = 69,             /* unaryoperator  */
  YYSYMBOL_binaryoperator = 70,            /* binaryoperator  */
  YYSYMBOL_parenexpr = 71,                 /* parenexpr  */
  YYSYMBOL_declrefexpr = 72,               /* declrefexpr  */
  YYSYMBOL_arraysubscriptexpr = 73,        /* arraysubscriptexpr  */
  YYSYMBOL_lvalexpr = 74,                  /* lvalexpr  */
  YYSYMBOL_callexpr = 75,                  /* callexpr  */
  YYSYMBOL_bracedlistexpr = 76,            /* bracedlistexpr  */
  YYSYMBOL_primaryexprlist = 77,           /* primaryexprlist  */
  YYSYMBOL_condition = 78,                 /* condition  */
  YYSYMBOL_stmt = 79,                      /* stmt  */
  YYSYMBOL_compoundstmt = 80,              /* compoundstmt  */
  YYSYMBOL_stmtseq = 81,                   /* stmtseq  */
  YYSYMBOL_nullstmt = 82,                  /* nullstmt  */
  YYSYMBOL_declstmt = 83,                  /* declstmt  */
  YYSYMBOL_assignstmt = 84,                /* assignstmt  */
  YYSYMBOL_callexprstmt = 85,              /* callexprstmt  */
  YYSYMBOL_returnstmt = 86,                /* returnstmt  */
  YYSYMBOL_ifstmt = 87,                    /* ifstmt  */
  YYSYMBOL_dostmt = 88,                    /* dostmt  */
  YYSYMBOL_whilestmt = 89,                 /* whilestmt  */
  YYSYMBOL_breakstmt = 90,                 /* breakstmt  */
  YYSYMBOL_continuestmt = 91               /* continuestmt  */
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   328

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   307,   307,   313,   325,   340,   347,   348,   349,   353,
     362,   377,   383,   392,   399,   411,   412,   420,   426,   433,
     438,   447,   448,   459,   477,   502,   506,   512,   518,   527,
     534,   548,   556,   560,   569,   575,   580,   586,   592,   598,
     610,   611,   615,   616,   617,   618,   619,   620,   621,   622,
     626,   627,   628,   632,   639,   646,   657,   665,   673,   681,
     689,   697,   705,   713,   721,   729,   737,   745,   753,   761,
     772,   781,   790,   802,   817,   818,   822,   830,   845,   856,
     862,   871,   880,   881,   882,   883,   884,   885,   886,   887,
     888,   889,   890,   894,   906,   910,   919,   927,   940,   950,
     963,   968,   977,   984,   995,  1005,  1015,  1023
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
  "\"end of file\"", "error", "\"invalid token\"", "T_VOID", "T_CONST",
  "T_CHAR", "T_LONG", "T_INT", "T_FLOAT", "T_DOUBLE", "T_IF", "T_ELSE",
  "T_DO", "T_WHILE", "T_BREAK", "T_CONTINUE", "T_RETURN", "T_LEFT_BRACE",
  "T_RIGHT_BRACE", "T_SEMI", "T_EOF", "T_COMMA", "T_EQUAL", "T_PIPEPIPE",
  "T_AMPAMP", "T_EQUALEQUAL", "T_EXCLAIMEQUAL", "T_LESS", "T_GREATER",
  "T_LESSEQUAL", "T_GREATEREQUAL", "T_PLUS", "T_MINUS", "T_STAR",
  "T_SLASH", "T_PERCENT", "T_EXCLAIM", "UOP", "T_LEFT_SQUARE",
  "T_RIGHT_SQUARE", "T_LEFT_PAREN", "T_RIGHT_PAREN", "T_ELLIPSIS",
  "T_IDENTIFIER", "T_INTEGER_LITERAL", "T_FLOATING_LITERAL",
  "T_STRING_LITERAL", "T_CHAR_LITERAL", "$accept", "start",
  "translationunitdecl", "declarationseq", "declaration", "emptydecl",
  "vardeclseq", "declaratorlist", "declarator", "uninitdeclarator",
  "arrayuninitdeclaratorlist", "ptruninitdeclarator", "functiondecl",
  "paramslist", "parmvardecl", "typespecifier", "typemodifier",
  "simpletypespecifier", "primaryexpr", "numexpr", "literalexpr",
  "unaryoperator", "binaryoperator", "parenexpr", "declrefexpr",
  "arraysubscriptexpr", "lvalexpr", "callexpr", "bracedlistexpr",
  "primaryexprlist", "condition", "stmt", "compoundstmt", "stmtseq",
  "nullstmt", "declstmt", "assignstmt", "callexprstmt", "returnstmt",
  "ifstmt", "dostmt", "whilestmt", "breakstmt", "continuestmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
#endif

#define YYPACT_NINF (-113)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-95)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,  -113,  -113,     9,  -113,    -8,     6,  -113,  -113,  -113,
     -28,    82,  -113,  -113,  -113,   -25,   -27,    31,    33,    36,
      34,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
      15,  -113,   -25,   145,    25,  -113,  -113,    27,    55,   -25,
    -113,   145,    30,    30,    30,    30,  -113,  -113,  -113,  -113,
    -113,  -113,   261,  -113,  -113,  -113,  -113,   -11,    44,  -113,
    -113,    34,    45,    48,    15,  -113,    71,    76,  -113,  -113,
    -113,   171,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,   107,    30,  -113,
      34,   102,  -113,  -113,  -113,   145,  -113,  -113,   261,   273,
     284,   293,   293,    69,    69,    69,    69,    74,    74,  -113,
    -113,  -113,   211,  -113,    56,   229,  -113,    58,   118,    58,
      91,    92,   127,  -113,  -113,   -25,   -11,    44,   101,   106,
     102,  -113,   108,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,    30,   118,   114,
     118,  -113,  -113,  -113,   110,    30,  -113,  -113,  -113,   191,
     125,    58,  -113,  -113,   247,  -113,   118,   121,  -113,  -113,
    -113
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      32,    33,     9,     0,     2,     0,    32,     6,     7,     8,
       0,     0,     1,     3,     4,     0,    21,     0,    11,    13,
      15,    34,    39,    36,    35,    37,    38,    31,    21,    22,
      32,    10,     0,     0,     0,    16,    26,     0,    27,    29,
      12,     0,     0,     0,     0,     0,    71,    42,    43,    52,
      51,    14,    50,    40,    48,    47,    49,    44,    46,    45,
      41,    17,     0,     0,    32,    30,    79,     0,    53,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      18,    32,    23,    24,    28,     0,    78,    70,    61,    69,
      68,    66,    67,    62,    63,    64,    65,    56,    57,    58,
      59,    60,     0,    76,     0,     0,    20,     0,    32,     0,
       0,     0,     0,    96,    97,     0,    74,    75,     0,     0,
      32,    82,     0,    92,    83,    84,    85,    91,    86,    87,
      88,    89,    90,    80,    72,    77,    73,     0,    32,     0,
      32,   106,   107,   100,     0,     0,    99,    95,    93,     0,
     102,     0,   105,   101,     0,    81,    32,     0,    98,   103,
     104
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,  -113,  -113,   135,  -113,  -113,    11,   117,  -113,   103,
     -45,   140,  -113,    93,  -113,    22,  -113,  -113,   -29,   -42,
    -113,  -113,  -113,  -113,   -71,   -70,  -113,   -67,  -113,   -81,
    -112,   -95,    97,    26,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,   124,    17,    18,    19,
      35,    20,     9,    37,    38,   125,    11,    27,    66,    52,
      53,    54,    55,    56,    57,    58,   128,    59,    60,    67,
     148,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    69,    70,    71,    51,    15,   114,   150,    15,    12,
       1,     8,    13,    30,   143,    16,    89,     8,    28,     1,
     126,   127,    10,   149,   129,     2,    -5,    86,    10,    87,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   116,   115,   126,   127,   167,
      31,   129,    39,   160,    32,   162,   -25,    36,    33,   126,
     127,    42,    43,   129,    61,    91,    44,    92,    63,    62,
      45,   169,    34,    46,    47,    48,    64,   126,   127,   126,
     127,   129,    88,   129,    90,    21,    39,    22,    23,    24,
      25,    26,    95,   154,    96,   126,   127,   145,   147,   129,
      81,    82,    83,    84,    85,   159,     1,    83,    84,    85,
     151,   152,   117,   164,   118,   119,   120,   121,   122,    91,
     -94,   123,     1,   155,    41,   156,   158,   161,   117,   163,
     118,   119,   120,   121,   122,    91,   166,   123,    42,    43,
     170,    14,    65,    44,    41,    46,   153,    45,   113,    40,
      46,    47,    48,    49,    50,    29,   157,    94,    42,    43,
      93,    46,    41,    44,     0,     0,     0,    45,     0,     0,
      46,    47,    48,    49,    50,     0,    42,    43,     0,     0,
       0,    44,     0,     0,     0,    45,     0,     0,    46,    47,
      48,    49,    50,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
       0,     0,    97,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
       0,     0,   165,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
     144,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     0,   168,     0,   146,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      77,    78,    79,    80,    81,    82,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
      42,    43,    44,    45,    33,    33,    87,   119,    33,     0,
       4,     0,    20,    40,    95,    43,    61,     6,    43,     4,
      91,    91,     0,   118,    91,    19,    20,    38,     6,    40,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    90,    88,   118,   118,   161,
      19,   118,    30,   148,    21,   150,    41,    42,    22,   130,
     130,    31,    32,   130,    39,    17,    36,    19,    41,    44,
      40,   166,    38,    43,    44,    45,    21,   148,   148,   150,
     150,   148,    38,   150,    39,     3,    64,     5,     6,     7,
       8,     9,    21,   122,    18,   166,   166,    41,    40,   166,
      31,    32,    33,    34,    35,   147,     4,    33,    34,    35,
      19,    19,    10,   155,    12,    13,    14,    15,    16,    17,
      18,    19,     4,    22,    17,    19,    18,    13,    10,    19,
      12,    13,    14,    15,    16,    17,    11,    19,    31,    32,
      19,     6,    39,    36,    17,    43,    19,    40,    41,    32,
      43,    44,    45,    46,    47,    15,   130,    64,    31,    32,
      63,    43,    17,    36,    -1,    -1,    -1,    40,    -1,    -1,
      43,    44,    45,    46,    47,    -1,    31,    32,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,    44,
      45,    46,    47,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    41,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    41,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      39,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    19,    -1,    39,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      27,    28,    29,    30,    31,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    19,    49,    50,    51,    52,    53,    54,    60,
      63,    64,     0,    20,    51,    33,    43,    55,    56,    57,
      59,     3,     5,     6,     7,     8,     9,    65,    43,    59,
      40,    19,    21,    22,    38,    58,    42,    61,    62,    63,
      55,    17,    31,    32,    36,    40,    43,    44,    45,    46,
      47,    66,    67,    68,    69,    70,    71,    72,    73,    75,
      76,    39,    44,    41,    21,    57,    66,    77,    67,    67,
      67,    67,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    38,    40,    38,    58,
      39,    17,    19,    80,    61,    21,    18,    41,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    41,    77,    67,    58,    10,    12,    13,
      14,    15,    16,    19,    54,    63,    72,    73,    74,    75,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    77,    39,    41,    39,    40,    78,    79,
      78,    19,    19,    19,    66,    22,    19,    81,    18,    67,
      79,    13,    79,    19,    67,    41,    11,    78,    19,    79,
      19
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    51,    51,    52,    52,    52,    53,
      54,    55,    55,    56,    56,    57,    57,    58,    58,    58,
      58,    59,    59,    60,    60,    61,    61,    61,    61,    62,
      62,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    67,    67,    67,    67,    67,    67,    67,
      68,    68,    68,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      71,    72,    73,    73,    74,    74,    75,    75,    76,    77,
      77,    78,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    81,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    88,    89,    90,    91
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     1,     2,     2,     3,     3,
       4,     1,     2,     6,     6,     0,     1,     1,     3,     1,
       2,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     4,     1,     1,     3,     4,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     2,     1,     1,     4,     2,
       2,     3,     3,     5,     5,     3,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
  case 2: /* start: translationunitdecl  */
#line 307 "/workspace/SYsU-lang/parser/build/parser.y"
                      {
    root = (yyvsp[0].decl);
  }
#line 1514 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 3: /* translationunitdecl: declarationseq T_EOF  */
#line 313 "/workspace/SYsU-lang/parser/build/parser.y"
                      {
    auto decl = gMgr.make<TranslationUnitDecl>();
    if((yyvsp[-1].decl) != nullptr){
      auto p = dynamic_cast<DeclarationSeq*>((yyvsp[-1].decl));
      p->reverse();
      decl->inner = p->seq;
    }
    (yyval.decl) = decl;
  }
#line 1528 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 4: /* declarationseq: declaration declarationseq  */
#line 326 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = dynamic_cast<DeclarationSeq*>((yyvsp[0].decl));

    if(auto q = dynamic_cast<VarDeclSeq*>((yyvsp[-1].decl))){
      for(auto & iter : q->seq)
      decl->seq.push_back(std::move(iter));
      (yyval.decl) = decl;
    }
    else{
      decl->seq.push_back(std::move((yyvsp[-1].decl)));
      (yyval.decl) = decl;
    }
  }
#line 1546 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 5: /* declarationseq: %empty  */
#line 340 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<DeclarationSeq>();
    (yyval.decl) = decl;
  }
#line 1555 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 9: /* emptydecl: T_SEMI  */
#line 354 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<EmptyDecl>();
    (yyval.decl) = decl;
  }
#line 1564 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 10: /* vardeclseq: typespecifier declaratorlist T_SEMI  */
#line 363 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<VarDeclSeq>();
    auto p = dynamic_cast<DeclaratorList*>((yyvsp[-1].decl));
    decl->seq = p->seq;
    for(auto it: decl->seq){
      auto iter = dynamic_cast<VarDecl*>(it);
      iter->type.is_const = (yyvsp[-2].decl)->type.is_const;
      iter->type.basic_type = (yyvsp[-2].decl)->type.basic_type;
    }
    (yyval.decl) = decl;
  }
#line 1580 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 11: /* declaratorlist: declarator  */
#line 378 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<DeclaratorList>();
    decl->seq.push_back((yyvsp[0].decl));
    (yyval.decl) = decl;
  }
#line 1590 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 12: /* declaratorlist: declarator T_COMMA declaratorlist  */
#line 384 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto p = dynamic_cast<DeclaratorList*>((yyvsp[0].decl));
    p->seq.push_back((yyvsp[-2].decl));
    (yyval.decl) = p;
  }
#line 1600 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 13: /* declarator: uninitdeclarator  */
#line 393 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<VarDecl>();
    decl->type = (yyvsp[0].decl)->type;
    decl->name = (yyvsp[0].decl)->name;
    (yyval.decl) = decl;
  }
#line 1611 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 14: /* declarator: uninitdeclarator T_EQUAL primaryexpr  */
#line 400 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<VarDecl>();
    decl->type = (yyvsp[-2].decl)->type;
    decl->name = (yyvsp[-2].decl)->name;
    decl->inner.push_back((yyvsp[0].expr));
    (yyval.decl) = decl;
  }
#line 1623 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 16: /* uninitdeclarator: ptruninitdeclarator arrayuninitdeclaratorlist  */
#line 412 "/workspace/SYsU-lang/parser/build/parser.y"
                                               {
    (yyval.decl) = (yyvsp[-1].decl);
    (yyval.decl)->type.is_array = 1;
    (yyval.decl)->type.dim = (yyvsp[0].decl)->type.dim;
  }
#line 1633 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 17: /* arrayuninitdeclaratorlist: T_LEFT_SQUARE T_RIGHT_SQUARE  */
#line 421 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    (yyval.decl) = gMgr.make<Decl>();
    (yyval.decl)->type.is_array = 1;
    (yyval.decl)->type.dim.push_back(-1);
   }
#line 1643 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 18: /* arrayuninitdeclaratorlist: T_LEFT_SQUARE T_INTEGER_LITERAL T_RIGHT_SQUARE  */
#line 427 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    (yyval.decl) = gMgr.make<Decl>();
    auto p = dynamic_cast<IntegerLiteral*>((yyvsp[-1].expr));
    (yyval.decl)->type.is_array = 1;
    (yyval.decl)->type.dim.push_back(p->val);
   }
#line 1654 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 19: /* arrayuninitdeclaratorlist: T_LEFT_SQUARE T_RIGHT_SQUARE arrayuninitdeclaratorlist  */
#line 434 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    (yyval.decl) = (yyvsp[0].decl);
    (yyval.decl)->type.dim.push_back(-1);
   }
#line 1663 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 20: /* arrayuninitdeclaratorlist: T_LEFT_SQUARE T_INTEGER_LITERAL T_RIGHT_SQUARE arrayuninitdeclaratorlist  */
#line 439 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    (yyval.decl) = (yyvsp[0].decl);
    auto p = dynamic_cast<IntegerLiteral*>((yyvsp[-2].expr));
    (yyval.decl)->type.dim.push_back(p->val);
  }
#line 1673 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 22: /* ptruninitdeclarator: T_STAR ptruninitdeclarator  */
#line 449 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    (yyval.decl) = (yyvsp[0].decl);
    (yyval.decl)->type.is_ptr += 1;
  }
#line 1682 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 23: /* functiondecl: typespecifier T_IDENTIFIER T_LEFT_PAREN paramslist T_RIGHT_PAREN T_SEMI  */
#line 460 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<FunctionDecl>();
    auto p = dynamic_cast<ParamsList*>((yyvsp[-2].decl));
    p->reverse();
    decl->type = (yyvsp[-5].decl)->type;
    decl->type.is_func = 1;
    decl->name = (yyvsp[-4].decl)->name;
    for(auto & iter : p->seq){
        auto q = dynamic_cast<ParmVarDecl*>(iter);
        decl->inner.push_back(q);
        decl->type.params.push_back(q->type.print());
    }
    if(p->ellipsis == 1)
      decl->type.params.push_back("...");
    
    (yyval.decl) = decl;
  }
#line 1704 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 24: /* functiondecl: typespecifier T_IDENTIFIER T_LEFT_PAREN paramslist T_RIGHT_PAREN compoundstmt  */
#line 478 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<FunctionDecl>();
    auto p = dynamic_cast<ParamsList*>((yyvsp[-2].decl));
    auto q = dynamic_cast<CompoundStmt*>((yyvsp[0].stmt));
    p->reverse();
    decl->type = (yyvsp[-5].decl)->type;
    decl->type.is_func = 1;
    decl->name = (yyvsp[-4].decl)->name;
    for(auto & iter : p->seq){
        auto tmp = dynamic_cast<ParmVarDecl*>(iter);
        decl->inner.push_back(tmp);
        decl->type.params.push_back(tmp->type.print());
    }
    if(p->ellipsis == 1)
      decl->type.params.push_back("...");
    
    decl->inner.push_back(q);
    decl->defined = 1;
    (yyval.decl) = decl;
  }
#line 1729 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 25: /* paramslist: %empty  */
#line 502 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<ParamsList>();
    (yyval.decl) = decl;
  }
#line 1738 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 26: /* paramslist: T_ELLIPSIS  */
#line 507 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<ParamsList>();
    decl->ellipsis = 1;
    (yyval.decl) = decl;
  }
#line 1748 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 27: /* paramslist: parmvardecl  */
#line 513 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<ParamsList>();
    decl->seq.push_back((yyvsp[0].decl));
    (yyval.decl) = decl;
  }
#line 1758 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 28: /* paramslist: parmvardecl T_COMMA paramslist  */
#line 519 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = dynamic_cast<ParamsList*>((yyvsp[0].decl));
    decl->seq.push_back((yyvsp[-2].decl));
    (yyval.decl) = decl;
  }
#line 1768 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 29: /* parmvardecl: typespecifier  */
#line 528 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<ParmVarDecl>();
    decl->type = (yyvsp[0].decl)->type;
    decl->type.is_param = 1;
    (yyval.decl) = decl;
  }
#line 1779 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 30: /* parmvardecl: typespecifier uninitdeclarator  */
#line 535 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<ParmVarDecl>();
    decl->type = (yyvsp[0].decl)->type;
    decl->type.is_const = (yyvsp[-1].decl)->type.is_const;
    decl->type.basic_type = (yyvsp[-1].decl)->type.basic_type;
    decl->name = (yyvsp[0].decl)->name;
    decl->type.is_param = 1;
    (yyval.decl) = decl;
  }
#line 1793 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 31: /* typespecifier: typemodifier simpletypespecifier  */
#line 548 "/workspace/SYsU-lang/parser/build/parser.y"
                                  {
    (yyval.decl)->type.is_const = (yyvsp[-1].decl)->type.is_const;
    (yyval.decl)->type.basic_type = (yyvsp[0].decl)->type.basic_type;
  }
#line 1802 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 32: /* typemodifier: %empty  */
#line 556 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    (yyval.decl) = decl;
  }
#line 1811 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 33: /* typemodifier: T_CONST  */
#line 561 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    decl->type.is_const = 1;
    (yyval.decl) = decl;
  }
#line 1821 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 34: /* simpletypespecifier: T_VOID  */
#line 570 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    (yyval.decl) = decl;
    (yyval.decl)->type.basic_type = Type::my_void;
    }
#line 1831 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 35: /* simpletypespecifier: T_INT  */
#line 576 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    (yyval.decl) = decl;
    (yyval.decl)->type.basic_type = Type::my_int;}
#line 1840 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 36: /* simpletypespecifier: T_LONG  */
#line 581 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    (yyval.decl) = decl;
    (yyval.decl)->type.basic_type = Type::my_long;
  }
#line 1850 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 37: /* simpletypespecifier: T_FLOAT  */
#line 587 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    (yyval.decl) = decl;
    (yyval.decl)->type.basic_type = Type::my_float;
  }
#line 1860 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 38: /* simpletypespecifier: T_DOUBLE  */
#line 593 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    (yyval.decl) = decl;
    (yyval.decl)->type.basic_type = Type::my_double;
  }
#line 1870 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 39: /* simpletypespecifier: T_CHAR  */
#line 599 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto decl = gMgr.make<Decl>();
    (yyval.decl) = decl;
    (yyval.decl)->type.basic_type = Type::my_char;
  }
#line 1880 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 53: /* unaryoperator: T_PLUS numexpr  */
#line 633 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<UnaryOperator>();
    expr->op = UnaryOperator::kPlus;
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1891 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 54: /* unaryoperator: T_MINUS numexpr  */
#line 640 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<UnaryOperator>();
    expr->op = UnaryOperator::kMinus;
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1902 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 55: /* unaryoperator: T_EXCLAIM numexpr  */
#line 647 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<UnaryOperator>();
    expr->op = UnaryOperator::kExclaim;
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1913 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 56: /* binaryoperator: numexpr T_PLUS numexpr  */
#line 658 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kPlus;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1925 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 57: /* binaryoperator: numexpr T_MINUS numexpr  */
#line 666 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kMinus;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1937 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 58: /* binaryoperator: numexpr T_STAR numexpr  */
#line 674 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kMultiply;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1949 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 59: /* binaryoperator: numexpr T_SLASH numexpr  */
#line 682 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kDivide;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1961 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 60: /* binaryoperator: numexpr T_PERCENT numexpr  */
#line 690 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kMod;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1973 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 61: /* binaryoperator: numexpr T_EQUAL numexpr  */
#line 698 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kEqual;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1985 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 62: /* binaryoperator: numexpr T_LESS numexpr  */
#line 706 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kLess;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 1997 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 63: /* binaryoperator: numexpr T_GREATER numexpr  */
#line 714 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kGreater;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2009 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 64: /* binaryoperator: numexpr T_LESSEQUAL numexpr  */
#line 722 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kLessEqual;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2021 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 65: /* binaryoperator: numexpr T_GREATEREQUAL numexpr  */
#line 730 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kGreaterEqual;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2033 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 66: /* binaryoperator: numexpr T_EQUALEQUAL numexpr  */
#line 738 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kEqualEqual;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2045 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 67: /* binaryoperator: numexpr T_EXCLAIMEQUAL numexpr  */
#line 746 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kExclaimEqual;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2057 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 68: /* binaryoperator: numexpr T_AMPAMP numexpr  */
#line 754 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kAmpAmp;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2069 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 69: /* binaryoperator: numexpr T_PIPEPIPE numexpr  */
#line 762 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kPipePipe;
    expr->inner.push_back((yyvsp[-2].expr));
    expr->inner.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2081 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 70: /* parenexpr: T_LEFT_PAREN numexpr T_RIGHT_PAREN  */
#line 773 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<ParenExpr>();
    expr->inner.push_back((yyvsp[-1].expr));
    (yyval.expr) = expr;
  }
#line 2091 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 71: /* declrefexpr: T_IDENTIFIER  */
#line 782 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<DeclRefExpr>();
    expr->name = (yyvsp[0].decl)->name;
    (yyval.expr) = expr;
  }
#line 2101 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 72: /* arraysubscriptexpr: declrefexpr T_LEFT_SQUARE numexpr T_RIGHT_SQUARE  */
#line 791 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<ArraySubscriptExpr>();
//    if(auto p = dynamic_cast<IntegerLiteral*>($3)){
//      expr->type = $1->type;
//      expr->type.is_array = 1;
//      expr->type.dim.push_back(p->val);
//    }
    expr->inner.push_back((yyvsp[-3].expr));
    expr->inner.push_back((yyvsp[-1].expr));
    (yyval.expr) = expr;
  }
#line 2117 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 73: /* arraysubscriptexpr: arraysubscriptexpr T_LEFT_SQUARE numexpr T_RIGHT_SQUARE  */
#line 803 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<ArraySubscriptExpr>();
//    if(auto p = dynamic_cast<IntegerLiteral*>($3)){
//      expr->type = $1->type;
//      expr->type.is_array = 1;
//      expr->type.dim.push_back(p->val);
//    }
    expr->inner.push_back((yyvsp[-3].expr));
    expr->inner.push_back((yyvsp[-1].expr));
    (yyval.expr) = expr;
  }
#line 2133 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 76: /* callexpr: declrefexpr T_LEFT_PAREN T_RIGHT_PAREN  */
#line 823 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<CallExpr>();
    auto declrefexpr = dynamic_cast<DeclRefExpr*>((yyvsp[-2].expr));
    expr->name = declrefexpr->name;
    expr->inner.push_back((yyvsp[-2].expr));
    (yyval.expr) = expr;
  }
#line 2145 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 77: /* callexpr: declrefexpr T_LEFT_PAREN primaryexprlist T_RIGHT_PAREN  */
#line 831 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<CallExpr>();
    auto declrefexpr = dynamic_cast<DeclRefExpr*>((yyvsp[-3].expr));
    auto p = dynamic_cast<PrimaryExprList*>((yyvsp[-1].expr));
    expr->inner.push_back((yyvsp[-3].expr));
    p->reverse();
    for(auto it : p->seq)
      expr->inner.push_back(it);
    expr->name = declrefexpr->name;
    (yyval.expr) = expr;
  }
#line 2161 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 78: /* bracedlistexpr: T_LEFT_BRACE primaryexprlist T_RIGHT_BRACE  */
#line 846 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<InitListExpr>();
    auto p = dynamic_cast<PrimaryExprList*>((yyvsp[-1].expr));
    p->reverse();
    expr->inner = p->seq;
    (yyval.expr) = expr;
  }
#line 2173 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 79: /* primaryexprlist: primaryexpr  */
#line 857 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = gMgr.make<PrimaryExprList>();
    expr->seq.push_back((yyvsp[0].expr));
    (yyval.expr) = expr;
  }
#line 2183 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 80: /* primaryexprlist: primaryexpr T_COMMA primaryexprlist  */
#line 863 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto expr = dynamic_cast<PrimaryExprList*>((yyvsp[0].expr));
    expr->seq.push_back((yyvsp[-2].expr));
    (yyval.expr) = expr;
  }
#line 2193 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 81: /* condition: T_LEFT_PAREN numexpr T_RIGHT_PAREN  */
#line 872 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    (yyval.expr) = (yyvsp[-1].expr);
  }
#line 2201 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 93: /* compoundstmt: T_LEFT_BRACE stmtseq T_RIGHT_BRACE  */
#line 895 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<CompoundStmt>();
    auto p = dynamic_cast<StmtSeq*>((yyvsp[-1].stmt));
    p->reverse();
    stmt->inner = p->seq;
    (yyval.stmt) = stmt;
  }
#line 2213 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 94: /* stmtseq: %empty  */
#line 906 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<StmtSeq>();
    (yyval.stmt) = stmt;
  }
#line 2222 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 95: /* stmtseq: stmt stmtseq  */
#line 911 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = dynamic_cast<StmtSeq*>((yyvsp[0].stmt));
    stmt->seq.push_back((yyvsp[-1].stmt));
    (yyval.stmt) = stmt;
  }
#line 2232 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 96: /* nullstmt: T_SEMI  */
#line 920 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<NullStmt>();
    (yyval.stmt) = stmt;
  }
#line 2241 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 97: /* declstmt: vardeclseq  */
#line 928 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<DeclStmt>();
    if(auto q = dynamic_cast<VarDeclSeq*>((yyvsp[0].decl))){
      q->reverse();
      for(auto & iter : q->seq)
        stmt->inner.push_back(std::move(iter));
      (yyval.stmt) = stmt;
    }
  }
#line 2255 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 98: /* assignstmt: lvalexpr T_EQUAL numexpr T_SEMI  */
#line 941 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<AssignStmt>();
    stmt->inner.push_back((yyvsp[-3].expr));
    stmt->inner.push_back((yyvsp[-1].expr));
    (yyval.stmt) = stmt;
  }
#line 2266 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 99: /* callexprstmt: callexpr T_SEMI  */
#line 951 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<CallExprStmt>();
    auto obj = dynamic_cast<CallExpr*>((yyvsp[-1].expr));
    stmt->kind = obj->kind;
    stmt->name = obj->name;
    stmt->inner = obj->inner;
    stmt->decl = obj->decl;
    (yyval.stmt) = stmt;
  }
#line 2280 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 100: /* returnstmt: T_RETURN T_SEMI  */
#line 964 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<ReturnStmt>();
    (yyval.stmt) = stmt;
  }
#line 2289 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 101: /* returnstmt: T_RETURN primaryexpr T_SEMI  */
#line 969 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<ReturnStmt>();
    stmt->inner.push_back((yyvsp[-1].expr));
    (yyval.stmt) = stmt;
  }
#line 2299 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 102: /* ifstmt: T_IF condition stmt  */
#line 978 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<IfStmt>();
    stmt->inner.push_back((yyvsp[-1].expr));
    stmt->inner.push_back((yyvsp[0].stmt));
    (yyval.stmt) = stmt;
  }
#line 2310 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 103: /* ifstmt: T_IF condition stmt T_ELSE stmt  */
#line 985 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<IfStmt>();
    stmt->inner.push_back((yyvsp[-3].expr));
    stmt->inner.push_back((yyvsp[-2].stmt));
    stmt->inner.push_back((yyvsp[0].stmt));
    (yyval.stmt) = stmt;
  }
#line 2322 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 104: /* dostmt: T_DO stmt T_WHILE condition T_SEMI  */
#line 996 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<DoStmt>();
    stmt->inner.push_back((yyvsp[-3].stmt));
    stmt->inner.push_back((yyvsp[-1].expr));
    (yyval.stmt) = stmt;
  }
#line 2333 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 105: /* whilestmt: T_WHILE condition stmt  */
#line 1006 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<WhileStmt>();
    stmt->inner.push_back((yyvsp[-1].expr));
    stmt->inner.push_back((yyvsp[0].stmt));
    (yyval.stmt) = stmt;
  }
#line 2344 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 106: /* breakstmt: T_BREAK T_SEMI  */
#line 1016 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<BreakStmt>();
    (yyval.stmt) = stmt;
  }
#line 2353 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;

  case 107: /* continuestmt: T_CONTINUE T_SEMI  */
#line 1024 "/workspace/SYsU-lang/parser/build/parser.y"
  {
    auto stmt = gMgr.make<ContinueStmt>();
    (yyval.stmt) = stmt;
  }
#line 2362 "/workspace/SYsU-lang/parser/build/parser.cc"
    break;


#line 2366 "/workspace/SYsU-lang/parser/build/parser.cc"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 1030 "/workspace/SYsU-lang/parser/build/parser.y"

