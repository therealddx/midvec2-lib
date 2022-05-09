/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeFile.hpp
 * Defines interface for putting bytes out to a file on disk.
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

/**
 * @class OutputPipeFile
 */
class OutputPipeFile : public OutputPipeBase
{
public:

  /**
   * OutputPipeFile
   *
   * Constructs an instance by opening a write handle to a file on disk.
   *   If the file already exists, appends.
   *   If the file does not already exist, creates.
   *   If permissions are not amicable, behavior is undefined.
   *
   * @param[in] arg_filePath
   * Fully-qualified path to a file on disk.
   */
  OutputPipeFile(std::string arg_filePath);

  /**
   * ~OutputPipeFile
   * Closes the handle to the file on disk.
   */
  ~OutputPipeFile();

  /**
   * PutMessage
   * Satisfies base class.
   */
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

  /**
   * Close
   * Satisfies base class.
   */
  void Close()
  {
    return;
  }

private:
  std::string _fqFile;
  std::ofstream _outputFile;
};

#endif // OUTPUTPIPEFILE_HPP
