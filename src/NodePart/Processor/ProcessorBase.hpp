/*
 * reference LICENSE file provided.
 *
 * ProcessorBase.hpp.
 * 
 * Generic class that represents 'processing' data of type 'T_in' into
 * data of type 'T_out'.
 *
 */

#ifndef PROCESSORBASE_HPP
#define PROCESSORBASE_HPP

#include <stdint.h>
#include <vector>

template <class T_in, class T_out>
class ProcessorBase
{
public:

  // 
  // Ctor.
  //
  ProcessorBase() { };

  // 
  // Dtor.
  //
  virtual ~ProcessorBase() { };

  // 
  // ProcessMarshal.
  // Hand-off from master class.
  //
  virtual char* ProcessMarshal(char*);

  // 
  // Process.
  // Chew data of type 'T_in', and process it out as type 'T_out'.
  //
  virtual T_out Process(T_in) = 0;

};

#endif // PROCESSORBASE_HPP

