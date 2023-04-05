%code requires
{
#include "asg.hpp"
#include <vector>
#include <memory>
#include <llvm/Support/JSON.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
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
  while (it != end && *it != endline)
    ++it;
  auto len = it - beg;
  if (it != end && *it == endline)
    ++it;
  return llvm::StringRef(beg, len);
}

union YYSTYPE {
  Obj* obj;
	Decl* decl;
	Expr* expr;
};

} // namespace

auto yylex() {
  auto tk = wk_getline();
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
    return T_L_PAREN;
  if (t == "r_paren")
    return T_R_PAREN;
  if (t == "l_square")
    return T_L_SQUARE;
  if (t == "r_square")
    return T_R_SQUARE;
  if (t == "l_brace")
    return T_L_BRACE;
  if (t == "r_brace")
    return T_R_BRACE;
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
    return T_IDENTIFIER;
  }    
  if (t == "numeric_constant") { //TODO
    return T_NUMERIC_CONSTANT;
  }  
  if (t == "string_literal") { //TODO
    return T_STRING_LITERAL;
  }
  if (t == "char_constant") { //TODO
    return T_CHAR_CONSTANT;
  }
  return YYEOF;
}

Obj* root = nullptr;

%}
%define api.value.type { YYSTYPE }

// TO-DO：你需要在这里补充更多的TOKEN
%start Begin
%token T_VOID
%token T_CONST
%token T_CHAR
%token T_LONG
%token T_INT
%token T_FLOAT
%token T_DOUBLE
%token T_IF
%token T_ELSE
%token T_DO
%token T_WHILE
%token T_BREAK
%token T_CONTINUE
%token T_RETURN
%token T_L_PAREN
%token T_R_PAREN
%token T_L_SQUARE
%token T_R_SQUARE
%token T_L_BRACE
%token T_R_BRACE
%token T_COMMA
%token T_SEMI
%token T_EQUAL
%token T_EXCLAIM
%token T_PLUS
%token T_MINUS
%token T_STAR
%token T_SLASH
%token T_PERCENT
%token T_LESS
%token T_GREATER
%token T_LESSEQUAL
%token T_GREATEREQUAL
%token T_EQUALEQUAL
%token T_EXCLAIMEQUAL
%token T_AMPAMP
%token T_PIPEPIPE
%token T_ELLIPSIS
%token T_IDENTIFIER
%token T_NUMERIC_CONSTANT
%token T_STRING_LITERAL
%token T_CHAR_CONSTANT




%%
Begin: CompUnit {
    root = $1;
  }
  ;

CompUnit: GlobalDecl {
    auto ptr = new Tree("TranslationUnitDecl");
    ptr->addSon($1);
    $$ = ptr;
  }
	;

GlobalDecl: FuncDef {
    $$ = $1;
  }
	;

FuncDef:T_INT T_IDENTIFIER T_L_PAREN T_R_PAREN Block {
    auto ptr = new Tree("FunctionDecl", $2->name);
    delete $2;
    ptr->addSon($5);
    $$ = ptr;
  }
  ;
Block: T_L_BRACE Stmt T_R_BRACE {
    auto ptr = new Tree("CompoundStmt");
    ptr->addSon($2);
    $$ = ptr;
  }
  ;

Stmt: T_RETURN T_NUMERIC_CONSTANT T_SEMI {
    auto ptr = new Tree("ReturnStmt");
    ptr->addSon($2);
    $$ = ptr;
}
// TO-DO：你需要在这里实现文法和树，通过测例
%%