/**
 * reference LICENSE file provided.
 *
 * @file ErrorCode.hpp
 *
 * Provides an index space for errors that occur within this library.
 *
 * 'Error's, meaning-- a significant offroad from 'happy-path' program flow.
 *
 */

#ifndef ERRORCODE_HPP
#define ERRORCODE_HPP

/**
 * @enum ErrorCode
 */
enum class ErrorCode 
{
  /**
   * The function executed without issue ('happy-path').
   */
  Ok = 0,

  /**
   * The function encountered an unexpected end-of-file.
   */
  EofReached = -1,

  /**
   * The function encountered an unexpected null pointer.
   */
  NullPointer = -2,

  /**
   * The function encountered an unexpected full buffer.
   */
  BufferFull = -3,

  /**
   * The function encountered an unexpected empty buffer.
   */
  BufferEmpty = -4,

  /**
   * The function encountered an unexpected socket error.
   */
  SocketError = -5,

  /**
   * The function encountered an unexpected generic error.
   */
  Shrug = -6,

  /**
   * The function encountered an unexpected bad argument.
   */
  BadArgument = -7,

  /**
   * The function encountered an unexpected cancellation.
   */
  Cancelled = -8
};

#endif // ERRORCODE_HPP

