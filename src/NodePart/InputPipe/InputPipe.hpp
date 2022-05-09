/**
 * reference LICENSE file provided.
 *
 * @file InputPipe.hpp
 * Sequences the collection and deserialization of bytes into Messages.
 * Subclasses need only specify how to read one byte.
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
 */
class InputPipe : public InputPipeBase
{

public:

  /**
   * InputPipe
   */
  InputPipe() { } ;

  /**
   * ~InputPipe
   */
  virtual ~InputPipe() { } ; 

  /**
   * GetMessage
   * Satisfies base class.
   */
  char* GetMessage(size_t arg_backerLength);

  /**
   * Close
   * Satisfies base class.
   */
  virtual void Close()
  {
    return;
  }

protected:

  /** 
   * FindMessageHeader
   * Finds the header of a Message<T> from the input bytestream.
   * @return ErrorCode::Ok iff header is found and '_headerBuf' is filled.
   */
  virtual ErrorCode FindMessageHeader();

  /**
   * FindMessageBacker
   * Finds the backing data of a Message<T> from the input bytestream.
   * @return ErrorCode::Ok iff the message is found and '_messageBuf' is filled.
   */
  virtual ErrorCode FindMessageBacker(size_t arg_backerLength);

  /**
   * _headerBuf
   * Allocated storage for Message header, as obtained from bytestream.
   */
  char _headerBuf[sizeof(MessageConstants::MESSAGE_HEADER)];

  /**
   * _messageBuf
   * Allocated storage for Message header plus backing data, as obtained from bytestream.
   */
  char _messageBuf[MessageConstants::MAX_SIZE_MESSAGE]; 

  /**
   * GetByte
   * @param[out] rtn_byte
   * Storage for one byte from the input bytestream.
   *
   * @return ErrorCode::Ok iff a valid byte was read into the argument pointer.
   */
  virtual ErrorCode GetByte(char* rtn_byte) = 0;
}; 

#endif // INPUTPIPE_HPP

