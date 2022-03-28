/*
 * reference LICENSE file provided.
 *
 * InputPipeUdp.hpp.
 * Defines an interface for reading bytes from a file into Message
 * instances, via a UDP socket.
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

class InputPipeUdp : public InputPipe
{

public:

  // 
  // Ctor.
  // Opens handle to UDP socket.
  //
  InputPipeUdp(std::string arg_ipv4_bind, uint16_t arg_port);

  // 
  // Dtor.
  // Closes handle to socket.
  //
  ~InputPipeUdp(); 

  // 
  // GetBindEndpoint.
  // Get the <IPv4 address>:<port> that we are currently bound to.
  // 
  std::string GetBindEndpoint() const;

  // 
  // GetBindAddress.
  // Get the IPv4 address that we are currently bound to.
  // 
  std::string GetBindAddress() const { return _ipv4; }

  // 
  // GetBindPort.
  // Get the port that we are currently bound to.
  // 
  uint16_t GetBindPort() const { return _port; }

private:

  // 
  // GetByte.
  // Controlled file read.
  //
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

