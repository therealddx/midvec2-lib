#ifndef TESTINPUTPIPEUDP_HPP
#define TESTINPUTPIPEUDP_HPP

#include "stdinclude.hpp"
#include "TestInputPipeGeneral.hpp"

class InputPipeUdp;

static const uint32_t MAX_BYTES_UDP_DATAGRAM = 60000;

template<class T_d>
ErrorCode sendTestData(uint32_t, std::string, uint16_t, uint32_t);

template <class T_d>
ErrorCode TestInputPipeUdp(InputPipeUdp*);

#include "TestInputPipeUdp.tpp"

#endif // TESTINPUTPIPEUDP_HPP

