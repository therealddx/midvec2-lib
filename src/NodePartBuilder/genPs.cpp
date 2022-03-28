/*
 * reference LICENSE file provided.
 * 
 * genPs.cpp.
 * Implements genPs.hpp.
 *
 */

#include <Types/Complex.hpp>
#include <NodePart/Generator/GeneratorBase.hpp>
#include <NodePart/Generator/GeneratorSine.hpp>
#include <NodePart/Generator/GeneratorSquare.hpp>
#include "genPs.hpp"

template <class T_out>
GeneratorBase<T_out>* genSinePs<T_out>::Make()
{ 
  return new GeneratorSine<T_out>
    ( _xShift
    , _xScale
    , _yShift
    , _yScale
    , _samplesPerPeriod
    );
}

template <class T_out>
GeneratorBase<T_out>* genSquarePs<T_out>::Make()
{
  return new GeneratorSquare<T_out>
    ( _xShift
    , _xScale
    , _yShift
    , _yScale
    , _samplesPerPeriod
    , _numSamplesDuty
    );
}

template class genPs<double>;
template class genPs<Complex<double>>;

template class genSinePs<double>;
template class genSinePs<Complex<double>>;

template class genSquarePs<double>;
template class genSquarePs<Complex<double>>;

