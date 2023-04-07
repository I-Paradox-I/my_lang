#!/bin/bash
test_file_path=${1:-'/workspace/SYsU-lang/tester/functional/000_main.sysu.c'}

 ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  clang -E $test_file_path |
  clang -cc1 -ast-dump=json  &>  /workspace/SYsU-lang/parser/debug/ori_json.json # &&
#   clang -E $test_file_path |
#   clang -cc1 -ast-dump &>  /workspace/SYsU-lang/parser/debug/ori_tree.txt   
  ) 

 ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  sysu-preprocessor $test_file_path |
  sysu-lexer |
  sysu-parser &> /workspace/SYsU-lang/parser/debug/sysu.json)
 
  python compare.py

  diff /workspace/SYsU-lang/parser/debug/ori_yaml.yaml /workspace/SYsU-lang/parser/debug/sysu.yaml &> /workspace/SYsU-lang/parser/debug/di.txt

  ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  sysu-compiler --unittest=parser-1 $test_file_path)

