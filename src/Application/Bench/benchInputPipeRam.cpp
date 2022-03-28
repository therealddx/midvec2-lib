#include "stdinclude.hpp"
#include "TestInputPipeRam.hpp"
#include "bench.hpp"

extern uint32_t gl_sequential_test_id;

ErrorCode marshalInputPipeRamArgs(const char** argv_ipr, InputPipeRamArgs& rtn_ipr_args)
{
  try
  {
    // Marshal the 'backing storage' and 'backing size'.
    std::string sel_ipr_t_back(argv_ipr[1]);
    rtn_ipr_args.t_back_storage = sel_ipr_t_back[0];
    rtn_ipr_args.t_back_size = static_cast<uint32_t>(
      std::stoul(sel_ipr_t_back.substr(1, sel_ipr_t_back.size())));

    // Marshal the 'num messages'.
    rtn_ipr_args.num_msg = static_cast<uint32_t>(std::stoul(argv_ipr[2]));

    // Marshal the 'rb size'.
    rtn_ipr_args.rb_size = static_cast<uint32_t>(std::stoul(argv_ipr[3]));

    // ret.
    return ErrorCode::Ok;
  }
  catch (std::exception) // std::invalid_argument | std::out_of_range
    { return ErrorCode::BadArgument; }
}

ErrorCode switch_writeRingBuffer(RingBuffer<char>* arg_ring_buffer, InputPipeRamArgs arg_ipr)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;

  // Convert: CLI args => `writeRingBuffer<T>` call.
  if (arg_ipr.t_back_storage == 'f')
  {
    if (arg_ipr.t_back_size == 32)
      { rtn_error = writeRingBuffer<float>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 64)
      { rtn_error = writeRingBuffer<double>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 128)
      { rtn_error = writeRingBuffer<long double>(arg_ring_buffer, arg_ipr.num_msg); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipr.t_back_storage == 'i')
  {
    if (arg_ipr.t_back_size == 8)
      { rtn_error = writeRingBuffer<int8_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 16)
      { rtn_error = writeRingBuffer<int16_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 32)
      { rtn_error = writeRingBuffer<int32_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 64)
      { rtn_error = writeRingBuffer<int64_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipr.t_back_storage == 'u')
  {
    if (arg_ipr.t_back_size == 8)
      { rtn_error = writeRingBuffer<uint8_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 16)
      { rtn_error = writeRingBuffer<uint16_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 32)
      { rtn_error = writeRingBuffer<uint32_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else if (arg_ipr.t_back_size == 64)
      { rtn_error = writeRingBuffer<uint64_t>(arg_ring_buffer, arg_ipr.num_msg); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipr.t_back_storage == 'c')
  {
    if (arg_ipr.t_back_size == 64)
    {
      rtn_error =
        writeRingBuffer<Complex<float>>(arg_ring_buffer, arg_ipr.num_msg);
    }
    else if (arg_ipr.t_back_size == 128)
    {
      rtn_error =
        writeRingBuffer<Complex<double>>(arg_ring_buffer, arg_ipr.num_msg);
    }
    else if (arg_ipr.t_back_size == 256)
    {
      rtn_error =
        writeRingBuffer<Complex<long double>>(arg_ring_buffer, arg_ipr.num_msg);
    }
    else
      { return ErrorCode::BadArgument; }
   }
  else
    { return ErrorCode::BadArgument; }

  // Report.
  return rtn_error;
}

ErrorCode switch_TestInputPipeRam(InputPipeRam* arg_ipr, InputPipeRamArgs arg_ipr_args)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;

  // Convert: CLI args => `TestInputPipeRam<T>` call.
  if (arg_ipr_args.t_back_storage == 'f')
  {
    if (arg_ipr_args.t_back_size == 32)
      { TestInputPipeRam<float>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 64)
      { TestInputPipeRam<double>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 128)
      { TestInputPipeRam<long double>(arg_ipr); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipr_args.t_back_storage == 'i')
  {
    if (arg_ipr_args.t_back_size == 8)
      { TestInputPipeRam<int8_t>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 16)
      { TestInputPipeRam<int16_t>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 32)
      { TestInputPipeRam<int32_t>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 64)
      { TestInputPipeRam<int64_t>(arg_ipr); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipr_args.t_back_storage == 'u')
  {
    if (arg_ipr_args.t_back_size == 8)
      { TestInputPipeRam<uint8_t>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 16)
      { TestInputPipeRam<uint16_t>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 32)
      { TestInputPipeRam<uint32_t>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 64)
      { TestInputPipeRam<uint64_t>(arg_ipr); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipr_args.t_back_storage == 'c')
  {
    if (arg_ipr_args.t_back_size == 64)
      { TestInputPipeRam<Complex<float>>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 128)
      { TestInputPipeRam<Complex<double>>(arg_ipr); }
    else if (arg_ipr_args.t_back_size == 256)
      { TestInputPipeRam<Complex<long double>>(arg_ipr); }
    else
      { return ErrorCode::BadArgument; }
   }
   else
    { return ErrorCode::BadArgument; }

  // ret.
  return rtn_error;
}

