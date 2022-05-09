/**
 * reference LICENSE file provided.
 *
 * @file GeneratorSquare.hpp
 * Concrete class for generating square waves.
 *
 */

#ifndef GENERATORSQUARE_HPP
#define GENERATORSQUARE_HPP

#include <cmath>
#include "GeneratorBase.hpp"

/**
 * @class GeneratorSquare
 */
template <class T_out>
class GeneratorSquare : public GeneratorBase<T_out>
{
public:

  /**
   * GeneratorSquare
   *
   * Constructs a squarewave generator, given arguments.
   *
   * @param[in] arg_xShift Horizontal shift for squarewave.
   * @param[in] arg_xScale Horizontal scale for squarewave.
   * @param[in] arg_yShift Vertical shift for squarewave.
   * @param[in] arg_yScale Vertical scale for squarewave.
   * @param[in] arg_samplesPerPeriod Samples per period for squarewave.
   * @param[in] arg_numSamplesDuty Number of 'ON' samples per period.
   */
  GeneratorSquare
    ( double arg_xShift
    , double arg_xScale
    , double arg_yShift
    , double arg_yScale
    , int32_t arg_samplesPerPeriod
    , int32_t arg_numSamplesDuty
    );
 
  /**
   * ~GeneratorSquare
   */ 
  ~GeneratorSquare() { } ;

  /**
   * Next
   * Satisfies base class.
   */
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


