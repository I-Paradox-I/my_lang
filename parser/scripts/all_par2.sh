#!/bin/bash
parser=${1:-"parser-2"}
  ( export PATH=$HOME/sysu/bin:$PATH  \
    CPATH=$HOME/sysu/include:$CPATH   \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH   \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&   \
    sysu-compiler --unittest=$parser /workspace/SYsU-lang/tester/*/*.sysu.c )


