/*
 * reference LICENSE file provided.
 *
 * GeneratorBase.hpp.
 * Generic class for, in stateful fashion, presenting an interface to the
 * next value of any function.
 *
 */

#ifndef GENERATORBASE_HPP
#define GENERATORBASE_HPP

template <class T_out>
class GeneratorBase
{
public:

  // 
  // Ctor.
  //
  GeneratorBase<T_out>() { } ;

  // 
  // Dtor.
  //
  virtual ~GeneratorBase<T_out>() { } ;

  // 
  // Next.
  // Hand-off from generalized master.
  //
  virtual void NextMarshal(char* rtn_data);

  // 
  // Next.
  // State of sub-class will cause correct 'Next' value to be returned.
  //
  virtual T_out Next() = 0;

};

#endif // GENERATORBASE_HPP

