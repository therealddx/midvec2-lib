/*
 * reference LICENSE file provided.
 *
 * outPs.hpp.
 * Class declarations for ParamSets ('Ps') that define building of a 
 * representative subtype of OutputPipeBase.
 *
 */

#ifndef OUTPS_HPP
#define OUTPS_HPP

class OutputPipeBase;

#include <stdint.h>
#include <string>
#include <Types/RingBuffer.hpp>

class outPs
{
public:
  virtual ~outPs() { } ;
  virtual OutputPipeBase* Make() = 0;
protected:
  outPs() { } ;
};

class outFilePs : public outPs
{
public:
  outFilePs(std::string arg_fqFile) : _fqFile(arg_fqFile) { } ;
  OutputPipeBase* Make();
private:
  std::string _fqFile;
};

class outUdpPs : public outPs
{
public:
  outUdpPs(std::string arg_ipAddress, uint16_t arg_port)
  : _ipAddress(arg_ipAddress)
  , _port(arg_port)
  {
  }
  OutputPipeBase* Make();
private:
  std::string _ipAddress;
  uint16_t _port;
};

class outRamPs : public outPs
{
public:
  outRamPs(RingBuffer<char>* arg_rb, std::atomic<bool>* arg_ct = nullptr) : _rb(arg_rb) , _ct(arg_ct) { } ;
  OutputPipeBase* Make();
private:
  RingBuffer<char>* _rb;
  std::atomic<bool>* _ct;
};

#endif // OUTPS_HPP

