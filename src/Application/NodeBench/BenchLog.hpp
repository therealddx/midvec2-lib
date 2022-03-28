#ifndef BENCHLOG_HPP
#define BENCHLOG_HPP

#include <string>
#include <ostream>
#include <mutex>

class BenchLog
{
public:
  BenchLog(std::ostream&);

  virtual ~BenchLog();

  void log(const std::string&);

private:
  std::ostream& _ostream;
  std::mutex _lock;

};

#endif // BENCHLOG_HPP

