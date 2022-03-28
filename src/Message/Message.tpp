/* 
 * reference LICENSE file provided.
 *
 * Message.tpp
 * Implements Message.hpp
 * 
 */

#ifndef MESSAGE_TPP
#define MESSAGE_TPP

#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include "MessageConstants.hpp"

// 
// Document map.
//   Ctor.
//   Accessors.
//

// 
// Ctor.
// 
template <class T>
Message<T>::Message()
{
  // let _backer be initialized to default IAW its type.
}

template <class T>
Message<T>::Message(char* arg_fromBuffer)
{
  // 
  // arg check: find header.
  // 
  uint32_t* pHeader = (uint32_t*)arg_fromBuffer;
  uint32_t headerValue = 
    MessageConstants::IS_LITTLE_ENDIAN ? ntohl(*pHeader) : *pHeader;

  if (headerValue != MessageConstants::MESSAGE_HEADER)
  {
    return; // no header. no Message.
  }

  // 
  // copy in the backer.
  //   currently: assume T is primitive, or predictable for serialization.
  // 
  if (MessageConstants::IS_LITTLE_ENDIAN == true)
  {
    // reverse copy.
    ReverseByteOrder
      ( arg_fromBuffer + sizeof(MessageConstants::MESSAGE_HEADER) +
        sizeof(T) - 1
      , (char*)&_backer
      , sizeof(T));
  }
  else
  {
    // direct copy.
    memcpy(&_backer, arg_fromBuffer + sizeof(uint32_t), sizeof(T));
  }
}

template <class T>
void Message<T>::ReverseByteOrder
  ( char* arg_badBo
  , char* rtn_goodBo
  , size_t arg_size)
{
  // vars.
  char* rtn_goodBoLimit = rtn_goodBo + arg_size;

  // copy.
  while (rtn_goodBo < rtn_goodBoLimit)
  {
    *rtn_goodBo++ = *arg_badBo--;
  }
}

template <class T>
Message<T>::Message(const Message<T>& arg_other)
{
  // copy backer field.
  _backer = arg_other.GetBacker();
}

template <class T>
Message<T>::Message(const T& arg_backer)
: _backer(arg_backer)
{
  // direct backer assignment.
  // other accessors can handle byte ordering.
}

// 
// Accessors.
//
template <class T>
size_t Message<T>::GetBytes(char* rtn_bytes)
{
  // 
  // copy header out.
  // 
  uint32_t copyHeader = MessageConstants::MESSAGE_HEADER;

  if (MessageConstants::IS_LITTLE_ENDIAN == true)
  {
    ReverseByteOrder
      ( (char*)&copyHeader + sizeof(MessageConstants::MESSAGE_HEADER) - 1
      , rtn_bytes
      , sizeof(MessageConstants::MESSAGE_HEADER));
  }
  else
  {
    memcpy
      ( rtn_bytes
      , &copyHeader
      , sizeof(MessageConstants::MESSAGE_HEADER));
  }

  //  
  // copy backer out.
  // 
  if (MessageConstants::IS_LITTLE_ENDIAN == true)
  {
    ReverseByteOrder
      ( (char*)&_backer + sizeof(T) - 1
      , rtn_bytes + sizeof(MessageConstants::MESSAGE_HEADER)
      , sizeof(T));
  }
  else
  {
    memcpy
      ( rtn_bytes + sizeof(MessageConstants::MESSAGE_HEADER)
      , &_backer
      , sizeof(T));
  }

  // ret num bytes on wire.
  return sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T);
}

template <class T>
T Message<T>::GetBacker()
{
  return _backer;
}

#endif // MESSAGE_TPP

