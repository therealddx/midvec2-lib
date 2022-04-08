/*
 * reference LICENSE file provided.
 *
 * InputPipeRam.hpp.
 * Defines an implementation for an input pipe that operates on data 
 * stored in system main memory. Intended for fully-reliable maximum speed
 * pipe communication within localhost.
 *
 */

#ifndef INPUTPIPERAM_HPP
#define INPUTPIPERAM_HPP

#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <Types/RingBuffer.hpp>
#include "InputPipe.hpp"

class InputPipeRam : public InputPipe
{
public:

  // 
  // Ctor.
  //
  InputPipeRam(RingBuffer<char>* arg_ringBuffer);

  // 
  // Dtor.
  //
  ~InputPipeRam();

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

  // 
  // InputPipe: Mandatory Implementations.
  //
  ErrorCode GetByte(char* rtn_byte); 

  // members: data: ram read.
  RingBuffer<char>* _ringBuffer;
};

#endif // INPUTPIPERAM_HPP

