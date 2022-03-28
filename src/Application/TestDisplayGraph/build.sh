#!/bin/bash

# 
# build script for application in this directory.
# 

# vars.
PATH_SRC="$PWD"/../../

# prep.
if [[ -d "$PWD"/bin ]]; then
  rm -rf "$PWD"/bin
fi

mkdir "$PWD"/bin

# build.
g++ main.cpp TestDisplayGraph.cpp TestGraphGlui.cpp \
  $(find "$PATH_SRC" -type f -name '*.cpp' | grep -v '/Application/') \
  -lpthread --std=c++11 -I"$PATH_SRC" -o "$PWD"/bin/TestDisplayGraph.out

