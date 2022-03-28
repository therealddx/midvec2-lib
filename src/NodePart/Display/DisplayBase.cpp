/*
 * reference LICENSE file provided.
 * 
 * DisplayBase.cpp.
 *
 */

#include <string.h>
#include <Types/Complex.hpp>
#include "DisplayBase.hpp"

template <class T_in>
void DisplayBase<T_in>::UpdateMarshal(char* arg_data)
{
  T_in marshal_arg = *(reinterpret_cast<T_in*>(arg_data));
  Update(marshal_arg);
}

template class DisplayBase<double>;
template class DisplayBase<Complex<double>>;

