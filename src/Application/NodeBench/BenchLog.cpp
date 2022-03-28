#include "BenchLog.hpp"

BenchLog::BenchLog(std::ostream& arg_os)
: _ostream(arg_os)
{
}

BenchLog::~BenchLog()
{
  // no need-- reference-only
}

void BenchLog::log(const std::string& arg_s)
{
  _lock.lock();
  
  _ostream << arg_s;
  _ostream.flush();
  
  _lock.unlock();
}

