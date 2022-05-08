/*
 * reference LICENSE file provided.
 *
 * OutputPipeRam.cpp.
 * Implements OutputPipeRam.hpp.
 *
 */

#include "OutputPipeRam.hpp"

OutputPipeRam::OutputPipeRam(RingBuffer<char>* arg_ringBuffer)
: _ringBuffer(arg_ringBuffer)
{
  _clientWriteEnabled = true;
}

OutputPipeRam::~OutputPipeRam()
{
}

ErrorCode OutputPipeRam::PutMessage(char* arg_msgBytes, int32_t arg_msgLen)
{
  // arg check.
  if (arg_msgBytes == NULL) { return ErrorCode::NullPointer; }

  // state check.
  if (!_clientWriteEnabled) { return ErrorCode::Cancelled; }

  // vars.
  int32_t e_write = 0;

  // write.
  for (int32_t n_b = 0; n_b < arg_msgLen; n_b++)
  {
    _ringBuffer->Write(arg_msgBytes[n_b], &e_write, 1000);
    if (0 != e_write) { break; }
  }

  // ret.
  return 0 == e_write ? ErrorCode::Ok : ErrorCode::Cancelled;
}

