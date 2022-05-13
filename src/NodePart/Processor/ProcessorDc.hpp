/**
 * reference LICENSE file provided.
 *
 * @file ProcessorDc.hpp
 * Declarations for ProcessorDc
 *
 */

#ifndef PROCESSORDC_HPP
#define PROCESSORDC_HPP

#include <stdint.h>
#include "ProcessorBase.hpp"

/**
 * @class ProcessorDc
 * Implements ProcessorBase for adding a DC bias to an input signal.
 */
template <class T_in, class T_out>
class ProcessorDc : public ProcessorBase<T_in, T_out>
{
public:

  /**
   * Constructs a DC bias processor.
   *
   * @param[in] arg_dc
   * DC offset that this processor is to provide to its input signals.
   */
  ProcessorDc(T_in arg_dc);

  /**
   * Destroys this instance.
   */
  ~ProcessorDc() { };

  /**
   * Satisfies base class.
   */
  T_out Process(T_in);

private:

  // members: data.
  T_in _dc;

};

#endif // PROCESSORDC_HPP

