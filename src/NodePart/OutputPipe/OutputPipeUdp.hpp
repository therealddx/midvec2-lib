/* 
 * reference LICENSE file provided.
 *
 * OutputPipeUdp.hpp.
 * Defines interface for putting bytes out over a UDP socket.
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

class OutputPipeUdp : public OutputPipeBase
{
public:

  // 
  // ctor / dtor.
  //
  OutputPipeUdp(std::string arg_ipAddress, uint16_t arg_port);
  ~OutputPipeUdp();

  //  
  // Mandatory implementations: OutputPipeBase
  //  
  ErrorCode PutMessage(char* arg_msgBytes, int32_t arg_msgLen);

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

