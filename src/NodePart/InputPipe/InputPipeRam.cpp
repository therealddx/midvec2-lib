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
  _clientReadEnabled = true;
}

InputPipeRam::~InputPipeRam()
{
  _ringBuffer->ResetRead();
}

ErrorCode InputPipeRam::GetByte(char* rtn_byte)
{
  // arg check.
  if (rtn_byte == 0) { return ErrorCode::NullPointer; }

  // state check.
  if (!_clientReadEnabled) { return ErrorCode::Cancelled; }

  // get a byte from the ringbuffer.
  int32_t e_read = 0;
  *rtn_byte = _ringBuffer->Read(&e_read, 1000);
  return 0 == e_read ? ErrorCode::Ok : ErrorCode::Cancelled;
}

