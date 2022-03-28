#ifndef RINGBUFFER_TPP
#define RINGBUFFER_TPP

#include <thread>
#include <chrono>

template <class T>
RingBuffer<T>::RingBuffer(int32_t arg_sz, int32_t arg_denominator_zone_guard)
{
  _sz = arg_sz;
  _buf = new T[_sz];
  _r = _buf;
  _w = _buf;
  _buf_last = _buf + _sz - 1;

  for (int32_t n = 0; n < _sz; n++)
    { _buf[n] = 0; }

  _is_empty = true;
  _is_full = false;
  _dtor_kill = false;
  _denominator_zone_guard = arg_denominator_zone_guard < 2 ? 4 : arg_denominator_zone_guard;
  _drain_done = true;
  _fill_done = true;
}

template <class T>
RingBuffer<T>::~RingBuffer()
{
  // Taking these locks will block all public methods.
  // 
  _r_lock.lock();
  _w_lock.lock();

  // `_dtor_kill.load() == true` will shunt out all
  // subsequent calls on 'drain' mode and 'fill' mode.
  // 
  _dtor_kill = true;
  while (!_drain_done || !_fill_done)
  {
  }

  // The main reason we're here.
  delete[] _buf;

  // Don't delete a locked mutex...
  _r_lock.unlock();
  _w_lock.unlock();
}

template <class T>
void RingBuffer<T>::Write(T arg_w, std::atomic<bool>* arg_client_token)
{
  if (_is_full.load()) // handle drain mode if necessary.
  {
    _drain_done = false;

    while (
      ( get_occupancy() > ( GetSize() * (_denominator_zone_guard - 1) / _denominator_zone_guard ) )
      && !_dtor_kill.load()
      && ( arg_client_token == nullptr || !arg_client_token->load() )
      ) // in the 'drain' zone
    {
    }

    _drain_done = true;

    if (_dtor_kill.load())
    {
      return;
    }

    if (arg_client_token != nullptr && arg_client_token->load())
    {
      return;
    }
  }

  _w_lock.lock(); // execute the write.

  *_w = arg_w;
  inc_w();
  _is_full = inc(_w) == _r; // inter-thread access: 'r' pointer.

  _w_lock.unlock();
}

template <class T>
T RingBuffer<T>::Read(std::atomic<bool>* arg_client_token)
{
  if (_is_empty.load()) // handle fill mode if necessary.
  {
    _fill_done = false;

    while (
      ( get_occupancy() < ( GetSize() / _denominator_zone_guard ) )
      && !_dtor_kill.load()
      && ( arg_client_token == nullptr || !arg_client_token->load() )
      ) // in the 'fill' zone
    {
    }

    _fill_done = true;

    if (_dtor_kill.load())
    {
      T rtn;
      return rtn;
    }

    if (arg_client_token != nullptr && arg_client_token->load())
    {
      T rtn;
      return rtn;
    }
  }

  _r_lock.lock(); // execute the read.

  T rtn = *_r;
  inc_r();
  _is_empty = _r == _w; // inter-thread access: 'w' pointer.

  _r_lock.unlock();

  return rtn;
}

template <class T>
int32_t RingBuffer<T>::GetOccupancy()
{
  // lock the entire buffer--
  //   otherwise function output will be wrong by return-time
  // up for debate, though...
  // 
  _w_lock.lock();
  _r_lock.lock();

  T* local_r = _r;
  T* local_w = _w;

  int32_t rtn_occupancy = 0;

  while (local_r != local_w)
  {
    rtn_occupancy++;
    local_r = inc(local_r);
  }

  _w_lock.unlock();
  _r_lock.unlock();

  return rtn_occupancy;
}

template <class T>
void RingBuffer<T>::Dump(std::ostream& arg_os)
{
  // lock the entire buffer--
  //   otherwise data may change while we read
  // 
  _w_lock.lock();
  _r_lock.lock();

  arg_os << "{ ";

  for
    ( T* it_buf = _buf
    ; it_buf != _buf_last + 1
    ; ++it_buf
    )
  {
    if (it_buf == _r)
    {
      arg_os << "(r)";
    }

    if (it_buf == _w)
    {
      arg_os << "(w)";
    }

    arg_os << *it_buf << " ";
  }

  arg_os << "}" << std::endl;

  _w_lock.unlock();
  _r_lock.unlock();
}

template <class T>
int32_t RingBuffer<T>::get_occupancy()
{
  // snapshot, but no lock.
  //   this function is read-only wrt the member variables it uses.
  //   it just needs a mostly-faithful read on occupancy at this moment.
  // 
  T* local_r = _r.load();
  T* local_w = _w.load();

  int32_t rtn_occupancy = 0;

  while (local_r != local_w)
  {
    rtn_occupancy++;
    local_r = inc(local_r);
  }

  return rtn_occupancy;
}

#endif // RINGBUFFER_TPP

