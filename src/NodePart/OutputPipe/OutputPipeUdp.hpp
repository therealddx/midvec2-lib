/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeUdp.hpp
 * Declarations for OutputPipeUdp
 *
 */

#ifndef OUTPUTPIPEUDP_HPP
#define OUTPUTPIPEUDP_HPP

// 
// include: general.
//
#include <stdint.h>
#include <unistd.h>
#include <string>
#include <vector>

// 
// include: socket.
//
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

// 
// include: app-specific.
//
#include "OutputPipeBase.hpp"

/**
 * @class OutputPipeUdp
 * Concrete output pipe for sending serialized values via UDP socket.
 */
class OutputPipeUdp : public OutputPipeBase
{
public:

  /**
   * Constructs an instance to send Message instances to a remote UDP endpoint,
   *   at the given IPv4 address:port.
   *
   * @param[in] arg_ipAddress IPv4 address to send values to.
   * @param[in] arg_port IPv4 port to send values to.
   */
  OutputPipeUdp(std::string arg_ipAddress, uint16_t arg_port);

  /**
   * Destroys this instance,
   *   and releases the IPv4 socket back to the operating system.
   */
  ~OutputPipeUdp();

  /**
   * Satisfies base class.
   */
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

  /**
   * Satisfies base class.
   */
  void Close()
  {
    return;
  }

private:

  // members: endpoint.
  struct sockaddr_in _endpoint;
  int32_t _socketFd;

  // members: limits.
  static const int32_t MAX_UDP_BYTE_PAYLOAD = 60000;
};

#endif // OUTPUTPIPEUDP_HPP

