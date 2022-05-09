/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeRam.hpp
 * Defines a concrete output pipe that writes data to main memory.
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
 */
class OutputPipeRam : public OutputPipeBase
{
public:

  /**
   * OutputPipeRam
   *
   * @param[in] arg_ringBuffer RingBuffer to write to.
   *
   * Note: This class does not own the RingBuffer; it only writes to it.
   */
  OutputPipeRam(RingBuffer<char>* arg_ringBuffer);

  /**
   * ~OutputPipeRam
   * Resets the write state of the RingBuffer and destroys 'this' instance.
   */
  ~OutputPipeRam();

  /**
   * PutMessage
   * Satisfies base class.
   */
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

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
   *
   * @return
   * A human-readable string denoting the address of this instance's ringbuffer.
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
   *
   * Cancels any blocking `RingBuffer<T>::Write` call.
   * Permanently shunts out of `PutMessage` calls.
   * Note: This function kills this instance, not the RingBuffer.
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

