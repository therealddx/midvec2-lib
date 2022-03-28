/*
 * reference LICENSE file provided.
 *
 * OutputPipeRam.hpp.
 * Defines an implementation for an output pipe that sends data to a
 * known area of system main memory.
 *
 */

#ifndef OUTPUTPIPERAM_HPP
#define OUTPUTPIPERAM_HPP

#include <stdint.h>
#include <string>
#include <sstream>
#include <atomic>
#include <iomanip>
#include <Types/RingBuffer.hpp>
#include "OutputPipeBase.hpp"

class OutputPipeRam : public OutputPipeBase
{
public:

  // 
  // Ctor.
  //
  OutputPipeRam(RingBuffer<char>* arg_ringBuffer, std::atomic<bool>* = nullptr);

  // 
  // Dtor.
  //
  ~OutputPipeRam();

  // 
  // PutMessage.
  //
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

  // 
  // GetRingBuffer
  // Return the ringbuffer held by this instance.
  // 
  RingBuffer<char>* GetRingBuffer() { return _ringBuffer; }

  // 
  // GetRingBufferAddress
  // Return a pretty-print string, holding the address of this instance's ringbuffer.
  // 
  std::string GetRingBufferAddress() const
  {
    std::stringstream addr_ss;

    addr_ss << "0x"
      << std::setw(8) << std::setfill('0') << std::hex
      << reinterpret_cast<uint64_t>(_ringBuffer);

    return addr_ss.str();
  }

private:

  // members: data.
  RingBuffer<char>* _ringBuffer;
  std::atomic<bool>* _rb_cancellation_token;
};

#endif // OUTPUTPIPERAM_HPP

