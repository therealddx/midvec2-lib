/* 
 * reference LICENSE file provided.
 *
 * OutputPipeFile.hpp.
 * Defines interface for putting bytes out over a regular system file.
 *
 */

#ifndef OUTPUTPIPEFILE_HPP
#define OUTPUTPIPEFILE_HPP

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "OutputPipeBase.hpp"

class OutputPipeFile : public OutputPipeBase
{
public:

  // 
  // ctor / dtor.
  //
  OutputPipeFile(std::string arg_filePath);
  ~OutputPipeFile();
 
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

  void Close()
  {
    return;
  }

private:
  std::string _fqFile;
  std::ofstream _outputFile;
};

#endif // OUTPUTPIPEFILE_HPP
