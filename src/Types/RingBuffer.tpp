#ifndef RINGBUFFER_TPP
#define RINGBUFFER_TPP

template <class T>
RingBuffer<T>::RingBuffer
( int32_t arg_sz
, bool arg_should_log
)
: _s_empty(std::binary_semaphore(0))
, _s_full(std::binary_semaphore(0))
{
  // basic buffer variables.
  // 
  _sz = arg_sz;
  _buf = new T[_sz + 1];
  _r = _buf;
  _w = _buf;
  _buf_last = _buf + _sz;

  for (int32_t n = 0; n <= _sz; n++) { _buf[n] = 0; }

  // concurrency setup.
  // 
  _help_empty = false;
  _help_full = false;

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
  // delete buffer.
  delete[] _buf;

  // logs (safe if 'nullptr').
  delete _r_log;
  delete _w_log;
}

template <class T>
T RingBuffer<T>::Read(int32_t* rtn_error, int32_t arg_patience_ms)
{
  // Block if empty.
  if (is_empty())
  {
if (_r_log != nullptr)
(*_r_log) << log_timestamp() << "RingBuffer<T>::Read: entering empty-wait..." << std::endl;

    _help_empty = true;
    _s_empty.acquire();

if (_r_log != nullptr)
(*_r_log) << log_timestamp() << "RingBuffer<T>::Read: exiting empty-wait" << std::endl;
  }

  // Do read.
  T rtn = *_r;
  inc_r();

if (_r_log != nullptr)
(*_r_log) << log_timestamp() << "RingBuffer<T>::Read: read '" << rtn << "', occupancy now '"
  << get_occupancy(_r.load(), _w.load()) << "'"
  << std::endl;

  // Help writer.
  if ( _help_full.load()
    && get_occupancy(_r.load(), _w.load()) < (GetSize() - (GetSize() / 4)) )
  {
    _help_full = false;
    _s_full.release();

if (_r_log != nullptr)
(*_r_log) << log_timestamp() << "RingBuffer<T>::Read: helped writer" << std::endl;
  }

  // ret.
  assign_error(rtn_error, 0);
  return rtn;
}

template <class T>
void RingBuffer<T>::Write(T arg_w, int32_t* rtn_error, int32_t arg_patience_ms)
{
  // Block if full.
  if (is_full())
  {
if (_w_log != nullptr)
(*_w_log) << log_timestamp() << "RingBuffer<T>::Write: entering full-wait..." << std::endl;

    _help_full = true;
    _s_full.acquire();

if (_w_log != nullptr)
(*_w_log) << log_timestamp() << "RingBuffer<T>::Write: exiting full-wait" << std::endl;
  }

  // Do write.
  *_w = arg_w;
  inc_w();

if (_w_log != nullptr)
(*_w_log) << log_timestamp() << "RingBuffer<T>::Write: wrote '" << arg_w << "', occupancy now '"
  << get_occupancy(_r.load(), _w.load()) << "'"
  << std::endl;

  // Help reader.
  if ( _help_empty.load()
    && get_occupancy(_r.load(), _w.load()) > (GetSize() / 4) )
  {
    _help_empty = false;
    _s_empty.release();

if (_w_log != nullptr)
(*_w_log) << log_timestamp() << "RingBuffer<T>::Write: helped reader" << std::endl;
  }

  // ret.
  assign_error(rtn_error, 0);
}

#endif // RINGBUFFER_TPP

