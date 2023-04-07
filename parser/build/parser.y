%code requires
{
class Tree;
}
%{
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
Obj* root;
Mgr gMgr;
} // namespace

union YYSTYPE {
  Obj* obj;
	Decl* decl;
	Expr* expr;
};

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
      expr->kind = "FloatingLiteral";
      expr->value = s;
      expr->val = std::stod((stirng)(s));      
      llvm::StringRef str(expr->value);
      llvm::APFloat apf(0.0);
      apf.convertFromString(str, llvm::APFloat::rmNearestTiesToEven);
      llvm::SmallString<16> Buffer;
      apf.toString(Buffer);
      expr->value = Buffer.c_str();
      yylval.expr = expr;
      return T_FLOATING_LITERAL;
    }
    else{ //整数
      auto expr = gMgr.make<IntegerLiteral>();
      expr->kind = "IntegerLiteral";
      expr->value = s;
      expr->val = std::stoi((string)(s));
      yylval.expr = expr;
      return T_INTEGER_LITERAL;
    }
  }  
  if (t == "string_literal") { //TODO
    auto expr = gMgr.make<StringLiteral>();
    expr->kind = "StringLiteral";
    expr->value = s;
    yylval.expr = expr;
    return T_STRING_LITERAL;
  }
  if (t == "char_constant") { //TODO
    auto expr = gMgr.make<CharacterLiteral>();
    expr->kind = "CharacterLiteral";
    expr->value = s;
    expr->val = s[0];
    yylval.expr = expr
    return T_CHAR_CONSTANT;
  }
  return YYEOF;
}


%}
%define api.value.type {union YYSTYPE }

// TO-DO：你需要在这里补充更多的TOKEN
%start start
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
%token T_LEFT_BRACE
%token T_RIGHT_BRACE
%token T_SEMI

%left T_COMMA
%right T_EQUAL
%left T_PIPEPIPE
%left T_AMPAMP
%left T_EQUALEQUAL T_EXCLAIMEQUAL
%left T_LESS T_GREATER T_LESSEQUAL T_GREATEREQUAL
%left T_PLUS T_MINUS
%left T_STAR T_SLASH T_PERCENT
%left T_EXCLAIM
%left T_LEFT_SQUARE T_RIGHT_SQUARE
%left T_LEFT_PAREN T_RIGHT_PAREN

%token T_ELLIPSIS
%token <decl> T_IDENTIFIER
%token <expr> T_INTEGER_LITERAL
%token <expr> T_FLOATING_LITERAL
%token <expr> T_STRING_LITERAL
%token <expr> T_CHAR_CONSTANT

%nterm <decl> start
%nterm <decl> TranslationUnitDecl
%nterm <decl> TypedefDecl


%%
start: TranslationUnitDecl {
    root = $1;
  }
  ;

TranslationUnitDecl: TypedefDecl {
    auto decl = gMgr.make<TranslationUnitDecl>()
    decl->inner.push_back($1);
    $$ = decl;
  }
	;

TypedefDecl: T_INT T_IDENTIFIER T_EQUAL T_INTEGER_LITERAL T_SEMI{
    auto decl = gMgr.make<TypedefDecl>()
    decl->name = $2->name;
    decl->inner.push_back($4);
    $$ = decl;
  }
  ;

%%