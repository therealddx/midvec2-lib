/*
 * reference LICENSE file provided.
 *
 * InputPipeRam.cpp.
 * Implements InputPipeRam.hpp.
 *
 */

#include "InputPipeRam.hpp"

InputPipeRam::InputPipeRam(RingBuffer<char>* arg_ringBuffer, std::atomic<bool>* arg_rb_token)
: _ringBuffer(arg_ringBuffer)
, _rb_cancellation_token(arg_rb_token)
{
}

InputPipeRam::~InputPipeRam()
{
}

ErrorCode InputPipeRam::GetByte(char* rtn_byte)
{
  // arg check.
  if (rtn_byte == 0) { return ErrorCode::NullPointer; }

  // state check.
  if (_rb_cancellation_token != nullptr && _rb_cancellation_token->load())
    { return ErrorCode::Cancelled; }

  // get a byte from the ringbuffer.
  int32_t e_read = 0;
  *rtn_byte = _ringBuffer->Read(&e_read, 1000);
  return ErrorCode::Ok;
}

