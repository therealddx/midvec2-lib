/**
 * reference LICENSE file provided.
 *
 * @file OutputPipeUdp.cpp
 * Implements OutputPipeUdp.hpp
 *
 */

#include "OutputPipeUdp.hpp"

OutputPipeUdp::OutputPipeUdp(std::string arg_ipAddress, uint16_t arg_port)
{
  // 
  // define endpoint.
  //
  _endpoint.sin_family = AF_INET;
  _endpoint.sin_port = htons(arg_port);
  inet_aton(arg_ipAddress.c_str(), &this->_endpoint.sin_addr);

  // 
  // open socket.
  //
  _socketFd = socket(AF_INET, SOCK_DGRAM, 0);
}

OutputPipeUdp::~OutputPipeUdp()
{
  // close.
  close(_socketFd);
}

ErrorCode OutputPipeUdp::PutMessage(char* arg_msgBytes, int32_t arg_msgLen)
{
  // 
  // send to.
  //
  
  // 
  // get array + tracker variables.
  //

  int32_t totalNumBytesSent = 0;
  int32_t totalNumBytesToSend = arg_msgLen;
  int32_t tmpNumBytesToSend = 0;

  while (totalNumBytesSent < totalNumBytesToSend)
  {
    // 
    // determine num bytes to send.
    //

    //
    // start by assigning max possible payload.
    // 
    tmpNumBytesToSend = MAX_UDP_BYTE_PAYLOAD;

    // if that value is larger than necessary:
    if (tmpNumBytesToSend > (totalNumBytesToSend - totalNumBytesSent))
    {
      // demote it.
      tmpNumBytesToSend = totalNumBytesToSend - totalNumBytesSent;
    }

    //
    // send.
    //
    int32_t numBytesSent = sendto(
      _socketFd                    , // socket file descriptor.
      arg_msgBytes + totalNumBytesSent , // buffer; data. advance pointer.
      tmpNumBytesToSend           , // buffer; len.
      0                           , // flags.
      (struct sockaddr*)(&this->_endpoint), // to-endpoint.
      sizeof(this->_endpoint));   // size of 'struct sockaddr'.

    if (numBytesSent < 0) { return ErrorCode::SocketError; }

    totalNumBytesSent += numBytesSent;
  }

  return ErrorCode::Ok;
}
