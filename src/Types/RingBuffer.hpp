/**
 * reference LICENSE file provided.
 *
 * RingBuffer.hpp
 * Concurrent user ringbuffer.
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
 * RingBuffer
 *
 * This class represents a concurrent ringbuffer
 *   (both producer and consumer active)
 * in user space.
 *
 * This class expects to be serviced by three roles:
 *   producer (calling `Write`),
 *   consumer (calling `Read`), or
 *   monitor (calling `ctor`/`delete`).
 *
 * This class blocks `Write` to prevent overflow,
 *   and blocks `Read` to prevent underflow.
 *
 */
template <class T>
class RingBuffer
{
public:

  /**
   * Ctor
   *
   * @brief
   *   Creates the RingBuffer.
   *
   * @param[in] arg_size
   *   The amount of objects of type 'T' that this buffer can hold.
   *
   * @param[in] arg_restore_occupancy 
   *   If `Read` sees that the buffer is empty,
   *     it will block until the occupancy is greater than this number.
   *   If `Write` sees that the buffer is full,
   *     it will block until the occupancy is less than size minus this number.
   *   Minimum allowed value is '0'; maximum allowed value is 'size - 1'.
   *
   * @param[in] arg_should_log
   *   Iff 'true', puts out separate, timestamped logs on `Read` and `Write` calls.
   *
   */
  RingBuffer
    ( int32_t arg_size
    , int32_t arg_restore_occupancy
    , bool arg_should_log = false
    );

  /**
   * Dtor
   *
   * @brief
   *   Destroys the RingBuffer.
   *   Does not clean up after client callers, however!
   *   Call `Close` before `delete`, to unblock client callers.
   */
  ~RingBuffer();

  /**
   * Write
   * 
   * @brief
   *   Writes 'T' into the ringbuffer.
   *   Blocks until buffer is no-longer full.
   *   Optional 'int32_t*' argument holds return-error value.
   *   Optional 'int32_t' argument holds blocking patience in milliseconds.
   *     < 0: wait indefinitely
   *     >= 0: wait this many milliseconds
   */
  void Write(T, int32_t* = nullptr, int32_t = -1);

  /**
   * Read
   * 
   * @brief
   *   Reads one element of type 'T' from the ringbuffer.
   *   Blocks until buffer is no-longer empty.
   *   Optional 'int32_t*' argument holds return-error value.
   *   Optional 'int32_t' argument holds blocking patience in milliseconds.
   *     < 0: wait indefinitely
   *     >= 0: wait this many milliseconds
   */
  T Read(int32_t* = nullptr, int32_t = -1);

  /**
   * GetSize
   * @brief Self-explanatory.
   */
  int32_t GetSize() const
  {
    return _size;
  }

  /**
   * GetOccupancy
   * @brief Returns number of readable elements in the buffer.
   */
  int32_t GetOccupancy() const
  {
    return get_occupancy(_r.load(), _w.load());
  }

  /**
   * Close
   * @brief Unblocks any `Read` or `Write` stuck in wait,
   *   and ensures that any future `Read` or `Write` call will immediately shunt.
   */
  void Close()
  {
    _closed = true;
    _s_empty.release();
    _s_full.release();
  }

  /**
   * ReleaseRead
   * @brief Unblocks a blocking `Read` call; and forces it to return with no action.
   *   Unlike `Close`, carries no persistent effect on the RingBuffer.
   * 
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
   * @brief Unblocks a blocking `Write` call; and forces it to return with no action.
   *   Unlike `Close`, carries no persistent effect on the RingBuffer.
   * 
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

  // Occupancy management--
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

