/**
 * reference LICENSE file provided.
 *
 * @file outPs.hpp
 * Declarations for outPs
 *
 */

#ifndef OUTPS_HPP
#define OUTPS_HPP

class OutputPipeBase;

#include <stdint.h>
#include <string>
#include <Types/RingBuffer.hpp>

/**
 * @class outPs
 * Represents the set of parameters-- 'parameter set', or 'ps'--
 *   that construct subclasses of OutputPipeBase.
 */
class outPs
{
public:

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~outPs() { } ;

  /**
   * Subclasses are guaranteed to construct a subclass of OutputPipeBase.
   * @return Instance of OutputPipeBase.
   */
  virtual OutputPipeBase* Make() = 0;

protected:
  outPs() { } ;
};

/**
 * @class outFilePs
 * Class representing the parameters for constructing a OutputPipeFile.
 */
class outFilePs : public outPs
{
public:

  /**
   * Stores OutputPipeFile constructor arguments, for construction by `Make`.
   * @param[in] arg_fqFile Fully-qualified path to writeable disk file.
   */
  outFilePs(std::string arg_fqFile) : _fqFile(arg_fqFile) { } ;

  /**
   * Satisfies base class.
   */
  OutputPipeBase* Make();

private:
  std::string _fqFile;
};

/**
 * @class outUdpPs
 * Class representing the parameters for constructing a OutputPipeUdp.
 */
class outUdpPs : public outPs
{
public:

  /**
   * Stores OutputPipeUdp constructor arguments, for construction by `Make`.
   * @param[in] arg_ipv4_bind IPv4 address to send to, as a dotted-quad string.
   * @param[in] arg_port IPv4 port to send to, in host byte order.
   */
  outUdpPs(std::string arg_ipAddress, uint16_t arg_port)
  : _ipAddress(arg_ipAddress)
  , _port(arg_port)
  {
  }

  /**
   * Satisfies base class.
   */
  OutputPipeBase* Make();

private:
  std::string _ipAddress;
  uint16_t _port;
};

/**
 * @class outRamPs
 * Class representing the parameters for constructing a OutputPipeRam.
 */
class outRamPs : public outPs
{
public:

  /**
   * Stores OutputPipeRam constructor arguments, for construction by `Make`.
   * @param[in] arg_rb Pointer to RingBuffer for writing bytes to.
   */
  outRamPs(RingBuffer<char>* arg_rb) : _rb(arg_rb) { } ;

  /**
   * Satisfies base class.
   */
  OutputPipeBase* Make();

private:
  RingBuffer<char>* _rb;
};

#endif // OUTPS_HPP

