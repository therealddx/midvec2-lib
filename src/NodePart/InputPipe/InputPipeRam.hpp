/**
 * reference LICENSE file provided.
 *
 * @file InputPipeRam.hpp
 * Implements an input pipe that deserializes Messages from shared RAM.
 *
 */

#ifndef INPUTPIPERAM_HPP
#define INPUTPIPERAM_HPP

#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>
#include <atomic>
#include <sstream>
#include <iomanip>
#include <Types/RingBuffer.hpp>
#include "InputPipe.hpp"

/**
 * @class InputPipeRam
 */
class InputPipeRam : public InputPipe
{
public:

  /**
   * InputPipeRam
   *
   * @param[in] arg_ringBuffer
   * RingBuffer to read from.
   *
   * Note: This class does not own the RingBuffer; it only reads from it.
   */
  InputPipeRam(RingBuffer<char>* arg_ringBuffer);

  /**
   * ~InputPipeRam
   * Resets the read state of the RingBuffer and destroys 'this' instance.
   */
  ~InputPipeRam();

  /**
   * GetRingBuffer
   * @return Pointer to the ringbuffer held by this instance.
   */
  RingBuffer<char>* GetRingBuffer()
  {
    return _ringBuffer;
  }

  /**
   * GetRingBufferAddress
   * @return A human-readable string denoting the address of this instance's ringbuffer.
   */
  std::string GetRingBufferAddress() const
  {
    std::stringstream addr_ss;

    addr_ss << "0x"
      << std::setw(8) << std::setfill('0') << std::hex
      << reinterpret_cast<uint64_t>(_ringBuffer);

    return addr_ss.str();
  }

  /**
   * Close
   * Permanently shuts off this instance's ability to read (`GetMessage`).
   * Cancels any blocking `RingBuffer<T>::Read` call.
   * Note: This function kills this instance, not the RingBuffer.
   */
  void Close()
  {
    _clientReadEnabled = false;
    _ringBuffer->ReleaseRead();
  }

private:

  /**
   * GetByte
   * Satisfies base class.
   */
  ErrorCode GetByte(char* rtn_byte); 

  // members: data: ram read.
  RingBuffer<char>* _ringBuffer;
  std::atomic<bool> _clientReadEnabled;
};

#endif // INPUTPIPERAM_HPP

