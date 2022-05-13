/**
 * reference LICENSE file provided.
 *
 * @file genPs.hpp
 * Declarations for genPs
 *
 */

#ifndef GENPS_HPP
#define GENPS_HPP

#include <stdint.h>
#include <NodePart/Generator/GeneratorBase.hpp>

/**
 * @class genPs
 * Represents the set of parameters-- 'parameter set', or 'ps'--
 *   that construct subclasses of GeneratorBase.
 */
template <class T_out>
class genPs
{
public:

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~genPs() { } ;

  /**
   * Subclasses are guaranteed to construct a subclass of GeneratorBase.
   * @return Instance of GeneratorBase.
   */
  virtual GeneratorBase<T_out>* Make() = 0;

protected:
  genPs() { } ;
};

/**
 * @class genSinePs
 * Class representing the parameters for constructing a GeneratorSine.
 */
template <class T_out>
class genSinePs : public genPs<T_out>
{
public:

  /**
   * Stores GeneratorSine constructor arguments, for construction by `Make`.
   *
   * @param[in] a_xsh Horizontal shift for sinewave.
   * @param[in] a_xsc Horizontal scale for sinewave.
   * @param[in] a_ysh Vertical shift for sinewave.
   * @param[in] a_ysc Vertical scale for sinewave.
   * @param[in] a_sp Samples per period for sinewave.
   */
  genSinePs(double a_xsh, double a_xsc, double a_ysh, double a_ysc, int32_t a_sp)
    : _xShift             ( a_xsh )
    , _xScale             ( a_xsc )
    , _yShift             ( a_ysh )
    , _yScale             ( a_ysc )
    , _samplesPerPeriod   ( a_sp )
  {
  }

  /**
   * Satisfies base class.
   */
  GeneratorBase<T_out>* Make();

private:
  double _xShift;
  double _xScale;
  double _yShift;
  double _yScale;
  int32_t _samplesPerPeriod;
};

/**
 * @class genSquarePs
 * Class representing the parameters for constructing a GeneratorSquare.
 */
template <class T_out>
class genSquarePs : public genPs<T_out>
{
public:

  /**
   * Stores GeneratorSquare constructor arguments, for construction by `Make`.
   *
   * @param[in] a_xh Horizontal shift for squarewave.
   * @param[in] a_xc Horizontal scale for squarewave.
   * @param[in] a_yh Vertical shift for squarewave.
   * @param[in] a_yc Vertical scale for squarewave.
   * @param[in] a_sp Samples per period for squarewave.
   * @param[in] a_n Number of 'on' samples per period.
   */
  genSquarePs(double a_xh, double a_xc, double a_yh, double a_yc, int32_t a_sp, int32_t a_n)
    : _xShift           ( a_xh )
    , _xScale           ( a_xc )
    , _yShift           ( a_yh )
    , _yScale           ( a_yc )
    , _samplesPerPeriod ( a_sp )
    , _numSamplesDuty   ( a_n  )
    {
    }

  /**
   * Satisfies base class.
   */
  GeneratorBase<T_out>* Make();

private:
  double _xShift;
  double _xScale;
  double _yShift;
  double _yScale;
  int32_t _samplesPerPeriod;
  int32_t _numSamplesDuty;
};

#endif // GENPS_HPP

