#include "parser.hh"
#include "ToJson.hpp"
#include "Typing.hpp"
#include <unistd.h>

using namespace std;

extern Obj* root;
extern  Mgr gMgr;


int main() {
  yydebug = 1; 
  // sleep(20); //调试时使用
  yyparse();
  ToJson toJson;
  toJson.visit(root);
}