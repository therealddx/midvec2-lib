/**
 * reference LICENSE file provided.
 *
 * @file MessageConstants.hpp
 * Declarations for MessageConstants.
 */

#ifndef MESSAGECONSTANTS_HPP
#define MESSAGECONSTANTS_HPP

#include <stdint.h>

/**
 * @class MessageConstants
 * Namespace for static constants that pertain to `Message`s in this library.
 */
class MessageConstants
{
public:

  /**
   * All members in this class are static--
   *   calling this destructor is unnecessary.
   */
  ~MessageConstants() { };

  /**
   * Max number of bytes for any Message<T> instance, including header.
   */
  static const uint32_t MAX_SIZE_MESSAGE = 1024;

  /**
   * Every Message sent using this library shall start with this word.
   */
  static const uint32_t MESSAGE_HEADER = 0x4D494456;

  /**
   * Most significant byte of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B3 = 0x4D;

  /**
   * Byte '2' of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B2 = 0x49;

  /**
   * Byte '1' of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B1 = 0x44;

  /**
   * Least significant byte of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B0 = 0x56;

  /**
   * Moniker for host byte order of the host running this library-- 
   *   this should be a #define, but this library is untested on big-endian.
   */
  static const bool IS_LITTLE_ENDIAN = true;

private:

  MessageConstants() { };

};

#endif // MESSAGECONSTANTS_HPP
