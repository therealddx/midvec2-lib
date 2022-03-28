/*
 * reference LICENSE file provided.
 *
 * InputPipe.hpp.
 * Defines an interface for reading bytes from a file into Message
 * instances.
 * Implements that interface partially, leaving an abstract hole 
 * for which a hardware interface can be substituted to collect bytes.
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

class InputPipe : public InputPipeBase
{

public:

  // 
  // Ctor.
  //
  InputPipe() { } ;

  // 
  // Dtor.
  //
  virtual ~InputPipe() { } ; 

  //     
  // InputPipeBase: Mandatory Implementations.
  // 
  char* GetMessage(size_t arg_backerLength);

protected:

  // 
  // FindMessageHeader.
  // Find Message<T> Header from input bytestream.
  // Output: _headerBuf is filled, or an error is determined.
  //
  virtual ErrorCode FindMessageHeader();

  // 
  // FindMessageBacker.
  // Find Message<T> backing data from input bytestream.
  // Output: _messageBuf is filled, or an error is determined.
  //
  virtual ErrorCode FindMessageBacker(size_t arg_backerLength);

  //  
  // _headerBuf.
  // Specific-allocated storage for Message header, as obtained
  // from hw stream.
  // Needed for: default impl. of 'virtual FindMessageHeader'.
  // 
  char _headerBuf[sizeof(MessageConstants::MESSAGE_HEADER)];

  // 
  // _messageBuf.
  // Specific-allocated storage for Message header and backing data,
  // as obtained from hw stream.
  // Needed for: default impl. of 'virtual FindMessageBacker'.
  //
  char _messageBuf[MessageConstants::MAX_SIZE_MESSAGE]; 

  // 
  // GetByte.
  // Returns a byte into rtn_byte, from the hardware stream.
  //
  virtual ErrorCode GetByte(char* rtn_byte) = 0;

}; 

#endif // INPUTPIPE_HPP

