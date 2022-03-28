/*
 * reference LICENSE file provided.
 *
 * ErrorCode.hpp.
 *
 * Provides index space for errors that occur within this library, that do not necessitate exception + unwind.
 *
 */

#ifndef ERRORCODE_HPP
#define ERRORCODE_HPP

enum class ErrorCode 
{
  Ok = 0,
  EofReached = -1,
  NullPointer = -2,
  BufferFull = -3,
  BufferEmpty = -4,
  SocketError = -5,
  Shrug = -6,
  BadArgument = -7,
  Cancelled = -8
};

#endif // ERRORCODE_HPP

