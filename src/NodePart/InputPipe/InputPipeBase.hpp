/**
 * reference LICENSE file provided.
 *
 * @file InputPipeBase.hpp
 * Declarations for InputPipeBase
 *
 */

#ifndef INPUTPIPEBASE_HPP
#define INPUTPIPEBASE_HPP

#include <stdint.h>
#include <sys/types.h>

/**
 * @class InputPipeBase
 * Declares an interface for reading bytes from hardware into a Message instance.
 */
class InputPipeBase
{
public:

  /**
   * This class is pure-virtual--
   *   attempts to construct cause compile-time error.
   */
  InputPipeBase() { };

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~InputPipeBase() { };

  /**
   * Read a client-given amount of bytes from an input medium.
   *
   * @param[in] arg_backerLength
   * Number of backing data bytes to find from the input byte stream.
   *
   * @return Pointer to backing bytes of a user data type, in host byte order.
   *   Note: This pointer is no longer valid if the instance is destroyed
   *   or a subsequent call is made to this function.
   */
  virtual char* GetMessage(size_t arg_backerLength) = 0;

  /**
   * Permanently shut this instance off from its input medium.
   *
   * Precursor to calling destructor.
   */
  virtual void Close() = 0;

};

#endif // INPUTPIPEBASE_HPP

