#ifndef BENCH_HPP
#define BENCH_HPP

#include "stdinclude.hpp"

class inFilePs;
class InputPipeFile;

// 
// Number of CLI args in each bench tester, including the initial flag (e.g. '-ipf').
// 
static const uint32_t NUM_IPF_CLI_ARGS = 3;
static const uint32_t NUM_IPU_CLI_ARGS = 6;
static const uint32_t NUM_IPR_CLI_ARGS = 4;

typedef struct InputPipeFileArgs_o
{
  char t_back_storage;
  uint32_t t_back_size;
  uint32_t num_msg;
} InputPipeFileArgs;

typedef struct InputPipeUdpArgs_o
{
  char t_back_storage;
  uint32_t t_back_size;
  uint32_t num_msg;
  std::string ipv4;
  uint16_t port;
  uint32_t msg_sleep;
} InputPipeUdpArgs;

typedef struct InputPipeRamArgs_o
{
  char t_back_storage;
  uint32_t t_back_size;
  uint32_t num_msg;
  uint32_t rb_size;
} InputPipeRamArgs;

// printUsage
//   Print usage for this CLI application.
// 
void printUsage();

// printErrorBadArgv
//   Exhibit zero patience for bad CLI inputs.
// 
void printErrorBadArgv();

// marshalInputPipeFileArgs
//   CLI char*'s => testable InputPipeFile.
// 
ErrorCode marshalInputPipeFileArgs(const char** argv_ipf, InputPipeFileArgs& rtn_ipf_args);

// switch_makeTestFile
//   Given meaningful arguments for testing an InputPipeFile,
//   route those arguments into the proper templated
//   call to `TestInputPipeFile.tpp::makeTestFile`.
// 
//   If generation of the test file succeeds, make a new 'inFilePs',
//   so that the client has a ticket to build the InputPipeFile later.
// 
ErrorCode switch_makeTestFile(std::vector<inFilePs*>& arg_v_inFilePs, InputPipeFileArgs arg_ipf_args);

// switch_TestInputPipeFile
//   Given arguments for testing an InputPipeFile ('arg_ipf_args'),
//   route those arguments to the correct templated call to 
//   `TestInputPipeFile.tpp::TestInputPipeFile`.
// 
ErrorCode switch_TestInputPipeFile(InputPipeFile* arg_ipf, InputPipeFileArgs arg_ipf_args);

//
// marshalInputPipeUdpArgs
//   CLI char*'s => testable InputPipeUdp.
// 
ErrorCode marshalInputPipeUdpArgs(const char** argv_ipu, InputPipeUdpArgs& rtn_ipu_args);

// 
// switch_sendTestData
//   Given arguments for testing an InputPipeUdp ('arg_ipu'),
//   route those arguments to the correct templated call to
//   `TestInputPipeUdp.tpp::sendTestData`.
// 
ErrorCode switch_sendTestData(InputPipeUdpArgs arg_ipu);

// 
// switch_TestInputPipeUdp
//   Given arguments for testing an InputPipeUdp ('arg_ipu_args'),
//   route those arguments to the correct templated call to 
//   `TestInputPipeUdp.tpp::TestInputPipeUdp`.
// 
ErrorCode switch_TestInputPipeUdp(InputPipeUdp* arg_ipu, InputPipeUdpArgs arg_ipu_args);

// 
// marshalInputPipeRamArgs
//   CLI char*'s => testable InputPipeRam.
// 
ErrorCode marshalInputPipeRamArgs(const char** argv_ipr, InputPipeRamArgs& rtn_ipr_args);

// 
// switch_writeRingBuffer
//   Given arguments for testing an InputPipeRam ('arg_ipr'),
//   route those arguments to the correct templated call to
//   `TestInputPipeRam.tpp::writeRingBuffer`.
// 
ErrorCode switch_writeRingBuffer(RingBuffer<char>* arg_ring_buffer, InputPipeRamArgs arg_ipr);

// 
// switch_TestInputPipeRam
//   Given arguments for testing an InputPipeRam ('arg_ipr_args'),
//   route those arguments to the correct templated call to 
//   `TestInputPipeRam.tpp::TestInputPipeRam`.
// 
ErrorCode switch_TestInputPipeRam(InputPipeRam* arg_ipr, InputPipeRamArgs arg_ipr_args);

#endif // BENCH_HPP

