/*
 * reference LICENSE file provided.
 *
 * InputPipeRam.cpp.
 * Implements InputPipeRam.hpp.
 *
 */

#include "InputPipeRam.hpp"

InputPipeRam::InputPipeRam(RingBuffer<char>* arg_ringBuffer)
: _ringBuffer(arg_ringBuffer)
{
}

InputPipeRam::~InputPipeRam()
{
  _ringBuffer->ReleaseRead();
}

ErrorCode InputPipeRam::GetByte(char* rtn_byte)
{
  // arg check.
  if (rtn_byte == 0) { return ErrorCode::NullPointer; }

  // get a byte from the ringbuffer.
  int32_t e_read = 0;
  *rtn_byte = _ringBuffer->Read(&e_read, 1000);
  return 0 == e_read ? ErrorCode::Ok : ErrorCode::Cancelled;
}

