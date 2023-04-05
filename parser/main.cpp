#include "parser.hh"
#include "ToJson.hpp"
#include "Typing.hpp"
using namespace std;

int main() {
  yyparse();
  ToJson toJson;
  llvm::outs() << root->accept(toJson) << "\n";
}