#!/bin/bash
test_file_path=${1:-'/workspace/SYsU-lang/parser/debug/test.sysu.c'}

 ( export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  sysu-preprocessor $test_file_path |
  sysu-lexer |
  sysu-parser > /workspace/SYsU-lang/parser/debug/sysu.json 2> /workspace/SYsU-lang/parser/debug/sysu.log)
 
  python compare_sysu1.py
