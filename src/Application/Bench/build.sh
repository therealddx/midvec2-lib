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
  "$PATH_SRC"/Application/Bench/TestInputPipeFile.cpp  \
  "$PATH_SRC"/Application/Bench/benchGeneral.cpp       \
  "$PATH_SRC"/Application/Bench/benchInputPipeFile.cpp \
  "$PATH_SRC"/Application/Bench/benchInputPipeUdp.cpp  \
  "$PATH_SRC"/Application/Bench/benchInputPipeRam.cpp  \
  "$PATH_SRC"/Application/Bench/BenchLog.cpp           \
  "$PATH_SRC"/Application/Bench/main.cpp \
  -L"$PATH_LIB" -lmidvec2 -lpthread --std=c++11 -I"$PATH_SRC" -o "$PWD"/bin/bench

# grant `LD_LIBRARY_PATH`, but warn.
# 
echo 'remember to set `export LD_LIBRARY_PATH='"$PATH_LIB"'`...'
 
