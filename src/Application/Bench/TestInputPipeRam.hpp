#ifndef TESTINPUTPIPERAM_HPP
#define TESTINPUTPIPERAM_HPP

#include "stdinclude.hpp"
#include "TestInputPipeGeneral.hpp"

template <class T_d>
ErrorCode writeRingBuffer(RingBuffer<char>*, uint32_t);

template <class T_d>
ErrorCode TestInputPipeRam(InputPipeRam*);

#include "TestInputPipeRam.tpp"

#endif // TESTINPUTPIPERAM_HPP

