/*
 * reference LICENSE file provided.
 * 
 * GeneratorBase.cpp.
 * 
 */

#include <string.h>
#include <Types/Complex.hpp>
#include "GeneratorBase.hpp"

template <class T_out>
void GeneratorBase<T_out>::NextMarshal(char* rtn_data)
{
  T_out nextValue = Next();
  rtn_data = reinterpret_cast<char*>(new T_out(nextValue));
}

template class GeneratorBase<double>;
template class GeneratorBase<Complex<double>>;

