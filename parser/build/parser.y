%{
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
ScopeList gScopeList;

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
      expr->value = s;
      expr->val = std::stoi((std::string)(s));
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


%}//prologue finished

%code requires{
#include "asg.hpp"
#include <vector>
#include <memory>
#include <llvm/Support/JSON.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
}

%define api.value.type {
  union
  {
    Obj* obj;
	  Decl* decl;	
    Expr* expr;
    Stmt* stmt;
  }
}
%debug

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
%token T_EOF

%left T_COMMA
%right T_EQUAL
%left T_PIPEPIPE
%left T_AMPAMP
%left T_EQUALEQUAL T_EXCLAIMEQUAL
%left T_LESS T_GREATER T_LESSEQUAL T_GREATEREQUAL
%left T_PLUS T_MINUS
%left T_STAR T_SLASH T_PERCENT
%left T_EXCLAIM
%precedence UOP
%left T_LEFT_SQUARE T_RIGHT_SQUARE
%left T_LEFT_PAREN T_RIGHT_PAREN

%token T_ELLIPSIS
%token <decl> T_IDENTIFIER
%token <expr> T_INTEGER_LITERAL
%token <expr> T_FLOATING_LITERAL
%token <expr> T_STRING_LITERAL
%token <expr> T_CHAR_LITERAL

%nterm <decl> start
%nterm <decl> translationunitdecl
%nterm <decl> declarationseq
%nterm <decl> declaration

%nterm <decl> vardeclseq
%nterm <decl> functiondecl
%nterm <decl> paramslist
%nterm <decl> parmvardecl
%nterm <decl> emptydecl
%nterm <decl> declaratorlist  
%nterm <decl> declarator
%nterm <decl> uninitdeclarator
%nterm <decl> ptruninitdeclarator
%nterm <decl> arrayuninitdeclaratorlist
%nterm <decl> typespecifier
%nterm <decl> typemodifier
%nterm <decl> simpletypespecifier


%nterm <expr> literalexpr
%nterm <expr> numexpr
%nterm <expr> condition
%nterm <expr> unaryoperator
%nterm <expr> binaryoperator
%nterm <expr> parenexpr
%nterm <expr> primaryexpr
%nterm <expr> primaryexprlist
%nterm <expr> bracedlistexpr
%nterm <expr> implicitcastexpr

%nterm <stmt> stmt
%nterm <stmt> compoundstmt
%nterm <stmt> stmtseq
%nterm <stmt> declstmt
%nterm <stmt> ifstmt
%nterm <stmt> dostmt
%nterm <stmt> whilestmt
%nterm <stmt> breakstmt
%nterm <stmt> continuestmt
%nterm <stmt> returnstmt
%nterm <stmt> nullstmt


%%

//声明

start: 
  translationunitdecl {
    root = $1;
  }
;

translationunitdecl: 
  declarationseq T_EOF{
    auto decl = gMgr.make<TranslationUnitDecl>();
    if($1 != nullptr){
      auto p = dynamic_cast<DeclarationSeq*>($1);
      p->reverse();
      decl->inner = p->seq;
    }
    $$ = decl;
  }
;

declarationseq: 
  declaration declarationseq 
  {
    auto decl = dynamic_cast<DeclarationSeq*>($2);

    if(auto q = dynamic_cast<VarDeclSeq*>($1)){
      for(auto & iter : q->seq)
      decl->seq.push_back(std::move(iter));
      $$ = decl;
    }
    else{
      decl->seq.push_back(std::move($1));
      $$ = decl;
    }
  }
| /* empty */ 
  {
    auto decl = gMgr.make<DeclarationSeq>();
    $$ = decl;
  }
;

declaration: 
  emptydecl
| vardeclseq
| functiondecl 
;

emptydecl: 
  T_SEMI
  {
    auto decl = gMgr.make<EmptyDecl>();
    $$ = decl;
  }
