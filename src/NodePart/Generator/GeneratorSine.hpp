/*
 * reference LICENSE file provided.
 *
 * GeneratorSine.hpp.
 * Concrete class for generating sine function.
 *
 * Appropriates function: std::sin.
 * std::sin( float )
 * std::sin( double )
 * std::sin( long double )
 * std::sin( IntegralType arg )
 */

#ifndef GENERATORSINE_HPP
#define GENERATORSINE_HPP

#include <stdint.h>
#include <cmath>
#include "GeneratorBase.hpp"

template <class T_out>
class GeneratorSine : public GeneratorBase<T_out>
{
public:

  // 
  // Ctor.
  //
  GeneratorSine<T_out>
    ( double arg_xShift
    , double arg_xScale
    , double arg_yShift
    , double arg_yScale
    , int32_t arg_samplesPerPeriod
    );

  // 
  // Dtor.
  //
  ~GeneratorSine<T_out>() { } ;

  // 
  // Next.
  //
  T_out Next();

private:

  // members: data.
  double _xShift; // p
  double _xScale; // h
  double _yShift; // v
  double _yScale; // a
  int32_t _samplesPerPeriod; // T
  int32_t _xIndex;

  // 
  // sine function == v + a*sin( (x-p) * h )
  // p == phase shift.
  // s == scalar
  // a == amplitude
  // v == vertical shift.
  // 'x', it is given, has a domain of [0, 2pi).
  //   x then increments by 2pi * (1/T) for each sample.
  //

};

#endif // GENERATORSINE_HPP

