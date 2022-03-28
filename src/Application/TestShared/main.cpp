/**
 * main.cpp
 *
 * Trivial example application to demonstrate dynamic linking
 * with the target library (*.so).
 *
 * There's (4) key steps-- follow along through this file
 * and 'build.sh', to get a jogger on what they are.
 *
 */

// 1. include this header from the codebase, just to play with.
//
#include <NodePart/OutputPipe/OutputPipeFile.hpp>

int main()
{
  // 2. instantiate the included class
  //   (for this example, OutputPipeFile::ctor/dtor are linked
  //   into the application)
  //
  OutputPipeFile o("./shared-successful.txt");

  // ret. 
  return 0;
}

