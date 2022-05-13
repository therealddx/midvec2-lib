/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeRam.hpp
 * Declarations for OutputPipeRam
 *
 */

#ifndef OUTPUTPIPERAM_HPP
#define OUTPUTPIPERAM_HPP

#include <stdint.h>
#include <string>
#include <atomic>
#include <sstream>
#include <iomanip>
#include <Types/RingBuffer.hpp>
#include "OutputPipeBase.hpp"

/**
 * @class OutputPipeRam
 * Defines an output pipe that writes serialized Message instances to main memory.
 */
class OutputPipeRam : public OutputPipeBase
{
public:

  /**
   * Constructs an instance to write to a RingBuffer.
   *
   * Note: This class does not own the RingBuffer; it only writes to it.
   *
   * @param[in] arg_ringBuffer RingBuffer to write to.
   */
  OutputPipeRam(RingBuffer<char>* arg_ringBuffer);

  /**
   * Destroys this instance:
   * - Resets the write state of the RingBuffer.
   * - Destroys owned member variables.
   * - Leaves no persistent impact on RingBuffer functionality.
   */
  ~OutputPipeRam();

  /**
   * Satisfies base class.
   */
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

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
   * - Cancels any blocking write call on the RingBuffer.
   * - Permanently shunts out of `PutMessage` calls.
   *
   * Note: This function leaves no persistent impact on the RingBuffer.
   */
  void Close()
  {
    _clientWriteEnabled = false;
    _ringBuffer->ReleaseWrite();
  }

private:

  // members: data.
  RingBuffer<char>* _ringBuffer;
  std::atomic<bool> _clientWriteEnabled;
};

#endif // OUTPUTPIPERAM_HPP

