#include "parser.hh"
#include "ToJson.hpp"
#include "Typing.hpp"
using namespace std;

extern Obj* root;
extern  Mgr gMgr;

int main() {
  yyparse();
  ToJson toJson;
  toJson.visit(root);
}