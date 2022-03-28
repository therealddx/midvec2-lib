#!/bin/bash

# 
# build script for application in this directory.
# 

# vars.
PATH_SRC="$PWD"/../..
PATH_LIB="$PWD"/../../../build/BuildShared/lib

# prep.
if [[ -d "$PWD"/bin ]]; then
  rm -rf "$PWD"/bin
fi

mkdir "$PWD"/bin

# build.
# 
g++ \
  "$PATH_SRC"/Application/NodeBench/BenchLog.cpp \
  "$PATH_SRC"/Application/NodeBench/main.cpp \
  "$PATH_SRC"/Application/NodeBench/nodeBench.cpp \
  -L"$PATH_LIB" -lmidvec2 -lpthread --std=c++11 -I"$PATH_SRC" -o "$PWD"/bin/nodebench

# grant `LD_LIBRARY_PATH`, but warn.
# 
echo 'remember to set `export LD_LIBRARY_PATH='"$PATH_LIB"'`...'
 
