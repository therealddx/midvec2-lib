#include "stdinclude.hpp"
#include "bench.hpp"

class BenchLog;

int32_t            gl_error_main = 0;
uint32_t           gl_sequential_test_id = 0;
std::atomic<bool>* gl_rb_master_cancellation_token = nullptr;
BenchLog*          gl_bench_log = nullptr;

void printUsage()
{
  std::cout
    << "usage:"                                                                       << std::endl
    << "  bench [OPTION], where [OPTION] is one of:"                                  << std::endl
    << "    <[ --input-pipe-file | -ipf ]> <t_back> <num_msg>"                        << std::endl
    << "      t_back: backing type, any of:"                                          << std::endl
    << "        f[32|64|128] ('f' => 'float')"                                        << std::endl
    << "        [i|u][8|16|32|64] ('i' => 'signed int', 'u' => 'unsigned int')"       << std::endl
    << "        c[64|128|256] ('c' => 'complex')"                                     << std::endl
    << "      num_msg: #messages to inject into the test file"                        << std::endl
    << "    <[ --input-pipe-udp | -ipu ]> <t_back> <num_msg> <ip> <port> <msg_sleep>" << std::endl
    << "      t_back: backing type, any of:"                                          << std::endl
    << "        f[32|64|128] ('f' => 'float')"                                        << std::endl
    << "        [i|u][8|16|32|64] ('i' => 'signed int', 'u' => 'unsigned int')"       << std::endl
    << "        c[64|128|256] ('c' => 'complex')"                                     << std::endl
    << "      num_msg: #messages to send from test sender"                            << std::endl
    << "      ip: IP address to bind to"                                              << std::endl
    << "      port: port to bind to"                                                  << std::endl
    << "      msg_sleep: useconds for test sender to wait between each message"       << std::endl
    << "    <[ --input-pipe-ram | -ipr ]> <t_back> <num_msg> <rb_size>"               << std::endl
    << "      t_back: backing type, any of:"                                          << std::endl
    << "        f[32|64|128] ('f' => 'float')"                                        << std::endl
    << "        [i|u][8|16|32|64] ('i' => 'signed int', 'u' => 'unsigned int')"       << std::endl
    << "        c[64|128|256] ('c' => 'complex')"                                     << std::endl
    << "      num_msg: #messages to inject into the test ringbuffer"                  << std::endl
    << "      rb_size: #bytes that the test ringbuffer can hold"                      << std::endl
    << ""
    << std::endl;
}

void printErrorBadArgv()
{
  std::cout << "bench: bad CLI arg. read the usage (`bench`)"
    << std::endl;

  gl_error_main = -1;
}

