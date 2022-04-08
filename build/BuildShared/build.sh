#!/bin/bash

# 
# build script for application in this directory.
# 

# vars.
PATH_SRC="$PWD"/../../src

# prep.
if [[ -d "$PWD"/lib ]]; then
  rm -rf "$PWD"/lib
fi

mkdir "$PWD"/lib

# build.
# 
g++ \
  "$PATH_SRC"/NodeBuilder/nodePs.cpp \
  "$PATH_SRC"/Node/ByteNode.cpp \
  "$PATH_SRC"/Node/CoreNode.cpp \
  "$PATH_SRC"/Node/MixerNode.cpp \
  "$PATH_SRC"/Node/ShowNode.cpp \
  "$PATH_SRC"/Node/SourceNode.cpp \
  "$PATH_SRC"/NodePartBuilder/dispPs.cpp \
  "$PATH_SRC"/NodePartBuilder/genPs.cpp \
  "$PATH_SRC"/NodePartBuilder/inPs.cpp \
  "$PATH_SRC"/NodePartBuilder/outPs.cpp \
  "$PATH_SRC"/NodePartBuilder/procPs.cpp \
  "$PATH_SRC"/NodePart/Display/DisplayBase.cpp \
  "$PATH_SRC"/NodePart/Display/DisplayFile.cpp \
  "$PATH_SRC"/NodePart/Display/DisplayGraph.cpp \
  "$PATH_SRC"/NodePart/Generator/GeneratorBase.cpp \
  "$PATH_SRC"/NodePart/Generator/GeneratorSine.cpp \
  "$PATH_SRC"/NodePart/Generator/GeneratorSquare.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipe.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipeFile.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipeRam.cpp \
  "$PATH_SRC"/NodePart/InputPipe/InputPipeUdp.cpp \
  "$PATH_SRC"/NodePart/OutputPipe/OutputPipeFile.cpp \
  "$PATH_SRC"/NodePart/OutputPipe/OutputPipeRam.cpp \
  "$PATH_SRC"/NodePart/OutputPipe/OutputPipeUdp.cpp \
  "$PATH_SRC"/NodePart/Processor/ProcessorBase.cpp \
  "$PATH_SRC"/NodePart/Processor/ProcessorConv.cpp \
  "$PATH_SRC"/NodePart/Processor/ProcessorDc.cpp \
  "$PATH_SRC"/Types/Complex.cpp \
  -lpthread --std=c++20 -I"$PATH_SRC" -shared -fPIC -o "$PWD"/lib/libmidvec2.so


