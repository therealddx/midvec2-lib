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
  -L/usr/local/lib64 -L"$PATH_LIB" -lmidvec2 -lpthread --std=c++20 -I"$PATH_SRC" -o "$PWD"/bin/nodebench

# grant `LD_LIBRARY_PATH`, but warn.
# 
echo "build script complete. if it succeeded, remember the following!"
echo "  set `export LD_LIBRARY_PATH='"$PATH_LIB"'`..."
echo "  add stdc++20 libs to LD_LIBRARY_PATH, if they aren't in a standard location."
 
