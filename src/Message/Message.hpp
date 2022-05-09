/**
 * reference LICENSE file provided.
 *
 * @file Message.hpp
 *
 * Class 'Message<T>' is a function-oriented interface,
 *   to how midvec2-lib sends and receives one backing data of type 'T'.
 * 
 * The only data an instance of 'Message<T>' holds is an instance of 'T'.
 *
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

/**
 * @class Message
 */
template <class T>
class Message
{
public:

  // 
  // Ctor.
  //

  /**
   * Message
   * Default constructor.
   * Backing data is left uninitialized.
   */
  Message();

  /**
   * Message
   * Marshal member fields from a raw byte array.
   * @param[in] Pointer to data from which backing type will be marshaled.
   */
  Message(char* arg_fromBuffer);

  /**
   * Message
   * Copy constructor.
   * @param[in] arg_other Message to copy contents from.
   */
  Message(const Message<T>& arg_other);

  /**
   * Message
   * Backing type constructor.
   * @param[in] arg_backer Initial value for backing data.
   */
  Message(const T& arg_backer);

  /**
   * ~Message
   */
  ~Message() { }

  // 
  // Accessors.
  // 

  /**
   * GetBytes
   * Store the message header, plus backing data, to serialized storage.
   *
   * @param[in] rtn_bytes
   * Pre-allocated storage to which header and backing data will be copied.
   *
   * @return Number of bytes copied into argument pointer.
   */
  size_t GetBytes(char* rtn_bytes);

  /**
   * GetBacker
   * @return Copy of this instance's backing data.
   */
  T GetBacker();

  /**
   * GetRequiredSize
   * @return Required size for any char buffer that is to hold this serialized message.
   */
  size_t GetRequiredSize()
  {
    return sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T);
  }

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