;


vardeclseq: 
  typespecifier declaratorlist T_SEMI 
  {
    auto decl = gMgr.make<VarDeclSeq>();
    auto p = dynamic_cast<DeclaratorList*>($2);
    p->reverse();
    decl->seq = p->seq;
    for(auto it: decl->seq){
      auto iter = dynamic_cast<VarDecl*>(it);
      iter->type.is_const = $1->type.is_const;
      iter->type.basic_type = $1->type.basic_type;
    }
    $$ = decl;
  }
;

declaratorlist: 
  declarator  
  {
    auto decl = gMgr.make<DeclaratorList>();
    decl->seq.push_back($1);
    $$ = decl;
  }
| declarator T_COMMA declaratorlist
  {
    auto p = dynamic_cast<DeclaratorList*>($3);
    p->seq.push_back($1);
    $$ = p;
  }
;

declarator: 
  uninitdeclarator 
  {
    auto decl = gMgr.make<VarDecl>();
    decl->type = $1->type;
    decl->name = $1->name;
    $$ = decl;
  }
| uninitdeclarator T_EQUAL primaryexpr
  {
    auto decl = gMgr.make<VarDecl>();
    decl->type = $1->type;
    decl->name = $1->name;
    decl->inner.push_back($3);
    $$ = decl;
  }
;


uninitdeclarator: 
  ptruninitdeclarator
| ptruninitdeclarator arrayuninitdeclaratorlist{
    $$ = $1;
    $$->type.is_array = 1;
    $$->type.dim = $2->type.dim;
  }
;

arrayuninitdeclaratorlist: 
  T_LEFT_SQUARE T_INTEGER_LITERAL T_RIGHT_SQUARE 
  {
    $$ = gMgr.make<Decl>();
    auto p = dynamic_cast<IntegerLiteral*>($2);
    $$->type.is_array = 1;
    $$->type.dim.push_back(p->val);
   }
|  T_LEFT_SQUARE T_INTEGER_LITERAL T_RIGHT_SQUARE arrayuninitdeclaratorlist
  {
    $$ = $4;
    auto p = dynamic_cast<IntegerLiteral*>($2);
    $$->type.dim.push_back(p->val);
  }
;

ptruninitdeclarator:  
  T_IDENTIFIER
| T_STAR ptruninitdeclarator {
    $$ = $2;
    $$->type.is_ptr += 1;
  }
;




functiondecl: 
  typespecifier T_IDENTIFIER T_LEFT_PAREN paramslist T_RIGHT_PAREN T_SEMI
  {
    auto decl = gMgr.make<FunctionDecl>();
    auto p = dynamic_cast<ParamsList*>($4);
    p->reverse();
    decl->type = $1->type;
    decl->type.is_func = 1;
    decl->name = $2->name;
    for(auto & iter : p->seq){
        auto q = dynamic_cast<ParmVarDecl*>(iter);
        decl->inner.push_back(q);
        decl->type.params.push_back(q->process_type());
    }
    $$ = decl;
  }
| typespecifier T_IDENTIFIER T_LEFT_PAREN paramslist T_RIGHT_PAREN compoundstmt
  {
    auto decl = gMgr.make<FunctionDecl>();
    auto p = dynamic_cast<ParamsList*>($4);
    auto q = dynamic_cast<CompoundStmt*>($6);
    p->reverse();
    decl->type = $1->type;
    decl->type.is_func = 1;
    decl->name = $2->name;
    for(auto & iter : p->seq){
        auto tmp = dynamic_cast<ParmVarDecl*>(iter);
        decl->inner.push_back(tmp);
        decl->type.params.push_back(tmp->process_type());
    }
    decl->inner.push_back(q);
    $$ = decl;
  }
;

paramslist:
  /*empty*/
  {
    auto decl = gMgr.make<ParamsList>();
    $$ = decl;
  }
