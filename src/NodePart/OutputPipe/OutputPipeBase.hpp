/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeBase.hpp
 * Interface for serializing user-defined data into a stream of bytes.
 *
 */

#ifndef OUTPUTPIPEBASE_HPP
#define OUTPUTPIPEBASE_HPP

#include <stdint.h>
#include <Exception/ErrorCode.hpp>

/**
 * @class OutputPipeBase
 */
class OutputPipeBase
{
public:

  /**
   * OutputPipeBase
   */
  OutputPipeBase() { };

  /**
   * ~OutputPipeBase
   */
  virtual ~OutputPipeBase() { };

  /**
   * PutMessage
   *
   * Write a value, in serialized form, out of this bytestream.
   *
   * @param[in] arg_msgBytes
   * Pointer to bytes that must be written out of this instance.
   *
   * @param[in] arg_msgLen
   * Number of bytes to write out of this instance.
   *
   * @return ErrorCode::Ok iff write operation went as planned.
   */
  virtual ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen) = 0;

  /**
   * Close
   * Permanently shut this instance off from its output medium.
   * Precursor to calling destructor.
   */
  virtual void Close() = 0;
};

#endif // OUTPUTPIPEBASE_HPP
