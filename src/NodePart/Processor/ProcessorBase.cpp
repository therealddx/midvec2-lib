/*
 * reference LICENSE file provided.
 * 
 * ProcessorBase.cpp
 * Implements ProcessorBase.hpp
 *
 */

#include <Types/Complex.hpp>
#include "ProcessorBase.hpp"

template <class T_in, class T_out>
char* ProcessorBase<T_in, T_out>::ProcessMarshal(char* arg_inChar)
{
  // 'char*' => 'T_in'.
  T_in arg_in = *( reinterpret_cast<T_in*>(arg_inChar) );

  // Process (defer to child class).
  T_out rtn_out = Process(arg_in);

  // 'T_out' => 'char*'.
  char* rtn_outChar = reinterpret_cast<char*>(new T_out(rtn_out));

  // ret.
  return rtn_outChar;
}

template class ProcessorBase<double, double>;
template class ProcessorBase<Complex<double>, Complex<double>>;

