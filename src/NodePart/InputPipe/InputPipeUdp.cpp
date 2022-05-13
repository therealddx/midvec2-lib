/*
 * reference LICENSE file provided.
 *
 * @file InputPipeUdp.cpp
 * Implements InputPipeUdp.hpp
 *
 */

// include: app.
#include "InputPipeUdp.hpp"

InputPipeUdp::InputPipeUdp(std::string arg_ipv4_bind, uint16_t arg_port)
: _socketFd(0)
, _rxBufIndex(0)
, _rxBufValid(0)
{
  // set values.
  _endpoint.sin_family = AF_INET; // assign family.

  // assign IP addr.
  int32_t rtn_pton = inet_pton(AF_INET, arg_ipv4_bind.c_str(), &_endpoint.sin_addr);
  if (rtn_pton != 1)
  {
    return; // todo: throw an exception here.
  }

  _endpoint.sin_port = htons(arg_port); // assign port.
  _clientAddrLen = sizeof(_clientAddr);

  // 
  // make and bind socket.
  //  
  this->_socketFd = socket(AF_INET, SOCK_DGRAM, 0); 
  if (this->_socketFd < 0)
  {
    return; // todo: throw an exception here.
  }

  int32_t successBind = bind
    ( _socketFd
    , (const struct sockaddr*)(&_endpoint)
    , sizeof(_endpoint)
    );  
  if (successBind < 0)
  {
    return; // todo: throw an exception here.
  }

  // 
  // note the construction args.
  // 
  _ipv4 = arg_ipv4_bind;
  _port = arg_port;
}

InputPipeUdp::~InputPipeUdp()
{
  // destroy.
  close(_socketFd);
}

std::string InputPipeUdp::GetBindEndpoint() const
{
  std::stringstream rtn_s;
  rtn_s << _ipv4 << ":" << _port;
  return rtn_s.str();
}

ErrorCode InputPipeUdp::GetByte(char* rtn_byte)
{
  // arg check.
  if (rtn_byte == 0) { return ErrorCode::NullPointer; }

  // get a byte from the file buffer.
  if (_rxBufIndex < _rxBufValid)
  {
    *rtn_byte = _rxBuffer[_rxBufIndex];
    _rxBufIndex++;
    return ErrorCode::Ok;
  }
  else
  {
    // update the file buffer.
    memset(_rxBuffer, 0,  MAX_RXBUFFER_SIZE);

    _rxBufValid = recvfrom
      ( _socketFd
      , &_rxBuffer[0]
      , MAX_RXBUFFER_SIZE
      , MSG_DONTWAIT
      , &_clientAddr
      , &_clientAddrLen
      );

    _rxBufIndex = 0;

    // get a byte from the file buffer.
    if (_rxBufIndex < _rxBufValid)
    {
      *rtn_byte = _rxBuffer[_rxBufIndex];
      _rxBufIndex++;
      return ErrorCode::Ok;
    }
    else
    {
      *rtn_byte = 0;
      return ErrorCode::EofReached;
    }
  }
}

