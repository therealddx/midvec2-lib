#include "stdinclude.hpp"
#include "TestInputPipeFile.hpp"
#include "bench.hpp"
#include "BenchLog.hpp"

extern uint32_t  gl_sequential_test_id;
extern BenchLog* gl_bench_log;

ErrorCode marshalInputPipeFileArgs(const char** argv_ipf, InputPipeFileArgs& rtn_ipf_args)
{
  try
  {
    // Marshal the 'backing storage' and 'backing size'.
    std::string sel_ipf_t_back(argv_ipf[1]);
    rtn_ipf_args.t_back_storage = sel_ipf_t_back[0];
    rtn_ipf_args.t_back_size = static_cast<uint32_t>(
      std::stoul(sel_ipf_t_back.substr(1, sel_ipf_t_back.size())));

    // Marshal the 'num messages'.
    rtn_ipf_args.num_msg = static_cast<uint32_t>(std::stoul(argv_ipf[2]));

    // ret.
    return ErrorCode::Ok;
  }
  catch (std::exception) // std::invalid_argument | std::out_of_range
    { return ErrorCode::BadArgument; }
}

ErrorCode switch_makeTestFile(std::vector<inFilePs*>& arg_v_inFilePs, InputPipeFileArgs arg_ipf_args)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;

  // Make the test file's name.
  std::stringstream test_file_path;
  test_file_path << "TestInputPipeFile-"
    << std::dec << std::setfill('0') << std::setw(4) << gl_sequential_test_id
    << ".dat";

  // Convert: CLI args => `makeTestFile<T>` call.
  if (arg_ipf_args.t_back_storage == 'f')
  {
    if (arg_ipf_args.t_back_size == 32)
      { rtn_error = makeTestFile<float>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 64)
      { rtn_error = makeTestFile<double>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 128)
      { rtn_error = makeTestFile<long double>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipf_args.t_back_storage == 'i')
  {
    if (arg_ipf_args.t_back_size == 8)
      { rtn_error = makeTestFile<int8_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 16)
      { rtn_error = makeTestFile<int16_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 32)
      { rtn_error = makeTestFile<int32_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 64)
      { rtn_error = makeTestFile<int64_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipf_args.t_back_storage == 'u')
  {
    if (arg_ipf_args.t_back_size == 8)
      { rtn_error = makeTestFile<uint8_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 16)
      { rtn_error = makeTestFile<uint16_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 32)
      { rtn_error = makeTestFile<uint32_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else if (arg_ipf_args.t_back_size == 64)
      { rtn_error = makeTestFile<uint64_t>(test_file_path.str(), arg_ipf_args.num_msg, true); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipf_args.t_back_storage == 'c')
  {
    if (arg_ipf_args.t_back_size == 64)
    {
      rtn_error =
        makeTestFile<Complex<float>>(test_file_path.str(), arg_ipf_args.num_msg, true);
    }
    else if (arg_ipf_args.t_back_size == 128)
    {
      rtn_error =
        makeTestFile<Complex<double>>(test_file_path.str(), arg_ipf_args.num_msg, true);
    }
    else if (arg_ipf_args.t_back_size == 256)
    {
      rtn_error =
        makeTestFile<Complex<long double>>(test_file_path.str(), arg_ipf_args.num_msg, true);
    }
    else
      { return ErrorCode::BadArgument; }
   }
  else
    { return ErrorCode::BadArgument; }

  // Report.
  if (rtn_error == ErrorCode::Ok)
  {
    // Store the association.
    arg_v_inFilePs.push_back(new inFilePs(std::string(test_file_path.str())));

    {
      std::stringstream ss_msg;
      ss_msg << "bench: created test file \"" << test_file_path.str() << "\"" << std::endl;
      gl_bench_log->log(ss_msg.str());
    }
    return rtn_error;
  }
  else
  {
    {
      std::stringstream ss_msg;
      ss_msg << "bench: failed to create \"" << test_file_path.str() << "\"" << std::endl;
      gl_bench_log->log(ss_msg.str());
    }
    return rtn_error;
  }
}

ErrorCode switch_TestInputPipeFile(InputPipeFile* arg_ipf, InputPipeFileArgs arg_ipf_args)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;

  // Convert: CLI args => `TestInputPipeFile<T>` call.
  if (arg_ipf_args.t_back_storage == 'f')
  {
    if (arg_ipf_args.t_back_size == 32)
      { TestInputPipeFile<float>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 64)
      { TestInputPipeFile<double>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 128)
      { TestInputPipeFile<long double>(arg_ipf); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipf_args.t_back_storage == 'i')
  {
    if (arg_ipf_args.t_back_size == 8)
      { TestInputPipeFile<int8_t>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 16)
      { TestInputPipeFile<int16_t>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 32)
      { TestInputPipeFile<int32_t>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 64)
      { TestInputPipeFile<int64_t>(arg_ipf); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipf_args.t_back_storage == 'u')
  {
    if (arg_ipf_args.t_back_size == 8)
      { TestInputPipeFile<uint8_t>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 16)
      { TestInputPipeFile<uint16_t>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 32)
      { TestInputPipeFile<uint32_t>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 64)
      { TestInputPipeFile<uint64_t>(arg_ipf); }
    else
      { return ErrorCode::BadArgument; }
  }
  else if (arg_ipf_args.t_back_storage == 'c')
  {
    if (arg_ipf_args.t_back_size == 64)
      { TestInputPipeFile<Complex<float>>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 128)
      { TestInputPipeFile<Complex<double>>(arg_ipf); }
    else if (arg_ipf_args.t_back_size == 256)
      { TestInputPipeFile<Complex<long double>>(arg_ipf); }
    else
      { return ErrorCode::BadArgument; }
   }
   else
    { return ErrorCode::BadArgument; }

  // ret.
  return rtn_error;
}

