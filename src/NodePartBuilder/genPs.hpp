/*
 * reference LICENSE file provided.
 *
 * genPs.hpp.
 * Class declarations to implement a Builder pattern for subtypes of the
 * class GeneratorBase, as ParamSets ('Ps').
 *
 */

#ifndef GENPS_HPP
#define GENPS_HPP

#include <stdint.h>
#include <NodePart/Generator/GeneratorBase.hpp>

template <class T_out>
class genPs
{
public:
  virtual ~genPs() { } ;
  virtual GeneratorBase<T_out>* Make() = 0;
protected:
  genPs() { } ;
};

template <class T_out>
class genSinePs : public genPs<T_out>
{
public:

  genSinePs
    ( double arg_xShift
    , double arg_xScale
    , double arg_yShift
    , double arg_yScale
    , int32_t arg_samplesPerPeriod )
    : _xShift             ( arg_xShift )
    , _xScale             ( arg_xScale )
    , _yShift             ( arg_yShift )
    , _yScale             ( arg_yScale )
    , _samplesPerPeriod   ( arg_samplesPerPeriod )
  {
  }

  GeneratorBase<T_out>* Make();

private:
  double _xShift;
  double _xScale;
  double _yShift;
  double _yScale;
  int32_t _samplesPerPeriod;
};

template <class T_out>
class genSquarePs : public genPs<T_out>
{
public:

  genSquarePs
    ( double arg_xShift
    , double arg_xScale
    , double arg_yShift
    , double arg_yScale
    , int32_t arg_samplesPerPeriod
    , int32_t arg_numSamplesDuty )
    : _xShift           ( arg_xShift           )
    , _xScale           ( arg_xScale           )
    , _yShift           ( arg_yShift           )
    , _yScale           ( arg_yScale           )
    , _samplesPerPeriod ( arg_samplesPerPeriod )
    , _numSamplesDuty   ( arg_numSamplesDuty   )
    {
    }

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

