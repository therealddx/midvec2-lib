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
g++ main.cpp TestNodePartBuilder.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipe.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipeRam.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipeUdp.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipeFile.cpp \
  "$PATH_SRC"/NodePart/OutputPipe/OutputPipeFile.cpp \
  "$PATH_SRC"/NodePart/OutputPipe/OutputPipeRam.cpp \
  "$PATH_SRC"/NodePart/OutputPipe/OutputPipeUdp.cpp \
  "$PATH_SRC"/NodePartBuilder/inPs.cpp \
  "$PATH_SRC"/NodePartBuilder/outPs.cpp \
  -lpthread --std=c++11 -I"$PATH_SRC" -o "$PWD"/bin/TestNodePartBuilder.out

