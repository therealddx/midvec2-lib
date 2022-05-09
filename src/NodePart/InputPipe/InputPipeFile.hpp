/**
 * reference LICENSE file provided.
 *
 * @file InputPipeFile.hpp
 * Defines an interface for reading bytes from disk, into Message instances.
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

/**
 * @class InputPipeFile
 */
class InputPipeFile : public InputPipe
{

public:

  /**
   * InputPipeFile
   *
   * @param[in] arg_fqFile
   * Fully-qualified path to a file on disk.
   */
  InputPipeFile(std::string arg_fqFile);

  /**
   * ~InputPipeFile
   * Closes the handle to the file on disk.
   */
  ~InputPipeFile(); 

  /**
   * GetBasename
   * @return
   * String denoting the basename (ref. `man 1 basename`) of the file being read.
   */
  std::string GetBasename() const;

private:
  
  /**
   * GetByte
   * Satisfies base class.
   */
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

