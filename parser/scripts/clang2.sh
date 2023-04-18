#!/bin/bash
test_file_path=${1:-'/workspace/SYsU-lang/parser/debug/test.sysu.c'}

 ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  clang -E $test_file_path |
  clang -cc1 -ast-dump=json  >  /workspace/SYsU-lang/parser/debug/ori_json.json 2> /workspace/SYsU-lang/parser/debug/ori.log # &&
  clang -E $test_file_path |
  clang -cc1 -ast-dump &>  /workspace/SYsU-lang/parser/debug/ori_tree.txt   
  ) 

  python compare_clang2.py

