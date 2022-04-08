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

  RingBuffer(int32_t, bool = false);

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
  int32_t GetSize()
  {
    return _sz;
  }

  /**
   * GetOccupancy
   * @brief Returns number of readable elements in the buffer.
   */
  int32_t GetOccupancy()
  {
    return get_occupancy(_r.load(), _w.load());
  }

private:

  // Basic pointer navigation--
  //   Pointer incrementing-- simple ternary branch
  //   Empty/full checks-- even simpler than `GetOccupancy`
  //
  T* inc(T* arg_p)
  {
    return
      arg_p == _buf_last
        ? _buf
        : arg_p + 1;
  }
  
  void inc_w() { _w.store(inc(_w.load())); }

  void inc_r() { _r.store(inc(_r.load())); }

  bool is_empty() { return _r.load() == _w.load(); }

  bool is_full() { return inc(_w.load()) == _r.load(); }

  int32_t get_occupancy(T* arg_r, T* arg_w)
  {
    if (arg_r > arg_w)
      { return (_buf_last - arg_r + 1) + (arg_w - _buf); }
    else
      { return arg_w - arg_r; }
  }

  // Misc. private helpers--
  // 
  void assign_error(int32_t* arg_p, int32_t arg_value)
  {
    if (arg_p == nullptr) { return; }
    *arg_p = arg_value;
  }

  std::string log_timestamp()
  {
    std::stringstream ss;
    ss << "[" << clock() << "] ";
    return ss.str();
  }

  // Core variables--
  //   buffer, read pointer, write pointer.
  //
  T* _buf;
  std::atomic<T*> _r;
  std::atomic<T*> _w;
  int32_t _sz;
  T* _buf_last;

  // Occupancy management--
  // 
  std::binary_semaphore _s_empty;
  std::binary_semaphore _s_full;
  std::atomic<bool> _help_empty;
  std::atomic<bool> _help_full;

  // Debug helpers--
  // 
  std::ofstream* _r_log; // logs all calls to `Read`
  std::ofstream* _w_log; // logs all calls to `Write`
};

#include "RingBuffer.tpp"

#endif // RINGBUFFER_HPP

