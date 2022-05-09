/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeFile.cpp
 * Implements OutputPipeFile.hpp
 *
 */

#include "OutputPipeFile.hpp"

OutputPipeFile::OutputPipeFile(std::string arg_filePath)
: _fqFile(arg_filePath)
{
  // open file.
  _outputFile.open(_fqFile, std::ofstream::out | std::ofstream::app);
}

OutputPipeFile::~OutputPipeFile()
{
  if (_outputFile.is_open() == true)
    { _outputFile.close(); }
}

ErrorCode OutputPipeFile::PutMessage(char* arg_msgBytes, int32_t arg_msgLen)
{
  // write.
  _outputFile.write(arg_msgBytes, arg_msgLen);
  _outputFile.flush();

  // ret.
  return ErrorCode::Ok; 
}


