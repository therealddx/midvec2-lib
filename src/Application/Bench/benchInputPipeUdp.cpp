#include "stdinclude.hpp"
#include "TestInputPipeUdp.hpp"
#include "bench.hpp"

ErrorCode marshalInputPipeUdpArgs(const char** argv_ipu, InputPipeUdpArgs& rtn_ipu_args)
{
  try
  {
    // Marshal the 'backing storage' and 'backing size'.
    std::string sel_t_back(argv_ipu[1]);

    rtn_ipu_args.t_back_storage = sel_t_back[0];
    rtn_ipu_args.t_back_size = static_cast<uint32_t>(
      std::stoul(sel_t_back.substr(1, sel_t_back.size())));

    // Marshal the 'num messages'.
    rtn_ipu_args.num_msg = static_cast<uint32_t>(std::stoul(std::string(argv_ipu[2])));

    // Marshal the IP address.
    rtn_ipu_args.ipv4 = std::string(argv_ipu[3]);

    // Marshal the IP port.
    rtn_ipu_args.port = static_cast<uint16_t>(std::stoul(argv_ipu[4]));

    // Marshal the message sleep.
    rtn_ipu_args.msg_sleep = static_cast<uint32_t>(std::stoul(argv_ipu[5]));

    // ret.
    return ErrorCode::Ok;
  }
  catch (std::exception) // std::stoul exception
    { return ErrorCode::BadArgument; }
}

ErrorCode switch_sendTestData(InputPipeUdpArgs arg_ipu)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;

  // Convert: CLI args => `sendTestData<T>` call.
  if (arg_ipu.t_back_storage == 'f')
  {
    if (arg_ipu.t_back_size == 32)
      { rtn_error = sendTestData<float>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 64)
      { rtn_error = sendTestData<double>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 128)
      { rtn_error = sendTestData<long double>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipu.t_back_storage == 'i')
  {
    if (arg_ipu.t_back_size == 8)
      { rtn_error = sendTestData<int8_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 16)
      { rtn_error = sendTestData<int16_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 32)
      { rtn_error = sendTestData<int32_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 64)
      { rtn_error = sendTestData<int64_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipu.t_back_storage == 'u')
  {
    if (arg_ipu.t_back_size == 8)
      { rtn_error = sendTestData<uint8_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 16)
      { rtn_error = sendTestData<uint16_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 32)
      { rtn_error = sendTestData<uint32_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else if (arg_ipu.t_back_size == 64)
      { rtn_error = sendTestData<uint64_t>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipu.t_back_storage == 'c')
  {
    if (arg_ipu.t_back_size == 64)
    {
      rtn_error =
        sendTestData<Complex<float>>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep);
    }
    else if (arg_ipu.t_back_size == 128)
    {
      rtn_error =
        sendTestData<Complex<double>>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep);
    }
    else if (arg_ipu.t_back_size == 256)
    {
      rtn_error =
        sendTestData<Complex<long double>>(arg_ipu.num_msg, arg_ipu.ipv4, arg_ipu.port, arg_ipu.msg_sleep);
    }
    else
      { return ErrorCode::BadArgument; }
  }
  else
    { return ErrorCode::BadArgument; }

  // ret.
  return rtn_error;
}

ErrorCode switch_TestInputPipeUdp(InputPipeUdp* arg_ipu, InputPipeUdpArgs arg_ipu_args)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;

  // Convert: CLI args => `TestInputPipeUdp<T>` call.
  if (arg_ipu_args.t_back_storage == 'f')
  {
    if (arg_ipu_args.t_back_size == 32)
      { TestInputPipeUdp<float>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 64)
      { TestInputPipeUdp<double>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 128)
      { TestInputPipeUdp<long double>(arg_ipu); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipu_args.t_back_storage == 'i')
  {
    if (arg_ipu_args.t_back_size == 8)
      { TestInputPipeUdp<int8_t>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 16)
      { TestInputPipeUdp<int16_t>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 32)
      { TestInputPipeUdp<int32_t>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 64)
      { TestInputPipeUdp<int64_t>(arg_ipu); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipu_args.t_back_storage == 'u')
  {
    if (arg_ipu_args.t_back_size == 8)
      { TestInputPipeUdp<uint8_t>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 16)
      { TestInputPipeUdp<uint16_t>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 32)
      { TestInputPipeUdp<uint32_t>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 64)
      { TestInputPipeUdp<uint64_t>(arg_ipu); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipu_args.t_back_storage == 'c')
  {
    if (arg_ipu_args.t_back_size == 64)
      { TestInputPipeUdp<Complex<float>>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 128)
      { TestInputPipeUdp<Complex<double>>(arg_ipu); }
    else if (arg_ipu_args.t_back_size == 256)
      { TestInputPipeUdp<Complex<long double>>(arg_ipu); }
    else
      { return ErrorCode::BadArgument; }
   }
   else
    { return ErrorCode::BadArgument; }

  // ret.
  return rtn_error;
}

