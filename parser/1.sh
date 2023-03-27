#!/bin/bash
test_file_path=${1:-'/workspace/SYsU-lang/tester/functional/000_main.sysu.c'}

 ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  clang -E $test_file_path |
  clang -cc1 -ast-dump=json  &>  /workspace/SYsU-lang/parser/ori_json.txt &&
  clang -E $test_file_path |
  clang -cc1 -ast-dump &>  /workspace/SYsU-lang/parser/ori_tree.txt ) 

 ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  sysu-preprocessor $test_file_path |
  sysu-lexer |
  sysu-parser &> /workspace/SYsU-lang/parser/sysu.txt)

  ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  sysu-compiler --unittest=parser-1 $test_file_path)

