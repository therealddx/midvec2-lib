/* 
 * reference LICENSE file provided.
 *
 * Message.hpp.
 * Class 'Message<T>' is a function-oriented interface,
 *   to how midvec2-lib sends and receives one backing data of type 'T'.
 * 
 * The only data an instance of 'Message<T>' holds is an instance of 'T'.
 * The public functions of 'Message<T>', however, perform for the client:
 *   Serialization of 'T',
 *     into a message that can be sent from a midvec2-lib output pipe.
 *   Deserialization of 'T',
 *     from a message that was received at a midvec2-lib input pipe.
 *   Queries on said messages,
 *     such as requisite total size and byte-for-byte content.
 *   
 */ 

// 
// This class can do:
// char* => T : Message(char*)
// T => char* : GetBytes(char*)
// Message    : Message(const Message<T>&)
// T          : GetBacker()
//

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "MessageConstants.hpp"

template <class T>
class Message
{
public:

  // 
  // Ctor.
  // Default to initialize memory.
  //
  Message<T>();

  // 
  // Ctor.
  // Marshal member fields from a raw byte array.
  // 
  Message<T>(char* arg_fromBuffer);

  // 
  // Ctor.
  // Marshal member fields from a copy operation.
  //
  Message<T>(const Message<T>& arg_other);

  // 
  // Ctor. 
  // Marshal member fields from an instance of backer's type.
  //
  Message<T>(const T& arg_backer);

  // 
  // Dtor.
  // Nothing done. All members allocated on stack.
  // 
  ~Message<T>() { }

  // 
  // Accessors.
  // 

  // 
  // GetBytes.
  // Get a byte array to represent this instance over a wire.
  // 
  size_t GetBytes(char* rtn_bytes);

  // 
  // GetBacker.
  // Return the backing data for this instance.
  //
  T GetBacker();

  // 
  // GetRequiredSize.
  // Returns the requisite size for a char* that wishes
  // to hold this serialized message.
  // 
  size_t GetRequiredSize()
    { return sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T); }

private:

  // 
  // ReverseByteOrder.
  // arg_badBo  : 'n' bytes bytes exist here at the wrong byte order.
  // rtn_goodBo : put those 'n' bytes in the opposite byte order, here.
  // arg_size   : 'n'.
  // 
  void ReverseByteOrder(char* arg_badBo, char* rtn_goodBo, size_t arg_size);
  
  // members: data.
  T _backer; // payload data for this Message.

};

#include "Message.tpp"

#endif // MESSAGE_HPP

