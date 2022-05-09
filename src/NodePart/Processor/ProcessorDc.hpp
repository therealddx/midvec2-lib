/**
 * reference LICENSE file provided.
 *
 * @file ProcessorDc.hpp
 * Implements ProcessorBase for adding a DC bias to an input signal.
 *
 */

#ifndef PROCESSORDC_HPP
#define PROCESSORDC_HPP

#include <stdint.h>
#include "ProcessorBase.hpp"

/**
 * @class ProcessorDc
 */
template <class T_in, class T_out>
class ProcessorDc : public ProcessorBase<T_in, T_out>
{
public:

  /**
   * ProcessorDc
   *
   * @param[in] arg_dc
   * DC offset that this Processor is to provide to its input signals.
   */
  ProcessorDc(T_in arg_dc);

  /**
   * ~ProcessorDc
   */
  ~ProcessorDc() { };

  /**
   * Process
   * Satisfies base class.
   */
  T_out Process(T_in);

private:

  // members: data.
  T_in _dc;

};

#endif // PROCESSORDC_HPP

