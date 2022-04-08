/*
 * reference LICENSE file provided.
 *
 * GeneratorSquare.hpp.
 * Concrete class for generating square wave.
 *
 */

#ifndef GENERATORSQUARE_HPP
#define GENERATORSQUARE_HPP

#include <cmath>
#include "GeneratorBase.hpp"

template <class T_out>
class GeneratorSquare : public GeneratorBase<T_out>
{
public:

  // 
  // Ctor.
  //
  GeneratorSquare
    ( double arg_xShift
    , double arg_xScale
    , double arg_yShift
    , double arg_yScale
    , int32_t arg_samplesPerPeriod
    , int32_t arg_numSamplesDuty
    );
  
  // 
  // Dtor.
  //
  ~GeneratorSquare() { } ;

  // 
  // Next.
  //
  T_out Next();

private:
  
  // members: data.
  double _xShift;
  double _xScale;
  double _yShift;
  double _yScale;
  int32_t _samplesPerPeriod;
  int32_t _numSamplesDuty;

  int32_t _xIndex;
  double _dutyCycle;

};

#endif // GENERATORSQUARE_HPP


