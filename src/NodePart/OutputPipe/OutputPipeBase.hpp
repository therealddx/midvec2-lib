/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeBase.hpp
 * Declarations for OutputPipeBase
 *
 */

#ifndef OUTPUTPIPEBASE_HPP
#define OUTPUTPIPEBASE_HPP

#include <stdint.h>
#include <Exception/ErrorCode.hpp>

/**
 * @class OutputPipeBase
 * Interface for serializing user-defined data into a stream of bytes.
 */
class OutputPipeBase
{
public:

  /**
   * This class is pure-virtual--
   *   attempts to construct cause compile-time error.
   */
  OutputPipeBase() { };

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~OutputPipeBase() { };

  /**
   * Write a Message, in serialized form, out of this bytestream.
   *
   * @param[in] arg_msgBytes
   * Pointer to bytes that must be written out of this instance.
   *
   * @param[in] arg_msgLen
   * Number of bytes to write out of this instance.
   *
   * @return ErrorCode::Ok iff write operation was completed in full.
   */
  virtual ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen) = 0;

  /**
   * Permanently shut this instance off from its output medium.
   *
   * Precursor to calling destructor.
   */
  virtual void Close() = 0;

};

#endif // OUTPUTPIPEBASE_HPP
