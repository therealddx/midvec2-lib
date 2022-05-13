/**
 * reference LICENSE file provided.
 *
 * @file InputPipeRam.hpp
 * Declarations for InputPipeRam
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
 * Implements an input pipe that deserializes Message instances from shared RAM.
 */
class InputPipeRam : public InputPipe
{
public:

  /**
   * Constructs an instance to read from a RingBuffer.
   *
   * Note: This class does not own the RingBuffer; it only reads from it.
   *
   * @param[in] arg_ringBuffer RingBuffer to read from.
   */
  InputPipeRam(RingBuffer<char>* arg_ringBuffer);

  /**
   * Destroys this instance:
   * - Resets the read state of the RingBuffer.
   * - Destroys member variables.
   * - Leaves no persistent impact on RingBuffer functionality.
   */
  ~InputPipeRam();

  /**
   * Reports RingBuffer pointer referenced by this instance.
   * @return Pointer to the RingBuffer held by this instance.
   */
  RingBuffer<char>* GetRingBuffer()
  {
    return _ringBuffer;
  }

  /**
   * Reports RingBuffer pointer referenced by this instance,
   *   as a human-readable string.
   *
   * @return
   * A human-readable string denoting the address of this instance's
   *   referenced RingBuffer.
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
   * Satisfies base implementation:
   * - Cancels any blocking read call on the RingBuffer.
   * - Permanently shunts out of `GetMessage` calls.
   *
   * Note: This function leaves no persistent impact on RingBuffer functionality.
   */
  void Close()
  {
    _clientReadEnabled = false;
    _ringBuffer->ReleaseRead();
  }

private:

  /**
   * Satisfies base class.
   */
  ErrorCode GetByte(char* rtn_byte); 

  // members: data: ram read.
  RingBuffer<char>* _ringBuffer;
  std::atomic<bool> _clientReadEnabled;
};

#endif // INPUTPIPERAM_HPP

