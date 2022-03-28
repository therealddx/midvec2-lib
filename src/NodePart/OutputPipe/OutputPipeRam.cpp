/*
 * reference LICENSE file provided.
 *
 * OutputPipeRam.cpp.
 * Implements OutputPipeRam.hpp.
 *
 */

#include "OutputPipeRam.hpp"

OutputPipeRam::OutputPipeRam(RingBuffer<char>* arg_ringBuffer, std::atomic<bool>* arg_token)
: _ringBuffer(arg_ringBuffer)
, _rb_cancellation_token(arg_token)
{
}

OutputPipeRam::~OutputPipeRam()
{
}

ErrorCode OutputPipeRam::PutMessage(char* arg_msgBytes, int32_t arg_msgLen)
{
  // arg check.
  if (arg_msgBytes == NULL) { return ErrorCode::NullPointer; }

  // state check.
  if (_rb_cancellation_token != nullptr && _rb_cancellation_token->load())
    { return ErrorCode::Cancelled; }

  // write.
  for (int32_t n_b = 0; n_b < arg_msgLen; n_b++)
  {
    _ringBuffer->Write(arg_msgBytes[n_b], _rb_cancellation_token);
  }

  // ret.
  return ErrorCode::Ok;
}

