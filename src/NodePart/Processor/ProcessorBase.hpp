/**
 * reference LICENSE file provided.
 *
 * @file ProcessorBase.hpp
 * Declarations for ProcessorBase
 */

#ifndef PROCESSORBASE_HPP
#define PROCESSORBASE_HPP

#include <stdint.h>
#include <vector>

/**
 * @class ProcessorBase
 * Represents the processing data of type `T_in` into data of type `T_out`.
 */
template <class T_in, class T_out>
class ProcessorBase
{
public:

  /**
   * This class is pure-virtual--
   *   attempts to construct cause compile-time error.
   */
  ProcessorBase() { };

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~ProcessorBase() { };

  /**
   * Perform a processing operation on some data, as defined by the subclass.
   *
   * @param[in] arg
   * Instance of type `T_in` to process.
   *
   * @return
   * Instance of type `T_out`, as result of processing.
   */
  virtual T_out Process(T_in arg) = 0;

};

#endif // PROCESSORBASE_HPP

