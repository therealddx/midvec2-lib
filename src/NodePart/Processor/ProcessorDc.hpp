/*
 * reference LICENSE file provided.
 *
 * ProcessorDc.hpp.
 * Implements ProcessorBase for adding a DC bias to an input signal.
 *
 */

#ifndef PROCESSORDC_HPP
#define PROCESSORDC_HPP

#include <stdint.h>
#include "ProcessorBase.hpp"

template <class T_in, class T_out>
class ProcessorDc : public ProcessorBase<T_in, T_out>
{
public:

  // 
  // Ctor.
  //
  ProcessorDc(T_in arg_dc);

  // 
  // Dtor.
  //
  ~ProcessorDc() { };

  // 
  // Process.
  //
  T_out Process(T_in);

private:

  // members: data.
  T_in _dc;

};

#endif // PROCESSORDC_HPP

