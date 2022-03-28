#!/bin/bash

# 
# build script for application in this directory.
# 

# vars.
PATH_SRC="$PWD"/../../../src
PATH_LIB="$PWD"/../../../build/BuildShared/lib

# prep.
if [[ -d "$PWD"/bin ]]; then
  rm -rf "$PWD"/bin
fi

mkdir "$PWD"/bin

# build.
# 
# 3. call out the *.so using:
#   `-L` (where is that *.so?), and
#   `-l` (what is that *.so's name?)
# 
g++ \
  main.cpp \
  -L"$PATH_LIB" -lmidvec2 -lpthread \
  -I"$PATH_SRC" \
  --std=c++11 \
  -o "$PWD"/bin/main

# 4. the application may've built, but you'll still need to
# modify `LD_LIBRARY_PATH` in order to run the application.
# 
# `LD_LIBRARY_PATH` does not have to be logically equivalent to `PATH_LIB` above.
# but for your own good, those two directories'd better be holding the same *.so.
# 

