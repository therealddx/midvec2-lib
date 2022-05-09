/**
 * reference LICENSE file provided.
 *
 * @file MessageConstants.hpp
 * Namespace for static constants that pertain to Message's in this library.
 */

#ifndef MESSAGECONSTANTS_HPP
#define MESSAGECONSTANTS_HPP

#include <stdint.h>

/**
 * @class MessageConstants
 */
class MessageConstants
{
public:

  /**
   * MessageConstants
   */
  MessageConstants() { };

  /**
   * ~MessageConstants
   */
  ~MessageConstants() { };

  /**
   * MAX_SIZE_MESSAGE
   * @brief Max number of bytes for any Message<T> instance, including header.
   */
  static const uint32_t MAX_SIZE_MESSAGE = 1024;

  /**
   * MESSAGE_HEADER
   *
   * @brief
   * Every Message sent using this library shall start with this word.
   */
  static const uint32_t MESSAGE_HEADER = 0x4D494456;

  /**
   * MESSAGE_HEADER_B3
   * @brief
   * Most significant byte of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B3 = 0x4D;

  /**
   * MESSAGE_HEADER_B2
   * @brief
   * Byte '2' of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B2 = 0x49;

  /**
   * MESSAGE_HEADER_B1
   * @brief
   * Byte '1' of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B1 = 0x44;

  /**
   * MESSAGE_HEADER_B0
   * @brief
   * Least significant byte of MESSAGE_HEADER, in network byte order.
   */
  static const unsigned char MESSAGE_HEADER_B0 = 0x56;

  /**
   * IS_LITTLE_ENDIAN
   *
   * @brief
   * Moniker for host byte order of the host running this library.
   * This should be a #define, but this library is untested on big-endian.
   */
  static const bool IS_LITTLE_ENDIAN = true;

};

#endif // MESSAGECONSTANTS_HPP
