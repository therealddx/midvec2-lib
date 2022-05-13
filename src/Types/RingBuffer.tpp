/**
 * reference LICENSE file provided.
 * 
 * @file RingBuffer.tpp
 * Implements RingBuffer.hpp
 *
 */

#ifndef RINGBUFFER_TPP
#define RINGBUFFER_TPP

#define D_RINGBUFFER_WLOG if (_w_log != nullptr) (*_w_log) << log_timestamp()
#define D_RINGBUFFER_RLOG if (_r_log != nullptr) (*_r_log) << log_timestamp()

template <class T>
RingBuffer<T>::RingBuffer
( int32_t arg_size
, int32_t arg_restore_occupancy
, bool arg_should_log
)
: _size(arg_size)
, _restore_occupancy(arg_restore_occupancy)
, _s_empty(std::binary_semaphore(0))
, _s_full(std::binary_semaphore(0))
{
  // arg check.
  // 
  if (arg_size < 0)
    { throw std::invalid_argument("arg_size"); }

  if (arg_restore_occupancy < 0 || arg_restore_occupancy >= arg_size)
    { throw std::invalid_argument("arg_restore_occupancy"); }

  // basic buffer variables.
  //   design note: this implementation allocates 'size + 1' total slots.
  //   this way, the implementation can delineate between empty-conditions
  //     ('r' pointer == 'w' pointer)
  //   and full-conditions.
  //     ('w' pointer will touch 'r' pointer, if it increments)
  // 
  _buf = new T[_size + 1];
  _buf_last = _buf + _size;
  _r = _buf;
  _w = _buf;

  for (int32_t n = 0; n <= _size; n++) { _buf[n] = 0; }

  // concurrency setup.
  // 
  _help_empty = false;
  _help_full = false;
  _closed = false;

  _r_cancel = false;
  _w_cancel = false;

  // logging variables.
  // 
  _r_log = arg_should_log ? 
    new std::ofstream("./RingBuffer-Read.log", std::ios_base::trunc) : nullptr;
  _w_log = arg_should_log ?
    new std::ofstream("./RingBuffer-Write.log", std::ios_base::trunc) : nullptr;
}

template <class T>
RingBuffer<T>::~RingBuffer()
{
  // flag + release.
  Close();

  // delete buffer.
  delete[] _buf;

  // logs (safe if 'nullptr').
  delete _r_log;
  delete _w_log;
}

template <class T>
T RingBuffer<T>::Read(int32_t* rtn_error, int32_t arg_patience_ms)
{
  if (_closed) { assign_error(rtn_error, -1); T rtn; return rtn; }

  // Block if empty.
  if (is_empty())
  {
D_RINGBUFFER_RLOG << "RingBuffer<T>::Read: entering empty-wait..." << std::endl;

    _help_empty = true;
    _s_empty.acquire();
    if (_closed) { assign_error(rtn_error, -1); T rtn; return rtn; }
    if (_r_cancel) { assign_error(rtn_error, -1); T rtn; return rtn; _r_cancel = false; }

D_RINGBUFFER_RLOG << "RingBuffer<T>::Read: exiting empty-wait" << std::endl;
  }

  // Do read.
  T rtn = *_r;
  inc_r();

D_RINGBUFFER_RLOG
  << "RingBuffer<T>::Read: read '" << rtn << "', occupancy now '"
  << get_occupancy(_r.load(), _w.load()) << "'"
  << std::endl;

  // Help writer.
  if ( _help_full.load()
    && get_occupancy(_r.load(), _w.load()) < (GetSize() - _restore_occupancy))
  {
    _help_full = false;
    _s_full.release();

D_RINGBUFFER_RLOG << "RingBuffer<T>::Read: helped writer" << std::endl;
  }

  // ret.
  assign_error(rtn_error, 0);
  return rtn;
}

template <class T>
void RingBuffer<T>::Write(T arg_w, int32_t* rtn_error, int32_t arg_patience_ms)
{
  if (_closed) { assign_error(rtn_error, -1); return; }

  // Block if full.
  if (is_full())
  {
D_RINGBUFFER_WLOG << "RingBuffer<T>::Write: entering full-wait..." << std::endl;

    _help_full = true;
    _s_full.acquire();
    if (_closed) { assign_error(rtn_error, -1); return; }
    if (_w_cancel) { assign_error(rtn_error, -1); return; _w_cancel = false; }

D_RINGBUFFER_WLOG << "RingBuffer<T>::Write: exiting full-wait" << std::endl;
  }

  // Do write.
  *_w = arg_w;
  inc_w();

D_RINGBUFFER_WLOG
  << "RingBuffer<T>::Write: wrote '" << arg_w << "', occupancy now '"
  << get_occupancy(_r.load(), _w.load()) << "'"
  << std::endl;

  // Help reader.
  if ( _help_empty.load()
    && get_occupancy(_r.load(), _w.load()) > _restore_occupancy )
  {
    _help_empty = false;
    _s_empty.release();

D_RINGBUFFER_WLOG << "RingBuffer<T>::Write: helped reader" << std::endl;
  }

  // ret.
  assign_error(rtn_error, 0);
}

#endif // RINGBUFFER_TPP

