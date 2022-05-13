/**
 * reference LICENSE file provided.
 * 
 * @file ProcessorDc.cpp
 * Implements ProcessorDc.hpp
 * 
 */

#include <Types/Complex.hpp>
#include "ProcessorDc.hpp"

template <class T_in, class T_out>
ProcessorDc<T_in, T_out>::ProcessorDc(T_in arg_dc)
: _dc(arg_dc)
{
}

template <class T_in, class T_out>
T_out ProcessorDc<T_in, T_out>::Process(T_in arg_xn)
{
  // add dc bias.
  return arg_xn + _dc;
}

template class ProcessorDc<double, double>;
template class ProcessorDc<Complex<double>, Complex<double>>;

