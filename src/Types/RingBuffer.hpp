/**
 * reference LICENSE file provided.
 *
 * @file RingBuffer.hpp
 * Concurrent ringbuffer in user space.
 *
 */

#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <time.h>
#include <stdint.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <sstream>
#include <condition_variable>
#include <iostream>
#include <ostream>
#include <fstream>
#include <semaphore>
#include <stdexcept>

/**
 * @class RingBuffer
 *
 * This class represents a ringbuffer with the following requirements:
 *   Producer and consumer shall be active simultaneously.
 *   Underflows shall never happen (`Read` blocks when empty).
 *   Overflows shall never happen (`Write` blocks when full).
 *
 */
template <class T>
class RingBuffer
{
public:

  /**
   * RingBuffer
   *
   * Creates the RingBuffer.
   *
   * @param[in] arg_size
   * The amount of objects of type 'T' that this buffer can hold.
   *
   * @param[in] arg_restore_oc 
   * If the buffer is empty,
   *   `Read` blocks until occupancy is greater than this number.
   * If the buffer is full,
   *   `Write` blocks until occupancy is less than size minus this number.
   * Minimum allowed value is '0'; maximum allowed value is 'size - 1'.
   *
   * @param[in] arg_should_log
   * Iff 'true', `Read` and `Write` timestamped logs to the cwd.
   */
  RingBuffer(int32_t arg_size, int32_t arg_restore_oc, bool arg_should_log = false);

  /**
   * ~RingBuffer
   *
   * Does the following:
   *   `Close`s off the RingBuffer (ref. `Close`).
   *   `delete[]`s the backing buffer.
   *   `delete`s the logs [if they were created].
   */
  ~RingBuffer();

  /**
   * Write
   * 
   * Writes one instance of type 'T' into the ringbuffer.
   * 
   * @param[in] arg_w
   * Instance of type 'T' to write into the ringbuffer.
   *
   * @param[out] rtn_e
   * Error code: '0' if a material value was written, '-1' otherwise.
   *
   * @param[in] arg_patience_ms
   * Blocking patience in milliseconds: <0 to wait indefinitely.
   * Note: The 'blocking patience' parameter is unimplemented to date.
   */
  void Write(T arg_w, int32_t* rtn_e = nullptr, int32_t arg_patience_ms = -1);

  /**
   * Read
   * 
   * Reads one instance of type 'T' from the ringbuffer.
   *
   * @param[out] rtn_e
   * Error code: '0' if a material value was returned; '-1' otherwise.
   *
   * @param[in] arg_patience_ms
   * Blocking patience in milliseconds: <0 to wait indefinitely.
   * Note: The 'blocking patience' parameter is unimplemented to date.
   *
   * @return
   * The value most-recently available to the read pointer.
   */
  T Read(int32_t* rtn_e = nullptr, int32_t arg_patience_ms = -1);

  /**
   * GetSize
   * @return Max number of instances of 'T' that this buffer can hold.
   */
  int32_t GetSize() const
  {
    return _size;
  }

  /**
   * GetOccupancy
   * @return Number of readable elements in the buffer.
   */
  int32_t GetOccupancy() const
  {
    return get_occupancy(_r.load(), _w.load());
  }

  /**
   * Close
   * Unblocks any `Read` or `Write` stuck in wait.
   * Permanently disables any future `Read` or `Write` call.
   */
  void Close()
  {
    _closed = true;
    _s_empty.release();
    _s_full.release();
  }

  /**
   * ReleaseRead
   * Cancels a blocking `Read` call.
   * Unlike `Close`, carries no persistent effect on the RingBuffer.
   * @return 'true' if there was a blocking operation to cancel, 'false' otherwise.
   */
  bool ReleaseRead()
  {
    if (_help_empty)
    {
      _r_cancel = true;
      _s_empty.release();
      _help_empty = false;
      return true;
    }

    return false;
  }

  /**
   * ReleaseWrite
   * Cancels a blocking `Write` call.
   * Unlike `Close`, carries no persistent effect on the RingBuffer.
   * @return 'true' if there was a blocking operation to cancel, 'false' otherwise.
   */
  bool ReleaseWrite()
  {
    if (_help_full)
    {
      _w_cancel = true;
      _s_full.release();
      _help_full = false;
      return true;
    }

    return false;
  }

  /**
   * ResetRead
   * Resets the read pointer, and state pertinent to `Read` calls.
   */
  void ResetRead()
  {
    _r.store(_buf);      // reset 'r' location.
    _help_empty = false; // unlatch: let the next blocking `Read` assert this.
    _r_cancel = false;   // unlatch, self-explanatory
  }

  /**
   * ResetWrite
   * Resets the write pointer, and state pertinent to `Write` calls.
   */
  void ResetWrite()
  {
    _w.store(_buf);      // reset 'w' location.
    _help_full = false;  // unlatch: let the next blocking `Write` catch this.
    _w_cancel = false;   // unlatch, self-explanatory
  }

private:

  // Basic pointer navigation--
  //   Pointer incrementing-- simple ternary branch
  //   Empty/full checks-- even simpler than `GetOccupancy`
  //
  T* inc(T* arg_p) const
  {
    return
      arg_p == _buf_last
        ? _buf
        : arg_p + 1;
  }
  
  void inc_w() { _w.store(inc(_w.load())); }

  void inc_r() { _r.store(inc(_r.load())); }

  bool is_empty() const { return _r.load() == _w.load(); }

  bool is_full() const { return inc(_w.load()) == _r.load(); }

  int32_t get_occupancy(T* arg_r, T* arg_w) const
  {
    if (arg_r > arg_w)
      { return (_buf_last - arg_r + 1) + (arg_w - _buf); }
    else
      { return arg_w - arg_r; }
  }

  // Misc. private helpers--
  // 
  void assign_error(int32_t* arg_p, int32_t arg_value) const
  {
    if (arg_p == nullptr) { return; }
    *arg_p = arg_value;
  }

  std::string log_timestamp() const
  {
    std::stringstream ss;
    ss << "[" << clock() << "] ";
    return ss.str();
  }

  // Core variables--
  //   buffer, read pointer, write pointer.
  //
  const int32_t _size;
  const int32_t _restore_occupancy;
  T* _buf;
  T* _buf_last;
  std::atomic<T*> _r;
  std::atomic<T*> _w;

  // Occupancy management (concurrency support)--
  // 
  std::binary_semaphore _s_empty;
  std::binary_semaphore _s_full;
  std::atomic<bool> _help_empty;
  std::atomic<bool> _help_full;
  std::atomic<bool> _closed;

  std::atomic<bool> _r_cancel;
  std::atomic<bool> _w_cancel;

  // Debug helpers--
  // 
  std::ofstream* _r_log; // logs all calls to `Read`
  std::ofstream* _w_log; // logs all calls to `Write`
};

#include "RingBuffer.tpp"

#endif // RINGBUFFER_HPP

