/**
 * reference LICENSE file provided.
 *
 * @file GeneratorSine.cpp
 * Implements GeneratorSine.hpp
 *
 */

#include <iostream>
#include <Types/Complex.hpp>
#include "GeneratorSine.hpp"

template <class T_out>
GeneratorSine<T_out>::GeneratorSine
  ( double arg_xShift
  , double arg_xScale
  , double arg_yShift
  , double arg_yScale 
  , int32_t arg_samplesPerPeriod)
: _xShift(arg_xShift)
, _xScale(arg_xScale)
, _yShift(arg_yShift)
, _yScale(arg_yScale)
, _samplesPerPeriod(arg_samplesPerPeriod)
, _xIndex(0)
{
}

template <class T_out>
T_out GeneratorSine<T_out>::Next()
{
  double xValue = 2 * M_PI * 
    (static_cast<double>(_xIndex) / static_cast<double>(_samplesPerPeriod));

  _xIndex = (_xIndex + 1) % _samplesPerPeriod;

  // std::cerr << "GeneratorSine::Next: " <<  xValue << std::endl;

  return static_cast<T_out>(
    _yShift + _yScale * std::sin( (xValue - _xShift) * _xScale ));
}

template class GeneratorSine<double>;
template class GeneratorSine<Complex<double>>;

