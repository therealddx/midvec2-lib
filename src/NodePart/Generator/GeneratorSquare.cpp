/**
 * reference LICENSE file provided.
 *
 * @file GeneratorSquare.cpp
 * Implements GeneratorSquare.hpp
 *
 */

#include <iostream>
#include <Types/Complex.hpp>
#include "GeneratorSquare.hpp"

template <class T_out>
GeneratorSquare<T_out>::GeneratorSquare
  ( double arg_xShift
  , double arg_xScale
  , double arg_yShift
  , double arg_yScale 
  , int32_t arg_samplesPerPeriod
  , int32_t arg_numSamplesDuty)
: _xShift(arg_xShift)
, _xScale(arg_xScale)
, _yShift(arg_yShift)
, _yScale(arg_yScale)
, _samplesPerPeriod(arg_samplesPerPeriod)
, _numSamplesDuty(arg_numSamplesDuty)
, _xIndex(0)
{
  _dutyCycle = static_cast<double>(_numSamplesDuty) / 
    static_cast<double>(_samplesPerPeriod);
}

template <class T_out>
T_out GeneratorSquare<T_out>::Next()
{
  double xValue = 2 * M_PI * 
    (static_cast<double>(_xIndex) / static_cast<double>(_samplesPerPeriod));
  
  _xIndex = (_xIndex + 1) % _samplesPerPeriod;
  
  double sineArg = (xValue - _xShift) * _xScale;

  if (sineArg >= 0 && sineArg < (_dutyCycle * 2.0 * M_PI))
  {
    return static_cast<T_out>(_yShift + _yScale); // square is 'ON'
  }
  else
  {
    return static_cast<T_out>(_yShift - _yScale); // square is 'OFF'
  }

}

template class GeneratorSquare<double>;
template class GeneratorSquare<Complex<double>>;

