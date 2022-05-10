/**
 * reference LICENSE file provided.
 *
 * @file GeneratorSine.hpp
 * Concrete class for generating sine function.
 */

#ifndef GENERATORSINE_HPP
#define GENERATORSINE_HPP

#include <stdint.h>
#include <cmath>
#include "GeneratorBase.hpp"

/**
 * @class GeneratorSine
 */
template <class T_out>
class GeneratorSine : public GeneratorBase<T_out>
{
public:

  /**
   * GeneratorSine
   *
   * Constructs a sinewave generator, given arguments.
   *
   * @param[in] arg_xShift Horizontal shift for sinewave.
   * @param[in] arg_xScale Horizontal scale for sinewave.
   * @param[in] arg_yShift Vertical shift for sinewave.
   * @param[in] arg_yScale Vertical scale for sinewave.
   * @param[in] arg_samplesPerPeriod Samples per period for sinewave.
   */
  GeneratorSine
    ( double arg_xShift
    , double arg_xScale
    , double arg_yShift
    , double arg_yScale
    , int32_t arg_samplesPerPeriod
    );

  /**
   * ~GeneratorSine
   */
  ~GeneratorSine() { } ;

  /**
   * Next
   * Satisfies base class.
   */
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

