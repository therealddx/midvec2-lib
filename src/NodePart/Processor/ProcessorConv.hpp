/*
 * reference LICENSE file provided.
 *
 * ProcessorConv.hpp.
 * Implements ProcessorBase for convolving an input signal with an
 * impulse response.
 *
 */

#ifndef PROCESSORCONV_HPP
#define PROCESSORCONV_HPP

#include <stdint.h>
#include <vector>
#include <deque>
#include "ProcessorBase.hpp"

template <class T_in, class T_out>
class ProcessorConv : public ProcessorBase<T_in, T_out>
{
public:

  // 
  // Ctor.
  //
  ProcessorConv(std::vector<T_in>);

  // 
  // Dtor.
  //
  ~ProcessorConv() { };

  // 
  // Process.
  //
  T_out Process(T_in);

private:
  
  // members: data.
  std::vector<T_in> _hn; // impulse response for convolution operation.
  std::deque<T_in> _xn; // cached values from the input signal.

};

#endif // PROCESSORCONV_HPP

