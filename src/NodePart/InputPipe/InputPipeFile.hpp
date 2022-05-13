/**
 * reference LICENSE file provided.
 *
 * @file InputPipeFile.hpp
 * Declarations for InputPipeFile
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
 * Defines an interface for reading bytes from disk, into Message instances.
 */
class InputPipeFile : public InputPipe
{

public:

  /**
   * Constructs an instance by opening a read handle to a file on disk.
   * - If the file does not exist, behavior is undefined.
   * - If permissions are not amicable, behavior is undefined.
   *
   * @param[in] arg_fqFile Fully-qualified path to a file on disk.
   */
  InputPipeFile(std::string arg_fqFile);

  /**
   * Closes the handle to the file on disk.
   */
  ~InputPipeFile(); 

  /**
   * Obtain the basename of the file this instance is reading from.
   * @return
   * String denoting the basename of the file being read.
   */
  std::string GetBasename() const;

private:
  
  /**
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

