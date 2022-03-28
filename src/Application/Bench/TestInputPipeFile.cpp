#include "stdinclude.hpp"
#include "TestInputPipeFile.hpp"

ErrorCode deleteFile(std::string arg_file_path)
{
  int32_t error = std::remove(arg_file_path.c_str());
  return error == 0 ? ErrorCode::Ok : ErrorCode::Shrug;
}

