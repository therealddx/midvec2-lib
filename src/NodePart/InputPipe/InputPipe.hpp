/**
 * reference LICENSE file provided.
 *
 * @file InputPipe.hpp
 * Declarations for InputPipe
 *
 */

#ifndef INPUTPIPE_HPP
#define INPUTPIPE_HPP

// 
// include: general.
//
#include <stdint.h>
#include <string.h>
#include <string>

// 
// include: app.
//
#include <Exception/ErrorCode.hpp>
#include <Message/MessageConstants.hpp>
#include "InputPipeBase.hpp"

/**
 * @class InputPipe
 * Pre-defines the collection and deserialization of bytes into Messages.
 * Subclasses need only specify how to read one byte from their respective medium.
 */
class InputPipe : public InputPipeBase
{

public:

  /**
   * This is a pure-virtual class--
   *   attempts to construct will cause a compile-time failure.
   */
  InputPipe() { } ;

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~InputPipe() { } ; 

  /**
   * Satisfies base class.
   */
  char* GetMessage(size_t arg_backerLength);

  /**
   * Satisfies base class.
   */
  virtual void Close()
  {
    return;
  }

protected:

  /** 
   * Finds the header of a Message from the input bytestream.
   * @return ErrorCode::Ok iff header is found.
   */
  virtual ErrorCode FindMessageHeader();

  /**
   * Finds the backing data of a Message from the input bytestream.
   *
   * @param[in] arg_backerLength
   * Size of payload Message data (in bytes) to obtain from bytestream.
   *
   * @return ErrorCode::Ok iff the Message's payload data is found.
   */
  virtual ErrorCode FindMessageBacker(size_t arg_backerLength);

  /**
   * _headerBuf
   * Allocated storage for Message header, as obtained from bytestream.
   */
  char _headerBuf[sizeof(MessageConstants::MESSAGE_HEADER)];

  /**
   * _messageBuf
   * Allocated storage for Message header plus backing data,
   *   as obtained from bytestream.
   */
  char _messageBuf[MessageConstants::MAX_SIZE_MESSAGE]; 

  /**
   * Obtain one byte from the input medium.
   *
   * @param[out] rtn_byte
   * Storage for one byte from the input bytestream.
   *
   * @return ErrorCode::Ok iff a valid byte was read into the argument pointer.
   */
  virtual ErrorCode GetByte(char* rtn_byte) = 0;
}; 

#endif // INPUTPIPE_HPP

