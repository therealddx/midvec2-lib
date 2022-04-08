/*
 * reference LICENSE file provided.
 *
 * inPs.hpp.
 * Class declarations for ParamSets ('Ps') that define building of a 
 * representative subtype of InputPipeBase.
 *
 */

#ifndef INPS_HPP
#define INPS_HPP

class InputPipeBase;

#include <stdint.h>
#include <string>
#include <Types/RingBuffer.hpp>

class inPs
{
public:
  virtual ~inPs() { } ;
  virtual InputPipeBase* Make() = 0;
protected:
  inPs() { } ;
};

class inFilePs : public inPs
{
public:
  inFilePs(std::string arg_fqFile) : _fqFile(arg_fqFile) { } ;
  InputPipeBase* Make();
private:
  std::string _fqFile;
};

class inUdpPs : public inPs
{
public:
  inUdpPs(std::string arg_ipv4_bind, uint16_t arg_port)
    : _ipv4_bind(arg_ipv4_bind)
    , _port(arg_port)
    {
    };
  InputPipeBase* Make();
private:
  std::string _ipv4_bind;
  uint16_t _port;
};

class inRamPs : public inPs
{
public:
  inRamPs(RingBuffer<char>* arg_rb) : _rb(arg_rb) { } ;
  InputPipeBase* Make();
private:
  RingBuffer<char>* _rb;
};

#endif // INPS_HPP

