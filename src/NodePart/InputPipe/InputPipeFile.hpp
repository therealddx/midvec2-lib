/*
 * reference LICENSE file provided.
 *
 * InputPipeFile.hpp.
 * Defines an interface for reading bytes from a file into Message
 * instances.
 *
 */

#ifndef INPUTPIPEFILE_HPP
#define INPUTPIPEFILE_HPP

// 
// include: general.
//
#include <string.h>
#include <stdint.h>
#include <fstream>
#include <string>

// 
// include: app.
//
#include <Message/MessageConstants.hpp>
#include "InputPipe.hpp"

class InputPipeFile : public InputPipe
{

public:

  // 
  // Ctor.
  // Opens handle to file.
  //
  InputPipeFile(std::string arg_fqFile);

  // 
  // Dtor.
  // Closes handle to file.
  //
  ~InputPipeFile(); 

  // 
  // GetBasename.
  // Get the basename of the file being read.
  // 
  std::string GetBasename() const;

private:
  
  // 
  // GetByte.
  // Controlled file read.
  //
  ErrorCode GetByte(char* rtn_byte);

  // members: data: file read.
  static const uint32_t MAX_SIZE_FILEBUF = 1024;
  char _fileBuf[MAX_SIZE_FILEBUF]; // buffer of file data.
  int32_t _fileBufIndex;           // index in _fileBuf.
  int32_t _fileBufValid;           // num valid bytes in _fileBuf.

  // members: data: file operation.
  std::string _fqFile;
  std::ifstream _inputFile;

}; 

#endif // INPUTPIPEFILE_HPP

