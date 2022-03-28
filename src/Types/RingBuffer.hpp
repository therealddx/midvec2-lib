#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <stdint.h>
#include <mutex>
#include <atomic>
#include <iostream>
#include <ostream>

/**
 * RingBuffer
 *
 * This class represents a ringbuffer that has the
 * ""potential""
 * for concurrent access between a producer and consumer.
 *
 * Some issues with building such a ringbuffer in user space--
 *   There is no promise of hard synchronization between producer and consumer.
 *   Overflows and underflows must be rigidly guarded against.
 *   To act on time values in any form (e.g. delays, speed measurements on either thread),
 *     is intensely unproductive.
 *
 */
template <class T>
class RingBuffer
{
public:

  RingBuffer(int32_t, int32_t = 4);

  ~RingBuffer();

  void Write(T, std::atomic<bool>* = nullptr);

  T Read(std::atomic<bool>* = nullptr);

  int32_t GetSize() { return _sz; }

  int32_t GetOccupancy();

  void Dump(std::ostream&);

private:

  T* inc(T* arg_p)
  {
    return
      arg_p == _buf_last
        ? _buf
        : arg_p + 1;
  }

  void inc_w()
  {
    _w =
      _w == _buf_last
        ? _buf
        : _w + 1;
  }

  void inc_r()
  {
    _r =
      _r == _buf_last
        ? _buf
        : _r + 1;
  }

  int32_t get_occupancy();

  // Core variables--
  //   buffer, read pointer, write pointer.
  //
  T* _buf;
  std::atomic<T*> _r;
  std::atomic<T*> _w;

  // Helper constants--
  //   store for size, and pointer to final allocated array index.
  //
  int32_t _sz;
  T* _buf_last;

  // Overflow guard variables--
  //
  // These variables are used to guard against over-/under-flow,
  //   while presenting a face of concurrency.
  // 
  // To do so, this class's occupancy is in one of three 'zones':
  //   the 'fill' zone,
  //   the 'drain' zone, and
  //   the 'concurrent' zone.
  // 
  // In the 'fill' zone, the ringbuffer blocks read operations...
  //   until the occupancy climbs from 'empty',
  //   back up to `1 / _denominator_zone_guard` ratio of the size.
  //
  // In the 'drain' zone, the ringbuffer blocks write operations...
  //   until the occupancy falls from 'full',
  //   back down to `1 - (1 / _denominator_zone_guard)` ratio of the size.
  //
  // In the 'concurrent' zone, both reader and writer threads are operating.
  // 
  std::atomic<bool> _is_empty;     // read thread cares about this; to prevent underflow.
  std::atomic<bool> _is_full;      // write thread cares about this; to prevent overflow.
  int32_t _denominator_zone_guard; // arguments < 2 are nonsense, and defaulted out.
  std::atomic<bool> _dtor_kill;    // dtor. bails the instance out of 'drain' mode / 'fill' mode.
  std::atomic<bool> _drain_done;   // 'true' == done with 'drain' mode; 'false' ow.
  std::atomic<bool> _fill_done;    // 'true' == done with 'fill' mode; 'false' ow.

  // Monitor lock variables--
  //
  // These locks cause contention 
  // 
  // **********************
  // *** IF AND ONLY IF ***
  // **********************
  // 
  // a client is periodically calling a 'monitor' function,
  // (e.g. `Dump` or `GetOccupancy`),
  // during operational, producer/consumer action.
  // 
  // Additionally-- the dtor takes these locks.
  // 
  std::mutex _r_lock;
  std::mutex _w_lock;
};

#include "RingBuffer.tpp"

#endif // RINGBUFFER_HPP

