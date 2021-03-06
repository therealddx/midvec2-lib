/**
 * reference LICENSE file provided.
 *
 * @file InputPipeUdp.hpp
 * Declarations for InputPipeUdp
 *
 */

#ifndef INPUTPIPEUDP_HPP
#define INPUTPIPEUDP_HPP

// include: C/C++ standard library.
// 
#include <stdint.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// include: app.
//
#include <Exception/ErrorCode.hpp>
#include <Message/MessageConstants.hpp>
#include "InputPipe.hpp"

/**
 * @class InputPipeUdp
 * Reads bytes from a UDP socket into Message instances.
 */
class InputPipeUdp : public InputPipe
{

public:

  /**
   * Constructs an instance to read Message instances from a UDP socket,
   *   by binding to the given IPv4 address:port.
   *
   * @param[in] arg_ipv4_bind IPv4 address to bind to.
   * @param[in] arg_port Port to bind to.
   */
  InputPipeUdp(std::string arg_ipv4_bind, uint16_t arg_port);

  /**
   * Destroys this instance,
   *   and releases the IPv4 socket back to the operating system.
   */
  ~InputPipeUdp(); 

  /**
   * Report the bound IPv4 endpoint.
   * @return
   * A human-readable string denoting the address:port this instance is bound to.
   */
  std::string GetBindEndpoint() const;

  /**
   * Report the bound IPv4 address.
   * @return
   * The IPv4 address this instance is currently bound to, in dotted-quad.
   */
  std::string GetBindAddress() const
  {
    return _ipv4;
  }

  /**
   * Report the bound IPv4 port.
   * @return
   * The port this instance is currently bound to, in host byte order.
   */
  uint16_t GetBindPort() const
  {
    return _port;
  }

private:

  /**
   * Satisfies base class.
   */
  ErrorCode GetByte(char* rtn_byte);

  // members: socket.
  int32_t _socketFd;
  struct sockaddr_in _endpoint; // IPv4 info for listener (local).
  struct sockaddr _clientAddr;  // IPv4 info for sender (remote).
  socklen_t _clientAddrLen;     // ^

  // members: buffer.
  static const uint32_t MAX_RXBUFFER_SIZE = 60000;
  char _rxBuffer[MAX_RXBUFFER_SIZE];
  int32_t _rxBufIndex;
  int32_t _rxBufValid; 

  // members: convenience storage.
  std::string _ipv4;
  uint16_t _port;
}; 

#endif // INPUTPIPEUDP_HPP

