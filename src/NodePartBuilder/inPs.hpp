/**
 * reference LICENSE file provided.
 *
 * @file inPs.hpp
 * Represents the set of parameters-- 'parameter set', or 'ps'--
 *   that construct subclasses of InputPipeBase.
 *
 */

#ifndef INPS_HPP
#define INPS_HPP

class InputPipeBase;

#include <stdint.h>
#include <string>
#include <Types/RingBuffer.hpp>

/**
 * @class inPs
 * Base class for parameter sets of InputPipeBase.
 */
class inPs
{
public:

  /**
   * ~inPs
   */
  virtual ~inPs() { } ;

  /**
   * Make
   * Subclasses are guaranteed to construct a subclass of InputPipeBase.
   * @return Instance of InputPipeBase.
   */
  virtual InputPipeBase* Make() = 0;

protected:
  inPs() { } ;
};

/**
 * @class inFilePs
 * Class representing the parameters for constructing a InputPipeFile.
 */
class inFilePs : public inPs
{
public:

  /**
   * inFilePs
   * Stores InputPipeFile constructor arguments, for construction by Make.
   * @param[in] arg_fqFile Fully-qualified path to readable disk file.
   */
  inFilePs(std::string arg_fqFile) : _fqFile(arg_fqFile) { } ;

  /**
   * Make
   * Satisfies base class.
   */
  InputPipeBase* Make();

private:
  std::string _fqFile;
};

/**
 * @class inUdpPs
 * Class representing the parameters for constructing a InputPipeUdp.
 */
class inUdpPs : public inPs
{
public:

  /**
   * inUdpPs
   * Stores InputPipeUdp constructor arguments, for construction by Make.
   * @param[in] arg_ipv4_bind IPv4 address to bind to, as a dotted-quad string.
   * @param[in] arg_port IPv4 port to bind to, in host byte order.
   */
  inUdpPs(std::string arg_ipv4_bind, uint16_t arg_port)
    : _ipv4_bind(arg_ipv4_bind)
    , _port(arg_port)
    {
    };

  /**
   * Make
   * Satisfies base class.
   */
  InputPipeBase* Make();

private:
  std::string _ipv4_bind;
  uint16_t _port;
};

/**
 * @class inRamPs
 * Class representing the parameters for constructing a InputPipeRam.
 */
class inRamPs : public inPs
{
public:

  /**
   * inRamPs
   * Stores InputPipeRam constructor arguments, for construction by Make.
   * @param[in] arg_rb Pointer to RingBuffer from which to read bytes.
   */
  inRamPs(RingBuffer<char>* arg_rb) : _rb(arg_rb) { } ;

  /**
   * Make
   * Satisfies base class.
   */
  InputPipeBase* Make();

private:
  RingBuffer<char>* _rb;
};

#endif // INPS_HPP

