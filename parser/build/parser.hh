/* A Bison parser, made by GNU Bison 3.7.5.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_WORKSPACE_SYSU_LANG_PARSER_BUILD_PARSER_HH_INCLUDED
# define YY_YY_WORKSPACE_SYSU_LANG_PARSER_BUILD_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 186 "/workspace/SYsU-lang/parser/build/parser.y"

#include "asg.hpp"
#include <vector>
#include <memory>
#include <llvm/Support/JSON.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>

#line 58 "/workspace/SYsU-lang/parser/build/parser.hh"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_VOID = 258,                  /* T_VOID  */
    T_CONST = 259,                 /* T_CONST  */
    T_CHAR = 260,                  /* T_CHAR  */
    T_LONG = 261,                  /* T_LONG  */
    T_INT = 262,                   /* T_INT  */
    T_FLOAT = 263,                 /* T_FLOAT  */
    T_DOUBLE = 264,                /* T_DOUBLE  */
    T_IF = 265,                    /* T_IF  */
    T_ELSE = 266,                  /* T_ELSE  */
    T_DO = 267,                    /* T_DO  */
    T_WHILE = 268,                 /* T_WHILE  */
    T_BREAK = 269,                 /* T_BREAK  */
    T_CONTINUE = 270,              /* T_CONTINUE  */
    T_RETURN = 271,                /* T_RETURN  */
    T_LEFT_BRACE = 272,            /* T_LEFT_BRACE  */
    T_RIGHT_BRACE = 273,           /* T_RIGHT_BRACE  */
    T_SEMI = 274,                  /* T_SEMI  */
    T_EOF = 275,                   /* T_EOF  */
    T_COMMA = 276,                 /* T_COMMA  */
    T_EQUAL = 277,                 /* T_EQUAL  */
    T_PIPEPIPE = 278,              /* T_PIPEPIPE  */
    T_AMPAMP = 279,                /* T_AMPAMP  */
    T_EQUALEQUAL = 280,            /* T_EQUALEQUAL  */
    T_EXCLAIMEQUAL = 281,          /* T_EXCLAIMEQUAL  */
    T_LESS = 282,                  /* T_LESS  */
    T_GREATER = 283,               /* T_GREATER  */
    T_LESSEQUAL = 284,             /* T_LESSEQUAL  */
    T_GREATEREQUAL = 285,          /* T_GREATEREQUAL  */
    T_PLUS = 286,                  /* T_PLUS  */
    T_MINUS = 287,                 /* T_MINUS  */
    T_STAR = 288,                  /* T_STAR  */
    T_SLASH = 289,                 /* T_SLASH  */
    T_PERCENT = 290,               /* T_PERCENT  */
    T_EXCLAIM = 291,               /* T_EXCLAIM  */
    UOP = 292,                     /* UOP  */
    T_LEFT_SQUARE = 293,           /* T_LEFT_SQUARE  */
    T_RIGHT_SQUARE = 294,          /* T_RIGHT_SQUARE  */
    T_LEFT_PAREN = 295,            /* T_LEFT_PAREN  */
    T_RIGHT_PAREN = 296,           /* T_RIGHT_PAREN  */
    T_ELLIPSIS = 297,              /* T_ELLIPSIS  */
    T_IDENTIFIER = 298,            /* T_IDENTIFIER  */
    T_INTEGER_LITERAL = 299,       /* T_INTEGER_LITERAL  */
    T_FLOATING_LITERAL = 300,      /* T_FLOATING_LITERAL  */
    T_STRING_LITERAL = 301,        /* T_STRING_LITERAL  */
    T_CHAR_LITERAL = 302           /* T_CHAR_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef 
  union
  {
    Obj* obj;
	  Decl* decl;	
    Expr* expr;
    Stmt* stmt;
  }
 YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_WORKSPACE_SYSU_LANG_PARSER_BUILD_PARSER_HH_INCLUDED  */