| parmvardecl
  {
    auto decl = gMgr.make<ParamsList>();
    decl->seq.push_back($1);
    $$ = decl;
  }
| parmvardecl T_COMMA paramslist
  {
    auto decl = dynamic_cast<ParamsList*>($3);
    decl->seq.push_back($1);
    $$ = decl;
  }
;

parmvardecl: 
  typespecifier
  {
    auto decl = gMgr.make<ParmVarDecl>();
    decl->type = $1->type;
    $$ = decl;
  }
| typespecifier uninitdeclarator 
  {
    auto decl = gMgr.make<ParmVarDecl>();
    decl->type = $2->type;
    decl->type.is_const = $1->type.is_const;
    decl->type.basic_type = $1->type.basic_type;
    decl->name = $2->name;
    $$ = decl;
  }
;


typespecifier: 
  typemodifier simpletypespecifier{
    $$->type.is_const = $1->type.is_const;
    $$->type.basic_type = $2->type.basic_type;
  }
;

typemodifier:
  /*empty*/
  {
    auto decl = gMgr.make<Decl>();
    $$ = decl;
  }
| T_CONST 
  {
    auto decl = gMgr.make<Decl>();
    decl->type.is_const = 1;
    $$ = decl;
  }
;

simpletypespecifier: 
  T_VOID 
  {
    auto decl = gMgr.make<Decl>();
    $$ = decl;
    $$->type.basic_type = Type::my_void;
    }
| T_INT  
  {
    auto decl = gMgr.make<Decl>();
    $$ = decl;
    $$->type.basic_type = Type::my_int;}
| T_LONG  
  {
    auto decl = gMgr.make<Decl>();
    $$ = decl;
    $$->type.basic_type = Type::my_long;
  }
| T_FLOAT 
  {
    auto decl = gMgr.make<Decl>();
    $$ = decl;
    $$->type.basic_type = Type::my_float;
  }
| T_DOUBLE  
  {
    auto decl = gMgr.make<Decl>();
    $$ = decl;
    $$->type.basic_type = Type::my_double;
  }
| T_CHAR  
  {
    auto decl = gMgr.make<Decl>();
    $$ = decl;
    $$->type.basic_type = Type::my_char;
  }
;

//表达式


primaryexpr: 
  literalexpr
| bracedlistexpr
| implicitcastexpr
;

numexpr: 
  T_INTEGER_LITERAL
| T_FLOATING_LITERAL
| binaryoperator
| unaryoperator
| parenexpr
;

literalexpr:
  numexpr
| T_CHAR_LITERAL
| T_STRING_LITERAL
;

unaryoperator:
  T_PLUS numexpr %prec UOP
  {
    auto expr = gMgr.make<UnaryOperator>();
    expr->op = UnaryOperator::kPlus;
    expr->inner.push_back($2);
    $$ = expr;
  }
| T_MINUS numexpr %prec UOP
  {
    auto expr = gMgr.make<UnaryOperator>();
    expr->op = UnaryOperator::kMinus;
    expr->inner.push_back($2);
    $$ = expr;
  }
| T_EXCLAIM numexpr %prec UOP
  {
    auto expr = gMgr.make<UnaryOperator>();
    expr->op = UnaryOperator::kExclaim;
    expr->inner.push_back($2);
    $$ = expr;
  }
;


binaryoperator:
  numexpr T_PLUS numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kPlus;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_MINUS numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kMinus;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_STAR numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kMultiply;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_SLASH numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kDivide;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_PERCENT numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kMod;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_EQUAL numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kEqual;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_LESSEQUAL numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kLessEqual;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_GREATEREQUAL numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kGreaterEqual;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_EQUALEQUAL numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kEqualEqual;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_AMPAMP numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kAmpAmp;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
| numexpr T_PIPEPIPE numexpr
  {
    auto expr = gMgr.make<BinaryOperator>();
    expr->op = BinaryOperator::kPipePipe;
    expr->inner.push_back($1);
    expr->inner.push_back($3);
    $$ = expr;
  }
