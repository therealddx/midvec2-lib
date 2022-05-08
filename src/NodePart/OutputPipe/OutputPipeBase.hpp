/* 
 * reference LICENSE file provided.
 *
 * OutputPipeBase.hpp.
 * Defines an interface to exporting bytes of a Message into a file, for
 * potential retrieval by other InputPipe instances.
 *
 */

#ifndef OUTPUTPIPEBASE_HPP
#define OUTPUTPIPEBASE_HPP

#include <stdint.h>
#include <Exception/ErrorCode.hpp>

class OutputPipeBase
{
public:

  OutputPipeBase() { };
  virtual ~OutputPipeBase() { };

  // 
  // PutMessage.
  // Write a serialized form out of this bytestream.
  // Returns error code.
  //
  virtual ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen) = 0;

  virtual void Close() = 0;
};

#endif // OUTPUTPIPEBASE_HPP
