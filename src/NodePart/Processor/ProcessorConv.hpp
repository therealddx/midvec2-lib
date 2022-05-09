/**
 * reference LICENSE file provided.
 *
 * @file ProcessorConv.hpp
 * Implements ProcessorBase to convolve an input signal with an impulse response.
 *
 */

#ifndef PROCESSORCONV_HPP
#define PROCESSORCONV_HPP

#include <stdint.h>
#include <vector>
#include <deque>
#include "ProcessorBase.hpp"

/**
 * @class ProcessorConv
 */
template <class T_in, class T_out>
class ProcessorConv : public ProcessorBase<T_in, T_out>
{
public:

  /**
   * ProcessorConv
   *
   * @param[in] arg_hn
   * Impulse response of input signal.
   */
  ProcessorConv(std::vector<T_in> arg_hn);

  /**
   * ~ProcessorConv
   * No concrete resources to destroy.
   */
  ~ProcessorConv() { };

  /**
   * Process
   * Satisfies base class.
   */
  T_out Process(T_in);

private:
  
  // members: data.
  std::vector<T_in> _hn; // impulse response for convolution operation.
  std::deque<T_in> _xn; // cached values from the input signal.

};

#endif // PROCESSORCONV_HPP

