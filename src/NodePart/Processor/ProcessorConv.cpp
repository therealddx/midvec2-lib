/*
 * reference LICENSE file provided.
 *
 * ProcessorConv.cpp
 * Implements ProcessorConv.hpp
 * 
 */

#include <Types/Complex.hpp>
#include "ProcessorConv.hpp"

template <class T_in, class T_out>
ProcessorConv<T_in, T_out>::ProcessorConv(std::vector<T_in> arg_hn)
{
  // setup the impulse response.
  _hn = std::vector<T_in>(arg_hn);

  // setup the x[n] cache.
  _xn = std::deque<T_in>(_hn.size());
  for (auto it_xn = _xn.begin(); it_xn != _xn.end(); ++it_xn)
    { *it_xn = 0; }
}

template <class T_in, class T_out>
T_out ProcessorConv<T_in, T_out>::Process(T_in arg_xn)
{
  // vars.
  T_out rtn_rn = 0;

  // update the xn-cache.
  // 
  _xn.push_back(arg_xn);
  _xn.pop_front();

  // calculate r[n].
  // 
  auto it_hn = _hn.crbegin(); // 'flip' the h[n] vector.
  auto it_xn = _xn.cbegin();
  while (it_hn != _hn.crend())
  {
    rtn_rn += static_cast<T_out>(*it_hn * *it_xn);
    ++it_hn;
    ++it_xn;
  }

  // ret.
  return rtn_rn;
}

template class ProcessorConv<double, double>;
template class ProcessorConv<Complex<double>, Complex<double>>;

