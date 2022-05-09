/**
 * reference LICENSE file provided.
 *
 * @file ProcessorBase.hpp
 * 
 * Represents the processing data of type 'T_in' into data of type 'T_out'.
 */

#ifndef PROCESSORBASE_HPP
#define PROCESSORBASE_HPP

#include <stdint.h>
#include <vector>

/**
 * @class ProcessorBase
 */
template <class T_in, class T_out>
class ProcessorBase
{
public:

  /**
   * ProcessorBase
   */
  ProcessorBase() { };

  /**
   * ~ProcessorBase
   */
  virtual ~ProcessorBase() { };

  /**
   * ProcessMarshal
   * Marshal the argument pointer into usable data;
   * Process it (using `Process`); and
   * Return a `new` pointer to the result.
   *
   * @param[in] arg_p_data
   * Pointer to data of type 'T_in' to process.
   *
   * @return Pointer to `new` data at outcome of processing.
   */
  virtual char* ProcessMarshal(char* arg_p_data);

  /**
   * Process
   *
   * Perform a processing operation on some data, as defined by the subclass.
   *
   * @param[in] arg
   * Instance of type 'T_in' to process.
   *
   * @return
   * Instance of type 'T_out', as result of processing.
   */
  virtual T_out Process(T_in arg) = 0;

};

#endif // PROCESSORBASE_HPP

