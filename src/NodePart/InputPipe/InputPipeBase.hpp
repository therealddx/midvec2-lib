/**
 * reference LICENSE file provided.
 *
 * @file InputPipeBase.hpp
 * Defines a base class for reading bytes from hardware into a Message instance.
 *
 */

#ifndef INPUTPIPEBASE_HPP
#define INPUTPIPEBASE_HPP

#include <stdint.h>
#include <sys/types.h>

/**
 * @class InputPipeBase
 */
class InputPipeBase
{
public:

  /**
   * InputPipeBase
   */
  InputPipeBase() { };

  /**
   * ~InputPipeBase
   */
  virtual ~InputPipeBase() { };

  /**
   * GetMessage
   * Read a client-given amount of bytes from an input medium.
   *
   * @param[in] arg_backerLength
   * Number of backing data bytes to find from the input byte stream.
   *
   * @return Pointer to backing bytes of a user data type, in host byte order.
   */
  virtual char* GetMessage(size_t arg_backerLength) = 0;

  /**
   * Close
   * Permanently shut this instance off from its input medium.
   * Precursor to calling destructor.
   */
  virtual void Close() = 0;

private:

};

#endif // INPUTPIPEBASE_HPP

