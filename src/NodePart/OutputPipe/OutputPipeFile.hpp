/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeFile.hpp
 * Declarations for OutputPipeFile
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
 * Defines interface for putting Message instances out to a file on disk.
 */
class OutputPipeFile : public OutputPipeBase
{
public:

  /**
   * Constructs an instance by opening a write handle to a file on disk.
   * - If the file already exists, appends.
   * - If the file does not already exist, creates.
   * - If permissions are not amicable, behavior is undefined.
   *
   * @param[in] arg_filePath Fully-qualified path to a file on disk.
   */
  OutputPipeFile(std::string arg_filePath);

  /**
   * Closes the handle to the file on disk.
   */
  ~OutputPipeFile();

  /**
   * Satisfies base class.
   */
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

  /**
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