;


parenexpr:
  T_LEFT_PAREN numexpr T_RIGHT_PAREN
  {
    auto expr = gMgr.make<ParenExpr>();
    expr->inner.push_back($2);
    $$ = expr;
  }
;



bracedlistexpr:
  T_LEFT_BRACE primaryexprlist T_RIGHT_BRACE 
  {
    auto expr = dynamic_cast<InitListExpr*>($2);
    expr->reverse();
    $$ = expr;
  }
;

primaryexprlist:
  primaryexpr
  {
    auto expr = gMgr.make<InitListExpr>();
    expr->inner.push_back($1);
    $$ = expr;
  }
| primaryexpr T_COMMA primaryexprlist
  {
    auto expr = dynamic_cast<InitListExpr*>($3);
    expr->inner.push_back($1);
    $$ = expr;
  }
;

condition: 
  T_LEFT_PAREN numexpr T_RIGHT_PAREN
  {
    $$ = $2;
  }
;

//语句块和作用域

stmt: 
  compoundstmt
| declstmt
| ifstmt
| dostmt
| whilestmt
| breakstmt
| continuestmt
| returnstmt
| nullstmt
;

compoundstmt: 
  T_LEFT_BRACE stmtseq T_RIGHT_BRACE
  {
    auto stmt = gMgr.make<CompoundStmt>();
    auto p = dynamic_cast<StmtSeq*>($2);
    p->reverse();
    stmt->inner = p->seq;
    $$ = stmt;
  }
;

stmtseq: 
  /*empty*/
  {
    auto stmt = gMgr.make<StmtSeq>();
    $$ = stmt;
  }
| stmt stmtseq 
  {
    auto stmt = dynamic_cast<StmtSeq*>($2);
    stmt->seq.push_back($1);
    $$ = stmt;
  }
;

nullstmt:
  T_SEMI
  {
    auto stmt = gMgr.make<NullStmt>();
    $$ = stmt;
  }
;

declstmt:
  vardeclseq
  {
    auto stmt = gMgr.make<DeclStmt>();
    if(auto q = dynamic_cast<VarDeclSeq*>($1)){
      for(auto & iter : q->seq)
      stmt->inner.push_back(std::move(iter));
      $$ = stmt;
    }
  }
;

returnstmt:
  T_RETURN primaryexpr T_SEMI
  {
    auto stmt = gMgr.make<ReturnStmt>();
    stmt->inner.push_back($2);
    $$ = stmt;
  }
;

ifstmt:
  T_IF condition stmt 
  {
    auto stmt = gMgr.make<IfStmt>();
    stmt->inner.push_back($2);
    stmt->inner.push_back($3);
    $$ = stmt;
  }
| T_IF condition stmt T_ELSE stmt
  {
    auto stmt = gMgr.make<IfStmt>();
    stmt->inner.push_back($2);
    stmt->inner.push_back($3);
    stmt->inner.push_back($5);
    $$ = stmt;
  }
;

dostmt:
  T_DO stmt T_WHILE condition T_SEMI
  {
    auto stmt = gMgr.make<DoStmt>();
    stmt->inner.push_back($2);
    stmt->inner.push_back($4);
    $$ = stmt;
  }
;

whilestmt:
  T_WHILE condition stmt
  {
    auto stmt = gMgr.make<WhileStmt>();
    stmt->inner.push_back($2);
    stmt->inner.push_back($3);
    $$ = stmt;
  }
;

breakstmt: 
  T_BREAK T_SEMI
  {
    auto stmt = gMgr.make<BreakStmt>();
    $$ = stmt;
  }
;

continuestmt: 
  T_CONTINUE T_SEMI
  {
    auto stmt = gMgr.make<ContinueStmt>();
    $$ = stmt;
  }
;

%%
