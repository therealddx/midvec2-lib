/*
 * reference LICENSE file provided.
 *
 * MessageConstants.hpp.
 * Defines static constants for Messages, outside of templated realm
 * of Message definitions.
 */

#ifndef MESSAGECONSTANTS_HPP
#define MESSAGECONSTANTS_HPP

#include <stdint.h>

class MessageConstants
{
public:
  MessageConstants() { };
  ~MessageConstants() { };

  // 
  // No Message<T> instance, to be sent over a wire,
  // will be longer than this amount of bytes, including header.
  //
  static const uint32_t MAX_SIZE_MESSAGE = 1024;

  // 
  // Every Message, in its serialized form, can be found with
  // this unsigned integer preceding it, in network byte order.
  //
  static const uint32_t MESSAGE_HEADER = 0x4D494456;
  static const unsigned char MESSAGE_HEADER_B3 = 0x4D; // MSB: byte 3, NBO.
  static const unsigned char MESSAGE_HEADER_B2 = 0x49;
  static const unsigned char MESSAGE_HEADER_B1 = 0x44;
  static const unsigned char MESSAGE_HEADER_B0 = 0x56; // LSB: byte 0, NBO.

  // 
  // Now we're starting to get into platform nitty grittys.
  // This bool is set to TRUE when this code runs on a little-endian host.
  // Otherwise, it is set to FALSE.
  //
  // This can be managed with preprocessor business to avoid the control
  // structure, but that's not a concern yet.
  //
  static const bool IS_LITTLE_ENDIAN = true;

};

#endif // MESSAGECONSTANTS_HPP
