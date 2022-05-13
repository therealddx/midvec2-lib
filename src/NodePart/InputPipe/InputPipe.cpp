/*
 * reference LICENSE file provided.
 *
 * @file InputPipe.cpp
 * Implements InputPipe.hpp
 *
 */

// include: ntohl
#include <arpa/inet.h>

// include: app.
#include "InputPipe.hpp"

char* InputPipe::GetMessage(size_t arg_backerLength)
{
  // clear.
  memset(_headerBuf, 0, sizeof(MessageConstants::MESSAGE_HEADER));
  memset(_messageBuf, 0, MessageConstants::MAX_SIZE_MESSAGE);

  // find header.
  ErrorCode error = FindMessageHeader();
  if (error != ErrorCode::Ok) { return NULL; }

  // find body.
  error = FindMessageBacker(arg_backerLength);
  if (error != ErrorCode::Ok) { return NULL; }

  // return a handle.
  return &_messageBuf[0];
}

ErrorCode InputPipe::FindMessageHeader()
{
  // vars.
  bool foundHeader = false;

  // set header startpoint.
  for (uint32_t n = 0; n < sizeof(uint32_t); n++)
  {
    // get byte.
    ErrorCode error = GetByte(&_headerBuf[n]);

    // printf("InputPipe::FindMessageHeader: %c %c %c %c\r\n"
    //   , _headerBuf[0] // Network Byte Order: MSB appears first.
    //   , _headerBuf[1]
    //   , _headerBuf[2]
    //   , _headerBuf[3]);

    // if error: exit.
    if (error != ErrorCode::Ok) { return error; }
  }

  // enter revolving loop.
  while (foundHeader == false)
  {
    // if found header:
    uint32_t* pHeader = (uint32_t*)_headerBuf;
    uint32_t headerValue = 
      MessageConstants::IS_LITTLE_ENDIAN ? ntohl(*pHeader) : *pHeader;
    if (headerValue == MessageConstants::MESSAGE_HEADER)
    {
      // exit.
      foundHeader = true;
    }
    else
    {
      // move every byte back-by-one.
      for (uint32_t n = 0; n < sizeof(uint32_t) - 1; n++)
      {
        _headerBuf[n] = _headerBuf[n + 1];
      }

      // get one new byte on the end.
      ErrorCode error = GetByte(&_headerBuf[sizeof(uint32_t) - 1]);
      if (error != ErrorCode::Ok) { return error; }
    }
  }

  // copy into buf.
  memcpy(_messageBuf, _headerBuf
    , sizeof(MessageConstants::MESSAGE_HEADER)
    );

  // ret.
  return ErrorCode::Ok;
}

ErrorCode InputPipe::FindMessageBacker(size_t arg_backerLength)
{
  // find body.
  char* pMessageBuf = _messageBuf +
    sizeof(MessageConstants::MESSAGE_HEADER);

  // copy: hw stream => _messageBuf.
  size_t n;
  for (n = 0
    ; n < arg_backerLength && n < MessageConstants::MAX_SIZE_MESSAGE
    ; n++)
  {
    ErrorCode error = GetByte(pMessageBuf);
    pMessageBuf++;

    if (error != ErrorCode::Ok) { return error; }
  }

  // if couldn't satisfy client:
  if (n < arg_backerLength)
  {
    return ErrorCode::BufferFull;
  }

  // ret.
  return ErrorCode::Ok;
}

