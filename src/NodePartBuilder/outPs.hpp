/**
 * reference LICENSE file provided.
 *
 * @file outPs.hpp
 * Represents the set of parameters-- 'parameter set', or 'ps'--
 *   that construct subclasses of OutputPipeBase.
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
 * Base class for parameter sets of OutputPipeBase.
 */
class outPs
{
public:

  /**
   * ~outPs
   */
  virtual ~outPs() { } ;

  /**
   * Make
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
   * outFilePs
   * Stores OutputPipeFile constructor arguments, for construction by Make.
   * @param[in] arg_fqFile Fully-qualified path to writeable disk file.
   */
  outFilePs(std::string arg_fqFile) : _fqFile(arg_fqFile) { } ;

  /**
   * Make
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
   * outUdpPs
   * Stores OutputPipeUdp constructor arguments, for construction by Make.
   * @param[in] arg_ipv4_bind IPv4 address to send to, as a dotted-quad string.
   * @param[in] arg_port IPv4 port to send to, in host byte order.
   */
  outUdpPs(std::string arg_ipAddress, uint16_t arg_port)
  : _ipAddress(arg_ipAddress)
  , _port(arg_port)
  {
  }

  /**
   * Make
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
   * outRamPs
   * Stores OutputPipeRam constructor arguments, for construction by Make.
   * @param[in] arg_rb Pointer to RingBuffer for writing bytes to.
   */
  outRamPs(RingBuffer<char>* arg_rb) : _rb(arg_rb) { } ;

  /**
   * Make
   * Satisfies base class.
   */
  OutputPipeBase* Make();

private:
  RingBuffer<char>* _rb;
};

#endif // OUTPS_HPP

